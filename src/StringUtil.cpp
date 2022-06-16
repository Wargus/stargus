/*
 * stringUtil.cpp
 *
 *      Author: Andreas Volz
 */

#include "StringUtil.h"
#include "Logger.h"
#include <algorithm>

#include <iconv.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

static Logger logger = Logger("startool.StringUtil");

int replaceString(const string &match, const string &replace, string &str)
{
  int i = 0;

  if (str.find(match) == std::string::npos)
    return false;

  std::string::size_type start = 0;


  while ((start = str.find(match)) != std::string::npos)
  {
    str.replace(start, match.size(), replace);

    i++;
  }

  return i;
}

bool hasFileEnding(const std::string &filename, const std::string &ending)
{
  const size_t loc = filename.find(ending, filename.length() - ending.length());

  if (loc != string::npos)
  {
    return true;
  }

  return false;
}

std::string cutFileEnding(std::string filename, const std::string &ending)
{
  if (ending == "")
  {
    const size_t loc = filename.find_last_of('.', filename.length());

    if (loc != string::npos)
    {
      filename.erase(loc);
      return filename;
    }
  }
  else
  {
    const size_t loc = filename.find(ending, filename.length() - ending.length());

    if (loc != string::npos)
    {
      filename.erase(loc);
      return filename;
    }
  }

  return filename;
}

std::string to_lower(std::string line)
{
  std::for_each(line.begin(), line.end(), [](char & c)
  {
      c = ::tolower(c);
  });

  return line;
}

// TODO: check if this helps to detect encoding https://github.com/freedesktop/uchardet
char *iconvISO2UTF8(char *iso)
{
  char buf[1024] = { '\0' };
  iconv_t iconvDesc = iconv_open("UTF-8//TRANSLIT//IGNORE", "ISO-8859-1");

  if (iconvDesc == (iconv_t) -1)
  {
    /* Something went wrong.  */
    if (errno == EINVAL)
    {
      snprintf(buf, sizeof(buf), "conversion from '%s' to '%s' not available",
               "ISO-8859-1", "UTF-8");
      LOG4CXX_ERROR(logger, buf);
    }
    else
    {
      snprintf(buf, sizeof(buf), "LibIcon initialization failure");
    }

    return NULL;
  }

  size_t iconv_value;
  char *utf8;
  size_t len;
  size_t utf8len;
  char *utf8start;

  len = strlen(iso);
  if (!len)
  {
    snprintf(buf, sizeof(buf), "iconvISO2UTF8: input String is empty.");
    LOG4CXX_ERROR(logger, buf);
    return NULL;
  }

  /* Assign enough space to put the UTF-8. */
  utf8len = 2 * len;
  utf8 = (char *) calloc(utf8len, sizeof(char));
  if (!utf8)
  {
    snprintf(buf, sizeof(buf), "iconvISO2UTF8: Calloc failed.");
    LOG4CXX_ERROR(logger, buf);
    return NULL;
  }
  /* Keep track of the variables. */
  utf8start = utf8;

#ifdef _MSC_VER
  iconv_value = iconv(iconvDesc, const_cast<const char**>(&iso), &len, &utf8, &utf8len);
#else
  iconv_value = iconv(iconvDesc, &iso, &len, &utf8, &utf8len);
#endif
  /* Handle failures. */
  if (iconv_value == (size_t) -1)
  {
    switch (errno)
    {
    /* See "man 3 iconv" for an explanation. */
    case EILSEQ:
      snprintf(buf, sizeof(buf),
               "iconv failed: Invalid multibyte sequence, in string '%s', length %d, out string '%s', length %d\n",
               iso, (int) len, utf8start, (int) utf8len);
      LOG4CXX_ERROR(logger, buf);
      break;
    case EINVAL:
      snprintf(buf, sizeof(buf),
               "iconv failed: Incomplete multibyte sequence, in string '%s', length %d, out string '%s', length %d\n",
               iso, (int) len, utf8start, (int) utf8len);
      LOG4CXX_ERROR(logger, buf);
      break;
    case E2BIG:
      snprintf(buf, sizeof(buf),
               "iconv failed: No more room, in string '%s', length %d, out string '%s', length %d\n",
               iso, (int) len, utf8start, (int) utf8len);
      LOG4CXX_ERROR(logger, buf);
      break;
    default:
      snprintf(buf, sizeof(buf),
               "iconv failed, in string '%s', length %d, out string '%s', length %d\n",
               iso, (int) len, utf8start, (int) utf8len);
      LOG4CXX_ERROR(logger, buf);
    }
    return NULL;
  }

  if (iconv_close(iconvDesc) != 0)
  {
    snprintf(buf, sizeof(buf), "libicon close failed: %s", strerror(errno));
    LOG4CXX_ERROR(logger, buf);
  }

  return utf8start;

}
