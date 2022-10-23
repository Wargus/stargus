/*
 * PropertyNotAvailableException.h
 *
 *      Author: Andreas Volz
 */

#ifndef PROPERTYNOTAVAILABLEEXCEPTION_H
#define PROPERTYNOTAVAILABLEEXCEPTION_H

#include <string>

namespace dat {

/**
 * This Exception is thrown if a property isn't available for a specific item, but requested by the caller
 */
class PropertyNotAvailableException : public std::exception
{
public:
  PropertyNotAvailableException(int parent_id, const std::string &property) :
    m_parent_id(parent_id),
    m_property(property)
  {}

  virtual ~PropertyNotAvailableException() throw() {}

  const char *what() const throw();

private:
  int m_parent_id;
  std::string m_property;
};

} /* namespace dat */

#endif /* PROPERTYNOTAVAILABLEEXCEPTION_H */
