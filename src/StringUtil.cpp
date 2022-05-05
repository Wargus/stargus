/*
 * stringUtil.cpp
 *
 *      Author: Andreas Volz
 */

#include "StringUtil.h"
#include <algorithm>

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

bool hasFileEnding(const std::string &filename, const std::string &ending)
{
  const size_t loc = filename.find(ending, filename.length() - ending.length());

  if (loc != string::npos)
  {
    return true;
  }

  return false;
}

std::string cutFileEnding(std::string filename, const std::string &ending)
{
  if (ending == "")
  {
    const size_t loc = filename.find_last_of('.', filename.length());

    if (loc != string::npos)
    {
      filename.erase(loc);
      return filename;
    }
  }
  else
  {
    const size_t loc = filename.find(ending, filename.length() - ending.length());

    if (loc != string::npos)
    {
      filename.erase(loc);
      return filename;
    }
  }

  return filename;
}

std::string to_lower(std::string line)
{
  std::for_each(line.begin(), line.end(), [](char & c)
  {
      c = ::tolower(c);
  });

  return line;
}
