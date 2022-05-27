/*
 * MegaTile.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "MegaTile.h"
#include "kaitai/tileset_vr4.h"
#include "kaitai/tileset_vx4.h"
#include "Logger.h"

// system
#include <string>
#include <iostream>

using namespace std;

namespace tileset
{

static Logger logger = Logger("startool.tileset.MegaTile");

MegaTile::MegaTile(TilesetHub &tilesethub, size_t element) :
  mTilesetHub(tilesethub),
  mElement(element)
{
  generateTiles();
}

MegaTile::~MegaTile()
{

}

void MegaTile::generateTiles()
{
  mPaletteImage = make_shared<TiledPaletteImage>(Size(4, 4), Size(8, 8));

  tileset_vx4_t::megatile_type_t *megatile = mTilesetHub.vx4_raw->elements()->at(mElement);

  std::vector<tileset_vx4_t::graphic_ref_type_t *> *vx4_graphic_ref = megatile->graphic_ref();

  unsigned int n = 0;
  for (auto g : *vx4_graphic_ref)
  {
    uint64_t g_ref = g->vr4_ref();
    bool horizontal_flip = g->horizontal_flip();

    std::vector<tileset_vr4_t::pixel_type_t *> *pixel_ref = mTilesetHub.vr4_raw->elements();

    tileset_vr4_t::pixel_type_t *color_ref = pixel_ref->at(g_ref);

    const string &color = color_ref->minitile();

    PaletteImage palImage(Size(8, 8));
    unsigned int i = 0;
    for (auto c : color)
    {
      Pos pos = palImage.indexToPosition(i);

      palImage.at(pos) = c;

      i++;
    }

    mPaletteImage->copyTile(palImage, n, horizontal_flip);

    n++;
  }
}

std::shared_ptr<PaletteImage> MegaTile::getImage()
{
  return mPaletteImage;
}
} /* namespace tileset */
