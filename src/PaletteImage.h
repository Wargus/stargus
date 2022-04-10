/*
 * PaletteImage.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTEIMAGE_H
#define PALETTEIMAGE_H

// Project
#include "DataChunk.h"

// System

class PaletteImage
{
public:
  PaletteImage(int width, int height);
  virtual ~PaletteImage();

  void addPaletteIndex(unsigned char paletteIndex);

  unsigned char* getPaletteIndexData() const;

  int getHeight() const;

  int getWidth() const;

  unsigned char at(size_t pos);

  unsigned char getPaletteIndex(int width, int height);

private:
  DataChunk mImageData;
  int mWidth;
  int mHeight;
};

#endif /* PALETTEIMAGE_H */
