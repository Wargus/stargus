/*
 * MegaTile.h
 *
 *      Author: Andreas Volz
 */

#ifndef MEGATILE_H
#define MEGATILE_H

// project
#include "TilesetHub.h"
#include "TiledPaletteImage.h"

namespace tileset
{

/**
 * MiniTiles are arranged in a MegaTile as follows:
 * 0 |  1 | 2 | 3
 * 4 |  5 | 6 | 7
 * 8 |  9 |10 |11
 * 12| 13 |14 |15
 */
class MegaTile
{
public:
  MegaTile(TilesetHub &tilesethub, size_t element);
  virtual ~MegaTile();

  std::shared_ptr<PaletteImage> getImage();

private:
  TilesetHub &mTilesetHub;
  size_t mElement;
  std::shared_ptr<TiledPaletteImage> mPaletteImage;

  void generateTiles();
};

} /* namespace tileset */

#endif /* MEGATILE_H */
