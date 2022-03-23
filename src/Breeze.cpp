/*
 * Breeze.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Breeze.h"

// System
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

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

// TODO 'compress' doesn't work!!
bool Breeze::extractFile(const std::string &archivedFile,
    const std::string &extractedName, bool compress)
{
  unsigned char *szEntryBuffer = nullptr;
  size_t bufferLen = 0;
  bool result = false;

  if (extractMemory(archivedFile, &szEntryBuffer, &bufferLen))
  {
    string extractedNamePath = mArchiveName + "/" + extractedName;
    FILE *f = fopen(extractedNamePath.c_str(), "w");
    if (f)
    {
      /*size_t dwBytes = */fwrite(szEntryBuffer, sizeof(char), bufferLen, f);
      // TODO error handling in case open/write fails

      free(szEntryBuffer);
      result = true;
    }
  }

  return result;
}

bool Breeze::extractMemory(const std::string &archivedFile,
    unsigned char **szEntryBufferPrt, size_t *bufferLen)
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
        szEntryBuffer = (unsigned char*) realloc(szEntryBuffer, len);
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

