#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>
#include "FileNotFoundException.h"

using namespace std;

const char *FileNotFoundException::what() const throw()
{
  static string s;
  s = "File not found: '";
  s += txt;
  s += "'.";

  return static_cast <const char *>(s.c_str());
}
