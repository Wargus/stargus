/*
 * Chk.h
 *
 *      Author: Andreas Volz
 */

#ifndef CHK_H_
#define CHK_H_

#include "WorldMap.h"

class Chk
{
public:
	Chk();
	virtual ~Chk();

	static void loadFromBuffer(unsigned char *chkdata, int len, WorldMap *map);
};



#endif /* CHK_H_ */
