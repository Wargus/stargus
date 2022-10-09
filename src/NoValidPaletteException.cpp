#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>
#include "NoValidPaletteException.h"

using namespace std;

const char *NoValidPaletteException::what() const throw()
{
  static string s;
  s = "Palette size doesn't fit to RGB, or RGBx/WPE or PCX2D: ";
  s += to_string(m_size);

  return static_cast <const char *>(s.c_str());
}
