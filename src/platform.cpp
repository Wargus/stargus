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

} /* namespace platform */
