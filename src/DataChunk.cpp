/*
 * DataChunk.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "DataChunk.h"
#include "Logger.h"

// System
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

static Logger logger = Logger("startool.DataChunk");

DataChunk::DataChunk() :
  mData(nullptr), mSize(0)
{

}

DataChunk::DataChunk(const DataChunk &datachunk) :
  mData(nullptr), mSize(0)
{
  addData(datachunk.mData, datachunk.mSize);
}

DataChunk::DataChunk(unsigned char **data, const size_t size)
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

void DataChunk::replaceData(unsigned char *data, const size_t size, size_t pos)
{
  size_t new_size = pos * sizeof(unsigned char) + size * sizeof(unsigned char);
  if (new_size > mSize)
  {
    mData = (unsigned char *) realloc(mData, new_size);
    mSize = new_size;
  }
  memcpy(mData + pos * sizeof(unsigned char), data, size);
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

bool DataChunk::write(const std::string &filename)
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
    LOG4CXX_ERROR(logger, string("Couldn't write in: ") + filename);
    result = false;
  }

  return result;
}

bool DataChunk::read(const std::string &filename)
{
  streampos size;
  char *memblock;
  bool result = false;

  ifstream file(filename, ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read(memblock, size);

    if(file)
    {
      addData(reinterpret_cast<unsigned char*>(memblock), size);
      result = true;
    }
    else
    {
      LOG4CXX_ERROR(logger, string("Couldn't read from: ") + filename);
    }

    file.close();

    delete[] memblock;
  }

  return result;
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
    LOG4CXX_WARN(logger, "'pos' bigger then data: " + to_string(pos) + " < " + to_string(mSize));
  }

  return ret;
}
