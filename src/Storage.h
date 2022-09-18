/*
 * Storage.h
 *
 *      Author: Andreas Volz
 */

#ifndef STORAGE_H_
#define STORAGE_H_

#include <string>

class Storage
{
public:
  Storage();

  Storage(const char *filename);

  Storage(const std::string &filename);

  virtual ~Storage();

  const std::string& getDataPath() const;

  void setDataPath(const std::string &dataPath);

  const std::string& getDataType() const;

  void setDataType(const std::string &dataType);

  const std::string& getFilename() const;

  void setFilename(const std::string &filename);

  std::string getFullPath() const;

  std::string getRelativePath() const;

  Storage operator()(std::string filename);

  std::string operator=(const Storage& storage);

  operator std::string() const;

private:
  std::string mDataPath;
  std::string mDataType;
  std::string mFilename;

};

std::string operator+(const std::string &str, const Storage& storage);

std::string operator+(const char *str, const Storage& storage);

std::string operator+(const Storage& storage, const std::string &str);

std::string operator+(const Storage& storage, const char *str);

#endif /* STORAGE_H_ */
