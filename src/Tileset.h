/*
 * Tileset.h
 *
 *      Author: Andreas Volz
 */

#ifndef TILESET_H_
#define TILESET_H_

#ifdef _MSC_VER
#define UNUSED
#else
#define UNUSED __attribute__((unused))
#endif

// System
#include <string>
#include <memory>

// Local
#include <Palette.h>

// Forward declarations
class Hurricane;

class Tileset
{
public:
  Tileset(std::shared_ptr<Hurricane> hurricane);
  virtual ~Tileset();

  /**
   * Not sure, but it seems this function generates some Gimp palette.
   * Maybe there is an external Gimp workflow...
   */
  bool ConvertRgb(const std::string &arcfile, const std::string &file);

  bool ConvertTileset(const std::string &arcfile, const std::string &file);

private:

  unsigned char* ConvertTile(const std::string &arcfile, unsigned char *mini,
      unsigned char *mega, int msize,
      unsigned char *map UNUSED,
      int mapl UNUSED, int *wp, int *hp);

  void DecodeMiniTile(unsigned char *image, int ix, int iy, int iadd,
      unsigned char *mini, int index, int flipx, int flipy);

  std::shared_ptr<Hurricane> mHurricane;
};

#endif /* TILESET_H_ */
