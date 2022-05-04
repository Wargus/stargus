/*
 * stringUtil.cpp
 *
 *      Author: Andreas Volz
 */

#include "StringUtil.h"

using namespace std;

int replaceString(const string &match, const string &replace, string &str)
{
  int i = 0;

  if (str.find(match) == std::string::npos)
    return false;

  std::string::size_type start = 0;


  while ((start = str.find(match)) != std::string::npos)
  {
    str.replace(start, match.size(), replace);

    i++;
  }

  return i;
}
