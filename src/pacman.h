#ifndef PACMAN_H
#define PACMAN_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>
#include <vector>

namespace pacman {

// public search functions
const std::string searchDir(const std::string &data);
const std::string searchFile(const std::string &data);

// helper function
const std::string statFile(std::vector <std::string> &name_vector);

}

#endif // PACMAN_H
