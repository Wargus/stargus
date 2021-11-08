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

	/**
	 * Extract file from CASC archive and create all directories if not existing
	 */
	bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress);

	/**
	 * Attention: This function malloc() bufferLen memory which you've to free yourself!
	 * Better use extractDataChunk()
	 */
	bool extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen);

	/**
	 * Extract a file in memory
	 * @return A shared_ptr with DataChunk to have responsibility of memory handling
	 */
	//std::shared_ptr<DataChunk> extractDataChunk(const std::string &archivedFile);


private:
	void *mStorage;
};

#endif /* CASC_H_ */
