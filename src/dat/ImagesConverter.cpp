/*
 * ImagesConverter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "ImagesConverter.h"
#include "Logger.h"
#include "Preferences.h"
#include "Storage.h"
#include "luagen.h"
#include "FileUtil.h"
#include "Image.h"
#include "StringUtil.h"
#include "Grp.h"

// system
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.ImagesConverter");

ImagesConverter::ImagesConverter(std::shared_ptr<Hurricane> hurricane, DataHub &datahub) :
    Converter(hurricane),
    mDatahub(datahub)
{

}

ImagesConverter::~ImagesConverter()
{

}

bool ImagesConverter::convert(std::map<std::string, std::shared_ptr<Palette>> &paletteMap,
                              std::map<std::string, std::shared_ptr<Palette2D>> palette2DMap)
{
  bool result = true;

  Preferences &preferences = Preferences::getInstance();

  Storage graphics;
  graphics.setDataPath(preferences.getDestDir());
  graphics.setDataType("graphics");

  Storage luagen;
  luagen.setDataPath(preferences.getDestDir());
  luagen.setDataType("luagen/images");
  CheckPath(luagen.getFullPath());

  ofstream lua_include;
  lua_include.open (luagen("luagen-images.lua").getFullPath());
  string lua_include_str;

  for (unsigned int i = 0; i < mDatahub.images->draw_function()->size(); i++)
  {
    Image image(mDatahub, i);

    string grp_name(image.grp()->name1);
    grp_name = to_lower(grp_name); // make lower case to match it always

    // find first slash
    size_t found = grp_name.find('\\');
    string imageType;
    if(found != string::npos)
    {
      imageType = grp_name.substr (0, found);
      LOG4CXX_TRACE(logger, "imageType: " + imageType);
    }

    // find second slash
    size_t found2 = grp_name.find('\\', found+1);
    string imageSubType;
    if(found2 != string::npos)
    {
      imageSubType = grp_name.substr (found+1, found2 - found-1);
      LOG4CXX_TRACE(logger, "imageSubType: " + imageSubType);
    }

    // find third slash
    size_t found3 = grp_name.find('\\', found2+1);
    string imageSubSubType;
    if(found3 != string::npos)
    {
      imageSubSubType = grp_name.substr (found2+1, found3 - found2-1);
      LOG4CXX_TRACE(logger, "imageSubSubType: " + imageSubSubType);
    }

    string grp_arcfile =  "unit\\" + grp_name;

    Grp grp(mHurricane, grp_arcfile);
    std::shared_ptr<Palette> pal;
    std::shared_ptr<Palette2D> pal2D;
    string remapping;

    bool save_grp = true;

    // TODO: map this constants in Kaitai parser
    if (image.draw_function() == 9) // uses remapping
    {
      if(image.remapping() == 1) // ofire
      {
        remapping = "ofire";
      }
      else if(image.remapping() == 2) // gfire
      {
        remapping = "gfire";
      }
      else if(image.remapping() == 3) // bfire
      {
        remapping = "bfire";
      }
      else if(image.remapping() == 4) // bexpl
      {
        remapping = "bexpl";
      }
      else // as default use ofire until I've a better idea....
      {
        remapping = "ofire";
      }

      pal2D = palette2DMap.at(remapping);
      grp.setPalette2D(pal2D);

      grp.setRGBA(true);
    }
    else if (image.draw_function() == 10) // shadow
    {
      // do not export shadows images as the stratagus engine has a better way to generate them
      save_grp = false;
    }
    else // all other drawing functions until I identify a special case
    {
      string tileset;

      if(imageType == "thingy" && imageSubType == "tileset" && !imageSubSubType.empty())
      {
        tileset = imageSubSubType;
        pal = paletteMap.at(tileset);
      }
      else // in all other cases use the "tunit" palette
      {
        pal = paletteMap.at("tunit");
      }
    }

    // FIXME: some blacklisting until I know why it crash!
    if(grp_name == "thingy\\blackx.grp")
    {
      save_grp = false;
    }
    // FIXME: some hard coded defaults to assign other palettes
    // make this configurable or find out if this is in the data
    else if(grp_name == "terran\\tank.grp")
    {
      // TODO: player color isn't available. But no problem visible for now.
      // maybe need to add cunit palette before into tileset palette?
      pal = paletteMap.at("badlands");
    }
    else if(grp_name == "neutral\\cbattle.grp")
    {
      // TODO: player color isn't available. See how to fix this (or if this is needed for neutral)
      pal = paletteMap.at("badlands");
    }
    else if(grp_name == "neutral\\ion.grp")
    {
      pal = paletteMap.at("platform");
    }
    else if(grp_name == "neutral\\khyad01.grp")
    {
      pal = paletteMap.at("jungle");
    }
    else if(grp_name == "neutral\\temple.grp")
    {
      pal = paletteMap.at("jungle");
    }
    else if(grp_name == "neutral\\geyser.grp")
    {
      /* FIXME: only the first frame is correct, but this looks ok as we use only this one in animation
      frame 0 = "badlands.wpe" (default frame for all other tilesets)
      frame 1 = "platform.wpe"
      frame 2 = "install.wpe"
      frame 3 = "ashworld.wpe"
      */
      pal = paletteMap.at("badlands");
    }

    grp.setPalette(pal);

    if(save_grp)
    {
      string grp_storage_file(grp_arcfile);
      replaceString("\\", "/", grp_storage_file);

      // cut the file ending and lower case it
      string grp_storage_file_base = to_lower(cutFileEnding(grp_storage_file, ".grp"));

      // if a remapping function is used for that Grp than save with specific name
      if(!remapping.empty())
      {
        grp_storage_file_base += "_" + remapping;
      }

      Storage png_file = graphics(grp_storage_file_base + ".png");

      result = grp.save(png_file);

      string image_id = image.createID();
      string image_lua = image_id + ".lua";

      Storage lua_file_store(luagen(image_lua));

      // only generate LUA file with the image properties in case it could be saved successful
      if(result)
      {
        ofstream lua_file;
        lua_file.open (lua_file_store.getFullPath());

        Size tilesize = grp.getTileSize();

        int NumDirections = 1;
        if(image.gfx_turns() == true)
        {
          // it seems all animations which are calculated by gfx_turns have 32 directions
          NumDirections = 32;
        }

        string unit_image_file(lg::assign(image_id + "_file", lg::quote(png_file.getRelativePath())));
        lua_file << unit_image_file << endl;

        string unit_image_size(lg::assign(image_id + "_size", lg::sizeTable(tilesize)));
        lua_file << unit_image_size << endl;

        string unit_image_NumDirections(lg::assign(image_id + "_NumDirections", to_string(NumDirections)));
        lua_file << unit_image_NumDirections << endl;

        string unit_image_table(
            lg::table({lg::quote("file"), image_id + "_file",
            lg::quote("size") , image_id + "_size"}));
        string unit_image = lg::assign(image_id, unit_image_table);
        lua_file << unit_image << endl;

        string unit_image_table_var(
            lg::table({lg::assign("File", image_id + "_file"),
            lg::assign("Size" , image_id + "_size")}));
        string unit_image_var = lg::assign(image_id + "_var", unit_image_table_var);
        lua_file << unit_image_var << endl;

        lua_file.close();

        string grp_save_trace(to_string(i) +  ": " + grp_name + " : " + grp_arcfile + " => " + grp_storage_file_base);
        LOG4CXX_TRACE(logger, grp_save_trace);
      }
      // write the Load call even if Grp not present to preserve the SC base files
      lua_include_str += lg::line(lg::function("Load", lg::quote(lua_file_store.getRelativePath())));
    }
  }

  lua_include << lua_include_str;
  lua_include.close();

  return result;
}

} /* namespace dat */
