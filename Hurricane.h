/*
 * Hurricane.h
 *
 *      Author: Andreas Volz
 */

#ifndef HURRICANE_H_
#define HURRICANE_H_

// Local
#include "DataChunk.h"

// System
#include <string>
#include <memory>

class Hurricane
{
public:
	Hurricane();
	Hurricane(const std::string &archiveName);
	virtual ~Hurricane();

	/**
	 * Extract file from archive and create all directories if not existing
	 */
	virtual bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress) = 0;

	/**
	 * Attention: This function malloc() bufferLen memory which you've to free yourself!
	 * Better use extractDataChunk()
	 */
	virtual bool extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen) = 0;

	/**
	 * Extract a file in memory
	 * @return A shared_ptr with DataChunk to have responsibility of memory handling
	 */
	virtual std::shared_ptr<DataChunk> extractDataChunk(const std::string &archivedFile);


protected:
	std::string mArchiveName;
};

#endif /* HURRICANE_H_ */
