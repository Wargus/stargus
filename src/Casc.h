/*
 * Casc.h
 *
 *      Author: Andreas Volz
 */
#ifdef HAVE_CASC

#include "Hurricane.h"

#ifndef CASC_H_
#define CASC_H_

class Casc: public Hurricane
{
public:
  Casc();
  Casc(const std::string &archiveName);
  virtual ~Casc();

  bool openArchive(const std::string &archiveName);
  void closeArchive();

  /**
   * Extract file from CASC archive and create all directories if not existing
   *
   * @param TODO compress gzip compression -> NOT IMPLEMENTED
   */
  bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress);

  /**
   * Attention: This function malloc() bufferLen memory which you've to free yourself!
   * Better use extractDataChunk()
   */
  bool extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen);

private:
  void *mStorage;
};


#endif /* CASC_H_ */

#endif /* HAVE_CASC */
