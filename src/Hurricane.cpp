/*
 * Hurricane.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Hurricane.h"

// Sytsem
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Hurricane::Hurricane()
{

}

Hurricane::~Hurricane()
{

}

std::shared_ptr<DataChunk> Hurricane::extractDataChunk(const std::string &archivedFile)
{
  size_t bufferLen = 0;
  unsigned char *szEntryBufferPrt = nullptr;

  if (extractMemory(archivedFile, &szEntryBufferPrt, &bufferLen))
  {
    shared_ptr<DataChunk> data = make_shared<DataChunk>(&szEntryBufferPrt,
                                 bufferLen);
    return data;
  }

  return nullptr;
}

std::shared_ptr<std::istream> Hurricane::extractStream(const std::string &archivedFile)
{
  size_t bufferLen = 0;
  unsigned char *szEntryBufferPrt = nullptr;

  if (extractMemory(archivedFile, &szEntryBufferPrt, &bufferLen))
  {
    shared_ptr<stringstream> sstream = make_shared<stringstream>();

    sstream->write(reinterpret_cast<char*>(szEntryBufferPrt), bufferLen);

    return sstream;
  }

  return nullptr;
}

const std::string &Hurricane::getArchiveName() const
{
  return mArchiveName;
}
