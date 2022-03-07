/*
 * DataChunk.h
 *
 *      Author: Andreas Volz
 */

#ifndef DATACHUNK_H_
#define DATACHUNK_H_

// Local
#include "Logger.h"

// System
#include <stdlib.h>
#include <string>

class DataChunk
{
public:
	/**
	 * Create a new DataChunk with empty size
	 */
	DataChunk();

	/**
	 * Create a new DataChunk and give DataChunk responsibility about freeing that memory
	 */
	DataChunk(unsigned char **data, const size_t size);

	virtual ~DataChunk();

	/**
	 * Add a *copy* of the provided data to internal data structure. This doesn't replace the data but concatenates it.
	 */
	void addData(unsigned char *data, const size_t size);

	unsigned char *getDataPointer() const;

	std::vector<unsigned char> getUCharVector() const;

	std::vector<char> getCharVector() const;

	size_t getSize() const;

	bool write(const std::string filename);

private:
	Logger mLogger;
	unsigned char *mData;
	size_t mSize;
};

#endif /* DATACHUNK_H_ */
