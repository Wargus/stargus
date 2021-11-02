/*
 * FileUtil.h
 *
 *  Created on: 02.11.2021
 *      Author: Andreas Volz <avolz.mobile@gmail.com>
 */

#ifndef FILEUTIL_H_
#define FILEUTIL_H_

// C++
#include <string>

// C
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// Function Prototypes
bool FileExists(const std::string &filename);
void CheckPath(const char* path);


#endif /* FILEUTIL_H_ */
