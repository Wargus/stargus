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

// system
#include <iostream>
#include <math.h>

using namespace std;

namespace tileset
{

TilesetHub::TilesetHub(std::shared_ptr<Hurricane> hurricane) :
  KaitaiConverter(hurricane)
{

}

TilesetHub::~TilesetHub()
{

}

void TilesetHub::convert(const std::string &terrain, std::shared_ptr<Palette> palette)
{
  mTerrain = terrain;
  mPalette = palette;

  string tileset_base_str(string("tileset") + + "\\" + mTerrain);

  std::shared_ptr<kaitai::kstream> cv5_ks;
  cv5_ks = getKaitaiStream(tileset_base_str + ".cv5");
  std::shared_ptr<tileset_cv5_t> cv5_loc(new tileset_cv5_t(cv5_ks.get()));
  cv5_raw = cv5_loc;

  std::shared_ptr<kaitai::kstream> vx4_ks;
  vx4_ks = getKaitaiStream(tileset_base_str + ".vx4");
  std::shared_ptr<tileset_vx4_t> vx4_loc(new tileset_vx4_t(vx4_ks.get()));
  vx4_raw = vx4_loc;

  std::shared_ptr<kaitai::kstream> vf4_ks;
  vf4_ks = getKaitaiStream(tileset_base_str + ".vf4");
  std::shared_ptr<tileset_vf4_t> vf4_loc(new tileset_vf4_t(vf4_ks.get()));
  vf4_raw = vf4_loc;

  std::shared_ptr<kaitai::kstream> vr4_ks;
  vr4_ks = getKaitaiStream(tileset_base_str + ".vr4");
  std::shared_ptr<tileset_vr4_t> vr4_loc(new tileset_vr4_t(vr4_ks.get()));
  vr4_raw = vr4_loc;

  cout << "cv5_raw->elements()->size(): " << cv5_raw->elements()->size() << endl;
  cout << "vx4_raw->elements()->size(): " << vx4_raw->elements()->size() << endl;
  cout << "vf4_raw->elements()->size(): " << vf4_raw->elements()->size() << endl;
  cout << "vr4_raw->elements()->size(): " << vr4_raw->elements()->size() << endl;

  //FIXME: there is still one bug - some MiniTiles aren't correctly flipped?

  unsigned int num_tiles = vx4_raw->elements()->size();
  int tiles_width = 16;
  int tiles_height = ceil(num_tiles / tiles_width);

  TiledPaletteImage ultraTile(Size(tiles_width, tiles_height), Size(32,32));

  for(unsigned int i = 0; i < num_tiles; i++)
  {
    MegaTile mega(*this, i);

    ultraTile.copyTile(*mega.getImage(), i);
  }

  string name = ("/tmp/test.png");
  PngExporter::save(name, ultraTile, *palette, 0);

}

} /* namespace tileset */
