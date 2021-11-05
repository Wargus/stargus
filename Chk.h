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

	void loadFromBuffer(unsigned char *chkdata, int len);
	void ConvertChk(const char *newname, unsigned char *chkdata, int chklen);


	void SaveMap(const char *name);


private:
	void SaveSMS(const char *name);
	void SaveTrigger(FILE *fd, Trigger *trigger);
	void SaveSMP(const char *name);
	void FreeMap();

	WorldMap *map;
};



#endif /* CHK_H_ */
