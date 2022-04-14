/*
 * Palettes.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTE_H
#define PALETTE_H

// project
#include "DataChunk.h"
#include "Logger.h"
#include "Color.h"

// project
#include <memory>

/**
 *
 */
class Palette
{
public:
  Palette();

  /**
   * Create from a WPE palette
   */
  Palette(std::shared_ptr<DataChunk> wpePalette);

  virtual ~Palette();

  void replaceIndexColor(unsigned int index, const Color &rgb);

  void replaceIndexColorRange(const Palette &pal, unsigned int startIndex, unsigned int endIndex);

  /**
   * Create a new DataChunk copy for (old) functions that need the data aligned in a big unsigned char*
   * Pay attention of the std::shared_ptr nature:
   *    If you directly call createDataChunk()->getDataPointer() without saving it before to a std::shared_ptr<DataChunk> it won't work!
   */
  std::shared_ptr<DataChunk> createDataChunk();

  void addColor(const Color &rgb);

  const Color &at(int index) const;

  Color &at(int index);

private:
  Logger mLogger;
  std::vector<Color> mColorPalette;
};

#endif /* PALETTE_H */
