/*
 * platform.cpp
 *
 *      Author: Andreas Volz
 */

#include "platform.h"

#ifdef _MSC_VER
#define DEBUG _DEBUG
#define PATH_MAX _MAX_PATH
#include <direct.h>
#include <io.h>
#define dirname(x) PathRemoveFileSpec(x); if (x[strlen(x) - 1] == '\\') x[strlen(x) - 1] = '\0'
#else
#include <libgen.h>
#include <limits.h>
#include <unistd.h>
#endif

#ifdef _MSC_VER
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#endif

#include <sys/stat.h>
#include <sys/types.h>


#include <cstring>

namespace platform
{

int unlink(const std::string &pathname)
{
#ifdef _MSC_VER
  return ::_unlink(pathname.c_str());
#else
  return ::unlink(pathname.c_str());
#endif
}

char *strdup(const char *s)
{
#ifdef WIN32
  return ::_strdup(s);
#else
  return ::strdup(s);
#endif
}

int mkdir(const std::string &pathname, mode_t mode)
{
#if defined(_MSC_VER) || defined(WIN32)
  return ::_mkdir(pathname.c_str());
#else
  return ::mkdir(pathname.c_str(), mode);
#endif
}

} /* namespace platform */
