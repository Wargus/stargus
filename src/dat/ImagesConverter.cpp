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

    string grp_name(image.grp().name1);
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

    bool save_grp = true;

    // TODO: map this constants in Kaitai parser
    if (image.draw_function() == 9) // uses remapping
    {
      if(image.remapping() == 1) // ofire
      {
        pal2D = palette2DMap.at("ofire");
        grp.setPalette2D(pal2D);
      }
      else if(image.remapping() == 2) // gfire
      {
        pal2D = palette2DMap.at("gfire");
        grp.setPalette2D(pal2D);
      }
      else if(image.remapping() == 3) // bfire
      {
        pal2D = palette2DMap.at("bfire");
        grp.setPalette2D(pal2D);
      }
      else if(image.remapping() == 4) // bexpl
      {
        pal2D = palette2DMap.at("bexpl");
        grp.setPalette2D(pal2D);
      }
      else // as default use ofire until I've a better idea....
      {
        pal2D = palette2DMap.at("ofire");
        grp.setPalette2D(pal2D);
      }

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

      string image_id = Image::createID(grp_storage_file);
      string image_lua = "image_" + image_id + ".lua";

      Storage png_file = graphics(grp_storage_file_base + ".png");

      Storage lua_file_store(luagen(image_lua));
      ofstream lua_file;
      lua_file.open (lua_file_store.getFullPath());

      result = grp.save(png_file);

      Size tilesize = grp.getTileSize();

      string unit_image(
          lg::table({lg::quote("file"), lg::quote(png_file.getRelativePath()), lg::quote("size") , lg::sizeTable(tilesize)})
          );

      string image_table = lg::assign("image_" + image_id ,unit_image);

      lua_include_str += lg::line(lg::function("Load", lg::quote(lua_file_store.getRelativePath())));

      lua_file << image_table;
      lua_file.close();

      string grp_save_trace(to_string(i) +  ": " + grp_name + " : " + grp_arcfile + " => " + grp_storage_file_base);
      LOG4CXX_TRACE(logger, grp_save_trace);
    }
  }

  lua_include << lua_include_str;
  lua_include.close();

  return result;
}

} /* namespace dat */
