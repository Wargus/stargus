/*
 * Palettes.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTE_H_
#define PALETTE_H_

// Local
#include "DataChunk.h"
#include "Logger.h"

// C++
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
  /**
   * Create Palette from DataChunk
   *
   * @rapam palData Size has to be 256 bytes * 3 (rgb). If you don't respect this it will crash!
   */
  Palette(std::shared_ptr<DataChunk> palData);

  virtual ~Palette();

  std::shared_ptr<DataChunk> getDataChunk();

  //std::shared_ptr<Palette> copy();

private:
  Logger mLogger;
  std::shared_ptr<DataChunk> mPalData;
  const int RGB_SIZE = 256 * 3;
};

#endif /* PALETTE_H_ */
