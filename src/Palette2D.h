/*
 * Palette2D.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTE2D_H
#define PALETTE2D_H

// project
#include "Color.h"
#include "Palette.h"

// system
#include <vector>
#include <array>

class Palette2D
{
public:
  Palette2D(unsigned int size);

  Palette2D(std::shared_ptr<DataChunk> rawPalette);

  virtual ~Palette2D();

  /**
   * Create a new DataChunk copy for (old) functions that need the data aligned in a big unsigned char*
   * Pay attention of the std::shared_ptr nature:
   *    If you directly call createDataChunk()->getDataPointer() without saving it before to a std::shared_ptr<DataChunk> it won't work!
   */
  std::shared_ptr<DataChunk> createDataChunk();

  /**
   * Property change of a color with r-value
   */
  Color &at(unsigned int column, unsigned int row);

  unsigned int getSize();

  void load(std::shared_ptr<DataChunk> rawPalette);

  bool write(const std::string &filename);

  bool read(const std::string &filename);

private:
  std::vector<Palette> mColorPalette2D;
  unsigned int mSize;
};

#endif /* PALETTE2D_H */
