#ifndef STORM_H_
#define STORM_H_

// Local
#include "Hurricane.h"
#include "DataChunk.h"

// System
#include <stdint.h>
#include <string>
#include <memory>

class Storm: public Hurricane
{
public:
  Storm();
  Storm(const std::string &archiveName);
  virtual ~Storm();

  bool openArchive(const std::string &archiveName);
  void closeArchive();

  /**
   * Extract file from MPQ archive and create all directories if not existing
   *
   * @param archivedFile File/name identifier in MPQ archive to extract (e.g. game//icons.grp)
   * @param extractedName File including path where it is extracted to (all folders will be created)
   */
  bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress);

  /**
   * Attention: This function malloc() bufferLen memory which you've to free yourself!
   * Better use extractDataChunk()
   */
  bool extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen);

  unsigned int getRecordCount(const std::string &archivedFile, unsigned int recordsize);

private:
  void *mMpqHandle; // Open archive handle

};

#endif /* STORM_H_ */
