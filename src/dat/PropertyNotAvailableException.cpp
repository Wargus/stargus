/*
 * PropertyNotAvailableException.cpp
 *
 *      Author: Andreas Volz
 */

#include "PropertyNotAvailableException.h"

using namespace std;

namespace dat {

const char *PropertyNotAvailableException::what() const throw()
{
  static string s;
  s = "Property '";
  s += m_property;
  s += "' not existing for parent: ";
  s += to_string(m_parent_id);

  return static_cast <const char *>(s.c_str());
}

} /* namespace dat */
