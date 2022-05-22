/*
 * Tileset.h
 *
 *      Author: Andreas Volz
 */

#ifndef TILESET_H
#define TILESET_H

#ifdef _MSC_VER
#define UNUSED
#else
#define UNUSED __attribute__((unused))
#endif

// System
#include <string>
#include <memory>

// Local
#include "Palette.h"
#include "KaitaiConverter.h"

// Forward declarations
class Hurricane;

class Tileset : public KaitaiConverter
{
public:
  Tileset(std::shared_ptr<Hurricane> hurricane);
  virtual ~Tileset();

  bool convert(const std::string &terrain, std::shared_ptr<Palette> palette);

  bool ConvertTileset(const std::string &arcfile, const std::string &file);

private:

  //void init_kaitai_parser(const std::string &terrain);

  unsigned char* ConvertTile(const std::string &arcfile, unsigned char *mini,
      unsigned char *mega, int msize,
      unsigned char *map UNUSED,
      int mapl UNUSED, int *wp, int *hp);

  void DecodeMiniTile(unsigned char *image, int ix, int iy, int iadd,
      unsigned char *mini, int index, int flipx, int flipy);
};

#endif /* TILESET_H */
