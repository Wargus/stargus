/*
 * Breeze.h
 *
 *      Author: Andreas Volz
 */

#ifndef BREEZE_H_
#define BREEZE_H_

#include "Hurricane.h"

/**
 * This has the same interface as Hurricane but is
 * a dummy file provider to provide extracted files to the converters.
 */
class Breeze: public Hurricane
{
public:
	Breeze();
	/**
	 * @param archiveName The folder where the extracted files are available
	 */
	Breeze(const std::string &archiveName);
	virtual ~Breeze();

	bool openArchive(const std::string &archiveName);

	void closeArchive();

	/* In fact copy files and create all directories if not existing. Not really useful, just to provide data for converters.
	 *
	 * @param archivedFile is the source
	 * @param extractedName is the target
	 */
	virtual bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress);

	/**
	 * Attention: This function malloc() bufferLen memory which you've to free yourself!
	 * Better use extractDataChunk()
	 */
	virtual bool extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen);

};

#endif /* BREEZE_H_ */
