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

/**
 * This is the virtual base class for Bl*zz*rd data containers
 */
class Hurricane
{
public:
	Hurricane();
	Hurricane(const std::string &archiveName);
	virtual ~Hurricane();

	virtual bool openArchive(const std::string &archiveName) = 0;

	virtual void closeArchive() = 0;

	/**
	 * Extract file from archive and create all directories if not existing
	 *
	 * @param compress if set true save file with gzip on drive. No special file extension is added automatic. (default: false)
	 */
  virtual bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress = false) = 0;

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

	virtual std::shared_ptr<std::istream> extractStream(const std::string &archivedFile);

	virtual const std::string &getArchiveName() const;

protected:

	std::string mArchiveName;
};

#endif /* HURRICANE_H_ */
