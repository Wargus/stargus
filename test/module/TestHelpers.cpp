/*
 * TestHelpers.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "TestHelpers.h"
#include "FileUtil.h"

// system
#include <cstdio>
#include <fstream>

using namespace std;

const std::string getStringFromFile(const std::string &file)
{
  string line;
  string filecontent;
  ifstream readfile(file);

  if (readfile.is_open())
  {
    while (getline(readfile, line))
    {
      filecontent += line;
    }
    readfile.close();
  }

  return filecontent;
}

bool compareFiles(const std::string &file1, const std::string &file2)
{
  if(!FileExists(file1) || !FileExists(file2))
  {
    return false;
  }

  string file1_content = getStringFromFile(file1);
  string file2_content = getStringFromFile(file2);

  if(file1_content.length() != file2_content.length())
  {
    return false;
  }
  else
  {
      const int ret = std::memcmp(file1_content.c_str(), file2_content.c_str(), file1_content.length());
      if(ret != 0)
      {
        return false;
      }
  }

  return true;
}
