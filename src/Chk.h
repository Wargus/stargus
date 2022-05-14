/*
 * Chk.h
 *
 *      Author: Andreas Volz
 */

#ifndef CHK_H_
#define CHK_H_

// Local
#include "WorldMap.h"
#include "Logger.h"
#include "Storage.h"
#include "Converter.h"

// System
#include <memory>

// Forward declarations
class Hurricane;

/**
 * For .chk files generate a combination of .smp and .sms file
 * The .smp and .sms files are Lua scripts and are executed by stargus/stratagus
 * The generated files describe the map, units, tiles, triggers - simply the map behavior
 *
 */
class Chk : public Converter
{
public:
  Chk(std::shared_ptr<Hurricane> hurricane);
  virtual ~Chk();

  void setUnitNames(const std::vector<std::string> &unitNames);

  virtual bool convert(const std::string &arcfile, Storage storage);

private:
  /**
   **	Load chk from buffer
   **
   **	@param chkdata	Buffer containing chk data
   **	@param len	Length of chk buffer
   **	@param map	The map
   */
  void loadFromBuffer(unsigned char *chkdata, int len);
  void ConvertChk(Storage storage, unsigned char *chkdata, int chklen);

  void SaveMap(Storage storage);

  void SaveSMS(Storage storage);
  void SaveTrigger(FILE *fd, Trigger *trigger);
  void SaveSMP(Storage storage);
  void FreeMap();

  Logger mLogger;
  WorldMap *map;
  std::vector<std::string> mUnitNames;
};

#endif /* CHK_H_ */
