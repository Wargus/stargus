/*
 * Png.h
 *
 *      Author: Andreas Volz
 */

#ifndef PNG_H_
#define PNG_H_

#include <png.h>

class Png
{
public:
  Png();
  virtual ~Png();

  //TODO: un-static this in the design!


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
  static int save(const char *name, unsigned char *image, int w, int h,
      unsigned char *pal, int transparent);

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
  static int saveRGBA(const char *name, unsigned char *image, int w, int h,
      unsigned char *pal, int transparent);
};

#endif /* PNG_H_ */
