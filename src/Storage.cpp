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

const std::string& Storage::getDataPath()
{
  return mDataPath;
}

void Storage::setDataPath(const std::string &dataPath)
{
  this->mDataPath = dataPath;
}

const std::string &Storage::getDataType()
{
  return mDataType;
}

void Storage::setDataType(const std::string &dataType)
{
  this->mDataType = dataType;
}

const std::string &Storage::getFilename()
{
  return mFilename;
}

void Storage::setFilename(const std::string &filename)
{
  this->mFilename = filename;
}

std::string Storage::getFullPath()
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
