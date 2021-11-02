/*
 * FileUtil.h
 *
 *  Created on: 02.11.2021
 *      Author: andreas
 */

#ifndef FILEUTIL_H_
#define FILEUTIL_H_

// C++
#include <string>

// C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// Function Prototypes
bool FileExists(const std::string &filename);
void CheckPath(const char* path);


#endif /* FILEUTIL_H_ */
