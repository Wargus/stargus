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

  Storage(const char *datapath);

  Storage(const std::string &datapath);

  Storage(const std::string &datapath, const std::string &datatype);

  Storage(const std::string &datapath, const std::string &datatype, const std::string &filename);

  virtual ~Storage();

  const std::string& getDataPath() const;

  void setDataPath(const std::string &dataPath);

  const std::string& getDataType() const;

  void setDataType(const std::string &dataType);

  const std::string& getFilename() const;

  void setFilename(const std::string &filename);

  std::string getFullPath() const;

  Storage operator()(std::string filename);

private:
  std::string mDataPath;
  std::string mDataType;
  std::string mFilename;

};

#endif /* STORAGE_H_ */
