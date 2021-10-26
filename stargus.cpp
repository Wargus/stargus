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

#define GAME_NAME "Stargus"
#define GAME_CD "Starcraft CD or installation stardat.mpq or starcraft.mpq file"
#define GAME_CD_FILE_PATTERNS "install.exe", "Install.exe", "stardat.mpq", "StarDat.mpq", "starcraft.mpq", "StarCraft.mpq"
#define GAME "stargus"
#define EXTRACTOR_TOOL "startool"
#define EXTRACTOR_ARGS {}
#define CHECK_EXTRACTED_VERSION 1
// contrib has fog.png.
// TODO: There's a bug in the lua files searching fog.png in the wrong path.
// I have no time to search and fix that right now, but once that's done, there's
// no need to copy it to two locations.
#define CONTRIB_DIRECTORIES { "mpqlist.txt", "mpqlist.txt", \
			      "contrib", "graphics/tilesets", \
			      "contrib", "tilesets", \
			      "scripts", "scripts", NULL }

const char* SRC_PATH() { return __FILE__; }

#include "stratagus-game-launcher.h"
