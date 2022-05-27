/*
 * TilesetHub.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "TilesetHub.h"
#include "PaletteImage.h"
#include "PngExporter.h"
#include "MegaTile.h"
#include "FileUtil.h"
#include "luagen.h"
#include "Preferences.h"

// system
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

namespace tileset
{

TilesetHub::TilesetHub(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
  KaitaiConverter(hurricane)
{
  init(arcfile);
}

TilesetHub::~TilesetHub()
{

}

void TilesetHub::init(const std::string &arcfile)
{
  std::shared_ptr<kaitai::kstream> cv5_ks;
  cv5_ks = getKaitaiStream(arcfile + ".cv5");
  std::shared_ptr<tileset_cv5_t> cv5_loc(new tileset_cv5_t(cv5_ks.get()));
  cv5 = cv5_loc;

  std::shared_ptr<kaitai::kstream> vx4_ks;
  vx4_ks = getKaitaiStream(arcfile + ".vx4");
  std::shared_ptr<tileset_vx4_t> vx4_loc(new tileset_vx4_t(vx4_ks.get()));
  vx4 = vx4_loc;

  std::shared_ptr<kaitai::kstream> vf4_ks;
  vf4_ks = getKaitaiStream(arcfile + ".vf4");
  std::shared_ptr<tileset_vf4_t> vf4_loc(new tileset_vf4_t(vf4_ks.get()));
  vf4 = vf4_loc;

  std::shared_ptr<kaitai::kstream> vr4_ks;
  vr4_ks = getKaitaiStream(arcfile + ".vr4");
  std::shared_ptr<tileset_vr4_t> vr4_loc(new tileset_vr4_t(vr4_ks.get()));
  vr4 = vr4_loc;

  //cout << "cv5_raw->elements()->size(): " << cv5_raw->elements()->size() << endl;
  //cout << "vx4_raw->elements()->size(): " << vx4_raw->elements()->size() << endl;
  //cout << "vf4_raw->elements()->size(): " << vf4_raw->elements()->size() << endl;
  //cout << "vr4_raw->elements()->size(): " << vr4_raw->elements()->size() << endl;

}

bool TilesetHub::convert(std::shared_ptr<Palette> palette, Storage storage)
{
  unsigned int num_tiles = vx4->elements()->size();
  int tiles_width = 16;
  int tiles_height = ceil(static_cast<float>(num_tiles) / static_cast<float>(tiles_width));

  TiledPaletteImage ultraTile(Size(tiles_width, tiles_height), Size(32,32));

  for(unsigned int i = 0; i < num_tiles; i++)
  {
    MegaTile mega(*this, i);

    ultraTile.copyTile(*mega.getImage(), i);
  }

  // FIXME: I don't like the path handling in this case. Needs to be changed!
  string save_png(storage.getFullPath() + "/" + storage.getFilename() + ".png");
  CheckPath(save_png);
  return !PngExporter::save(save_png, ultraTile, *palette, 0);
}

void TilesetHub::generateLua(const std::string &name, const std::string &image, Storage luafile)
{
  unsigned int num_cv5 = cv5->elements()->size();

  int num_doodad = 0;
  int num_normal = 0;

  ofstream lua_tileset_stream;
  CheckPath(luafile.getFullPath());
  lua_tileset_stream.open (luafile.getFullPath());

  vector<string> tile_slots_vector;

  for(unsigned int i = 0; i < num_cv5; i++)
  {
    tileset_cv5_t::group_t* group = cv5->elements()->at(i);

    if(group->doodad() != 0)
    {
      num_doodad++;
      //cout << "doodad(" << i << "): ";
    }
    else
    {
      num_normal++;
      //cout << "normal(" << i << "): ";
    }

    std::vector<uint16_t>* vx4_vf4_ref = group->megatile_references();

    vector<string> tile_solids_vector;

    for(auto elem : *vx4_vf4_ref)
    {
      //cout << to_string(elem);


      tileset_vf4_t::minitile_t* minitile = vf4->elements()->at(elem);

      unsigned int walkable_median = 0;
      for(auto flags : *minitile->flags())
      {
          walkable_median += flags->walkable();
      }


      walkable_median /= 16; // 8 is the 50% unpassable Minitles per Megatile rule

      tile_solids_vector.push_back(to_string(elem));

      if(!walkable_median)
      {
        tile_solids_vector.push_back(lg::table(lg::quote("unpassable")));
      }

      //cout << ", ";
    }
    //cout << endl;

    string tile_solids_str = lg::params(tile_solids_vector);
    string solid_str = lg::line(lg::tilesetSlotEntry("solid", {"light-grass", "land"}, {tile_solids_str}));

    tile_slots_vector.push_back(solid_str);
  }

  string tile_slots_str = lg::params(tile_slots_vector);
  string lua_tileset_str = lg::DefineTileset(name, image, {tile_slots_str});

  //cout << lua_tileset_str << endl;

  lua_tileset_stream << lua_tileset_str;
  lua_tileset_stream.close();

  //cout << "num_doodad: " << num_doodad << endl;
  //cout << "num_normal: " << num_normal << endl;
}

} /* namespace tileset */
