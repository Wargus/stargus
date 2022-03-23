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

/**
 * create std::string from any number
 */
template<typename T>
std::string toString(const T &thing, int w = 0, int p = 0)
{
  std::ostringstream os;
  os << std::setw(w) << std::setprecision(p) << thing;
  return os.str();
}

#endif /* STRINGUTIL_H_ */
