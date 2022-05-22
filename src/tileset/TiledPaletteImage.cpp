/*
 * TiledPaletteImage.cpp
 *
 *      Author: Andreas Volz
 */

#include "TiledPaletteImage.h"

namespace tileset
{

TiledPaletteImage::TiledPaletteImage(const Size &tileSize, const Size &subtileSize) :
    PaletteImage(tileSize * subtileSize),
    mLogger("startool.tileset.TiledPaletteImage"),
    mTileSize(tileSize),
    mSubtileSize(subtileSize)
{

}

TiledPaletteImage::~TiledPaletteImage()
{

}

void TiledPaletteImage::copyTile(const PaletteImage &palette_image, size_t index)
{
  int y = 0;
  int x = 0;

  // if index is out of data size that return Pos(0, 0) as fail safe
  if((int)index < (getSize().getWidth() * getSize().getHeight()) /
      (palette_image.getSize().getWidth() * palette_image.getSize().getHeight()))
  {
    y = index / (getSize().getWidth() / palette_image.getSize().getWidth());
    x = index % (getSize().getWidth() / palette_image.getSize().getWidth());
  }

  Pos rel_pos(x,y);
  copyTile(palette_image, rel_pos);
}

void TiledPaletteImage::copyTile(const PaletteImage &palette_image, const Pos &pos)
{
  if(pos.getX() < mTileSize.getWidth() || pos.getY() < mTileSize.getWidth())
  {

    for(int x = 0; x < palette_image.getSize().getWidth(); x++)
    {
      for(int y = 0; y < palette_image.getSize().getHeight(); y++)
      {
        unsigned char pixel = palette_image.at(Pos(x, y));

        at(calcAbsolutePos(pos, Pos(x, y))) = pixel;
      }
    }
  }
  else
  {
    LOG4CXX_WARN(mLogger, "copyTile() out of range!");
  }
}

const Pos TiledPaletteImage::calcAbsolutePos(const Pos &tile_pos, const Pos &relative_pos)
{
  return Pos(tile_pos.getX() * mSubtileSize.getWidth() + relative_pos.getX(), tile_pos.getY() * mSubtileSize.getHeight() + relative_pos.getY());
}

} /* namespace tileset */
