/*
 * Storage.cpp
 *
 *      Author: Andreas Volz
 */

#include "Storage.h"

using namespace std;

Storage::Storage()
{

}

Storage::Storage(const char *datapath) :
  mDataPath(datapath)
{

}

Storage::Storage(const std::string &datapath) :
  mDataPath(datapath)
{

}

Storage::Storage(const std::string &datapath, const std::string &datatype) :
  mDataPath(datapath), mDataType(datatype)
{

}

Storage::Storage(const std::string &datapath, const std::string &datatype, const std::string &filename) :
  mDataPath(datapath), mDataType(datatype), mFilename(filename)
{

}

Storage::~Storage()
{

}

const std::string &Storage::getDataPath() const
{
  return mDataPath;
}

void Storage::setDataPath(const std::string &dataPath)
{
  this->mDataPath = dataPath;
}

const std::string &Storage::getDataType() const
{
  return mDataType;
}

void Storage::setDataType(const std::string &dataType)
{
  this->mDataType = dataType;
}

const std::string &Storage::getFilename() const
{
  return mFilename;
}

void Storage::setFilename(const std::string &filename)
{
  this->mFilename = filename;
}

std::string Storage::getFullPath() const
{
  string path;

  if (!getDataPath().empty())
  {
    path += getDataPath();
  }

  if (!getDataType().empty())
  {
    path += "/" + getDataType();
  }

  if (!getFilename().empty())
  {
    path += "/" + getFilename();
  }

  return path;
}

Storage Storage::operator()(std::string filename)
{
  Storage storage(*this);

  storage.setFilename(filename);

  return storage;
}
