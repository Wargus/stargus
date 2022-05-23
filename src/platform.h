/*
 * platform.h
 *
 *      Author: Andreas Volz
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
error "Missing the <filesystem> header."
#endif

#include <string>

namespace platform
{

int remove(const std::string &pathname);

int remove_all(const std::string &pathname);

} /* namespace platform */

#endif /* PLATFORM_H */
