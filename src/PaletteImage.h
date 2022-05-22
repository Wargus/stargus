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
#include "Pos.h"

// System

/**
 * A PaletteImage could hold a number of Integers of fixed size width*height that describe a Palette based image.
 * The Image itself needs always an associated Palette in one of the savers (e.g. PngExporter).
 */
class PaletteImage
{
public:
  /**
   * Construct with specific size but zero data to fill byte by byte
   * It allows random access to fill the elements with data as the internal vector is constructed at that size
   */
  PaletteImage(const Size &size);

  /**
   * Construct with specific size but fill in one chunk
   */
  PaletteImage(const DataChunk &datachunk, const Size &size);

  virtual ~PaletteImage();

  /**
   * @return the internal std::vector<unsigned char> implementation. Handle carefully!!
   */
  virtual const unsigned char* getRawDataPointer() const;

  virtual const Size getSize() const;

  /**
   * Get or set a pixel with palette index based on l-value or r-value (and provide a const variant)
   * Just like a vector at() usage
   */
  virtual unsigned char &at(size_t pos);
  virtual const unsigned char &at(size_t pos) const;

  /**
   * set or get a pixel based on l-value/r-value implementation (and provide a const variant)
   */
  virtual unsigned char &at(const Pos &pos);
  virtual const unsigned char &at(const Pos &pos) const;

  virtual const Pos indexToPosition(size_t index) const;

  virtual size_t positionToIndex(const Pos &pos) const;

private:
  std::vector<unsigned char> mData;
  Size mSize;
};

#endif /* PALETTEIMAGE_H */
