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

  // TODO: this was a bad decision: make this functional access to add some logging functions...
  std::string name1;
  std::string name2;
  std::string name3;
  int shortcut_pos;
  std::string shortcut;

  void removeSpaces();

};

} /* namespace dat */

#endif /* TBLENTRY_H */
