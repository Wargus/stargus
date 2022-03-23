/*
 * FileUtil.cpp
 *
 *  Created on: 02.11.2021
 *      Author: Andreas Volz
 */

#include "FileUtil.h"

using namespace std;

/**
 **  Check if path exists - DOESN'T create any directories/files
 */
bool FileExists(const std::string &filename)
{
  struct stat buffer;
  return stat(filename.c_str(), &buffer) == 0 ? true : false;
}

void CheckPath(const std::string &path)
{
  CheckPath(path.c_str());
}

/**
 **  Check if path exists, if not make all directories.
 */
void CheckPath(const char *path)
{
  char *cp = NULL;
  char *s = NULL;

#ifdef WIN32
	cp = _strdup(path);
#else
  cp = strdup(path);
#endif
  s = strrchr(cp, '/');
  if (s)
  {
    *s = '\0';  // remove file
    s = cp;
    for (;;)
    {  // make each path element
      s = strchr(s, '/');
      if (s)
      {
        *s = '\0';
      }
#if defined(_MSC_VER) || defined(WIN32)
			_mkdir(cp);
#else
      mkdir(cp, 0777);
#endif
      if (s)
      {
        *s++ = '/';
      }
      else
      {
        break;
      }
    }
  }
  free(cp);
}
