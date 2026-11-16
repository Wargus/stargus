#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef _MSC_VER
#define DEBUG _DEBUG
#define PATH_MAX _MAX_PATH
#include <direct.h>
#include <io.h>
#else
#include <limits.h>
#include <unistd.h>
#endif
#include <ctype.h>
#include <iostream>
#include <zlib.h>
#include <StormLib.h>

#include "Storm.h"
#include "FileUtil.h"

using namespace std;

// added in StormLib 9.31
#if STORMLIB_VERSION < 0x091F
DWORD SErrGetLastError()
{
	return GetLastError();
}
#endif

Storm::Storm() :
  mMpqHandle(nullptr)
{

}

Storm::Storm(const std::string &archiveName) :
  mMpqHandle(nullptr)
{
  openArchive(archiveName);
}

Storm::~Storm()
{
  closeArchive();
}

bool Storm::openArchive(const std::string &archiveName)
{
  bool result = true;

  // close it in case it's still open
  closeArchive();

  // Open an archive, e.g. "d2music.mpq"
  if (!SFileOpenArchive(archiveName.c_str(), 0, STREAM_FLAG_READ_ONLY, &mMpqHandle))
  {
    result = false;
  }
  else
  {
    mArchiveName = archiveName;
  }
  return result;
}

void Storm::closeArchive()
{
  if (mMpqHandle != nullptr)
  {
    SFileCloseArchive(mMpqHandle);
    mArchiveName.clear();
  }
}

bool Storm::extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen)
{
  int nError = ERROR_SUCCESS;
  unsigned char *szEntryBuffer = nullptr;
  HANDLE hFile = nullptr;          // Archived file handle
  bool result = true;

  // Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
  if (nError == ERROR_SUCCESS)
  {
    if (!SFileOpenFileEx(mMpqHandle, archivedFile.c_str(), 0, &hFile))
      nError = SErrGetLastError();
  }

  int i = 0;
  size_t len = 0;
  // Read the file from the archive
  if (nError == ERROR_SUCCESS)
  {
    char szBuffer[0x10000];

    szEntryBuffer = (unsigned char *) malloc(sizeof(szBuffer)); // TODO: this might me useless and then free() could be avoid below
    DWORD dwBytes = 1;

    while (dwBytes > 0)
    {
      SFileReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL);
      if (dwBytes > 0)
      {
        len = len + dwBytes;
        szEntryBuffer = (unsigned char *) realloc(szEntryBuffer, len);
        memcpy(szEntryBuffer + (i * sizeof(szBuffer)), szBuffer, dwBytes);

      }
      i++;
    }
  }
  if (bufferLen != NULL)
  {
    *bufferLen = len;
  }

  if (hFile != NULL)
    SFileCloseFile(hFile);

  if (nError != ERROR_SUCCESS)
  {
    result = false;
    // in case of problem free what ever has been allocated
    free(szEntryBuffer);
    szEntryBuffer = nullptr;
  }

  *szEntryBufferPrt = szEntryBuffer;

  return result;
}

bool Storm::extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress)
{
  HANDLE hFile = nullptr;          // Archived file handle
  gzFile gzfile = nullptr;         // Compressed file handle
  int nError = ERROR_SUCCESS;
  bool result = true;

  // Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
  if (nError == ERROR_SUCCESS)
  {
    if (!SFileOpenFileEx(mMpqHandle, archivedFile.c_str(), 0, &hFile))
      nError = SErrGetLastError();
  }

  if (nError == ERROR_SUCCESS && !compress)
  {
    // Let StormLib extract the complete file
    CheckPath(extractedName);
    bool extracted = SFileExtractFile(
                       mMpqHandle,
                       archivedFile.c_str(),
                       extractedName.c_str(),
                       SFILE_OPEN_FROM_MPQ
                     );
    SFileCloseFile(hFile);
    return extracted;
  }

  // Create the target file
  if (nError == ERROR_SUCCESS)
  {
    CheckPath(extractedName);
    gzfile = gzopen(extractedName.c_str(), "wb9");
    if (gzfile == nullptr)
      nError = ERROR_CAN_NOT_COMPLETE;
  }

  // Read the file from the archive
  if (nError == ERROR_SUCCESS)
  {
    char szBuffer[0x10000];
    DWORD dwBytes = 1;

    while (dwBytes > 0)
    {
      // SFileReadFile() fails with ERROR_HANDLE_EOF at the end of the
      // file; any other failure must abort instead of truncating.
      if (!SFileReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL))
      {
        nError = SErrGetLastError();
        if (nError == ERROR_HANDLE_EOF)
          nError = ERROR_SUCCESS;
      }
      if (nError != ERROR_SUCCESS || dwBytes == 0)
        break;
      gzwrite(gzfile, szBuffer, dwBytes);
    }
  }

  // Cleanup and exit
  if (gzfile != NULL)
  {
    gzclose(gzfile);
  }
  if (hFile != NULL)
    SFileCloseFile(hFile);

  if (nError != ERROR_SUCCESS)
    result = false;

  return result;
}

unsigned int Storm::getRecordCount(const std::string &archivedFile, unsigned int recordsize)
{
  // TODO: implement
  return 0;
}

