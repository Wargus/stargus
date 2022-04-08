/*
 * Palettes.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTE_H_
#define PALETTE_H_

// project
#include "DataChunk.h"
#include "Logger.h"
#include "RGBColor.h"

// system
#include <memory>

// TODO: unextern this !!
extern unsigned char SC_Unit_Palette[];
extern unsigned char Terrain_Palette[];
extern unsigned char Cmdicons_Palette[];
extern unsigned char Orange_Palette[];
extern unsigned char *Palettes[];

/**
 *
 */
class Palette
{
public:
  Palette();

  /**
   * Create Palette from DataChunk
   *
   * @rapam palData Size has to be mutlible of 256 bytes (rgb or rgba). If you don't respect this it will crash!
   * TODO: better data type check needed
   */
  Palette(std::shared_ptr<DataChunk> palData);

  virtual ~Palette();

  std::shared_ptr<DataChunk> getDataChunk();

  void addRGBColor(const RGBColor &rgb);

  void addColorComponent(unsigned char color);

  RGBColor getRGBColor(int index);

  void replaceRGBColor(int index, const RGBColor &rgb);

  //int getSize();

  //std::shared_ptr<Palette> copy();

private:
  Logger mLogger;
  std::shared_ptr<DataChunk> mPalData;
};

#endif /* PALETTE_H_ */
