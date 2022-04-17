/*
 * Storage.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "Storage.h"

// system
#include <iostream>

using namespace std;

Storage::Storage()
{

}

Storage::Storage(const char *filename) :
  mFilename(filename)
{

}

Storage::Storage(const std::string &filename) :
  mFilename(filename)
{

}

Storage::~Storage()
{

}

const std::string& Storage::getDataPath() const
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
  string path = getDataPath();

  if(!path.empty())
  {
    path += "/";
  }

  path += getDataType();

  if(!path.empty())
  {
    path += "/";
  }

  path += getFilename();

  return path;
}

Storage Storage::operator()(std::string filename)
{
  Storage storage(*this);

  storage.setFilename(filename);

  return storage;
}

/*std::string Storage::operator+(const Storage& storage)
{
  return getFullPath();
}*/

std::string Storage::operator=(const Storage& storage)
{
  return getFullPath();
}


std::string operator+(const std::string &str, const Storage& storage)
{
  return str + storage.getFullPath();
}

std::string operator+(const Storage& storage, const std::string &str)
{
  return storage.getFullPath() + str;
}

std::string operator+(const char *str, const Storage& storage)
{
  return str + storage.getFullPath();
}

std::string operator+(const Storage& storage, const char *str)
{
  return storage.getFullPath() + str;
}
