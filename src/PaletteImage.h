/*
 * PaletteImage.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTEIMAGE_H
#define PALETTEIMAGE_H

// Project
#include "DataChunk.h"
#include "Size.h"

// System

class PaletteImage
{
public:
  /**
   * Construct with specific size but empty data to fill byte by byte
   */
  PaletteImage(Size size);

  /**
   * Construct with specific size but fill in one chunk
   */
  PaletteImage(const DataChunk &datachunk, Size size);
  virtual ~PaletteImage();

  void addPaletteIndex(unsigned char paletteIndex);

  unsigned char* getRawData() const;

  Size getSize() const;

  unsigned char at(size_t pos);

  unsigned char getPaletteIndex(int width, int height);

private:
  DataChunk mImageData;
  Size mSize;
};

#endif /* PALETTEIMAGE_H */
