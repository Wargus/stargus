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
  static int save(const char *name, unsigned char *image, int w, int h,
      unsigned char *pal, int transparent);
};

#endif /* PNG_H_ */
