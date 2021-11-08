/*
 * Hurricane.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Hurricane.h"

// Sytsem
#include <string>

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
	unsigned char *szEntryBufferPrt;

	if(extractMemory(archivedFile, &szEntryBufferPrt, &bufferLen))
	{
		shared_ptr<DataChunk> data = make_shared<DataChunk>(&szEntryBufferPrt, bufferLen);
		return data;
	}
	return nullptr;
}
