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
#include <vector>

class DataChunk
{
public:
  /**
   * Create a new DataChunk with empty size
   */
  DataChunk();

  /**
   * Create a new DataChunk from existing data on heap and give DataChunk responsibility about freeing that memory
   * (works like a smart pointer)
   */
  DataChunk(unsigned char **data, const size_t size);

  virtual ~DataChunk();

  /**
   * Add a *copy* of the provided data to internal data structure. This doesn't replace the data but concatenates it.
   */
  void addData(unsigned char *data, const size_t size);

  /**
   * @return a pointer to the raw data inside the DataChunk. Modifying the content changes the data itself.
   */
  unsigned char* getDataPointer() const;

  /**
   * @return a vector with a copy of the data
   */
  std::vector<unsigned char> getUCharVector() const;

  /**
   * @return a vector with a copy of the data
   */
  std::vector<char> getCharVector() const;

  /**
   * @return the number of elements in the container
   */
  size_t getSize() const;

  /**
   * Write the content as binary steam into filename
   *
   * @return true if succeed
   */
  bool write(const std::string filename);

  /**
   * Make a full copy of the Object
   *
   * @return a new Object with a complete copy of the data
   */
  DataChunk* copy();

  /**
   * Access to a specific element
   *
   * @pos which element to access (if you give a size bigger then elements you get a log warning, buthing bad happens)
   *
   * @return the element to access
   */
  unsigned char at(size_t pos);

private:
  Logger mLogger;
  unsigned char *mData;
  size_t mSize;
};

#endif /* DATACHUNK_H_ */
