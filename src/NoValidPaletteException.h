#ifndef NOVALIDPALETTEEXCEPTION_H
#define NOVALIDPALETTEEXCEPTION_H

#include <exception>

class NoValidPaletteException : public std::exception
{
public:
  NoValidPaletteException(const size_t size) : m_size(size) {}

  const char *what() const throw();

private:
  const int m_size;
};

#endif // NOVALIDPALETTEEXCEPTION_H
