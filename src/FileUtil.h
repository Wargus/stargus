/*
 * FileUtil.h
 *
 *      Author: Andreas Volz
 */

#ifndef FILEUTIL_H_
#define FILEUTIL_H_

// project
#include "platform.h"

// system
#include <string>
#include <stdlib.h>
#include <string.h>

/**
 * Check if path exists - DOESN'T create any directories/files
 */
bool FileExists(const std::string &filename);

/**
 *  Check if path exists, if not make all directories.
 */
void CheckPath(const char *path);

/**
 *  Check if path exists, if not make all directories.
 */
void CheckPath(const std::string &path);

#endif /* FILEUTIL_H_ */
