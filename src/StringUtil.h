/*
 * stringUtil.h
 *
 *      Author: Andreas Volz
 */

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

// C++
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

// some functions that are very usefull for writing files
bool hasFileEnding(const std::string &filename, const std::string &ending);
std::string cutFileEnding(std::string filename, const std::string &ending = "");

/**
 * TODO: Does this modify the input string? Check and document
 *
 * @return the lower case string variant
 */
std::string to_lower(std::string line);

/**
 * An function to replace occurences of substrings in a bigger string. Very basic function without regex.
 * @param match This is the string that is matched to replace.
 * @param replace The string that replaces all found match strings.
 * @param str The string that is matched and replaced.
 *
 * @return number of replaced strings
 */
int replaceString(const std::string &match, const std::string &replace, std::string &str);

/**
 * A helper to convert text to UTF-8.
 *
 * @return a UTF-8 string that has to be free()d after usage
 */
char* iconvISO2UTF8(char *iso);

/**
 * print Vector on std::cout
 */
template<typename T>
void printVector(std::vector<T> iv)
{
  std::cout << "[";
  for (unsigned i = 0; i < iv.size(); i++)
  {
    std::cout << iv[i];
    if (i < iv.size() - 1)
      std::cout << ",";
  }
  std::cout << "]" << std::endl;
}


#endif /* STRINGUTIL_H_ */
