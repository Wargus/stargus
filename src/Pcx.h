/*
 * Pcx.h
 *
 *      Author: Andreas Volz
 */

#ifndef PCX_H
#define PCX_H

// Project
#include "Converter.h"
#include "Logger.h"
#include "Palette.h"
#include "Storage.h"
#include "PaletteImage.h"

class Pcx: public Converter
{
public:
  Pcx(std::shared_ptr<Hurricane> hurricane);
  Pcx(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile);
  virtual ~Pcx();

  bool load(const std::string &arcfile);

  /**
   *  Convert a pcx graphic to PNG format
   *
   *  @param arcfile File identifier in the MPQ file
   *  @param file Place to save the file on the drive
   */
  bool savePNG(Storage storage);

  std::shared_ptr<Palette> getPalette();

  /**
   * Map palette colors from one place in the image to a position in the color palette
   *
   * TODO: I need to write a more extensive documentation for this
   *
   * @param length the length of one color index
   * @param index the color index
   * @param start where to place the copy in the palette position
   */
  void mapIndexPalette(int length, int index, int start);

  /**
   * Wrapper for mapIndexPalette() with configuration to use ticon.pcx palette
   *
   * @param index the color index selector to choose
   */
  void mapIndexPaletteTypeIcon(int index = 0);

  /**
    * Wrapper for mapIndexPalette() with configuration to use tselect.pcx palette
    *
    * @param index the color index selector to choose
    */
  void mapIndexPaletteTypeSelect(int index = 0);

  /**
   * Fake some 2D palette handling for e.g. fire generation.
   * FIXME: a better algorithm is needed based on generating alpha over tileset or so...
   */
  void map2DPalette();

private:
  struct PCXheader
  {
    unsigned char Manufacturer;
    unsigned char Version;
    unsigned char Encoding;
    unsigned char BitsPerPixel;
    short Xmin, Ymin, Xmax, Ymax;
    short HDpi, VDpi;
    unsigned char Colormap[48];
    unsigned char Reserved;
    unsigned char NPlanes;
    short BytesPerLine;
    short PaletteInfo;
    short HscreenSize;
    short VscreenSize;
    unsigned char Filler[54];
  };

  void extractHeader();

  /**
   *  Convert 8 bit pcx file to raw image
   */
  void extractImage();

  Logger mLogger;
  std::shared_ptr<Palette> mPalette;
  std::shared_ptr<DataChunk> mRawData;
  std::shared_ptr<PaletteImage> mPaletteImage;
  unsigned char *rawImage;
  const int RGB_BYTE_SIZE = 3;
  const int RGB_SIZE = 256 * RGB_BYTE_SIZE;
};

#endif /* PCX_H */
