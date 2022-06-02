/*
 stargus.c - Start game engine Stratagus with Stargus data
 Copyright (C) 2010-2012  Pali Rohár <pali.rohar@gmail.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

using namespace std;

#define GAME_NAME "Stargus"
#define GAME_CD "Starcraft CD or installation stardat.mpq or starcraft.mpq file"
#define GAME_CD_FILE_PATTERNS "install.exe", "Install.exe", "stardat.mpq", "StarDat.mpq", "starcraft.mpq", "StarCraft.mpq"
#define GAME "stargus"
#define EXTRACTOR_TOOL "startool"
#define EXTRACTOR_ARGS {"-v", NULL}
#define CHECK_EXTRACTED_VERSION 1

// configure here which files/directories will be copied from stargus (e.g. contrib)
#define CONTRIB_DIRECTORIES { "mpqlist.txt", "mpqlist.txt", \
			      "contrib/fog.png", "graphics/tilesets/fog.png", \
			      "contrib/transparent.png", "graphics/ui/transparent.png", \
			      "scripts", "scripts", NULL }

const char *SRC_PATH()
{
  std::cout << "sourcedir:" << SOURCE_DIR << std::endl;
  return SOURCE_DIR;
}

// I still have hope some far day someone will fix this annoying warnings... ->
#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wformat-overflow="
#endif
#include "stratagus-game-launcher.h"
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif
// <-
