/*
 * Png.h
 *
 *      Author: Andreas Volz
 */

#ifndef PNG_H_
#define PNG_H_

// project
#include "PaletteImage.h"
#include "Palette.h"
#include "Palette2D.h"

// system
#include <png.h>
#include <string>

class PngExporter
{
public:
  PngExporter();
  virtual ~PngExporter();

  //TODO: un-static this in the design!

  static bool save(const std::string &name, PaletteImage &palImage,
        std::shared_ptr<AbstractPalette> abs_palette, int transparent);

  /**
   **  Save a png file with 8-bit colormap palette
   **
   **  @param name         File name
   **  @param image        Graphic data
   **  @param w            Graphic width
   **  @param h            Graphic height
   **  @param pal          Palette (256*3 colors/bytes)
   **  @param transparent  Image uses transparency
   */
  static bool saveRGB(const std::string &name, PaletteImage &palImage,
      Palette &palette, int transparent);

  /**
   **  Save a png file as 8-bit/color RGBA
   **  Color information is collected from palette and converted to pixel RGBA information
   **
   **  @param name         File name
   **  @param image        Graphic data
   **  @param w            Graphic width
   **  @param h            Graphic height
   **  @param pal          Palette (256*3 colors/bytes)
   **  @param transparent  Image uses transparency from from specific palette index
   */
  static bool saveRGBA(const std::string &name, PaletteImage &palImageh,
      Palette &palette, int transparent);

  static bool saveRGBA(const std::string &name, PaletteImage &palImageh,
      Palette2D &palette2d, int transparent);

};

#endif /* PNG_H_ */
