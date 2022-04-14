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
  /**
   * Construct with specific size but empty data to fill byte by byte
   */
  PaletteImage(int width, int height);

  /**
   * Construct with specific size but fill in one chunk
   */
  PaletteImage(const DataChunk &datachunk, int width, int height);
  virtual ~PaletteImage();

  void addPaletteIndex(unsigned char paletteIndex);

  unsigned char* getRawData() const;

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
