/*
 * Chk.h
 *
 *      Author: Andreas Volz
 */

#ifndef CHK_H_
#define CHK_H_

// Local
#include "WorldMap.h"

// System
#include <memory>

// Forward declarations
class Hurricane;

/**
 * For .chk files generate a combination of .smp and .sms file
 * The .smp and .sms files are Lua scripts and are executed by stargus/stratagus
 * The generated files describe the map, units, tiles, triggers - simply the map behavior
 *
 */
class Chk
{
public:
	Chk(std::shared_ptr<Hurricane> hurricane);
	virtual ~Chk();

	virtual bool convert(const std::string &arcfile, const std::string &file);

private:
	void loadFromBuffer(unsigned char *chkdata, int len);
	void ConvertChk(const char *savedir, unsigned char *chkdata, int chklen);

	void SaveMap(const char *savedir);

	void SaveSMS(const char *name);
	void SaveTrigger(FILE *fd, Trigger *trigger);
	void SaveSMP(const char *name);
	void FreeMap();

	WorldMap *map;
	std::shared_ptr<Hurricane> mHurricane;
};



#endif /* CHK_H_ */
