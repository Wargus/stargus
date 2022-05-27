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

// Function Prototypes
bool FileExists(const std::string &filename);
void CheckPath(const char *path);
void CheckPath(const std::string &path);

#endif /* FILEUTIL_H_ */
