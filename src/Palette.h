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
	Palette();
	virtual ~Palette();


private:
	Logger mLogger;
};

#endif /* PALETTE_H_ */
