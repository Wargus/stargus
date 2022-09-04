/*
 * FileUtil.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "FileUtil.h"
// system
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

/**
 **  Check if path exists - DOESN'T create any directories/files
 */
bool FileExists(const std::string &filename)
{
  struct stat buffer;
  return stat(filename.c_str(), &buffer) == 0 ? true : false;
}

/**
 *  Check if path exists, if not make all directories.
 */
void CheckPath(const std::string &path)
{
  CheckPath(path.c_str());
}

/**
 *  Check if path exists, if not make all directories.
 */
void CheckPath(const char *path)
{
  char *cp = NULL;
  char *s = NULL;

  cp = platform::strdup(path);

  s = strrchr(cp, '/');
  if (s)
  {
    *s = '\0';  // remove file
    s = cp;
    for (;;)
    {
      // make each path element
      s = strchr(s, '/');
      if (s)
      {
        *s = '\0';
      }

      platform::mkdir(cp, 0777);

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
