/*
 * PaletteImage.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTEIMAGE_H
#define PALETTEIMAGE_H

// System

// Project
#include "DataChunk.h"

class PaletteImage
{
public:
  PaletteImage(int width, int height);
  virtual ~PaletteImage();

  void addPixel(unsigned char paletteIndex);

  unsigned char* getPixelData() const;

  int getHeight() const;

  int getWidth() const;

private:
  DataChunk mImageData;
  int mWidth;
  int mHeight;
};

#endif /* PALETTEIMAGE_H */
