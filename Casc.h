/*
 * Casc.h
 *
 *      Author: Andreas Volz
 */

#include "Hurricane.h"

#ifndef CASC_H_
#define CASC_H_

class Casc : public Hurricane
{
public:
	Casc();
	virtual ~Casc();

	bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress);
};

#endif /* CASC_H_ */
