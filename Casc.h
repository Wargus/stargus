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
	Casc(const std::string &archiveName);
	virtual ~Casc();

	bool openArchive(const std::string &archiveName);
	void closeArchive();

	bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress);

private:
	void *mStorage;
};

#endif /* CASC_H_ */
