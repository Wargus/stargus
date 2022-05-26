/*
 * platform.cpp
 *
 *      Author: Andreas Volz
 */

#include "platform.h"

namespace platform
{

int remove(const std::string &pathname)
{
  return fs::remove(pathname);
}

int remove_all(const std::string &pathname)
{
  return fs::remove_all(pathname);
}

int unlink(const std::string &pathname)
{
#ifdef _MSC_VER
  return _unlink(pathname.c_str());
#else
  return unlink(pathname.c_str());
#endif
}

} /* namespace platform */
