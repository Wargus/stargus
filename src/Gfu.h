/*
 * Gfu.h
 *
 *      Author: Andreas Volz
 */

#ifndef GFU_H_
#define GFU_H_

#include "Grp.h"

class Gfu: public Grp
{
public:
	Gfu();
	virtual ~Gfu();

	/**
	**  Convert a uncompressed graphic to my format.
	*/
	bool convert(const char *mpqfile, const char* arcfile, const char* file, int pale);

private:

};

#endif /* GFU_H_ */
