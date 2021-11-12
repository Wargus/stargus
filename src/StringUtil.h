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

/**
 * create std::string from any number
 */
template <typename T>
std::string toString(const T &thing, int w = 0, int p = 0)
{
  std::ostringstream os;
  os << std::setw(w) << std::setprecision(p) << thing;
  return os.str();
}


#endif /* STRINGUTIL_H_ */
