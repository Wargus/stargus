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
	 * Create Palette from memory. The Palette class takes over responsibility for deleting the memory.
	 *
	 * @rapam palData Size has to be 256 bytes * 3 (rgb). If you don't respect this it will crash!
	 */
	Palette(std::shared_ptr<DataChunk> palData);

	virtual ~Palette();

	std::shared_ptr<DataChunk> getDataChunk();

private:
	Logger mLogger;
	std::shared_ptr<DataChunk> mPalData;
};

#endif /* PALETTE_H_ */
