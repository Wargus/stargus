#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>
#include "NoValidPaletteException.h"

using namespace std;

const char *NoValidPaletteException::what() const throw()
{
  static string s;
  s = "Palette size doesn't fit to RGB (256*3 bytes) or RGBx/WPE (256*4 bytes): ";
  s += to_string(m_size);

  return static_cast <const char *>(s.c_str());
}
