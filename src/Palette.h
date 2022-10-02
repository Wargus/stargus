/*
 * Palettes.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTE_H
#define PALETTE_H

// project
#include "DataChunk.h"
#include "Color.h"
#include "Converter.h"

// project
#include <memory>
#include <array>

/**
 *
 */
class Palette
{
public:
  Palette();

  /**
   * Create from a RGB or RGBx/WPE palette
   */
  Palette(std::shared_ptr<DataChunk> rawPalette);

  virtual ~Palette();

  /**
   * Create a new DataChunk copy for (old) functions that need the data aligned in a big unsigned char*
   * Pay attention of the std::shared_ptr nature:
   *    If you directly call createDataChunk()->getDataPointer() without saving it before to a std::shared_ptr<DataChunk> it won't work!
   */
  std::shared_ptr<DataChunk> createDataChunk();

  /**
   * Property change of a color with r-value
   */
  Color &at(unsigned int index);

  void load(std::shared_ptr<DataChunk> rawPalette);

  bool write(const std::string &filename);

  bool read(const std::string &filename);

private:
  std::array<Color, 256> mColorPalette;
};

#endif /* PALETTE_H */
