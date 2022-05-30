/*
 * platform.h
 *
 *      Author: Andreas Volz
 */

#ifndef PLATFORM_H
#define PLATFORM_H



#include <string>


namespace platform
{

int remove(const std::string &pathname);

int remove_all(const std::string &pathname);

int unlink(const std::string &pathname);

char *strdup(const char *s);

#if defined(_MSC_VER) || defined(WIN32)
typedef int mode_t;
#endif

int mkdir(const std::string &pathname, mode_t mode = 0);

} /* namespace platform */

#endif /* PLATFORM_H */
