/*
 * Breeze.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Breeze.h"
#include "FileUtil.h"
#include "Logger.h"

// System
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <zlib.h>

using namespace std;

static Logger logger = Logger("startool.Breeze");

Breeze::Breeze()
{

}

Breeze::~Breeze()
{
  closeArchive();
}

Breeze::Breeze(const std::string &archiveName)
{
  openArchive(archiveName);
}

bool Breeze::openArchive(const std::string &archiveName)
{
  mArchiveName = archiveName;
  return true;
}

void Breeze::closeArchive()
{
  mArchiveName.clear();
}

bool Breeze::extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress)
{
  unsigned char *szEntryBuffer = nullptr;
  size_t bufferLen = 0;
  bool result = false;
  FILE *file = nullptr;            // Disk file handle
  gzFile gzfile = nullptr;         // Compressed file handle

  if (extractMemory(archivedFile, &szEntryBuffer, &bufferLen))
  {
    CheckPath(extractedName);

    if (compress)
    {
      gzfile = gzopen(extractedName.c_str(), "wb9");
      if (gzfile)
      {
        int bytes_written = gzwrite(gzfile, szEntryBuffer, bufferLen);
        gzclose(gzfile);
        if (bytes_written != (int) bufferLen)
        {
          LOG4CXX_FATAL(logger, "Wrong buffer len:" + to_string(bytes_written) + "!=" + to_string(bufferLen));
        }

      }
    }
    else
    {
      file = fopen(extractedName.c_str(), "wb");
      if (file)
      {
        size_t dwBytes = fwrite(szEntryBuffer, sizeof(char), bufferLen, file);
        fclose(file);
        if (dwBytes != bufferLen)
        {
          LOG4CXX_FATAL(logger, "Wrong buffer len:" + to_string(dwBytes) + "!=" + to_string(bufferLen));
        }
      }
    }

    free(szEntryBuffer);
    result = true;
  }

  return result;
}

bool Breeze::extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen)
{
  FILE *f;
  bool result = true;
  unsigned char *szEntryBuffer = nullptr;

  string archivedFilePath = mArchiveName + "/" + archivedFile;

  f = fopen(archivedFilePath.c_str(), "r");
  if (f)
  {
    unsigned char szBuffer[0x10000];
    size_t len = 0;
    int i = 0;
    size_t dwBytes = 1;

    while (dwBytes > 0)
    {
      dwBytes = fread(szBuffer, sizeof(char), sizeof(szBuffer), f);
      if (dwBytes > 0)
      {
        len = len + dwBytes;
        szEntryBuffer = (unsigned char *) realloc(szEntryBuffer, len);
        memcpy(szEntryBuffer + (i * sizeof(szBuffer)), szBuffer, dwBytes);
      }
    }
    i++;
    *bufferLen = len;
  }
  else
  {
    result = false;
  }

  *szEntryBufferPrt = szEntryBuffer;

  return result;
}

