/*
 * Gfx.h
 *
 *      Author: Andreas Volz
 */

#ifndef GFX_H_
#define GFX_H_

#include "Grp.h"

class Gfx: public Grp
{
public:
	Gfx();
	virtual ~Gfx();

	/**
	**  Convert a graphic to my format.
	*/
	bool convert(const char *mpqfile, const char* arcfile, const char* file, int pale);

private:

};

#endif /* GFX_H_ */
