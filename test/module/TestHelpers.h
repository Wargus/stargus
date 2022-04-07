/*
 * TestHelpers.h
 *
 *      Author: Andreas Volz
 */

#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <string>
#include <cstring>

const std::string getStringFromFile(const std::string &file);

bool compareFiles(const std::string &file1, const std::string &file2);

#endif /* TESTHELPERS_H */
