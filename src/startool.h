//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//   Utility for Stratagus - A free fantasy real time strategy game engine
//
/**@name startool.h - Extract files from war archives. */
//
//      (c) Copyright 1999-2016 by Lutz Sammer, Nehal Mistry, Jimmy Salmon,
//                                 Pali Rohár and cybermind
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; version 2 dated June, 1991.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//      02111-1307, USA.
//

#ifndef _STARTOOL_H
#define _STARTOOL_H

/*----------------------------------------------------------------------------
--  General
----------------------------------------------------------------------------*/

#define VERSION "2.4.1" // Version of extractor startool

const char NameLine[] = "startool V" VERSION " for Stratagus (c) 2002-2021 by the Stratagus Project.\n";

/*----------------------------------------------------------------------------
--  Includes
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// C++
#include <iostream>
#include <string>

#ifdef _MSC_VER
#define strdup _strdup
#define DEBUG _DEBUG
#define PATH_MAX _MAX_PATH
#include <direct.h>
#include <io.h>
#else
#include <limits.h>
#include <unistd.h>
#endif
#include <ctype.h>
#include <png.h>

#include "Storm.h"

#ifndef __GNUC__
	#define __attribute__(args)  // Does nothing for non GNU CC
#endif

#ifndef O_BINARY
	#define O_BINARY 0
#endif

using namespace std;


//----------------------------------------------------------------------------
//  Config
//----------------------------------------------------------------------------


/**
**		Path the cursor files. (default=$DIR/graphic/ui/)
*/
#define CURSOR_PATH		"graphics/ui"

/**
**		Path the graphic files. (default=$DIR/graphic)
*/
#define GRAPHIC_PATH		"graphics"

/**
**		Path the sound files. (default=$DIR/sounds)
*/
#define SOUND_PATH		"sounds"

/**
**		Path the text files. (default=$DIR/texts)
*/
#define TEXT_PATH		"campaigns"





/**
**  Conversion control sturcture.
*/
typedef struct _control_ {
	int   Type;          /// Entry type
	int   Version;       /// Only in this version
	const char* File;    /// Save file
	const char* ArcFile;/// File name in list file
	int   Arg1;          /// Extra argument 1
	int   Arg2;          /// Extra argument 2
	int   Arg3;          /// Extra argument 3
	int   Arg4;          /// Extra argument 4
} Control;

/**
**  Possible entry types of archive file.
*/
enum _archive_type_ {
	S,    // Setup
	F,    // File                          (name)
	M,    // Map                           (name)
	T,    // Tileset                       (name,pal,mega,mini,map)
	R,    // RGB -> gimp                   (name,rgb)
	G,    // Graphics                      (name,pal,gfx)
	U,    // Uncompressed Graphics         (name,pal,gfu)
	I,    // Widgets                       (name,pal,gfu)
	N,    // Font                          (name,idx)
	W,    // Wav                           (name,wav)
	H,    // Pcx                           (name)
	E,    // Raw extract                   (name)
	V,    // Video                         (name,video)
	L,    // Campaign Levels
	Q,    // MPQ archive
	D     // Graphics in DDS format
};

#define __3 ,0,0,0
#define __4 ,0,0,0,0

#include "startool_mpq.h"
#include "startool_cd.h"
#include "startool_rm.h"

#endif // _STARTOOL_H
