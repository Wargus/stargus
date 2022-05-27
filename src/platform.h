/*
 * platform.h
 *
 *      Author: Andreas Volz
 */

#ifndef PLATFORM_H
#define PLATFORM_H

// filesystem ->
#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
error "Missing the <filesystem> header."
#endif
// <- filesystem

#ifdef _MSC_VER
#define strdup _strdup
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

#include <string>

namespace platform
{

int remove(const std::string &pathname);

int remove_all(const std::string &pathname);

int unlink(const std::string &pathname);

} /* namespace platform */

#endif /* PLATFORM_H */
