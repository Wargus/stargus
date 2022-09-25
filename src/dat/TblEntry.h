/*
 * TblEntry.h
 *
 *      Author: Andreas Volz
 */

#ifndef TBLENTRY_H
#define TBLENTRY_H

// system
#include <string>

namespace dat
{

class TblEntry
{
public:
  TblEntry();
  virtual ~TblEntry();

  std::string name1();
  std::string name2();
  std::string name3();
  int shortcut_pos();
  std::string shortcut();


private:
  std::string m_name1;
  std::string m_name2;
  std::string m_name3;
  int m_shortcut_pos;
  std::string m_shortcut;

  friend class Tbl;
};

} /* namespace dat */

#endif /* TBLENTRY_H */
