/*
 * UnitsExporter.cpp
 *
 *      Author: Andreas
 */

// project
#include "UnitsConverter.h"
#include "Preferences.h"
#include "FileUtil.h"
#include "Logger.h"
#include "Unit.h"
#include "StringUtil.h"
#include "Grp.h"
#include "luagen.h"
#include "DataHub.h"

// system
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <nlohmann/json.hpp>

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.UnitsConverter");

UnitsConverter::UnitsConverter(std::shared_ptr<Hurricane> hurricane, DataHub &datahub) :
  Converter(hurricane),
  mDatahub(datahub)
{

}

UnitsConverter::~UnitsConverter()
{

}

bool UnitsConverter::convert(json &unitsJson,
                                std::map<std::string, std::shared_ptr<Palette>> &paletteMap,
                                std::map<std::string, std::shared_ptr<Palette2D>> palette2DMap)
{
  bool result = true;

  Preferences &preferences = Preferences::getInstance();

  Storage graphics;
  graphics.setDataPath(preferences.getDestDir());
  graphics.setDataType("graphics");

  Storage luagen;
  luagen.setDataPath(preferences.getDestDir());
  luagen.setDataType("luagen/units");
  CheckPath(luagen.getFullPath());

  ofstream lua_include;
  lua_include.open (luagen("luagen-units.lua").getFullPath());
  string lua_include_str;

  // this cache ensure not to extract GRP several times the same
  //vector<string> grp_name_cache;

  // units.dat
  for(auto &array : unitsJson)
  {
    string unit_name = array.at("name");
    int unit_id = array.at("id");
    bool extractor = true;
    bool save_result = true;

    LOG4CXX_TRACE(logger, string("Unit(") + to_string(unit_id) + ")");
    dat::Unit unit(mDatahub, unit_id);

    try
    {
      extractor = array.at("extractor");
    }
    catch (const nlohmann::detail::out_of_range &json_range)
    {
      extractor = true; // default behaviour TODO: maybe better write into JSON file and skip default
    }

    if(extractor)
    {
      uint8_t draw_function = unit.flingy().sprite().image().draw_function();
      uint8_t remapping_function = unit.flingy().sprite().image().remapping();

      string grp_arcfile =  "unit\\" + unit.flingy().sprite().image().grp().name1;

      string grp_storage_file(grp_arcfile);
      replaceString("\\", "/", grp_storage_file);

      // cut the file ending and lower case it
      string grp_storage_file_base = to_lower(cutFileEnding(grp_storage_file, ".grp"));

      cout << unit_name << " : " << grp_arcfile << " => " << grp_storage_file_base;

      Grp grp(mHurricane, grp_arcfile);
      std::shared_ptr<Palette> pal;
      std::shared_ptr<Palette2D> pal2D;

      if(draw_function == 9) // remapping
      {
        if(remapping_function == 1) // ofire
        {
          pal2D = palette2DMap.at("ofire");
          grp.setPalette2D(pal2D);
        }
        else if(remapping_function == 2) // gfire
        {
          pal2D = palette2DMap.at("gfire");
          grp.setPalette2D(pal2D);
        }
        else if(remapping_function == 3) // bfire
        {
          pal2D = palette2DMap.at("bfire");
          grp.setPalette2D(pal2D);
        }
        else if(remapping_function == 4) // bexpl
        {
          pal2D = palette2DMap.at("bexpl");
          grp.setPalette2D(pal2D);
        }
        else // TODO: as default use ofire until I've a better idea....
        {
          pal2D = palette2DMap.at("ofire");
          grp.setPalette2D(pal2D);
        }

        grp.setRGBA(true);
      }
      else // default
      {
        pal = paletteMap.begin()->second;
        grp.setPalette(pal);
      }

      // for the LUA reference it's enough to use the idle name as we save only one LUA for idle+talking
      string unit_portraits;
      try
      {
        string portrait_name = unit.portrait().tbl_idle().name1;
        string portrait_id = Portrait::PathToID(portrait_name);
        string portrait_lua = "portrait_" + portrait_id;
        unit_portraits = lg::assign("Portrait", portrait_lua);
      }
      catch (NoPortraitException &nex)
      {
        cout << nex.what() << endl;

        // FIXME: just use the tadvisor as some fallback for now
        unit_portraits = lg::assign("Portrait", "portrait_tadvisor");
      }

      // TODO: possible optimization possible as some units point toward the same grp
      // could be checked before if the png is yet extracted in the same run
      // idea: some list in memory to check which things (graphics, weapons, orders,...)
      // referenced by units are yet exported. Then also the LUA files have not to be overwritten several times
      Storage png_file = graphics(grp_storage_file_base + ".png");
      save_result = grp.save(png_file);

      Storage lua_file_store(luagen(unit_name + ".lua"));
      ofstream lua_file;
      lua_file.open (lua_file_store.getFullPath());

      Size tilesize = grp.getTileSize();

      string unit_image(lg::assign(
          "Image",
          lg::table({lg::quote("file"), lg::quote(png_file.getRelativePath()), lg::quote("size") , lg::sizeTable(tilesize)}))
          );

      string unit_hitpoints = lg::assign("HitPoints", to_string(unit.hitpoints()));
      string unit_name_translated = lg::assign("Name", lg::quote(unit.name().name1));

      units_dat_t::unit_dimension_type_t *unit_dimension_tilesize = unit.unit_dimension();

      int unit_width = unit_dimension_tilesize->left() + unit_dimension_tilesize->right();
      int unit_height = unit_dimension_tilesize->up() + unit_dimension_tilesize->down();

      int tilesize_pixel = 32;

      int unit_tilesize_width = ceil(unit_width / (double) tilesize_pixel);
      int unit_tilesize_height = ceil(unit_height / (double) tilesize_pixel);

      int unit_boxsize_width = unit_tilesize_width * tilesize_pixel;
      int unit_boxsize_height = unit_tilesize_height * tilesize_pixel;

      string unit_LuaTileSize = lg::assign("TileSize", lg::table({to_string(unit_tilesize_width), to_string(unit_tilesize_height)}));
      string unit_LuaBoxSize = lg::assign("BoxSize", lg::table({to_string(unit_boxsize_width), to_string(unit_boxsize_height)}));

      int unit_sight_range = unit.sight_range();
      string unit_computer_reaction_rangeStr ("math.ceil(" + to_string(unit_sight_range) + " * ComputerReactionRangeFactor)");
      string unit_person_reaction_rangeStr ("math.floor(" + to_string(unit_sight_range) + " * PersonReactionRangeFactor)");

      string unit_LuaSightRange = lg::assign("SightRange", to_string(unit_sight_range));
      string unit_LuaComputerReactionRange = lg::assign("ComputerReactionRange", unit_computer_reaction_rangeStr);
      string unit_LuaPersonReactionRange = lg::assign("PersonReactionRange", unit_person_reaction_rangeStr);

      // generate some standard shadow
      Pos shadow_position = Pos(-7, -7);

      // some basic flyer shadow support => to be improved
      if(unit.elevation_level() >= 16)
      {
        shadow_position = Pos(15, 15);
      }

      string unit_shadow = lg::assign("Shadow", lg::table({lg::quote("offset"), lg::posTable(shadow_position), lg::quote("scale"), "1"}));

      // generate a dummy animation as fallback to not crash
      string unit_animations = lg::assign("Animations", lg::quote("animations-dummy-still"));

      // generate a dummy icon as fallback to not crash
      string unit_icon = lg::assign("Icon", lg::quote("icon-terran-command-center"));

      string unit_defintion = lg::DefineUnitType(unit_name,
                                                {unit_name_translated, unit_image, unit_shadow, unit_icon, unit_animations,
                                                 unit_portraits, unit_hitpoints, unit_LuaTileSize, unit_LuaBoxSize,
                                                 unit_LuaSightRange, unit_LuaComputerReactionRange, unit_LuaPersonReactionRange});

      lua_include_str += lg::line(lg::function("Load", lg::quote(lua_file_store.getRelativePath())));

      //cout << unit_defintion << endl;

      lua_file << unit_defintion;
      lua_file.close();
    }

    printf("...%s\n", save_result ? "ok" : "nok");
  }

  lua_include << lua_include_str;
  lua_include.close();

  return result;
}

void convertGrp(const std::string &arcfile, Storage storage)
{

}

} /* namespace dat */
