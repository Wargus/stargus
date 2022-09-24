/*
 * TblEntry.cpp
 *
 *      Author: Andreas Volz
 */

#include "TblEntry.h"

using namespace std;

namespace dat
{

TblEntry::TblEntry()
{
  shortcut_pos = -1;
  shortcut = ' ';
}

TblEntry::~TblEntry()
{

}

void TblEntry::removeSpaces()
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

} /* namespace dat */
