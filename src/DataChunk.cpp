/*
 * DataChunk.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "DataChunk.h"

// System
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

DataChunk::DataChunk() :
  mLogger("startool.DataChunk"), mData(nullptr), mSize(0)
{

}

DataChunk::DataChunk(unsigned char **data, const size_t size) :
  mLogger("startool.DataChunk")
{
  mData = *data;
  mSize = size;
}

DataChunk::~DataChunk()
{
  free(mData);
  mData = nullptr;
}

void DataChunk::addData(unsigned char *data, const size_t size)
{
  mData = (unsigned char *) realloc(mData, mSize * sizeof(unsigned char) + size * sizeof(unsigned char));
  memcpy(mData + mSize * sizeof(unsigned char), data, size);
  mSize += size;
}

unsigned char *DataChunk::getDataPointer() const
{
  return mData;
}

size_t DataChunk::getSize() const
{
  return mSize;
}

std::vector<unsigned char> DataChunk::getUCharVector() const
{
  return std::vector<unsigned char>(mData, mData + mSize);
}

std::vector<char> DataChunk::getCharVector() const
{
  return std::vector<char>(mData, mData + mSize);
}

bool DataChunk::write(const std::string filename)
{
  bool result = true;

  ofstream wf(filename, ios::out | ios::binary);

  if (wf)
  {
    for (size_t i = 0; i < mSize; i++)
    {
      wf.write((char *) &mData[i], sizeof(unsigned char));
    }
    wf.close();
  }
  else
  {
    LOG4CXX_DEBUG(mLogger, string("Couldn't write in: ") + filename);
    result = false;
  }

  return result;
}

DataChunk *DataChunk::copy()
{
  return new DataChunk(&mData, mSize);
}

unsigned char DataChunk::at(size_t pos)
{
  unsigned char ret = '\0';

  if (pos < mSize)
  {
    ret = mData[pos];
  }
  else
  {
    LOG4CXX_WARN(mLogger, "'pos' bigger then data: " + pos);
  }

  return ret;
}
