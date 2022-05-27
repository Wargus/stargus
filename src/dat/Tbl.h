/*
 * Tbl.h
 *
 *      Author: Andreas Volz
 */

#ifndef STAT_TXT_TBL_H
#define STAT_TXT_TBL_H

// Local
#include "Logger.h"
#include "kaitai/file_tbl.h"

// System
#include <memory>

class TblEntry
{
public:
  TblEntry()
  {
    shortcut_pos = -1;
    shortcut = ' ';
  }
  std::string name1;
  std::string name2;
  std::string name3;
  int shortcut_pos;
  std::string shortcut;

  void removeSpaces()
  {
    size_t pos;
    while ((pos = name1.find("  ")) != std::string::npos)
    {
      name1 = name1.replace(pos, 2, " ");
    }

    while ((pos = name2.find("  ")) != std::string::npos)
    {
      name2 = name2.replace(pos, 2, " ");
    }

    while ((pos = name3.find("  ")) != std::string::npos)
    {
      name3 = name3.replace(pos, 2, " ");
    }
  }
};

class Tbl
{
public:
  Tbl();
  virtual ~Tbl();

  std::vector<TblEntry> convertFromStream(std::shared_ptr<kaitai::kstream> ks);

private:
  /**
   *  @return a UTF-8 string that has to be free()d after usage
   */
  char* iconvISO2UTF8(char *iso);

  Logger mLogger;
};

#endif /* STAT_TXT_TBL_H */
