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
/**
 * The TileSetHub parses the complete data structures inside those files:
 * - tileset\\<tileset>.cv5|vx4|vf4|vr4
 *
 * The Kaitai parsed objects in this class are by intension public. There's no benefit in putting dozen silly
 * getter around them. The alternative to put them private means to implement every parser logic
 * inside this class or friend them all.
 *
 * So the design decision is just to let them public and the outside accessing function should only read them!
 * If I ever put this stuff to a general purpose library this design might change.
 *
 *  "with great power comes great responsibility" - (Spiderman)
 */
class TilesetHub : public KaitaiConverter
{
public:
  TilesetHub(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile);
  virtual ~TilesetHub();

  bool convert(std::shared_ptr<AbstractPalette> palette, Storage storage);

  void generateLua(const std::string &name, const std::string &image, Storage luafile);

  std::shared_ptr<tileset_cv5_t> cv5;
  std::shared_ptr<tileset_vx4_t> vx4;
  std::shared_ptr<tileset_vf4_t> vf4;
  std::shared_ptr<tileset_vr4_t> vr4;

private:
  void init(const std::string &arcfile);

};

} /* namespace tileset */

#endif /* TILESETHUB_H */
