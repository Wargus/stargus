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

DataChunk::DataChunk()
: mData(nullptr),
  mSize(0)
{

}

DataChunk::DataChunk(unsigned char **data, const size_t size)
{
	mData = *data;
	mSize = size;
}

DataChunk::~DataChunk()
{
	free(mData);
}

void DataChunk::addData(unsigned char *data, const size_t size)
{
	mData  = (unsigned char*) realloc(mData, mSize * sizeof(unsigned char) + size * sizeof(unsigned char));
	memcpy(mData + mSize * sizeof(unsigned char), data, size);
}

unsigned char *DataChunk::getDataPointer() const
{
	return mData;
}

size_t DataChunk::getSize() const
{
	return mSize;
}
