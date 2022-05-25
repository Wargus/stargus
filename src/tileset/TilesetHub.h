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
#include "Storage.h"

// system
#include <memory>
#include <string>

namespace tileset
{

class TilesetHub : public KaitaiConverter
{
public:
  TilesetHub(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile);
  virtual ~TilesetHub();

  bool convert(std::shared_ptr<Palette> palette, Storage storage);

  void generateLua(const std::string &name, const std::string &image, Storage luafile);

private:
  void init(const std::string &arcfile);

  std::shared_ptr<tileset_cv5_t> cv5_raw;
  std::shared_ptr<tileset_vx4_t> vx4_raw;
  std::shared_ptr<tileset_vf4_t> vf4_raw;
  std::shared_ptr<tileset_vr4_t> vr4_raw;

  // we trust the other classes in the namespace to access our private members as this is easier
  friend class MegaTile;

};

} /* namespace tileset */

#endif /* TILESETHUB_H */
