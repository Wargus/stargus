/*
 * Tileset.h
 *
 *      Author: Andreas Volz
 */

#ifndef TILESET_H_
#define TILESET_H_

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

  // FIXME: made this static just to test terrein palette
  static unsigned char* ConvertPaletteRGBXtoRGB(unsigned char *pal);

private:

  unsigned char* ConvertTile(const std::string &arcfile, unsigned char *mini,
      unsigned char *mega, int msize,
      unsigned char *map __attribute__((unused)),
      int mapl __attribute__((unused)), int *wp, int *hp);

  void DecodeMiniTile(unsigned char *image, int ix, int iy, int iadd,
      unsigned char *mini, int index, int flipx, int flipy);

  std::shared_ptr<Hurricane> mHurricane;
};

#endif /* TILESET_H_ */
