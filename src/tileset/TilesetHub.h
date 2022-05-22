/*
 * TilesetHub.h
 *
 *      Author: Andreas Volz
 */

#ifndef TILESETHUB_H
#define TILESETHUB_H

// project
#include "Palette.h"
#include "KaitaiConverter.h"
#include "kaitai/tileset_cv5.h"
#include "kaitai/tileset_vx4.h"
#include "kaitai/tileset_vf4.h"
#include "kaitai/tileset_vr4.h"

// system
#include <memory>
#include <string>

namespace tileset
{

class TilesetHub : public KaitaiConverter
{
public:
  TilesetHub(std::shared_ptr<Hurricane> hurricane);
  virtual ~TilesetHub();

  void convert(const std::string &terrain, std::shared_ptr<Palette> palette);


private:
  std::string mTerrain;
  std::shared_ptr<Palette> mPalette;

  std::shared_ptr<tileset_cv5_t> cv5_raw;
  std::shared_ptr<tileset_vx4_t> vx4_raw;
  std::shared_ptr<tileset_vf4_t> vf4_raw;
  std::shared_ptr<tileset_vr4_t> vr4_raw;

  // we trust the other classes in the namespace to access our private members as this is easier
  friend class MegaTile;

};

} /* namespace tileset */

#endif /* TILESETHUB_H */
