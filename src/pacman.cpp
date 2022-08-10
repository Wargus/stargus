#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// system
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

// project
#include "pacman.h"
#include "FileNotFoundException.h"
#include "platform.h"

using namespace std;

namespace pacman {

const std::string searchFile(const std::string &data)
{
  vector <string> name_vector;

#ifdef HAVE_CONFIG_H
  // first search in the package directory (e.g. /usr/share/<package>
  name_vector.push_back(string(PACKAGE_DATA_DIR));

  // if this fails it search the data in a relative position
  name_vector.push_back(data);

  // and if this still fails we assume the developer case and search the data in absolute source folder
  name_vector.push_back(string(PACKAGE_SOURCE_DIR));
#endif

  const string &file = statFile(name_vector);

  if (file.empty())
  {
    throw FileNotFoundException(data);
  }

  return file;
}

const std::string searchDir(const std::string &data)
{
  const string &file = searchFile(data);

  fs::path p(file);

  return p.remove_filename();
}

const std::string statFile(std::vector <std::string> &name_vector)
{
  struct stat buf;

  for (unsigned int i = 0; i < name_vector.size(); i++)
  {
    string &try_name = name_vector[i];

    bool found = !(stat(try_name.c_str(), &buf));
    //cout << "try_name: " << try_name << endl;

    if (found)
    {
      return try_name;
    }
  }

  return "";
}

}

