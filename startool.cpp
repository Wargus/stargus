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
/**@name startool.c - Extract files from star archives. */
//
//      (c) Copyright 2002-2007 by Jimmy Salmon
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
//      $Id$

//@{

/*----------------------------------------------------------------------------
--  General
----------------------------------------------------------------------------*/

#define VERSION "1.0" // Version of extractor wartool

const char NameLine[] = "startool V" VERSION " for Stratagus (c) 2002-2010 by the Stratagus Project.\n"\
"  Written by Lutz Sammer, Nehal Mistry, and Jimmy Salmon and Pali Rohar.\n"\
"  https://launchpad.net/stargus";

/*----------------------------------------------------------------------------
--		Includes
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

#include "mpq.h"

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(USE_BEOS)
	typedef unsigned long u_int32_t;
#endif

#ifndef __GNUC__
	#define __attribute__(args)  // Does nothing for non GNU CC
#endif

#ifndef O_BINARY
	#define O_BINARY 0
#endif


#if  defined(__i386__) || defined(__ia64__) || defined(WIN32) || \
    (defined(__alpha__) || defined(__alpha)) || \
     defined(__arm__) || \
    (defined(__mips__) && defined(__MIPSEL__)) || \
     defined(__SYMBIAN32__) || \
     defined(__x86_64__) || \
     defined(__LITTLE_ENDIAN__)
#ifdef __cplusplus
static inline unsigned short FetchLE16(unsigned char*& p) {
	unsigned short s = *(unsigned short*)p;
	p += 2;
	return s;
}
static inline unsigned int FetchLE32(unsigned char*& p) {
	unsigned int s = *(unsigned int*)p;
	p += 4;
	return s;
}
#else
#define FetchLE16(p) (*((unsigned short*)(p))); p += 2
#define FetchLE32(p) (*((unsigned int*)(p))); p += 4
#endif
#define AccessLE16(p) (*((unsigned short*)(p)))
#define AccessLE32(p) (*((unsigned int*)(p)))
#define ConvertLE16(v) (v)
#define ConvertLE32(v) (v)
#else
static inline unsigned short Swap16(unsigned short D) {
	return ((D << 8) | (D >> 8));
}
static inline unsigned int Swap32(unsigned int D) {
	return ((D << 24) | ((D << 8) & 0x00FF0000) | ((D >> 8) & 0x0000FF00) | (D >> 24));
}
#define FetchLE16(p) Swap16(*((unsigned short*)(p))); p += 2
#define FetchLE32(p) Swap32(*((unsigned int*)(p))); p += 4
#define AccessLE16(p) Swap16((*((unsigned short*)(p))))
#define AccessLE32(p) Swap32(*((unsigned int*)(p)))
#define ConvertLE16(v) Swap16(v)
#define ConvertLE32(v) Swap32(v)
#endif

#define FetchByte(p) (*((unsigned char*)(p))); ++p


//----------------------------------------------------------------------------
//		Config
//----------------------------------------------------------------------------

/**
**		Mpq file
*/
FILE *MpqFD;
static CMpq *Mpq;

/**
**		Destination directory of the graphics
*/
char *Dir = NULL;

/**
**		Path to the tileset graphics. (default=$DIR/graphics/tilesets)
*/
#define TILESET_PATH		"graphics/tilesets"

/**
**		Path to the unit graphics. (default=$DIR/graphics)
*/
#define UNIT_PATH		"graphics"

/**
**		Path the pud files. (default=$DIR)
*/
#define PUD_PATH		"."

/**
**		Path the font files. (default=$DIR/graphics/ui/fonts)
*/
#define FONT_PATH		"graphics/ui/fonts"

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
**		Path the sound files. (default=$DIR/music)
*/
#define MUSIC_PATH		"music"

/**
**		Path the text files. (default=$DIR/texts)
*/
#define TEXT_PATH		"campaigns"

/**
**		How much tiles are stored in a row.
*/
#define TILE_PER_ROW		16

//----------------------------------------------------------------------------

/**
**		Conversion control sturcture.
*/
typedef struct _control_ {
	int				Type;						/// Entry type
	int				Version;				/// Only in this version
	char*		File;						/// Save file
	char*		ListFile;				/// File name in list file
	int				Arg1;						/// Extra argument 1
	int				Arg2;						/// Extra argument 2
	int				Arg3;						/// Extra argument 3
	int				Arg4;						/// Extra argument 4
} Control;

/**
**		Entry size
*/
int EntrySize;

/**
**		Possible entry types of archive file.
*/
enum _archive_type_ {
	S,						// Setup
	F,						// File							(name)
	M,						// Map							(name)
	T,						// Tileset						(name,pal,mega,mini,map)
	R,						// RGB -> gimp					(name,rgb)
	G,						// Graphics						(name,pal,gfx)
	U,						// Uncompressed Graphics		(name,pal,gfu)
	I,                      // Widgets                      (name,pal,gfu)
	N,						// Font							(name,idx)
	W,						// Wav							(name,wav)
	H,						// Pcx							(name)
	E,						// Raw extract					(name)
};

/**
**		What, where, how to extract.
*/
#define __3 ,0,0,0
#define __4 ,0,0,0,0

Control CDTodo[] = {
	{F,0,"","install.exe" __4},

	// Fonts
	{N,0,"font8","files\\font\\font8.fnt" __4},
	{N,0,"font10","files\\font\\font10.fnt" __4},
	{N,0,"font12","files\\font\\font12.fnt" __4},
	{N,0,"font14","files\\font\\font14.fnt" __4},
	{N,0,"font16","files\\font\\font16.fnt" __4},
	{N,0,"font16x","files\\font\\font16x.fnt" __4},
	{N,0,"font32","files\\font\\font32.fnt" __4},
	{N,0,"font50","files\\font\\font50.fnt" __4},

	// Maps
	{M,0,"maps/(2)Challenger.scm","multimaps\\(2)Challenger.scm" __4},
	{M,0,"maps/(2)River Crossing.scm","multimaps\\(2)River Crossing.scm" __4},
	{M,0,"maps/(2)Road War.scm","multimaps\\(2)Road War.scm" __4},
	{M,0,"maps/(2)Space Madness.scm","multimaps\\(2)Space Madness.scm" __4},
	{M,0,"maps/(2)The Small Divide.scm","multimaps\\(2)The Small Divide.scm" __4},
	{M,0,"maps/(2)Volcanis.scm","multimaps\\(2)Volcanis.scm" __4},
	{M,0,"maps/(3)Holy Ground.scm","multimaps\\(3)Holy Ground.scm" __4},
	{M,0,"maps/(3)Meltdown.scm","multimaps\\(3)Meltdown.scm" __4},
	{M,0,"maps/(3)Three Kingdoms.scm","multimaps\\(3)Three Kingdoms.scm" __4},
	{M,0,"maps/(3)Triumvirate.scm","multimaps\\(3)Triumvirate.scm" __4},
	{M,0,"maps/(4)Alpha Draconis.scm","multimaps\\(4)Alpha Draconis.scm" __4},
	{M,0,"maps/(4)Blood Bath.scm","multimaps\\(4)Blood Bath.scm" __4},
	{M,0,"maps/(4)Bridge Too Near.scm","multimaps\\(4)Bridge Too Near.scm" __4},
	{M,0,"maps/(4)Cyclone.scm","multimaps\\(4)Cyclone.scm" __4},
	{M,0,"maps/(4)Dark Crystal.scm","multimaps\\(4)Dark Crystal.scm" __4},
	{M,0,"maps/(4)Dark Star.scm","multimaps\\(4)Dark Star.scm" __4},
	{M,0,"maps/(4)Lost Civilization.scm","multimaps\\(4)Lost Civilization.scm" __4},
	{M,0,"maps/(4)Opposing City States '98.scm","multimaps\\(4)Opposing City States '98.scm" __4},
	{M,0,"maps/(4)Orbital Relay.scm","multimaps\\(4)Orbital Relay.scm" __4},
	{M,0,"maps/(4)Power Lines.scm","multimaps\\(4)Power Lines.scm" __4},
	{M,0,"maps/(4)Ruins of the Ancients.scm","multimaps\\(4)Ruins of the Ancients.scm" __4},
	{M,0,"maps/(4)Tarsonis Orbital.scm","multimaps\\(4)Tarsonis Orbital.scm" __4},
	{M,0,"maps/(5)Diablo.scm","multimaps\\(5)Diablo.scm" __4},
	{M,0,"maps/(5)Island Hop.scm","multimaps\\(5)Island Hop.scm" __4},
	{M,0,"maps/(5)Jeweled River.scm","multimaps\\(5)Jeweled River.scm" __4},
	{M,0,"maps/(5)Sherwood Forest.scm","multimaps\\(5)Sherwood Forest.scm" __4},
	{M,0,"maps/(6)Ground Zero.scm","multimaps\\(6)Ground Zero.scm" __4},
	{M,0,"maps/(6)Hidden Shrine.scm","multimaps\\(6)Hidden Shrine.scm" __4},
	{M,0,"maps/(6)New Gettysburg.scm","multimaps\\(6)New Gettysburg.scm" __4},
	{M,0,"maps/(7)Continental Divide.scm","multimaps\\(7)Continental Divide.scm" __4},
	{M,0,"maps/(7)River War.scm","multimaps\\(7)River War.scm" __4},
	{M,0,"maps/(8)Bridge to Bridge '98.scm","multimaps\\(8)Bridge to Bridge '98.scm" __4},
	{M,0,"maps/(8)Char Magma.scm","multimaps\\(8)Char Magma.scm" __4},
	{M,0,"maps/(8)Homeworld.scm","multimaps\\(8)Homeworld.scm" __4},
	{M,0,"maps/(8)Killing Fields.scm","multimaps\\(8)Killing Fields.scm" __4},
	{M,0,"maps/(8)Orbital Death.scm","multimaps\\(8)Orbital Death.scm" __4},
	{M,0,"maps/(8)Plains of Snow '98.scm","multimaps\\(8)Plains of Snow '98.scm" __4},
	{M,0,"maps/(8)Station Unrest.scm","multimaps\\(8)Station Unrest.scm" __4},
	{M,0,"maps/(8)The Hunters.scm","multimaps\\(8)The Hunters.scm" __4},

	// Terran Campaigns
	{H,0,"campaigns/terran/palta-blank","glue\\PalTA\\Blank.pcx",0 __3},
	{H,0,"campaigns/terran/palta-terrana","glue\\palta\\TerranA.pcx",0 __3},
	{H,0,"campaigns/terran/palta-tfont","glue\\palta\\tfont.pcx",0 __3},
	{H,0,"campaigns/terran/paltb-blank","glue\\paltb\\Blank.pcx",0 __3},
	{H,0,"campaigns/terran/paltb-terranb","glue\\paltb\\TerranB.pcx",0 __3},
	{H,0,"campaigns/terran/paltb-tfont","glue\\paltb\\tfont.pcx",0 __3},
	{H,0,"campaigns/terran/paltc-blank","glue\\paltc\\Blank.pcx",0 __3},
	{H,0,"campaigns/terran/paltc-terranc","glue\\paltc\\TerranC.pcx",0 __3},
	{H,0,"campaigns/terran/paltc-tfont","glue\\paltc\\tfont.pcx",0 __3},

	{E,0,"campaigns/terran/tutorial/scenario.chk","campaign\\terran\\tutorial\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/tutorial/ComBeep0","campaign\\terran\\tutorial\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0B00tad","campaign\\terran\\tutorial\\staredit\\wav\\T0B00tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0B01tad","campaign\\terran\\tutorial\\staredit\\wav\\T0B01tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0B02tad","campaign\\terran\\tutorial\\staredit\\wav\\T0B02tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0B03tad","campaign\\terran\\tutorial\\staredit\\wav\\T0B03tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0B04tad","campaign\\terran\\tutorial\\staredit\\wav\\T0B04tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0B05tad","campaign\\terran\\tutorial\\staredit\\wav\\T0B05tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0B60tad","campaign\\terran\\tutorial\\staredit\\wav\\T0B60tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M00tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M00tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M01tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M01tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M02tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M02tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M03tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M03tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M04tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M04tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M05tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M05tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M06tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M06tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M07tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M07tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M21tad","campaign\\terran\\tutorial\\staredit\\wav\\T0M21tad.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M30tma","campaign\\terran\\tutorial\\staredit\\wav\\T0M30tma.wav" __4},
	{W,0,"campaigns/terran/tutorial/T0M31tma","campaign\\terran\\tutorial\\staredit\\wav\\T0M31tma.wav" __4},
	{W,0,"campaigns/terran/tutorial/TSCYes01","campaign\\terran\\tutorial\\staredit\\wav\\TSCYes01.wav" __4},
	{E,0,"campaigns/terran/01/scenario.chk","campaign\\terran\\terran01\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/01/ComBeep0","campaign\\terran\\terran01\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/01/ComBeep1","campaign\\terran\\terran01\\staredit\\wav\\ComBeep1.wav" __4},
	{W,0,"campaigns/terran/01/T0M20tad","campaign\\terran\\terran01\\staredit\\wav\\T0M20tad.wav" __4},
	{W,0,"campaigns/terran/01/T1B00tad","campaign\\terran\\terran01\\staredit\\wav\\T1B00tad.wav" __4},
	{W,0,"campaigns/terran/01/T1B01udu","campaign\\terran\\terran01\\staredit\\wav\\T1B01udu.wav" __4},
	{W,0,"campaigns/terran/01/T1B02tad","campaign\\terran\\terran01\\staredit\\wav\\T1B02tad.wav" __4},
	{W,0,"campaigns/terran/01/T1M01uci","campaign\\terran\\terran01\\staredit\\wav\\T1M01uci.wav" __4},
	{W,0,"campaigns/terran/01/T1M20ura","campaign\\terran\\terran01\\staredit\\wav\\T1M20ura.wav" __4},
	{E,0,"campaigns/terran/02/scenario.chk","campaign\\terran\\terran02\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/02/ComBeep0","campaign\\terran\\terran02\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/02/ComBeep1","campaign\\terran\\terran02\\staredit\\wav\\ComBeep1.wav" __4},
	{W,0,"campaigns/terran/02/T2B00tad","campaign\\terran\\terran02\\staredit\\wav\\T2B00tad.wav" __4},
	{W,0,"campaigns/terran/02/T2B01ura","campaign\\terran\\terran02\\staredit\\wav\\T2B01ura.wav" __4},
	{W,0,"campaigns/terran/02/T2B02tad","campaign\\terran\\terran02\\staredit\\wav\\T2B02tad.wav" __4},
	{W,0,"campaigns/terran/02/T2B03udu","campaign\\terran\\terran02\\staredit\\wav\\T2B03udu.wav" __4},
	{W,0,"campaigns/terran/02/T2B04ura","campaign\\terran\\terran02\\staredit\\wav\\T2B04ura.wav" __4},
	{W,0,"campaigns/terran/02/T2M00ura","campaign\\terran\\terran02\\staredit\\wav\\T2M00ura.wav" __4},
	{W,0,"campaigns/terran/02/T2M20ura","campaign\\terran\\terran02\\staredit\\wav\\T2M20ura.wav" __4},
	{W,0,"campaigns/terran/02/T2M30uci","campaign\\terran\\terran02\\staredit\\wav\\T2M30uci.wav" __4},
	{W,0,"campaigns/terran/02/T2M40ura","campaign\\terran\\terran02\\staredit\\wav\\T2M40ura.wav" __4},
	{W,0,"campaigns/terran/02/T2M60ftb","campaign\\terran\\terran02\\staredit\\wav\\T2M60ftb.wav" __4},
	{W,0,"campaigns/terran/02/T2M60tma","campaign\\terran\\terran02\\staredit\\wav\\T2M60tma.wav" __4},
	{W,0,"campaigns/terran/02/T2M60ura","campaign\\terran\\terran02\\staredit\\wav\\T2M60ura.wav" __4},
	{W,0,"campaigns/terran/02/T2M80udu","campaign\\terran\\terran02\\staredit\\wav\\T2M80udu.wav" __4},
	{W,0,"campaigns/terran/02/T2M81ura","campaign\\terran\\terran02\\staredit\\wav\\T2M81ura.wav" __4},
	{W,0,"campaigns/terran/02/T2M82udu","campaign\\terran\\terran02\\staredit\\wav\\T2M82udu.wav" __4},
	{W,0,"campaigns/terran/02/T2M83ura","campaign\\terran\\terran02\\staredit\\wav\\T2M83ura.wav" __4},
	{W,0,"campaigns/terran/02/TCB02tad","campaign\\terran\\terran02\\staredit\\wav\\TCB02tad.wav" __4},
	{W,0,"campaigns/terran/02/tdrTra01","campaign\\terran\\terran02\\staredit\\wav\\tdrTra01.wav" __4},
	{W,0,"campaigns/terran/02/tfbRdy00","campaign\\terran\\terran02\\staredit\\wav\\tfbRdy00.wav" __4},
	{E,0,"campaigns/terran/03/scenario.chk","campaign\\terran\\terran03\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/03/ComBeep0","campaign\\terran\\terran03\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/03/T0M40tvu","campaign\\terran\\terran03\\staredit\\wav\\T0M40tvu.wav" __4},
	{W,0,"campaigns/terran/03/T3B00tad","campaign\\terran\\terran03\\staredit\\wav\\T3B00tad.wav" __4},
	{W,0,"campaigns/terran/03/T3B01udu","campaign\\terran\\terran03\\staredit\\wav\\T3B01udu.wav" __4},
	{W,0,"campaigns/terran/03/T3B02tad","campaign\\terran\\terran03\\staredit\\wav\\T3B02tad.wav" __4},
	{W,0,"campaigns/terran/03/T3B03ume","campaign\\terran\\terran03\\staredit\\wav\\T3B03ume.wav" __4},
	{W,0,"campaigns/terran/03/T3B04ume","campaign\\terran\\terran03\\staredit\\wav\\T3B04ume.wav" __4},
	{W,0,"campaigns/terran/03/T3B05tad","campaign\\terran\\terran03\\staredit\\wav\\T3B05tad.wav" __4},
	{W,0,"campaigns/terran/03/T3M00tad","campaign\\terran\\terran03\\staredit\\wav\\T3M00tad.wav" __4},
	{W,0,"campaigns/terran/03/T3M20tad","campaign\\terran\\terran03\\staredit\\wav\\T3M20tad.wav" __4},
	{W,0,"campaigns/terran/03/T3M21tad","campaign\\terran\\terran03\\staredit\\wav\\T3M21tad.wav" __4},
	{W,0,"campaigns/terran/03/T3M60tad","campaign\\terran\\terran03\\staredit\\wav\\T3M60tad.wav" __4},
	{W,0,"campaigns/terran/03/T3M70tad","campaign\\terran\\terran03\\staredit\\wav\\T3M70tad.wav" __4},
	{W,0,"campaigns/terran/03/T3M80tad","campaign\\terran\\terran03\\staredit\\wav\\T3M80tad.wav" __4},
	{W,0,"campaigns/terran/03/T3M90tma","campaign\\terran\\terran03\\staredit\\wav\\T3M90tma.wav" __4},
	{W,0,"campaigns/terran/03/TDrYes04","campaign\\terran\\terran03\\staredit\\wav\\TDrYes04.wav" __4},
	{E,0,"campaigns/terran/04/scenario.chk","campaign\\terran\\terran04\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/04/ComBeep0","campaign\\terran\\terran04\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/04/ComBeep1","campaign\\terran\\terran04\\staredit\\wav\\ComBeep1.wav" __4},
	{W,0,"campaigns/terran/04/P6M00tad","campaign\\terran\\terran04\\staredit\\wav\\P6M00tad.wav" __4},
	{W,0,"campaigns/terran/04/PPwrDown","campaign\\terran\\terran04\\staredit\\wav\\PPwrDown.wav" __4},
	{W,0,"campaigns/terran/04/T4B00tad","campaign\\terran\\terran04\\staredit\\wav\\T4B00tad.wav" __4},
	{W,0,"campaigns/terran/04/T4B01ura","campaign\\terran\\terran04\\staredit\\wav\\T4B01ura.wav" __4},
	{W,0,"campaigns/terran/04/T4B02ume","campaign\\terran\\terran04\\staredit\\wav\\T4B02ume.wav" __4},
	{W,0,"campaigns/terran/04/T4B03ume","campaign\\terran\\terran04\\staredit\\wav\\T4B03ume.wav" __4},
	{W,0,"campaigns/terran/04/T4B04ura","campaign\\terran\\terran04\\staredit\\wav\\T4B04ura.wav" __4},
	{W,0,"campaigns/terran/04/T4M00uci","campaign\\terran\\terran04\\staredit\\wav\\T4M00uci.wav" __4},
	{W,0,"campaigns/terran/04/T4M00ura","campaign\\terran\\terran04\\staredit\\wav\\T4M00ura.wav" __4},
	{W,0,"campaigns/terran/04/T4M01ume","campaign\\terran\\terran04\\staredit\\wav\\T4M01ume.wav" __4},
	{W,0,"campaigns/terran/04/T4M20uci","campaign\\terran\\terran04\\staredit\\wav\\T4M20uci.wav" __4},
	{W,0,"campaigns/terran/04/T4M20ura","campaign\\terran\\terran04\\staredit\\wav\\T4M20ura.wav" __4},
	{W,0,"campaigns/terran/04/T4M30uma","campaign\\terran\\terran04\\staredit\\wav\\T4M30uma.wav" __4},
	{W,0,"campaigns/terran/04/T4M70tad","campaign\\terran\\terran04\\staredit\\wav\\T4M70tad.wav" __4},
	{W,0,"campaigns/terran/04/Z5M00tad","campaign\\terran\\terran04\\staredit\\wav\\Z5M00tad.wav" __4},
	{E,0,"campaigns/terran/05/scenario.chk","campaign\\terran\\terran05\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/05/ComBeep0","campaign\\terran\\terran05\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/05/T5B00ura","campaign\\terran\\terran05\\staredit\\wav\\T5B00ura.wav" __4},
	{W,0,"campaigns/terran/05/T5B01tad","campaign\\terran\\terran05\\staredit\\wav\\T5B01tad.wav" __4},
	{W,0,"campaigns/terran/05/T5B02ume","campaign\\terran\\terran05\\staredit\\wav\\T5B02ume.wav" __4},
	{W,0,"campaigns/terran/05/T5B03uke","campaign\\terran\\terran05\\staredit\\wav\\T5B03uke.wav" __4},
	{W,0,"campaigns/terran/05/T5B04ume","campaign\\terran\\terran05\\staredit\\wav\\T5B04ume.wav" __4},
	{W,0,"campaigns/terran/05/T5M00uke","campaign\\terran\\terran05\\staredit\\wav\\T5M00uke.wav" __4},
	{W,0,"campaigns/terran/05/T5M01ura","campaign\\terran\\terran05\\staredit\\wav\\T5M01ura.wav" __4},
	{W,0,"campaigns/terran/05/T5M02uke","campaign\\terran\\terran05\\staredit\\wav\\T5M02uke.wav" __4},
	{W,0,"campaigns/terran/05/T5M03ura","campaign\\terran\\terran05\\staredit\\wav\\T5M03ura.wav" __4},
	{W,0,"campaigns/terran/05/T5M04uke","campaign\\terran\\terran05\\staredit\\wav\\T5M04uke.wav" __4},
	{W,0,"campaigns/terran/05/T5M20uke","campaign\\terran\\terran05\\staredit\\wav\\T5M20uke.wav" __4},
	{W,0,"campaigns/terran/05/T5M40uma","campaign\\terran\\terran05\\staredit\\wav\\T5M40uma.wav" __4},
	{W,0,"campaigns/terran/05/T5M41uke","campaign\\terran\\terran05\\staredit\\wav\\T5M41uke.wav" __4},
	{W,0,"campaigns/terran/05/T5M42tad","campaign\\terran\\terran05\\staredit\\wav\\T5M42tad.wav" __4},
	{W,0,"campaigns/terran/05/T5M43uke","campaign\\terran\\terran05\\staredit\\wav\\T5M43uke.wav" __4},
	{W,0,"campaigns/terran/05/T5M44uma","campaign\\terran\\terran05\\staredit\\wav\\T5M44uma.wav" __4},
	{E,0,"campaigns/terran/06/scenario.chk","campaign\\terran\\terran06\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/06/ComBeep0","campaign\\terran\\terran06\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/06/T6B00tad","campaign\\terran\\terran06\\staredit\\wav\\T6B00tad.wav" __4},
	{W,0,"campaigns/terran/06/T6B01udu","campaign\\terran\\terran06\\staredit\\wav\\T6B01udu.wav" __4},
	{W,0,"campaigns/terran/06/T6B02ura","campaign\\terran\\terran06\\staredit\\wav\\T6B02ura.wav" __4},
	{W,0,"campaigns/terran/06/T6B03ume","campaign\\terran\\terran06\\staredit\\wav\\T6B03ume.wav" __4},
	{W,0,"campaigns/terran/06/T6B04ura","campaign\\terran\\terran06\\staredit\\wav\\T6B04ura.wav" __4},
	{W,0,"campaigns/terran/06/T6B05uke","campaign\\terran\\terran06\\staredit\\wav\\T6B05uke.wav" __4},
	{W,0,"campaigns/terran/06/T6B06ume","campaign\\terran\\terran06\\staredit\\wav\\T6B06ume.wav" __4},
	{W,0,"campaigns/terran/06/T6B07uke","campaign\\terran\\terran06\\staredit\\wav\\T6B07uke.wav" __4},
	{W,0,"campaigns/terran/06/T6B08ume","campaign\\terran\\terran06\\staredit\\wav\\T6B08ume.wav" __4},
	{W,0,"campaigns/terran/06/T6B09uke","campaign\\terran\\terran06\\staredit\\wav\\T6B09uke.wav" __4},
	{W,0,"campaigns/terran/06/T6B10ura","campaign\\terran\\terran06\\staredit\\wav\\T6B10ura.wav" __4},
	{W,0,"campaigns/terran/06/T6M00ura","campaign\\terran\\terran06\\staredit\\wav\\T6M00ura.wav" __4},
	{W,0,"campaigns/terran/06/T6M20udu","campaign\\terran\\terran06\\staredit\\wav\\T6M20udu.wav" __4},
	{W,0,"campaigns/terran/06/T6M21ura","campaign\\terran\\terran06\\staredit\\wav\\T6M21ura.wav" __4},
	{W,0,"campaigns/terran/06/T6M22ume","campaign\\terran\\terran06\\staredit\\wav\\T6M22ume.wav" __4},
	{W,0,"campaigns/terran/06/T6M23udu","campaign\\terran\\terran06\\staredit\\wav\\T6M23udu.wav" __4},
	{W,0,"campaigns/terran/06/T6M24ume","campaign\\terran\\terran06\\staredit\\wav\\T6M24ume.wav" __4},
	{W,0,"campaigns/terran/06/T6M25udu","campaign\\terran\\terran06\\staredit\\wav\\T6M25udu.wav" __4},
	{W,0,"campaigns/terran/06/T6M26ume","campaign\\terran\\terran06\\staredit\\wav\\T6M26ume.wav" __4},
	{W,0,"campaigns/terran/06/T6M27udu","campaign\\terran\\terran06\\staredit\\wav\\T6M27udu.wav" __4},
	{W,0,"campaigns/terran/06/T6M28ume","campaign\\terran\\terran06\\staredit\\wav\\T6M28ume.wav" __4},
	{W,0,"campaigns/terran/06/T6M29ura","campaign\\terran\\terran06\\staredit\\wav\\T6M29ura.wav" __4},
	{W,0,"campaigns/terran/06/T6M30ume","campaign\\terran\\terran06\\staredit\\wav\\T6M30ume.wav" __4},
	{E,0,"campaigns/terran/07/scenario.chk","campaign\\terran\\terran07\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/07/ComBeep0","campaign\\terran\\terran07\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/07/T7B00tad","campaign\\terran\\terran07\\staredit\\wav\\T7B00tad.wav" __4},
	{W,0,"campaigns/terran/07/T7B01ura","campaign\\terran\\terran07\\staredit\\wav\\T7B01ura.wav" __4},
	{W,0,"campaigns/terran/07/T7B02udu","campaign\\terran\\terran07\\staredit\\wav\\T7B02udu.wav" __4},
	{W,0,"campaigns/terran/07/T7B03ura","campaign\\terran\\terran07\\staredit\\wav\\T7B03ura.wav" __4},
	{W,0,"campaigns/terran/07/T7B04udu","campaign\\terran\\terran07\\staredit\\wav\\T7B04udu.wav" __4},
	{W,0,"campaigns/terran/07/T7B05uke","campaign\\terran\\terran07\\staredit\\wav\\T7B05uke.wav" __4},
	{W,0,"campaigns/terran/07/T7B06ume","campaign\\terran\\terran07\\staredit\\wav\\T7B06ume.wav" __4},
	{W,0,"campaigns/terran/07/T7B07uke","campaign\\terran\\terran07\\staredit\\wav\\T7B07uke.wav" __4},
	{W,0,"campaigns/terran/07/T7B08ume","campaign\\terran\\terran07\\staredit\\wav\\T7B08ume.wav" __4},
	{W,0,"campaigns/terran/07/T7M00udu","campaign\\terran\\terran07\\staredit\\wav\\T7M00udu.wav" __4},
	{W,0,"campaigns/terran/07/T7M01ura","campaign\\terran\\terran07\\staredit\\wav\\T7M01ura.wav" __4},
	{W,0,"campaigns/terran/07/T7M02udu","campaign\\terran\\terran07\\staredit\\wav\\T7M02udu.wav" __4},
	{W,0,"campaigns/terran/07/T7M03ura","campaign\\terran\\terran07\\staredit\\wav\\T7M03ura.wav" __4},
	{W,0,"campaigns/terran/07/T7M20tad","campaign\\terran\\terran07\\staredit\\wav\\T7M20tad.wav" __4},
	{W,0,"campaigns/terran/07/T7M21ura","campaign\\terran\\terran07\\staredit\\wav\\T7M21ura.wav" __4},
	{W,0,"campaigns/terran/07/T7M22uta","campaign\\terran\\terran07\\staredit\\wav\\T7M22uta.wav" __4},
	{W,0,"campaigns/terran/07/T7M23ura","campaign\\terran\\terran07\\staredit\\wav\\T7M23ura.wav" __4},
	{W,0,"campaigns/terran/07/T7M24uta","campaign\\terran\\terran07\\staredit\\wav\\T7M24uta.wav" __4},
	{E,0,"campaigns/terran/08/scenario.chk","campaign\\terran\\terran08\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/08/ComBeep0","campaign\\terran\\terran08\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/08/T8B00tad","campaign\\terran\\terran08\\staredit\\wav\\T8B00tad.wav" __4},
	{W,0,"campaigns/terran/08/T8B01ume","campaign\\terran\\terran08\\staredit\\wav\\T8B01ume.wav" __4},
	{W,0,"campaigns/terran/08/T8B02uke","campaign\\terran\\terran08\\staredit\\wav\\T8B02uke.wav" __4},
	{W,0,"campaigns/terran/08/T8B03ura","campaign\\terran\\terran08\\staredit\\wav\\T8B03ura.wav" __4},
	{W,0,"campaigns/terran/08/T8B04uke","campaign\\terran\\terran08\\staredit\\wav\\T8B04uke.wav" __4},
	{W,0,"campaigns/terran/08/T8B05ume","campaign\\terran\\terran08\\staredit\\wav\\T8B05ume.wav" __4},
	{W,0,"campaigns/terran/08/T8B06ura","campaign\\terran\\terran08\\staredit\\wav\\T8B06ura.wav" __4},
	{W,0,"campaigns/terran/08/T8B07ume","campaign\\terran\\terran08\\staredit\\wav\\T8B07ume.wav" __4},
	{W,0,"campaigns/terran/08/T8B08ume","campaign\\terran\\terran08\\staredit\\wav\\T8B08ume.wav" __4},
	{W,0,"campaigns/terran/08/T8B09ume","campaign\\terran\\terran08\\staredit\\wav\\T8B09ume.wav" __4},
	{W,0,"campaigns/terran/08/T8M00uke","campaign\\terran\\terran08\\staredit\\wav\\T8M00uke.wav" __4},
	{W,0,"campaigns/terran/08/T8M01ume","campaign\\terran\\terran08\\staredit\\wav\\T8M01ume.wav" __4},
	{W,0,"campaigns/terran/08/T8M02uke","campaign\\terran\\terran08\\staredit\\wav\\T8M02uke.wav" __4},
	{W,0,"campaigns/terran/08/T8M40uke","campaign\\terran\\terran08\\staredit\\wav\\T8M40uke.wav" __4},
	{W,0,"campaigns/terran/08/T8m41ume","campaign\\terran\\terran08\\staredit\\wav\\T8m41ume.wav" __4},
	{E,0,"campaigns/terran/09/scenario.chk","campaign\\terran\\terran09\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/09/ComBeep0","campaign\\terran\\terran09\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/09/T9B00tad","campaign\\terran\\terran09\\staredit\\wav\\T9B00tad.wav" __4},
	{W,0,"campaigns/terran/09/T9B01ume","campaign\\terran\\terran09\\staredit\\wav\\T9B01ume.wav" __4},
	{W,0,"campaigns/terran/09/T9B02udu","campaign\\terran\\terran09\\staredit\\wav\\T9B02udu.wav" __4},
	{W,0,"campaigns/terran/09/T9B03ura","campaign\\terran\\terran09\\staredit\\wav\\T9B03ura.wav" __4},
	{W,0,"campaigns/terran/09/T9B04udu","campaign\\terran\\terran09\\staredit\\wav\\T9B04udu.wav" __4},
	{W,0,"campaigns/terran/09/T9B05ura","campaign\\terran\\terran09\\staredit\\wav\\T9B05ura.wav" __4},
	{W,0,"campaigns/terran/09/T9M00ura","campaign\\terran\\terran09\\staredit\\wav\\T9M00ura.wav" __4},
	{W,0,"campaigns/terran/09/T9M20udu","campaign\\terran\\terran09\\staredit\\wav\\T9M20udu.wav" __4},
	{W,0,"campaigns/terran/09/TAM00udu","campaign\\terran\\terran09\\staredit\\wav\\TAM00udu.wav" __4},
	{W,0,"campaigns/terran/09/TAM01uke","campaign\\terran\\terran09\\staredit\\wav\\TAM01uke.wav" __4},
	{W,0,"campaigns/terran/09/TAM02ume","campaign\\terran\\terran09\\staredit\\wav\\TAM02ume.wav" __4},
	{W,0,"campaigns/terran/09/TAM03uke","campaign\\terran\\terran09\\staredit\\wav\\TAM03uke.wav" __4},
	{W,0,"campaigns/terran/09/TAM04ura","campaign\\terran\\terran09\\staredit\\wav\\TAM04ura.wav" __4},
	{W,0,"campaigns/terran/09/TAM05ume","campaign\\terran\\terran09\\staredit\\wav\\TAM05ume.wav" __4},
	{E,0,"campaigns/terran/10/scenario.chk","campaign\\terran\\terran10\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/10/ComBeep0","campaign\\terran\\terran10\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/10/TAB00tad","campaign\\terran\\terran10\\staredit\\wav\\TAB00tad.wav" __4},
	{W,0,"campaigns/terran/10/TAB01ume","campaign\\terran\\terran10\\staredit\\wav\\TAB01ume.wav" __4},
	{W,0,"campaigns/terran/10/TAB02ume","campaign\\terran\\terran10\\staredit\\wav\\TAB02ume.wav" __4},
	{W,0,"campaigns/terran/10/TAB03uke","campaign\\terran\\terran10\\staredit\\wav\\TAB03uke.wav" __4},
	{W,0,"campaigns/terran/10/TAB04udu","campaign\\terran\\terran10\\staredit\\wav\\TAB04udu.wav" __4},
	{W,0,"campaigns/terran/10/TAB05ura","campaign\\terran\\terran10\\staredit\\wav\\TAB05ura.wav" __4},
	{W,0,"campaigns/terran/10/TAB06udu","campaign\\terran\\terran10\\staredit\\wav\\TAB06udu.wav" __4},
	{W,0,"campaigns/terran/10/TAM00udu","campaign\\terran\\terran10\\staredit\\wav\\TAM00udu.wav" __4},
	{W,0,"campaigns/terran/10/TAM01uke","campaign\\terran\\terran10\\staredit\\wav\\TAM01uke.wav" __4},
	{W,0,"campaigns/terran/10/TAM02ume","campaign\\terran\\terran10\\staredit\\wav\\TAM02ume.wav" __4},
	{W,0,"campaigns/terran/10/TAM03uke","campaign\\terran\\terran10\\staredit\\wav\\TAM03uke.wav" __4},
	{W,0,"campaigns/terran/10/TAM04ura","campaign\\terran\\terran10\\staredit\\wav\\TAM04ura.wav" __4},
	{W,0,"campaigns/terran/10/TAM05ume","campaign\\terran\\terran10\\staredit\\wav\\TAM05ume.wav" __4},
	{E,0,"campaigns/terran/11/scenario.chk","campaign\\terran\\terran11\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/11/ComBeep0","campaign\\terran\\terran11\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/11/TBB00tad","campaign\\terran\\terran11\\staredit\\wav\\TBB00tad.wav" __4},
	{W,0,"campaigns/terran/11/TBB01ume","campaign\\terran\\terran11\\staredit\\wav\\TBB01ume.wav" __4},
	{W,0,"campaigns/terran/11/TBB02ura","campaign\\terran\\terran11\\staredit\\wav\\TBB02ura.wav" __4},
	{W,0,"campaigns/terran/11/TBB03ume","campaign\\terran\\terran11\\staredit\\wav\\TBB03ume.wav" __4},
	{W,0,"campaigns/terran/11/TBB04ura","campaign\\terran\\terran11\\staredit\\wav\\TBB04ura.wav" __4},
	{W,0,"campaigns/terran/11/TBB05uke","campaign\\terran\\terran11\\staredit\\wav\\TBB05uke.wav" __4},
	{W,0,"campaigns/terran/11/TBB06ura","campaign\\terran\\terran11\\staredit\\wav\\TBB06ura.wav" __4},
	{W,0,"campaigns/terran/11/TBM00ura","campaign\\terran\\terran11\\staredit\\wav\\TBM00ura.wav" __4},
	{W,0,"campaigns/terran/11/TBM01uke","campaign\\terran\\terran11\\staredit\\wav\\TBM01uke.wav" __4},
	{W,0,"campaigns/terran/11/TBM04ura","campaign\\terran\\terran11\\staredit\\wav\\TBM04ura.wav" __4},
	{W,0,"campaigns/terran/11/TBM20ume","campaign\\terran\\terran11\\staredit\\wav\\TBM20ume.wav" __4},
	{W,0,"campaigns/terran/11/TBM21uma","campaign\\terran\\terran11\\staredit\\wav\\TBM21uma.wav" __4},
	{W,0,"campaigns/terran/11/TBM40tad","campaign\\terran\\terran11\\staredit\\wav\\TBM40tad.wav" __4},
	{W,0,"campaigns/terran/11/TBM41uke","campaign\\terran\\terran11\\staredit\\wav\\TBM41uke.wav" __4},
	{W,0,"campaigns/terran/11/TBM42ume","campaign\\terran\\terran11\\staredit\\wav\\TBM42ume.wav" __4},
	{W,0,"campaigns/terran/11/TBM43ura","campaign\\terran\\terran11\\staredit\\wav\\TBM43ura.wav" __4},
	{W,0,"campaigns/terran/11/TBM44ume","campaign\\terran\\terran11\\staredit\\wav\\TBM44ume.wav" __4},
	{W,0,"campaigns/terran/11/TBM45uke","campaign\\terran\\terran11\\staredit\\wav\\TBM45uke.wav" __4},
	{W,0,"campaigns/terran/11/TBM46ura","campaign\\terran\\terran11\\staredit\\wav\\TBM46ura.wav" __4},
	{W,0,"campaigns/terran/11/TBM47ume","campaign\\terran\\terran11\\staredit\\wav\\TBM47ume.wav" __4},
	{W,0,"campaigns/terran/11/TBm48uke","campaign\\terran\\terran11\\staredit\\wav\\TBm48uke.wav" __4},
	{E,0,"campaigns/terran/12/scenario.chk","campaign\\terran\\terran12\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/terran/12/ComBeep0","campaign\\terran\\terran12\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/terran/12/TCB00tad","campaign\\terran\\terran12\\staredit\\wav\\TCB00tad.wav" __4},
	{W,0,"campaigns/terran/12/TCB01ura","campaign\\terran\\terran12\\staredit\\wav\\TCB01ura.wav" __4},
	{W,0,"campaigns/terran/12/TCB02tad","campaign\\terran\\terran12\\staredit\\wav\\TCB02tad.wav" __4},
	{W,0,"campaigns/terran/12/TCB03ume","campaign\\terran\\terran12\\staredit\\wav\\TCB03ume.wav" __4},
	{W,0,"campaigns/terran/12/TCB04ura","campaign\\terran\\terran12\\staredit\\wav\\TCB04ura.wav" __4},
	{W,0,"campaigns/terran/12/TCB05ume","campaign\\terran\\terran12\\staredit\\wav\\TCB05ume.wav" __4},
	{W,0,"campaigns/terran/12/TCB06ura","campaign\\terran\\terran12\\staredit\\wav\\TCB06ura.wav" __4},
	{W,0,"campaigns/terran/12/TCB07ume","campaign\\terran\\terran12\\staredit\\wav\\TCB07ume.wav" __4},
	{W,0,"campaigns/terran/12/TCB08tad","campaign\\terran\\terran12\\staredit\\wav\\TCB08tad.wav" __4},
	{W,0,"campaigns/terran/12/TCB09ura","campaign\\terran\\terran12\\staredit\\wav\\TCB09ura.wav" __4},
	{W,0,"campaigns/terran/12/TCM00ura","campaign\\terran\\terran12\\staredit\\wav\\TCM00ura.wav" __4},
	{W,0,"campaigns/terran/12/TCM01ura","campaign\\terran\\terran12\\staredit\\wav\\TCM01ura.wav" __4},
	{W,0,"campaigns/terran/12/TCM20tad","campaign\\terran\\terran12\\staredit\\wav\\TCM20tad.wav" __4},

	{E,0,"campaigns/terran/EstT0t.txt","rez\\EstT0t.txt" __4},
	{E,0,"campaigns/terran/EstT01.txt","rez\\EstT01.txt" __4},
	{E,0,"campaigns/terran/EstT02.txt","rez\\EstT02.txt" __4},
	{E,0,"campaigns/terran/EstT03.txt","rez\\EstT03.txt" __4},
	{E,0,"campaigns/terran/EstT04.txt","rez\\EstT04.txt" __4},
	{E,0,"campaigns/terran/EstT05.txt","rez\\EstT05.txt" __4},
	{E,0,"campaigns/terran/EstT06.txt","rez\\EstT06.txt" __4},
	{E,0,"campaigns/terran/EstT07.txt","rez\\EstT07.txt" __4},
	{E,0,"campaigns/terran/EstT08.txt","rez\\EstT08.txt" __4},
	{E,0,"campaigns/terran/EstT09.txt","rez\\EstT09.txt" __4},
	{E,0,"campaigns/terran/EstT10.txt","rez\\EstT10.txt" __4},
	{E,0,"campaigns/terran/EstT11.txt","rez\\EstT11.txt" __4},
	{E,0,"campaigns/terran/EstT12.txt","rez\\EstT12.txt" __4},

	// Zerg Campaigns
	{H,0,"campaigns/zerg/palza-blank","glue\\palza\\Blank.pcx",0 __3},
	{H,0,"campaigns/zerg/palza-tfont","glue\\palza\\tFont.pcx",0 __3},
	{H,0,"campaigns/zerg/palza-zerga","glue\\palza\\ZergA.pcx",0 __3},
	{H,0,"campaigns/zerg/palzb-blank","glue\\palzb\\Blank.pcx",0 __3},
	{H,0,"campaigns/zerg/palzb-tfont","glue\\palzb\\tFont.pcx",0 __3},
	{H,0,"campaigns/zerg/palzb-zergb","glue\\palzb\\ZergB.pcx",0 __3},
	{H,0,"campaigns/zerg/palzc-blank","glue\\palzc\\Blank.pcx",0 __3},
	{H,0,"campaigns/zerg/palzc-tfont","glue\\palzc\\tfont.pcx",0 __3},
	{H,0,"campaigns/zerg/palzc-zergc","glue\\palzc\\ZergC.pcx",0 __3},

	{E,0,"campaigns/zerg/tutorial/scenario.chk","campaign\\zerg\\tutorial\\staredit\\scenario.chk" __4},
	{E,0,"campaigns/zerg/01/scenario.chk","campaign\\zerg\\zerg01\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/01/ComBeep0","campaign\\zerg\\zerg01\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M01uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M01uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M02uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M02uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M03uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M03uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M04uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M04uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M05uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M05uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M06uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M06uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M07uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M07uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M08uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M08uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z0M09uda","campaign\\zerg\\zerg01\\staredit\\wav\\Z0M09uda.wav" __4},
	{W,0,"campaigns/zerg/01/Z1B00zad.wav","campaign\\zerg\\zerg01\\staredit\\wav\\Z1B00zad.wav" __4},
	{W,0,"campaigns/zerg/01/Z1B01zad.wav","campaign\\zerg\\zerg01\\staredit\\wav\\Z1B01zad.wav" __4},
	{W,0,"campaigns/zerg/01/Z1B02zad","campaign\\zerg\\zerg01\\staredit\\wav\\Z1B02zad.wav" __4},
	{W,0,"campaigns/zerg/01/Z1B03zad","campaign\\zerg\\zerg01\\staredit\\wav\\Z1B03zad.wav" __4},
	{W,0,"campaigns/zerg/01/Z1M00uza","campaign\\zerg\\zerg01\\staredit\\wav\\Z1M00uza.wav" __4},
	{W,0,"campaigns/zerg/01/zpwrdown","campaign\\zerg\\zerg01\\staredit\\wav\\zpwrdown.wav" __4},
	{E,0,"campaigns/zerg/02/scenario.chk","campaign\\zerg\\zerg02\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/02/ComBeep0","campaign\\zerg\\zerg02\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/02/Z2B00zad","campaign\\zerg\\zerg02\\staredit\\wav\\Z2B00zad.wav" __4},
	{W,0,"campaigns/zerg/02/Z2B01zad","campaign\\zerg\\zerg02\\staredit\\wav\\Z2B01zad.wav" __4},
	{W,0,"campaigns/zerg/02/Z2B02uza","campaign\\zerg\\zerg02\\staredit\\wav\\Z2B02uza.wav" __4},
	{W,0,"campaigns/zerg/02/Z2B03uda","campaign\\zerg\\zerg02\\staredit\\wav\\Z2B03uda.wav" __4},
	{W,0,"campaigns/zerg/02/Z2M00uda","campaign\\zerg\\zerg02\\staredit\\wav\\Z2M00uda.wav" __4},
	{W,0,"campaigns/zerg/02/Z2M20uza","campaign\\zerg\\zerg02\\staredit\\wav\\Z2M20uza.wav" __4},
	{W,0,"campaigns/zerg/02/Z2M21uda","campaign\\zerg\\zerg02\\staredit\\wav\\Z2M21uda.wav" __4},
	{E,0,"campaigns/zerg/03/scenario.chk","campaign\\zerg\\zerg03\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/03/ComBeep0","campaign\\zerg\\zerg03\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/03/Z3B00zad","campaign\\zerg\\zerg03\\staredit\\wav\\Z3B00zad.wav" __4},
	{W,0,"campaigns/zerg/03/Z3B01uza","campaign\\zerg\\zerg03\\staredit\\wav\\Z3B01uza.wav" __4},
	{W,0,"campaigns/zerg/03/Z3B02udu","campaign\\zerg\\zerg03\\staredit\\wav\\Z3B02udu.wav" __4},
	{W,0,"campaigns/zerg/03/Z3B03uda","campaign\\zerg\\zerg03\\staredit\\wav\\Z3B03uda.wav" __4},
	{W,0,"campaigns/zerg/03/Z3M00udu","campaign\\zerg\\zerg03\\staredit\\wav\\Z3M00udu.wav" __4},
	{W,0,"campaigns/zerg/03/Z3M01uda","campaign\\zerg\\zerg03\\staredit\\wav\\Z3M01uda.wav" __4},
	{W,0,"campaigns/zerg/03/Z3M02uza","campaign\\zerg\\zerg03\\staredit\\wav\\Z3M02uza.wav" __4},
	{W,0,"campaigns/zerg/03/zpwrdown","campaign\\zerg\\zerg03\\staredit\\wav\\zpwrdown.wav" __4},
	{E,0,"campaigns/zerg/04/scenario.chk","campaign\\zerg\\zerg04\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/04/ComBeep0","campaign\\zerg\\zerg04\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/04/Z4B00uza","campaign\\zerg\\zerg04\\staredit\\wav\\Z4B00uza.wav" __4},
	{W,0,"campaigns/zerg/04/Z4B01zad","campaign\\zerg\\zerg04\\staredit\\wav\\Z4B01zad.wav" __4},
	{W,0,"campaigns/zerg/04/Z4B02zad","campaign\\zerg\\zerg04\\staredit\\wav\\Z4B02zad.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M00ura","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M00ura.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M20uza","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M20uza.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M40zad","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M40zad.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M41uki","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M41uki.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M42zad","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M42zad.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M43ura","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M43ura.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M60ura","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M60ura.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M61uki","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M61uki.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M62ura","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M62ura.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M63uki","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M63uki.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M65ura","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M65ura.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M66uki","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M66uki.wav" __4},
	{W,0,"campaigns/zerg/04/Z4M67ura","campaign\\zerg\\zerg04\\staredit\\wav\\Z4M67ura.wav" __4},
	{E,0,"campaigns/zerg/05/scenario.chk","campaign\\zerg\\zerg05\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/05/ComBeep0","campaign\\zerg\\zerg05\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/05/ComBeep1","campaign\\zerg\\zerg05\\staredit\\wav\\ComBeep1.wav" __4},
	{W,0,"campaigns/zerg/05/P6M00tad","campaign\\zerg\\zerg05\\staredit\\wav\\P6M00tad.wav" __4},
	{W,0,"campaigns/zerg/05/PPwrDown","campaign\\zerg\\zerg05\\staredit\\wav\\PPwrDown.wav" __4},
	{W,0,"campaigns/zerg/05/T4M70tad","campaign\\zerg\\zerg05\\staredit\\wav\\T4M70tad.wav" __4},
	{W,0,"campaigns/zerg/05/TBM21uma","campaign\\zerg\\zerg05\\staredit\\wav\\TBM21uma.wav" __4},
	{W,0,"campaigns/zerg/05/Z5B00uki","campaign\\zerg\\zerg05\\staredit\\wav\\Z5B00uki.wav" __4},
	{W,0,"campaigns/zerg/05/Z5B01uki","campaign\\zerg\\zerg05\\staredit\\wav\\Z5B01uki.wav" __4},
	{W,0,"campaigns/zerg/05/Z5B02uza","campaign\\zerg\\zerg05\\staredit\\wav\\Z5B02uza.wav" __4},
	{W,0,"campaigns/zerg/05/Z5B03uki","campaign\\zerg\\zerg05\\staredit\\wav\\Z5B03uki.wav" __4},
	{W,0,"campaigns/zerg/05/Z5B04zad","campaign\\zerg\\zerg05\\staredit\\wav\\Z5B04zad.wav" __4},
	{W,0,"campaigns/zerg/05/Z5B05uza","campaign\\zerg\\zerg05\\staredit\\wav\\Z5B05uza.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M00tad","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M00tad.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M00uda","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M00uda.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M20uci","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M20uci.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M20uki","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M20uki.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M30uci","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M30uci.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M40uma","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M40uma.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M50uma","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M50uma.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M51uma","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M51uma.wav" __4},
	{W,0,"campaigns/zerg/05/Z5M60uda","campaign\\zerg\\zerg05\\staredit\\wav\\Z5M60uda.wav" __4},
	{W,0,"campaigns/zerg/05/zpwrdown","campaign\\zerg\\zerg05\\staredit\\wav\\zpwrdown.wav" __4},
	{E,0,"campaigns/zerg/06/scenario.chk","campaign\\zerg\\zerg06\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/06/ComBeep0","campaign\\zerg\\zerg06\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/06/ComBeep1","campaign\\zerg\\zerg06\\staredit\\wav\\ComBeep1.wav" __4},
	{W,0,"campaigns/zerg/06/Z6B00uki","campaign\\zerg\\zerg06\\staredit\\wav\\Z6B00uki.wav" __4},
	{W,0,"campaigns/zerg/06/Z6B01uki","campaign\\zerg\\zerg06\\staredit\\wav\\Z6B01uki.wav" __4},
	{W,0,"campaigns/zerg/06/Z6B02uta","campaign\\zerg\\zerg06\\staredit\\wav\\Z6B02uta.wav" __4},
	{W,0,"campaigns/zerg/06/Z6B03uki","campaign\\zerg\\zerg06\\staredit\\wav\\Z6B03uki.wav" __4},
	{W,0,"campaigns/zerg/06/Z6B04uta","campaign\\zerg\\zerg06\\staredit\\wav\\Z6B04uta.wav" __4},
	{W,0,"campaigns/zerg/06/Z6B05uki","campaign\\zerg\\zerg06\\staredit\\wav\\Z6B05uki.wav" __4},
	{W,0,"campaigns/zerg/06/Z6M00uza","campaign\\zerg\\zerg06\\staredit\\wav\\Z6M00uza.wav" __4},
	{W,0,"campaigns/zerg/06/Z6M01uki","campaign\\zerg\\zerg06\\staredit\\wav\\Z6M01uki.wav" __4},
	{W,0,"campaigns/zerg/06/Z6M02uza","campaign\\zerg\\zerg06\\staredit\\wav\\Z6M02uza.wav" __4},
	{W,0,"campaigns/zerg/06/Z6M20uki","campaign\\zerg\\zerg06\\staredit\\wav\\Z6M20uki.wav" __4},
	{W,0,"campaigns/zerg/06/Z6M40uta","campaign\\zerg\\zerg06\\staredit\\wav\\Z6M40uta.wav" __4},
	{W,0,"campaigns/zerg/06/Z6M60uki","campaign\\zerg\\zerg06\\staredit\\wav\\Z6M60uki.wav" __4},
	{W,0,"campaigns/zerg/06/Z6M61uta","campaign\\zerg\\zerg06\\staredit\\wav\\Z6M61uta.wav" __4},
	{E,0,"campaigns/zerg/07/scenario.chk","campaign\\zerg\\zerg07\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/07/Z7B00uki","campaign\\zerg\\zerg07\\staredit\\wav\\Z7B00uki.wav" __4},
	{W,0,"campaigns/zerg/07/Z7B01uda","campaign\\zerg\\zerg07\\staredit\\wav\\Z7B01uda.wav" __4},
	{W,0,"campaigns/zerg/07/Z7B02uki","campaign\\zerg\\zerg07\\staredit\\wav\\Z7B02uki.wav" __4},
	{W,0,"campaigns/zerg/07/Z7B03uda","campaign\\zerg\\zerg07\\staredit\\wav\\Z7B03uda.wav" __4},
	{W,0,"campaigns/zerg/07/Z7B04uki","campaign\\zerg\\zerg07\\staredit\\wav\\Z7B04uki.wav" __4},
	{W,0,"campaigns/zerg/07/Z7B05uda","campaign\\zerg\\zerg07\\staredit\\wav\\Z7B05uda.wav" __4},
	{E,0,"campaigns/zerg/08/scenario.chk","campaign\\zerg\\zerg08\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/08/ComBeep0","campaign\\zerg\\zerg08\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/08/Z8B00zad","campaign\\zerg\\zerg08\\staredit\\wav\\Z8B00zad.wav" __4},
	{W,0,"campaigns/zerg/08/Z8B01zad","campaign\\zerg\\zerg08\\staredit\\wav\\Z8B01zad.wav" __4},
	{W,0,"campaigns/zerg/08/Z8B02zad","campaign\\zerg\\zerg08\\staredit\\wav\\Z8B02zad.wav" __4},
	{W,0,"campaigns/zerg/08/Z8B03uda","campaign\\zerg\\zerg08\\staredit\\wav\\Z8B03uda.wav" __4},
	{W,0,"campaigns/zerg/08/Z8M00uda","campaign\\zerg\\zerg08\\staredit\\wav\\Z8M00uda.wav" __4},
	{W,0,"campaigns/zerg/08/Z8M20uda","campaign\\zerg\\zerg08\\staredit\\wav\\Z8M20uda.wav" __4},
	{W,0,"campaigns/zerg/08/Z8M40uki","campaign\\zerg\\zerg08\\staredit\\wav\\Z8M40uki.wav" __4},
	{W,0,"campaigns/zerg/08/Z8M41uze","campaign\\zerg\\zerg08\\staredit\\wav\\Z8M41uze.wav" __4},
	{W,0,"campaigns/zerg/08/Z8M42uki","campaign\\zerg\\zerg08\\staredit\\wav\\Z8M42uki.wav" __4},
	{W,0,"campaigns/zerg/08/Z8M60uki","campaign\\zerg\\zerg08\\staredit\\wav\\Z8M60uki.wav" __4},
	{E,0,"campaigns/zerg/09/scenario.chk","campaign\\zerg\\zerg09\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/09/ComBeep0","campaign\\zerg\\zerg09\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/09/Z9B00zad","campaign\\zerg\\zerg09\\staredit\\wav\\Z9B00zad.wav" __4},
	{W,0,"campaigns/zerg/09/Z9B01zad","campaign\\zerg\\zerg09\\staredit\\wav\\Z9B01zad.wav" __4},
	{W,0,"campaigns/zerg/09/Z9B02zad","campaign\\zerg\\zerg09\\staredit\\wav\\Z9B02zad.wav" __4},
	{W,0,"campaigns/zerg/09/Z9M00uda","campaign\\zerg\\zerg09\\staredit\\wav\\Z9M00uda.wav" __4},
	{W,0,"campaigns/zerg/09/Z9M01uda","campaign\\zerg\\zerg09\\staredit\\wav\\Z9M01uda.wav" __4},
	{W,0,"campaigns/zerg/09/zdrErr00","campaign\\zerg\\zerg09\\staredit\\wav\\zdrErr00.wav" __4},
	{W,0,"campaigns/zerg/09/ZDrMin00","campaign\\zerg\\zerg09\\staredit\\wav\\ZDrMin00.wav" __4},
	{E,0,"campaigns/zerg/10/scenario.chk","campaign\\zerg\\zerg10\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/zerg/10/ComBeep0","campaign\\zerg\\zerg10\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/zerg/10/ZAB00zad","campaign\\zerg\\zerg10\\staredit\\wav\\ZAB00zad.wav" __4},
	{W,0,"campaigns/zerg/10/ZAB01zad","campaign\\zerg\\zerg10\\staredit\\wav\\ZAB01zad.wav" __4},
	{W,0,"campaigns/zerg/10/ZAB02zad","campaign\\zerg\\zerg10\\staredit\\wav\\ZAB02zad.wav" __4},
	{W,0,"campaigns/zerg/10/ZAM00uda","campaign\\zerg\\zerg10\\staredit\\wav\\ZAM00uda.wav" __4},
	{W,0,"campaigns/zerg/10/ZAM20zad","campaign\\zerg\\zerg10\\staredit\\wav\\ZAM20zad.wav" __4},

	{E,0,"campaigns/zerg/EstZ0t.txt","rez\\EstZ0t.txt" __4},
	{E,0,"campaigns/zerg/EstZ01.txt","rez\\EstZ01.txt" __4},
	{E,0,"campaigns/zerg/EstZ02.txt","rez\\EstZ02.txt" __4},
	{E,0,"campaigns/zerg/EstZ03.txt","rez\\EstZ03.txt" __4},
	{E,0,"campaigns/zerg/EstZ04.txt","rez\\EstZ04.txt" __4},
	{E,0,"campaigns/zerg/EstZ05.txt","rez\\EstZ05.txt" __4},
	{E,0,"campaigns/zerg/EstZ06.txt","rez\\EstZ06.txt" __4},
	{E,0,"campaigns/zerg/EstZ07.txt","rez\\EstZ07.txt" __4},
	{E,0,"campaigns/zerg/EstZ08.txt","rez\\EstZ08.txt" __4},
	{E,0,"campaigns/zerg/EstZ09.txt","rez\\EstZ09.txt" __4},
	{E,0,"campaigns/zerg/EstZ10.txt","rez\\EstZ10.txt" __4},

	// Protoss Campaigns
	{E,0,"campaigns/protoss/tutorial/scenario.chk","campaign\\protoss\\tutorial\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/tutorial/P1B00pad","campaign\\protoss\\tutorial\\staredit\\wav\\P1B00pad.wav" __4},
	{W,0,"campaigns/protoss/tutorial/P1B01pad","campaign\\protoss\\tutorial\\staredit\\wav\\P1B01pad.wav" __4},
	{W,0,"campaigns/protoss/tutorial/P1B02pad","campaign\\protoss\\tutorial\\staredit\\wav\\P1B02pad.wav" __4},
	{W,0,"campaigns/protoss/tutorial/P1M00ufe","campaign\\protoss\\tutorial\\staredit\\wav\\P1M00ufe.wav" __4},
	{W,0,"campaigns/protoss/tutorial/P1M20ufe","campaign\\protoss\\tutorial\\staredit\\wav\\P1M20ufe.wav" __4},
	{W,0,"campaigns/protoss/tutorial/P1M40ufe","campaign\\protoss\\tutorial\\staredit\\wav\\P1M40ufe.wav" __4},
	{E,0,"campaigns/protoss/01/scenario.chk","campaign\\protoss\\protoss01\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/01/ComBeep0","campaign\\protoss\\protoss01\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/01/P1B00pad","campaign\\protoss\\protoss01\\staredit\\wav\\P1B00pad.wav" __4},
	{W,0,"campaigns/protoss/01/P1B01pad","campaign\\protoss\\protoss01\\staredit\\wav\\P1B01pad.wav" __4},
	{W,0,"campaigns/protoss/01/P1B02pad","campaign\\protoss\\protoss01\\staredit\\wav\\P1B02pad.wav" __4},
	{W,0,"campaigns/protoss/01/P1M00ufe","campaign\\protoss\\protoss01\\staredit\\wav\\P1M00ufe.wav" __4},
	{W,0,"campaigns/protoss/01/P1M40ufe","campaign\\protoss\\protoss01\\staredit\\wav\\P1M40ufe.wav" __4},
	{W,0,"campaigns/protoss/01/P1M60ufe","campaign\\protoss\\protoss01\\staredit\\wav\\P1M60ufe.wav" __4},
	{W,0,"campaigns/protoss/01/P1M61ufe","campaign\\protoss\\protoss01\\staredit\\wav\\P1M61ufe.wav" __4},
	{W,0,"campaigns/protoss/01/P1M62ufe","campaign\\protoss\\protoss01\\staredit\\wav\\P1M62ufe.wav" __4},
	{E,0,"campaigns/protoss/02/scenario.chk","campaign\\protoss\\protoss02\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/02/ComBeep0","campaign\\protoss\\protoss02\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/02/P2B00pad","campaign\\protoss\\protoss02\\staredit\\wav\\P2B00pad.wav" __4},
	{W,0,"campaigns/protoss/02/P2B01uta","campaign\\protoss\\protoss02\\staredit\\wav\\P2B01uta.wav" __4},
	{W,0,"campaigns/protoss/02/P2B02pad","campaign\\protoss\\protoss02\\staredit\\wav\\P2B02pad.wav" __4},
	{W,0,"campaigns/protoss/02/P2B03uta","campaign\\protoss\\protoss02\\staredit\\wav\\P2B03uta.wav" __4},
	{W,0,"campaigns/protoss/02/P2B04uta","campaign\\protoss\\protoss02\\staredit\\wav\\P2B04uta.wav" __4},
	{W,0,"campaigns/protoss/02/P2B06pad","campaign\\protoss\\protoss02\\staredit\\wav\\P2B06pad.wav" __4},
	{W,0,"campaigns/protoss/02/P2B07uta","campaign\\protoss\\protoss02\\staredit\\wav\\P2B07uta.wav" __4},
	{W,0,"campaigns/protoss/02/P2B08uta","campaign\\protoss\\protoss02\\staredit\\wav\\P2B08uta.wav" __4},
	{W,0,"campaigns/protoss/02/P2B09pad","campaign\\protoss\\protoss02\\staredit\\wav\\P2B09pad.wav" __4},
	{W,0,"campaigns/protoss/02/P2B10uta","campaign\\protoss\\protoss02\\staredit\\wav\\P2B10uta.wav" __4},
	{W,0,"campaigns/protoss/02/P2B11ufe","campaign\\protoss\\protoss02\\staredit\\wav\\P2B11ufe.wav" __4},
	{W,0,"campaigns/protoss/02/P2M00ufe","campaign\\protoss\\protoss02\\staredit\\wav\\P2M00ufe.wav" __4},
	{W,0,"campaigns/protoss/02/P2M01ufe","campaign\\protoss\\protoss02\\staredit\\wav\\P2M01ufe.wav" __4},
	{E,0,"campaigns/protoss/03/scenario.chk","campaign\\protoss\\protoss03\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/03/P3B00ufe","campaign\\protoss\\protoss03\\staredit\\wav\\P3B00ufe.wav" __4},
	{W,0,"campaigns/protoss/03/P3B01pad","campaign\\protoss\\protoss03\\staredit\\wav\\P3B01pad.wav" __4},
	{W,0,"campaigns/protoss/03/P3B02pad","campaign\\protoss\\protoss03\\staredit\\wav\\P3B02pad.wav" __4},
	{W,0,"campaigns/protoss/03/P3B03ufe","campaign\\protoss\\protoss03\\staredit\\wav\\P3B03ufe.wav" __4},
	{W,0,"campaigns/protoss/03/P3M00ufe","campaign\\protoss\\protoss03\\staredit\\wav\\P3M00ufe.wav" __4},
	{W,0,"campaigns/protoss/03/P3M01pad","campaign\\protoss\\protoss03\\staredit\\wav\\P3M01pad.wav" __4},
	{E,0,"campaigns/protoss/04/scenario.chk","campaign\\protoss\\protoss04\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/04/ComBeep0","campaign\\protoss\\protoss04\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/04/P4B00pad","campaign\\protoss\\protoss04\\staredit\\wav\\P4B00pad.wav" __4},
	{W,0,"campaigns/protoss/04/P4B01pad","campaign\\protoss\\protoss04\\staredit\\wav\\P4B01pad.wav" __4},
	{W,0,"campaigns/protoss/04/P4B02pad","campaign\\protoss\\protoss04\\staredit\\wav\\P4B02pad.wav" __4},
	{W,0,"campaigns/protoss/04/P4B03pad","campaign\\protoss\\protoss04\\staredit\\wav\\P4B03pad.wav" __4},
	{W,0,"campaigns/protoss/04/P4M00uta","campaign\\protoss\\protoss04\\staredit\\wav\\P4M00uta.wav" __4},
	{W,0,"campaigns/protoss/04/P4M01pad","campaign\\protoss\\protoss04\\staredit\\wav\\P4M01pad.wav" __4},
	{W,0,"campaigns/protoss/04/P4M02uta","campaign\\protoss\\protoss04\\staredit\\wav\\P4M02uta.wav" __4},
	{W,0,"campaigns/protoss/04/P4M03ura","campaign\\protoss\\protoss04\\staredit\\wav\\P4M03ura.wav" __4},
	{W,0,"campaigns/protoss/04/P4M04pad","campaign\\protoss\\protoss04\\staredit\\wav\\P4M04pad.wav" __4},
	{W,0,"campaigns/protoss/04/P4M05ura","campaign\\protoss\\protoss04\\staredit\\wav\\P4M05ura.wav" __4},
	{W,0,"campaigns/protoss/04/P4M06pad","campaign\\protoss\\protoss04\\staredit\\wav\\P4M06pad.wav" __4},
	{W,0,"campaigns/protoss/04/P4M07uta","campaign\\protoss\\protoss04\\staredit\\wav\\P4M07uta.wav" __4},
	{W,0,"campaigns/protoss/04/P4M09pad","campaign\\protoss\\protoss04\\staredit\\wav\\P4M09pad.wav" __4},
	{W,0,"campaigns/protoss/04/P4M10uta","campaign\\protoss\\protoss04\\staredit\\wav\\P4M10uta.wav" __4},
	{W,0,"campaigns/protoss/04/P4M11ute","campaign\\protoss\\protoss04\\staredit\\wav\\P4M11ute.wav" __4},
	{W,0,"campaigns/protoss/04/P4M20uta","campaign\\protoss\\protoss04\\staredit\\wav\\P4M20uta.wav" __4},
	{W,0,"campaigns/protoss/04/zhyRdy00","campaign\\protoss\\protoss04\\staredit\\wav\\zhyRdy00.wav" __4},
	{W,0,"campaigns/protoss/04/zhyYes03","campaign\\protoss\\protoss04\\staredit\\wav\\zhyYes03.wav" __4},
	{W,0,"campaigns/protoss/04/zquRdy00","campaign\\protoss\\protoss04\\staredit\\wav\\zquRdy00.wav" __4},
	{W,0,"campaigns/protoss/04/ZZeRdy00","campaign\\protoss\\protoss04\\staredit\\wav\\ZZeRdy00.wav" __4},
	{E,0,"campaigns/protoss/05/scenario.chk","campaign\\protoss\\protoss05\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/05/ComBeep0","campaign\\protoss\\protoss05\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/05/P5B00pad","campaign\\protoss\\protoss05\\staredit\\wav\\P5B00pad.wav" __4},
	{W,0,"campaigns/protoss/05/P5B01uta","campaign\\protoss\\protoss05\\staredit\\wav\\P5B01uta.wav" __4},
	{W,0,"campaigns/protoss/05/P5B02pad","campaign\\protoss\\protoss05\\staredit\\wav\\P5B02pad.wav" __4},
	{W,0,"campaigns/protoss/05/P5B03uta","campaign\\protoss\\protoss05\\staredit\\wav\\P5B03uta.wav" __4},
	{W,0,"campaigns/protoss/05/P5B04uta","campaign\\protoss\\protoss05\\staredit\\wav\\P5B04uta.wav" __4},
	{W,0,"campaigns/protoss/05/P5B05pad","campaign\\protoss\\protoss05\\staredit\\wav\\P5B05pad.wav" __4},
	{W,0,"campaigns/protoss/05/P5B06uta","campaign\\protoss\\protoss05\\staredit\\wav\\P5B06uta.wav" __4},
	{W,0,"campaigns/protoss/05/P5B07uta","campaign\\protoss\\protoss05\\staredit\\wav\\P5B07uta.wav" __4},
	{W,0,"campaigns/protoss/05/P5B08pad","campaign\\protoss\\protoss05\\staredit\\wav\\P5B08pad.wav" __4},
	{W,0,"campaigns/protoss/05/P5M00udu","campaign\\protoss\\protoss05\\staredit\\wav\\P5M00udu.wav" __4},
	{W,0,"campaigns/protoss/05/P5M03uta","campaign\\protoss\\protoss05\\staredit\\wav\\P5M03uta.wav" __4},
	{W,0,"campaigns/protoss/05/P5M04udu","campaign\\protoss\\protoss05\\staredit\\wav\\P5M04udu.wav" __4},
	{E,0,"campaigns/protoss/06/scenario.chk","campaign\\protoss\\protoss06\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/06/ComBeep0","campaign\\protoss\\protoss06\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/06/P6B00uta","campaign\\protoss\\protoss06\\staredit\\wav\\P6B00uta.wav" __4},
	{W,0,"campaigns/protoss/06/P6B01ura","campaign\\protoss\\protoss06\\staredit\\wav\\P6B01ura.wav" __4},
	{W,0,"campaigns/protoss/06/P6B02uta","campaign\\protoss\\protoss06\\staredit\\wav\\P6B02uta.wav" __4},
	{W,0,"campaigns/protoss/06/P6M00tad","campaign\\protoss\\protoss06\\staredit\\wav\\P6M00tad.wav" __4},
	{W,0,"campaigns/protoss/06/P6M00uta","campaign\\protoss\\protoss06\\staredit\\wav\\P6M00uta.wav" __4},
	{W,0,"campaigns/protoss/06/P6M01uze","campaign\\protoss\\protoss06\\staredit\\wav\\P6M01uze.wav" __4},
	{W,0,"campaigns/protoss/06/P6M03uta","campaign\\protoss\\protoss06\\staredit\\wav\\P6M03uta.wav" __4},
	{W,0,"campaigns/protoss/06/P6M04uze","campaign\\protoss\\protoss06\\staredit\\wav\\P6M04uze.wav" __4},
	{W,0,"campaigns/protoss/06/P6M20uma","campaign\\protoss\\protoss06\\staredit\\wav\\P6M20uma.wav" __4},
	{W,0,"campaigns/protoss/06/P6M30uma","campaign\\protoss\\protoss06\\staredit\\wav\\P6M30uma.wav" __4},
	{W,0,"campaigns/protoss/06/P6M40uma","campaign\\protoss\\protoss06\\staredit\\wav\\P6M40uma.wav" __4},
	{W,0,"campaigns/protoss/06/pshBld03","campaign\\protoss\\protoss06\\staredit\\wav\\pshBld03.wav" __4},
	{W,0,"campaigns/protoss/06/TMaPss00","campaign\\protoss\\protoss06\\staredit\\wav\\TMaPss00.wav" __4},
	{W,0,"campaigns/protoss/06/ZBgRdy00","campaign\\protoss\\protoss06\\staredit\\wav\\ZBgRdy00.wav" __4},
	{W,0,"campaigns/protoss/06/ZZeRdy00","campaign\\protoss\\protoss06\\staredit\\wav\\ZZeRdy00.wav" __4},
	{W,0,"campaigns/protoss/06/ZZeYes01","campaign\\protoss\\protoss06\\staredit\\wav\\ZZeYes01.wav" __4},
	{W,0,"campaigns/protoss/06/ZZeYes03","campaign\\protoss\\protoss06\\staredit\\wav\\ZZeYes03.wav" __4},
	{E,0,"campaigns/protoss/07/scenario.chk","campaign\\protoss\\protoss07\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/07/ComBeep0","campaign\\protoss\\protoss07\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/07/P7B00ufd","campaign\\protoss\\protoss07\\staredit\\wav\\P7B00ufd.wav" __4},
	{W,0,"campaigns/protoss/07/P7B01uta","campaign\\protoss\\protoss07\\staredit\\wav\\P7B01uta.wav" __4},
	{W,0,"campaigns/protoss/07/P7B02ufd","campaign\\protoss\\protoss07\\staredit\\wav\\P7B02ufd.wav" __4},
	{W,0,"campaigns/protoss/07/P7B03uta","campaign\\protoss\\protoss07\\staredit\\wav\\P7B03uta.wav" __4},
	{W,0,"campaigns/protoss/07/P7B04ufd","campaign\\protoss\\protoss07\\staredit\\wav\\P7B04ufd.wav" __4},
	{W,0,"campaigns/protoss/07/P7B05ufd","campaign\\protoss\\protoss07\\staredit\\wav\\P7B05ufd.wav" __4},
	{W,0,"campaigns/protoss/07/P7B06uta","campaign\\protoss\\protoss07\\staredit\\wav\\P7B06uta.wav" __4},
	{W,0,"campaigns/protoss/07/P7B07ufd","campaign\\protoss\\protoss07\\staredit\\wav\\P7B07ufd.wav" __4},
	{W,0,"campaigns/protoss/07/P7B08uta","campaign\\protoss\\protoss07\\staredit\\wav\\P7B08uta.wav" __4},
	{W,0,"campaigns/protoss/07/P7M00pad","campaign\\protoss\\protoss07\\staredit\\wav\\P7M00pad.wav" __4},
	{W,0,"campaigns/protoss/07/P7M01uta","campaign\\protoss\\protoss07\\staredit\\wav\\P7M01uta.wav" __4},
	{W,0,"campaigns/protoss/07/P7M20uta","campaign\\protoss\\protoss07\\staredit\\wav\\P7M20uta.wav" __4},
	{W,0,"campaigns/protoss/07/P7M21pad","campaign\\protoss\\protoss07\\staredit\\wav\\P7M21pad.wav" __4},
	{W,0,"campaigns/protoss/07/P7M23uta","campaign\\protoss\\protoss07\\staredit\\wav\\P7M23uta.wav" __4},
	{W,0,"campaigns/protoss/07/pshBld03","campaign\\protoss\\protoss07\\staredit\\wav\\pshBld03.wav" __4},
	{E,0,"campaigns/protoss/08/scenario.chk","campaign\\protoss\\protoss08\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/08/ComBeep0","campaign\\protoss\\protoss08\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/08/ComBeep1","campaign\\protoss\\protoss08\\staredit\\wav\\ComBeep1.wav" __4},
	{W,0,"campaigns/protoss/08/P8B00ufd","campaign\\protoss\\protoss08\\staredit\\wav\\P8B00ufd.wav" __4},
	{W,0,"campaigns/protoss/08/P8B01ufd","campaign\\protoss\\protoss08\\staredit\\wav\\P8B01ufd.wav" __4},
	{W,0,"campaigns/protoss/08/P8B02ura","campaign\\protoss\\protoss08\\staredit\\wav\\P8B02ura.wav" __4},
	{W,0,"campaigns/protoss/08/P8B03ufd","campaign\\protoss\\protoss08\\staredit\\wav\\P8B03ufd.wav" __4},
	{W,0,"campaigns/protoss/08/P8M00ufd","campaign\\protoss\\protoss08\\staredit\\wav\\P8M00ufd.wav" __4},
	{W,0,"campaigns/protoss/08/P8M01pad","campaign\\protoss\\protoss08\\staredit\\wav\\P8M01pad.wav" __4},
	{W,0,"campaigns/protoss/08/P8M02uze","campaign\\protoss\\protoss08\\staredit\\wav\\P8M02uze.wav" __4},
	{W,0,"campaigns/protoss/08/P8M03pad","campaign\\protoss\\protoss08\\staredit\\wav\\P8M03pad.wav" __4},
	{W,0,"campaigns/protoss/08/P8M04uze","campaign\\protoss\\protoss08\\staredit\\wav\\P8M04uze.wav" __4},
	{W,0,"campaigns/protoss/08/P8M05pad","campaign\\protoss\\protoss08\\staredit\\wav\\P8M05pad.wav" __4},
	{W,0,"campaigns/protoss/08/P8M06uze","campaign\\protoss\\protoss08\\staredit\\wav\\P8M06uze.wav" __4},
	{W,0,"campaigns/protoss/08/P8M08pad","campaign\\protoss\\protoss08\\staredit\\wav\\P8M08pad.wav" __4},
	{W,0,"campaigns/protoss/08/pshBld03","campaign\\protoss\\protoss08\\staredit\\wav\\pshBld03.wav" __4},
	{E,0,"campaigns/protoss/09/scenario.chk","campaign\\protoss\\protoss09\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/09/ComBeep0","campaign\\protoss\\protoss09\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/09/P9B00uta","campaign\\protoss\\protoss09\\staredit\\wav\\P9B00uta.wav" __4},
	{W,0,"campaigns/protoss/09/P9B01uze","campaign\\protoss\\protoss09\\staredit\\wav\\P9B01uze.wav" __4},
	{W,0,"campaigns/protoss/09/P9B02uze","campaign\\protoss\\protoss09\\staredit\\wav\\P9B02uze.wav" __4},
	{W,0,"campaigns/protoss/09/P9B03uta","campaign\\protoss\\protoss09\\staredit\\wav\\P9B03uta.wav" __4},
	{W,0,"campaigns/protoss/09/P9B04ufd","campaign\\protoss\\protoss09\\staredit\\wav\\P9B04ufd.wav" __4},
	{E,0,"campaigns/protoss/10/scenario.chk","campaign\\protoss\\protoss10\\staredit\\scenario.chk" __4},
	{W,0,"campaigns/protoss/10/ComBeep0","campaign\\protoss\\protoss10\\staredit\\wav\\ComBeep0.wav" __4},
	{W,0,"campaigns/protoss/10/P9M00pad","campaign\\protoss\\protoss10\\staredit\\wav\\P9M00pad.wav" __4},
	{W,0,"campaigns/protoss/10/P9M02ura","campaign\\protoss\\protoss10\\staredit\\wav\\P9M02ura.wav" __4},
	{W,0,"campaigns/protoss/10/PAB00ufd","campaign\\protoss\\protoss10\\staredit\\wav\\PAB00ufd.wav" __4},
	{W,0,"campaigns/protoss/10/PAB01uta","campaign\\protoss\\protoss10\\staredit\\wav\\PAB01uta.wav" __4},
	{W,0,"campaigns/protoss/10/PAB02uta","campaign\\protoss\\protoss10\\staredit\\wav\\PAB02uta.wav" __4},
	{W,0,"campaigns/protoss/10/PAB03uze","campaign\\protoss\\protoss10\\staredit\\wav\\PAB03uze.wav" __4},
	{W,0,"campaigns/protoss/10/PAB05ura","campaign\\protoss\\protoss10\\staredit\\wav\\PAB05ura.wav" __4},
	{W,0,"campaigns/protoss/10/PAB06uta","campaign\\protoss\\protoss10\\staredit\\wav\\PAB06uta.wav" __4},
	{W,0,"campaigns/protoss/10/PAM00uta","campaign\\protoss\\protoss10\\staredit\\wav\\PAM00uta.wav" __4},

	{E,0,"campaigns/protoss/EstP0t.txt","rez\\EstP0t.txt" __4},
	{E,0,"campaigns/protoss/EstP01.txt","rez\\EstP01.txt" __4},
	{E,0,"campaigns/protoss/EstP02.txt","rez\\EstP02.txt" __4},
	{E,0,"campaigns/protoss/EstP03.txt","rez\\EstP03.txt" __4},
	{E,0,"campaigns/protoss/EstP04.txt","rez\\EstP04.txt" __4},
	{E,0,"campaigns/protoss/EstP05.txt","rez\\EstP05.txt" __4},
	{E,0,"campaigns/protoss/EstP06.txt","rez\\EstP06.txt" __4},
	{E,0,"campaigns/protoss/EstP07.txt","rez\\EstP07.txt" __4},
	{E,0,"campaigns/protoss/EstP08.txt","rez\\EstP08.txt" __4},
	{E,0,"campaigns/protoss/EstP09.txt","rez\\EstP09.txt" __4},
	{E,0,"campaigns/protoss/EstP10.txt","rez\\EstP10.txt" __4},

	// Music
	{W,0,"music/title","music\\title.wav" __4},
	{W,0,"music/terran/defeat","music\\tdefeat.wav" __4},
	{W,0,"music/terran/1","music\\terran1.wav" __4},
	{W,0,"music/terran/2","music\\terran2.wav" __4},
	{W,0,"music/terran/3","music\\terran3.wav" __4},
	{W,0,"music/terran/ready room","music\\trdyroom.wav" __4},
	{W,0,"music/terran/victory","music\\tvict.wav" __4},
	{W,0,"music/zerg/defeat","music\\zdefeat.wav" __4},
	{W,0,"music/zerg/1","music\\zerg1.wav" __4},
	{W,0,"music/zerg/2","music\\zerg2.wav" __4},
	{W,0,"music/zerg/3","music\\zerg3.wav" __4},
	{W,0,"music/zerg/ready room","music\\zrdyroom.wav" __4},
	{W,0,"music/zerg/victory","music\\zvict.wav" __4},
	{W,0,"music/protoss/defeat","music\\pdefeat.wav" __4},
	{W,0,"music/protoss/1","music\\protoss1.wav" __4},
	{W,0,"music/protoss/2","music\\protoss2.wav" __4},
	{W,0,"music/protoss/3","music\\protoss3.wav" __4},
	{W,0,"music/protoss/ready room","music\\prdyroom.wav" __4},
	{W,0,"music/protoss/victory","music\\pvict.wav" __4},
};

Control Todo[] = {
	{F,0,"","stardat.mpq" __4},

//	{G,0,"ui/blink","game\\blink.grp",0 __3},

	// UI
	{U,0,"ui/icons","game\\icons.grp",0 __3},
	{I,0,"ui/protoss","dlgs\\protoss.grp",0 __3},
	{I,0,"ui/terran","dlgs\\terran.grp",0 __3},
	{I,0,"ui/zerg","dlgs\\zerg.grp",0 __3},
	{H,0,"ui/aggicons","game\\aggicons.pcx",0 __3},
	{H,0,"ui/pconover","game\\pconover.pcx",0 __3},
	{H,0,"ui/pconsole","game\\pconsole.pcx",0 __3},
	{H,0,"ui/ppbrempt","game\\ppbrempt.pcx",0 __3},
	{H,0,"ui/ppbrfull","game\\ppbrfull.pcx",0 __3},
	{H,0,"ui/tblink","game\\tblink.pcx",0 __3},
	{H,0,"ui/tconover","game\\tconover.pcx",0 __3},
	{H,0,"ui/tconsole","game\\tconsole.pcx",0 __3},
	{H,0,"ui/tfontgam","game\\tfontgam.pcx",0 __3},
	{H,0,"ui/thpbar","game\\thpbar.pcx",0 __3},
	{H,0,"ui/tminimap","game\\tminimap.pcx",0 __3},
	{H,0,"ui/tpbrempt","game\\tpbrempt.pcx",0 __3},
	{H,0,"ui/tpbrfull","game\\tpbrfull.pcx",0 __3},
	{H,0,"ui/tselect","game\\tselect.pcx",0 __3},
	{H,0,"ui/tunit","game\\tunit.pcx",0 __3},
	{H,0,"ui/twire","game\\twire.pcx",0 __3},
	{H,0,"ui/zconover","game\\zconover.pcx",0 __3},
	{H,0,"ui/zconsole","game\\zconsole.pcx",0 __3},
	{H,0,"ui/zpbrempt","game\\zpbrempt.pcx",0 __3},
	{H,0,"ui/zpbrfull","game\\zpbrfull.pcx",0 __3},
	{H,0,"ui/tfont","glue\\title\\tFont.pcx",0 __3},
//	{H,0,"ui/tfont-beta","glue\\title\\tFont-beta.pcx",0 __3},
	{H,0,"ui/title","glue\\title\\title.pcx",0 __3},
//	{H,0,"ui/title-beta","glue\\title\\title-beta.pcx",0 __3},
	{H,0,"ui/Menu background without title","glue\\PalMm\\Backgnd.pcx",0 __3},
	{G,0,"ui/o022","unit\\thingy\\o022.grp",2 __3},
	{G,0,"ui/o032","unit\\thingy\\o032.grp",2 __3},
	{G,0,"ui/o048","unit\\thingy\\o048.grp",2 __3},
	{G,0,"ui/o062","unit\\thingy\\o062.grp",2 __3},
	{G,0,"ui/o072","unit\\thingy\\o072.grp",2 __3},
	{G,0,"ui/o094","unit\\thingy\\o094.grp",2 __3},
	{G,0,"ui/o110","unit\\thingy\\o110.grp",2 __3},
	{G,0,"ui/o122","unit\\thingy\\o122.grp",2 __3},
	{G,0,"ui/o146","unit\\thingy\\o146.grp",2 __3},
	{G,0,"ui/o224","unit\\thingy\\o224.grp",2 __3},
#if 0
	{G,0,"ui/od022","unit\\thingy\\od022.grp",2 __3},
	{G,0,"ui/od032","unit\\thingy\\od032.grp",2 __3},
	{G,0,"ui/od048","unit\\thingy\\od048.grp",2 __3},
	{G,0,"ui/od062","unit\\thingy\\od062.grp",2 __3},
	{G,0,"ui/od072","unit\\thingy\\od072.grp",2 __3},
	{G,0,"ui/od094","unit\\thingy\\od094.grp",2 __3},
	{G,0,"ui/od110","unit\\thingy\\od110.grp",2 __3},
	{G,0,"ui/od122","unit\\thingy\\od122.grp",2 __3},
	{G,0,"ui/od146","unit\\thingy\\od146.grp",2 __3},
	{G,0,"ui/od224","unit\\thingy\\od224.grp",2 __3},
#endif

	{H,0,"terran/briefing room","glue\\PalRt\\Backgnd.pcx",0 __3},
	{H,0,"terran/victory screen","glue\\PalTv\\Backgnd.pcx",0 __3},
	{H,0,"terran/defeat screen","glue\\PalTd\\Backgnd.pcx",0 __3},
	{H,0,"protoss/briefing room","glue\\PalRp\\Backgnd.pcx",0 __3},
	{H,0,"protoss/victory screen","glue\\PalPv\\Backgnd.pcx",0 __3},
	{H,0,"protoss/defeat screen","glue\\PalPd\\Backgnd.pcx",0 __3},
	{H,0,"zerg/briefing room","glue\\PalRz\\Backgnd.pcx",0 __3},
	{H,0,"zerg/victory screen","glue\\PalZv\\Backgnd.pcx",0 __3},
	{H,0,"zerg/defeat screen","glue\\PalZd\\Backgnd.pcx",0 __3},

	{H,0,"ui/readyt/butterr","Glue\\ReadyT\\ButTerr.pcx",0 __3},
	{H,0,"ui/readyt/objterr","Glue\\ReadyT\\ObjTerr.pcx",0 __3},
	{H,0,"ui/readyt/p1terr","Glue\\ReadyT\\P1Terr.pcx",0 __3},
	{H,0,"ui/readyt/p2terr","Glue\\ReadyT\\P2Terr.pcx",0 __3},
	{H,0,"ui/readyt/p3terr","Glue\\ReadyT\\P3Terr.pcx",0 __3},
	{H,0,"ui/readyt/p4terr","Glue\\ReadyT\\P4Terr.pcx",0 __3},
	{H,0,"ui/readyt/terrframe","glue\\readyt\\TerrFrame.pcx",0 __3},
	{H,0,"ui/readyt/terrframeh","glue\\readyt\\TerrFrameh.pcx",0 __3},
	{H,0,"ui/readyt/tframe1","glue\\ReadyT\\TFrame1.pcx",0 __3},
	{H,0,"ui/readyt/tframe2","glue\\ReadyT\\TFrame2.pcx",0 __3},
	{H,0,"ui/readyt/tframe3","glue\\ReadyT\\TFrame3.pcx",0 __3},
	{H,0,"ui/readyt/tframe4","glue\\ReadyT\\TFrame4.pcx",0 __3},
	{H,0,"ui/readyt/tframeh1","glue\\ReadyT\\TFrameH1.pcx",0 __3},
	{H,0,"ui/readyt/tframeh2","glue\\ReadyT\\TFrameH2.pcx",0 __3},
	{H,0,"ui/readyt/tframeh3","glue\\ReadyT\\TFrameH3.pcx",0 __3},
	{H,0,"ui/readyt/tframeh4","glue\\ReadyT\\TFrameH4.pcx",0 __3},
	{H,0,"ui/readyt/tutbtn","Glue\\ReadyT\\TutBtn.pcx",0 __3},
	{G,0,"cmdicons","unit\\cmdbtns\\cmdicons.grp",2 __3},
	{G,0,"pcmdbtns","unit\\cmdbtns\\pcmdbtns.grp",2 __3},
	{G,0,"tcmdbtns","unit\\cmdbtns\\tcmdbtns.grp",2 __3},
	{G,0,"zcmdbtns","unit\\cmdbtns\\zcmdbtns.grp",2 __3},

	// Cursors
	{G,0,"ui/cursors/arrow","cursor\\arrow.grp",0 __3},
	{G,0,"ui/cursors/drag","cursor\\Drag.grp",0 __3},
	{G,0,"ui/cursors/illegal","cursor\\Illegal.grp",0 __3},
	{G,0,"ui/cursors/magg","cursor\\MagG.grp",0 __3},
	{G,0,"ui/cursors/magr","cursor\\MagR.grp",0 __3},
	{G,0,"ui/cursors/magy","cursor\\MagY.grp",0 __3},
	{G,0,"ui/cursors/scrolld","cursor\\ScrollD.grp",0 __3},
	{G,0,"ui/cursors/scrolldl","cursor\\ScrollDL.grp",0 __3},
	{G,0,"ui/cursors/scrolldr","cursor\\ScrollDR.grp",0 __3},
	{G,0,"ui/cursors/scrolll","cursor\\ScrollL.grp",0 __3},
	{G,0,"ui/cursors/scrollr","cursor\\ScrollR.grp",0 __3},
	{G,0,"ui/cursors/scrollu","cursor\\ScrollU.grp",0 __3},
	{G,0,"ui/cursors/scrollul","cursor\\ScrollUL.grp",0 __3},
	{G,0,"ui/cursors/scrollur","cursor\\ScrollUR.grp",0 __3},
	{G,0,"ui/cursors/targg","cursor\\TargG.grp",0 __3},
	{G,0,"ui/cursors/targn","cursor\\TargN.grp",0 __3},
	{G,0,"ui/cursors/targr","cursor\\TargR.grp",0 __3},
	{G,0,"ui/cursors/targy","cursor\\TargY.grp",0 __3},
	{G,0,"ui/cursors/time","cursor\\Time.grp",0 __3},

	// Game sounds
	{W,0,"ui/button","sound\\misc\\button.wav" __4},
	{W,0,"ui/buzz","sound\\misc\\buzz.wav" __4},

	// Fonts
	// FIXME: These fonts are in a different format
#if 0
	{N,0,"font10","font\\font10.fnt" __4},
	{N,0,"font12","font\\font12.fnt" __4},
	{N,0,"font14","font\\font14.fnt" __4},
	{N,0,"font16","font\\font16.fnt" __4},
	{N,0,"font16x","font\\font16x.fnt" __4},
	{N,0,"font32","font\\font32.fnt" __4},
	{N,0,"font50","font\\font50.fnt" __4},
	{N,0,"font8","font\\font8.fnt" __4},
#endif

	// Tilesets
	{T,0,"ashworld/ashworld","tileset\\AshWorld" __4},
//	{R,0,"ashworld/ashworld","tileset\\AshWorld" __4},
	{G,0,"tilesets/ashworld/creep","tileset\\AshWorld.grp",1 __3},
	{T,0,"ashworld-nc/ashworld-nc","tileset\\AshWorld-nc" __4},
//	{R,0,"ashworld-nc/ashworld-nc","tileset\\AshWorld-nc" __4},
	{T,0,"badlands/badlands","tileset\\badlands" __4},
//	{R,0,"badlands/badlands","tileset\\badlands" __4},
	{G,0,"tilesets/badlands/creep","tileset\\badlands.grp",1 __3},
	{T,0,"badlands-nc/badlands-nc","tileset\\badlands-nc" __4},
//	{R,0,"badlands-nc/badlands-nc","tileset\\badlands-nc" __4},
	{T,0,"installation/installation","tileset\\Install" __4},
//	{R,0,"installation/installation","tileset\\install" __4},
	{G,0,"tilesets/installation/creep","tileset\\Install.grp",1 __3},
	{T,0,"jungle/jungle","tileset\\Jungle" __4},
//	{R,0,"jungle/jungle","tileset\\Jungle" __4},
	{G,0,"tilesets/jungle/creep","tileset\\Jungle.grp",1 __3},
	{T,0,"jungle-nc/jungle-nc","tileset\\Jungle-nc" __4},
//	{R,0,"jungle-nc/jungle-nc","tileset\\Jungle-nc" __4},
	{T,0,"platform/platform","tileset\\platform" __4},
//	{R,0,"platform/platform","tileset\\platform" __4},
	{G,0,"tilesets/platform/creep","tileset\\platform.grp",1 __3},

	// Neutral
	{G,0,"neutral/start location","unit\\thingy\\StartLoc.grp",0 __3},
	{G,0,"neutral/flamer","unit\\thingy\\flamer.grp",3 __3},
	{G,0,"neutral/smoke","unit\\thingy\\smoke.grp",3 __3},
	{G,0,"neutral/building burnc","unit\\thingy\\oFireC.grp",3 __3},
	{G,0,"neutral/building burnf","unit\\thingy\\oFireF.grp",3 __3},
	{G,0,"neutral/building burnv","unit\\thingy\\oFireV.grp",3 __3},

	{G,0,"neutral/missiles/blastcan","unit\\bullet\\blastcan.grp",1 __3},
	{G,0,"neutral/missiles/circle14","unit\\bullet\\circle14.grp",1 __3},
	{G,0,"neutral/missiles/dragbull","unit\\bullet\\dragbull.grp",1 __3},
	{G,0,"neutral/missiles/epbbul","unit\\bullet\\epbBul.grp",1 __3},
	{G,0,"neutral/missiles/ephfire","unit\\bullet\\ephFire.grp",1 __3},
	{G,0,"neutral/missiles/explo1","unit\\bullet\\explo1.grp",1 __3},
	{G,0,"neutral/missiles/eycbull","unit\\bullet\\eycBull.grp",1 __3},
	{G,0,"neutral/missiles/gemini","unit\\bullet\\gemini.grp",1 __3},
	{G,0,"neutral/missiles/grenade","unit\\bullet\\grenade.grp",1 __3},
	{G,0,"neutral/missiles/hks","unit\\bullet\\hks.grp",1 __3},
	{G,0,"neutral/missiles/missile","unit\\bullet\\missile.grp",1 __3},
	{G,0,"neutral/missiles/parasite","unit\\bullet\\parasite.grp",1 __3},
	{G,0,"neutral/missiles/pdriphit","unit\\bullet\\PDripHit.grp",1 __3},
	{G,0,"neutral/missiles/psibeam","unit\\bullet\\PsiBeam.grp",1 __3},
	{G,0,"neutral/missiles/pspark","unit\\bullet\\pspark.grp",1 __3},
	{G,0,"neutral/missiles/scvspark","unit\\bullet\\scvspark.grp",1 __3},
	{G,0,"neutral/missiles/shockbmb","unit\\bullet\\shockbmb.grp",1 __3},
	{G,0,"neutral/missiles/spore2","unit\\bullet\\Spore2.grp",1 __3},
	{G,0,"neutral/missiles/spores","unit\\bullet\\spores.grp",1 __3},
	{G,0,"neutral/missiles/squib1","unit\\bullet\\squib1.grp",1 __3},
	{G,0,"neutral/missiles/squib2","unit\\bullet\\squib2.grp",1 __3},
	{G,0,"neutral/missiles/tentacle","unit\\bullet\\Tentacle.grp",1 __3},
	{G,0,"neutral/missiles/tspark","unit\\bullet\\tspark.grp",1 __3},
	{G,0,"neutral/missiles/zspark","unit\\bullet\\zspark.grp",1 __3},

	{G,0,"neutral/units/ragnasaur ashworld critter","unit\\neutral\\Acritter.grp",0 __3},
	{G,0,"neutral/units/ragnasaur ashworld critter shadow","unit\\neutral\\nacShad.grp",0 __3},
	{G,0,"neutral/units/rhynadon badlands critter","unit\\neutral\\Bcritter.grp",0 __3},
	{G,0,"neutral/units/rhynadon badlands critter shadow","unit\\neutral\\nbcShad.grp",0 __3},
	{G,0,"neutral/units/bengalaas jungle critter","unit\\neutral\\Jcritter.grp",0 __3},
	{G,0,"neutral/units/bengalaas jungle critter shadow","unit\\neutral\\njcShad.grp",0 __3},
	{G,0,"neutral/units/geyser","unit\\neutral\\geyser.grp",1 __3},
	{G,0,"neutral/units/geyser shadow","unit\\neutral\\geyShad.grp",1 __3},
	{G,0,"neutral/units/mineral1","unit\\neutral\\min01.grp",1 __3},
	{G,0,"neutral/units/mineral1 shadow","unit\\neutral\\min01Sha.grp",1 __3},
	{G,0,"neutral/units/mineral2","unit\\neutral\\min02.grp",1 __3},
	{G,0,"neutral/units/mineral2 shadow","unit\\neutral\\min02Sha.grp",1 __3},
	{G,0,"neutral/units/mineral3","unit\\neutral\\min03.grp",1 __3},
	{G,0,"neutral/units/mineral3 shadow","unit\\neutral\\min03Sha.grp",1 __3},
	{G,0,"neutral/units/crashed battlecruiser","unit\\neutral\\Cbattle.grp",1 __3},
	{G,0,"neutral/units/crashed battlecruiser shadow","unit\\neutral\\cbaShad.grp",1 __3},
	{G,0,"neutral/units/data disk","unit\\neutral\\DataDisk.grp",1 __3},
	{G,0,"neutral/units/data disk shadow","unit\\neutral\\nddShad.grp",1 __3},
	{G,0,"neutral/units/data disk shadow2","unit\\neutral\\nddSha2.grp",1 __3},
	{G,0,"neutral/units/flag","unit\\neutral\\Flag.grp",0 __3},
	{G,0,"neutral/units/flag shadow","unit\\neutral\\nflShad.grp",1 __3},
	{G,0,"neutral/units/flag shadow2","unit\\neutral\\nflSha2.grp",1 __3},
	{G,0,"neutral/units/gas orb","unit\\neutral\\GasOrb.grp",1 __3},
	{G,0,"neutral/units/gas orb shadow","unit\\neutral\\ngoShad.grp",1 __3},
	{G,0,"neutral/units/gas sac","unit\\neutral\\GasSac.grp",1 __3},
	{G,0,"neutral/units/gas sac shadow","unit\\neutral\\ngsShad.grp",1 __3},
	{G,0,"neutral/units/gas tank","unit\\neutral\\GasTank.grp",1 __3},
	{G,0,"neutral/units/gas tank shadow","unit\\neutral\\ngcShad.grp",1 __3},
	{G,0,"neutral/units/ion cannon","unit\\neutral\\ion.grp",1 __3},
	{G,0,"neutral/units/kerrigan chrysalis","unit\\neutral\\kerrChry.grp",1 __3},
	{G,0,"neutral/units/kerrigan chrysalis shadow","unit\\neutral\\nkoShad.grp",1 __3},
	{G,0,"neutral/units/kerrigan egg","unit\\neutral\\KerrEgg.grp",1 __3},
	{G,0,"neutral/units/kerrigan egg shadow","unit\\neutral\\nkeShad.grp",1 __3},
	{G,0,"neutral/units/kerrigan egg shadow2","unit\\neutral\\nkeSha2.grp",1 __3},
	{G,0,"neutral/units/khaydarin crystal","unit\\neutral\\KhChunk.grp",1 __3},
	{G,0,"neutral/units/khaydarin01","unit\\neutral\\Khyad01.grp",1 __3},
	{G,0,"neutral/units/map revealer","unit\\neutral\\maprev.grp",1 __3},
	{G,0,"neutral/units/khaydarin crystal shadow2","unit\\neutral\\nkhSha2.grp",1 __3},
	{G,0,"neutral/units/khaydarin crystal shadow","unit\\neutral\\nkhShad.grp",1 __3},
	{G,0,"neutral/units/ore chunk","unit\\neutral\\OreChunk.grp",1 __3},
	{G,0,"neutral/units/ore chunk shadow","unit\\neutral\\norShad.grp",1 __3},
	{G,0,"neutral/units/psi emitter","unit\\neutral\\PsiEmit.grp",1 __3},
	{G,0,"neutral/units/psi emitter shadow","unit\\neutral\\npsShad.grp",1 __3},
	{G,0,"neutral/units/psi emitter shadow2","unit\\neutral\\npsSha2.grp",1 __3},
	{G,0,"neutral/units/starbase","unit\\neutral\\starbase.grp",1 __3},
	{G,0,"neutral/units/stasis","unit\\neutral\\stasis.grp",1 __3},
	{G,0,"neutral/units/temple","unit\\neutral\\temple.grp",1 __3},

#if 0
	{G,0,"neutral/units/pg1deb","unit\\flingy\\pg1deb.grp",1 __3},
	{G,0,"neutral/units/pg2deb","unit\\flingy\\pg2deb.grp",1 __3},
	{G,0,"neutral/units/pg3deb","unit\\flingy\\pg3deb.grp",1 __3},
	{G,0,"neutral/units/pg4deb","unit\\flingy\\pg4deb.grp",1 __3},
	{G,0,"neutral/units/pg5deb","unit\\flingy\\pg5deb.grp",1 __3},
	{G,0,"neutral/units/pscdeb","unit\\flingy\\pscdeb.grp",1 __3},
	{G,0,"neutral/units/tg5deb","unit\\flingy\\tg5deb.grp",1 __3},
#endif

	{G,0,"tilesets/badlands/thingy/HDRock01","unit\\thingy\\tileset\\Badlands\\HDRock01.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock02","unit\\thingy\\tileset\\Badlands\\HDRock02.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock03","unit\\thingy\\tileset\\Badlands\\HDRock03.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock04","unit\\thingy\\tileset\\Badlands\\HDRock04.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock05","unit\\thingy\\tileset\\Badlands\\HDRock05.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock06","unit\\thingy\\tileset\\Badlands\\HDRock06.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock07","unit\\thingy\\tileset\\Badlands\\HDRock07.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock08","unit\\thingy\\tileset\\Badlands\\HDRock08.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock1S","unit\\thingy\\tileset\\Badlands\\HDRock1S.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock2S","unit\\thingy\\tileset\\Badlands\\HDRock2S.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock3S","unit\\thingy\\tileset\\Badlands\\HDRock3S.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDRock4S","unit\\thingy\\tileset\\Badlands\\HDRock4S.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDTree01","unit\\thingy\\tileset\\Badlands\\HDTree01.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDTree02","unit\\thingy\\tileset\\Badlands\\HDTree02.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDTree03","unit\\thingy\\tileset\\Badlands\\HDTree03.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDTree04","unit\\thingy\\tileset\\Badlands\\HDTree04.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HDVent01","unit\\thingy\\tileset\\Badlands\\HDVent01.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/HGTree01","unit\\thingy\\tileset\\Badlands\\HGTree01.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop01","unit\\thingy\\tileset\\Badlands\\LCShop01.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop02","unit\\thingy\\tileset\\Badlands\\LCShop02.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop03","unit\\thingy\\tileset\\Badlands\\LCShop03.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop04","unit\\thingy\\tileset\\Badlands\\LCShop04.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop05","unit\\thingy\\tileset\\Badlands\\LCShop05.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop06","unit\\thingy\\tileset\\Badlands\\LCShop06.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop07","unit\\thingy\\tileset\\Badlands\\LCShop07.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop08","unit\\thingy\\tileset\\Badlands\\LCShop08.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShop09","unit\\thingy\\tileset\\Badlands\\LCShop09.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCShopAA","unit\\thingy\\tileset\\Badlands\\LCShopAA.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign01","unit\\thingy\\tileset\\Badlands\\LCSign01.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign02","unit\\thingy\\tileset\\Badlands\\LCSign02.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign03","unit\\thingy\\tileset\\Badlands\\LCSign03.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign04","unit\\thingy\\tileset\\Badlands\\LCSign04.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign05","unit\\thingy\\tileset\\Badlands\\LCSign05.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign06","unit\\thingy\\tileset\\Badlands\\LCSign06.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign07","unit\\thingy\\tileset\\Badlands\\LCSign07.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign08","unit\\thingy\\tileset\\Badlands\\LCSign08.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSign09","unit\\thingy\\tileset\\Badlands\\LCSign09.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSignAA","unit\\thingy\\tileset\\Badlands\\LCSignAA.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSignBB","unit\\thingy\\tileset\\Badlands\\LCSignBB.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LCSignCC","unit\\thingy\\tileset\\Badlands\\LCSignCC.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LDTree1S","unit\\thingy\\tileset\\Badlands\\LDTree1S.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LDTree2S","unit\\thingy\\tileset\\Badlands\\LDTree2S.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LDTree3S","unit\\thingy\\tileset\\Badlands\\LDTree3S.grp",1 __3},
	{G,0,"tilesets/badlands/thingy/LDTree4S","unit\\thingy\\tileset\\Badlands\\LDTree4S.grp",1 __3},

	{G,0,"tilesets/jungle/thingy/dd025","unit\\thingy\\tileset\\Jungle\\dd025.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd026","unit\\thingy\\tileset\\Jungle\\dd026.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd027","unit\\thingy\\tileset\\Jungle\\dd027.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd028","unit\\thingy\\tileset\\Jungle\\dd028.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd029","unit\\thingy\\tileset\\Jungle\\dd029.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd030","unit\\thingy\\tileset\\Jungle\\dd030.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd031","unit\\thingy\\tileset\\Jungle\\dd031.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd055","unit\\thingy\\tileset\\Jungle\\dd055.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd056","unit\\thingy\\tileset\\Jungle\\dd056.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd075","unit\\thingy\\tileset\\Jungle\\dd075.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd076","unit\\thingy\\tileset\\Jungle\\dd076.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd077","unit\\thingy\\tileset\\Jungle\\dd077.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd078","unit\\thingy\\tileset\\Jungle\\dd078.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd079","unit\\thingy\\tileset\\Jungle\\dd079.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd080","unit\\thingy\\tileset\\Jungle\\dd080.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd081","unit\\thingy\\tileset\\Jungle\\dd081.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd091","unit\\thingy\\tileset\\Jungle\\dd091.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd203","unit\\thingy\\tileset\\Jungle\\dd203.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd204","unit\\thingy\\tileset\\Jungle\\dd204.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd205","unit\\thingy\\tileset\\Jungle\\dd205.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd206","unit\\thingy\\tileset\\Jungle\\dd206.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd207","unit\\thingy\\tileset\\Jungle\\dd207.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd209","unit\\thingy\\tileset\\Jungle\\dd209.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd210","unit\\thingy\\tileset\\Jungle\\dd210.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/dd211","unit\\thingy\\tileset\\Jungle\\dd211.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/HDRock01","unit\\thingy\\tileset\\Jungle\\HDRock01.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/HDRock02","unit\\thingy\\tileset\\Jungle\\HDRock02.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/HDRock03","unit\\thingy\\tileset\\Jungle\\HDRock03.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/HDRock04","unit\\thingy\\tileset\\Jungle\\HDRock04.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/HDRock1s","unit\\thingy\\tileset\\Jungle\\HDRock1s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/HDRock2s","unit\\thingy\\tileset\\Jungle\\HDRock2s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/HDRock3s","unit\\thingy\\tileset\\Jungle\\HDRock3s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/HDRock4s","unit\\thingy\\tileset\\Jungle\\HDRock4s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/JUbush01","unit\\thingy\\tileset\\Jungle\\JUbush01.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/JUbush03","unit\\thingy\\tileset\\Jungle\\JUbush03.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/JUbush05","unit\\thingy\\tileset\\Jungle\\JUbush05.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/JUbush1S","unit\\thingy\\tileset\\Jungle\\JUbush1S.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/JUbush3s","unit\\thingy\\tileset\\Jungle\\JUbush3s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/JUbush5s","unit\\thingy\\tileset\\Jungle\\JUbush5s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/LDtree01","unit\\thingy\\tileset\\Jungle\\LDtree01.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/LDtree02","unit\\thingy\\tileset\\Jungle\\LDtree02.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/LDtree03","unit\\thingy\\tileset\\Jungle\\LDtree03.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/LDtree04","unit\\thingy\\tileset\\Jungle\\LDtree04.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/LDtree1s","unit\\thingy\\tileset\\Jungle\\LDtree1s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/LDtree2s","unit\\thingy\\tileset\\Jungle\\LDtree2s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/LDtree3s","unit\\thingy\\tileset\\Jungle\\LDtree3s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/LDtree4s","unit\\thingy\\tileset\\Jungle\\LDtree4s.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/tree01","unit\\thingy\\tileset\\Jungle\\tree01.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/tree02","unit\\thingy\\tileset\\Jungle\\tree02.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/tree03","unit\\thingy\\tileset\\Jungle\\tree03.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/tree04","unit\\thingy\\tileset\\Jungle\\tree04.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/tree1sha","unit\\thingy\\tileset\\Jungle\\tree1sha.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/tree2sha","unit\\thingy\\tileset\\Jungle\\tree2sha.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/tree3sha","unit\\thingy\\tileset\\Jungle\\tree3sha.grp",1 __3},
	{G,0,"tilesets/jungle/thingy/tree4sha","unit\\thingy\\tileset\\Jungle\\tree4sha.grp",1 __3},

	// Terran unit graphics
	{G,0,"terran/units/civilian","unit\\neutral\\civilian.grp",0 __3},
	{G,0,"terran/units/civilian shadow","unit\\neutral\\nciShad.grp",0 __3},
	{G,0,"terran/units/academy","unit\\terran\\Academy.grp",0 __3},
	{G,0,"terran/units/academy-t","unit\\terran\\AcademyT.grp",0 __3},
	{G,0,"terran/units/battlecruiser","unit\\terran\\BattleCr.grp",0 __3},
	{G,0,"terran/units/battlecruiser glow","unit\\thingy\\tbaGlow.grp",3 __3},
	{G,0,"terran/units/armory","unit\\terran\\chemlab.grp",0 __3},
	{G,0,"terran/units/armory-t","unit\\terran\\chemlabT.grp",0 __3},
	{G,0,"terran/units/comsat station","unit\\terran\\ComSat.grp",0 __3},
	{G,0,"terran/units/comsat station-c","unit\\terran\\ComSatC.grp",0 __3},
	{G,0,"terran/units/comsat station-t","unit\\terran\\ComSatT.grp",0 __3},
	{G,0,"terran/units/command center","unit\\terran\\control.grp",0 __3},
	{G,0,"terran/units/command center-t","unit\\terran\\controlT.grp",  0 __3},
	{G,0,"terran/units/supply depot","unit\\terran\\Depot.grp",0 __3},
	{G,0,"terran/units/supply depot-t","unit\\terran\\DepotT.grp",0 __3},
	{G,0,"terran/units/dropship","unit\\terran\\dropship.grp",0 __3},
	{G,0,"terran/units/dropship glow","unit\\thingy\\tdrGlow.grp",3 __3},
	{G,0,"terran/units/control tower-c","unit\\terran\\DryDockC.grp",0 __3},
	{G,0,"terran/units/control tower","unit\\terran\\DryDocks.grp",0 __3},
	{G,0,"terran/units/control tower-t","unit\\terran\\DryDockT.grp",0 __3},
	{G,0,"terran/units/factory","unit\\terran\\factory.grp",0 __3},
	{G,0,"terran/units/factory-t","unit\\terran\\factoryT.grp",0 __3},
	{G,0,"terran/units/firebat","unit\\terran\\firebat.grp",0 __3},
	{G,0,"terran/units/covert ops","unit\\terran\\GeneLab.grp",0 __3},
	{G,0,"terran/units/covert ops-c","unit\\terran\\GeneLabC.grp",0 __3},
	{G,0,"terran/units/covert ops-t","unit\\terran\\GeneLabT.grp",0 __3},
	{G,0,"terran/units/ghost","unit\\terran\\ghost.grp",0 __3},
	{G,0,"terran/units/goliath","unit\\terran\\goliath.grp",0 __3},
	{G,0,"terran/units/goliath-t","unit\\terran\\goliathT.grp",0 __3},
	{G,0,"terran/units/lowm/dropship","unit\\terran\\LowM\\Dropship.grp",0 __3},
	{G,0,"terran/units/lowm/wraith","unit\\terran\\LowM\\Phoenix.grp",0 __3},
	{G,0,"terran/units/machine shop-c","unit\\terran\\machineC.grp",0 __3},
	{G,0,"terran/units/machine shop","unit\\terran\\machines.grp",0 __3},
	{G,0,"terran/units/marine","unit\\terran\\marine.grp",0 __3},
	{G,0,"terran/units/missile turret","unit\\terran\\missile.grp",0 __3},
	{G,0,"terran/units/missile turret-t","unit\\terran\\missileT.grp",0 __3},
	{G,0,"terran/units/nuke missile","unit\\terran\\nukemiss.grp",0 __3},
	{G,0,"terran/units/nuke explosion","unit\\thingy\\NukeHit.grp",3 __3},
	{G,0,"terran/units/nuclear silo-c","unit\\terran\\NukeSilC.grp",0 __3},
	{G,0,"terran/units/nuclear silo","unit\\terran\\nukesilo.grp",0 __3},
	{G,0,"terran/units/nuclear silo-t","unit\\terran\\NukeSilT.grp",0 __3},
	{G,0,"terran/units/wraith","unit\\terran\\phoenix.grp",0 __3},
	{G,0,"terran/units/wraith glow","unit\\thingy\\tphGlow.grp",3 __3},
	{G,0,"terran/units/physics lab","unit\\terran\\physics.grp",0 __3},
	{G,0,"terran/units/physics lab-c","unit\\terran\\physicsC.grp",0 __3},
	{G,0,"terran/units/bunker","unit\\terran\\PillBox.grp",0 __3},
	{G,0,"terran/units/bunker-t","unit\\terran\\PillBoxT.grp",0 __3},
	{G,0,"terran/units/refinery","unit\\terran\\refinery.grp",0 __3},
	{G,0,"terran/units/science facility","unit\\terran\\research.grp",0 __3},
	{G,0,"terran/units/science facility-t","unit\\terran\\ResearcT.grp",0 __3},
	{G,0,"terran/units/scv","unit\\terran\\SCV.grp",0 __3},
	{G,0,"terran/units/scv glow","unit\\thingy\\tscGlow.grp",3 __3},
	{G,0,"terran/units/vulture spider mine","unit\\terran\\Spider.grp",0 __3},
	{G,0,"terran/units/siege tank siege","unit\\terran\\stank.grp",0 __3},
	{G,0,"terran/units/siege tank siege-t","unit\\terran\\stankt.grp",0 __3},
	{G,0,"terran/units/starport","unit\\terran\\starport.grp",0 __3},
	{G,0,"terran/units/starport-t","unit\\terran\\StarpoT.grp",0 __3},
	{G,0,"terran/units/academy shadow","unit\\terran\\tacShad.grp",0 __3},
	{G,0,"terran/units/siege tank tank","unit\\terran\\tank.grp",0 __3},
	{G,0,"terran/units/siege tank tank-t","unit\\terran\\tankt.grp",0 __3},
	{G,0,"terran/units/barracks","unit\\terran\\TBarrack.grp",0 __3},
	{G,0,"terran/units/barracks shadow","unit\\terran\\tbrShad.grp",0 __3},
	{G,0,"terran/units/command center shadow","unit\\terran\\tccShad.grp",0 __3},
	{G,0,"terran/units/beacon overlay","unit\\terran\\tCirGlow.grp",0 __3},
	{G,0,"terran/units/armory shadow","unit\\terran\\tclShad.grp",0 __3},
	{G,0,"terran/units/comsat station shadow","unit\\terran\\tcsShad.grp",0 __3},
	{G,0,"terran/units/control tower shadow","unit\\terran\\tddShad.grp",0 __3},
	{G,0,"terran/units/supply depot shadow","unit\\terran\\tdeShad.grp",0 __3},
	{G,0,"terran/units/factory shadow","unit\\terran\\tfaShad.grp",0 __3},
	{G,0,"terran/units/firebat shadow","unit\\terran\\tfbShad.grp",0 __3},
	{G,0,"terran/units/ghost death","unit\\terran\\tghDeath.grp",0 __3},
	{G,0,"terran/units/ghost shadow","unit\\terran\\tghShad.grp",0 __3},
	{G,0,"terran/units/covert ops shadow","unit\\terran\\tglShad.grp",0 __3},
	{G,0,"terran/units/goliath shadow","unit\\terran\\tgoShad.grp",0 __3},
	{G,0,"terran/units/marine death","unit\\terran\\tmaDeath.grp",0 __3},
	{G,0,"terran/units/beacon","unit\\terran\\tMarker.grp",0 __3},
	{G,0,"terran/units/marine shadow","unit\\terran\\tmaShad.grp",0 __3},
	{G,0,"terran/units/missile turret shadow","unit\\terran\\tmiShad.grp",0 __3},
	{G,0,"terran/units/machine shop shadow","unit\\terran\\tmsShad.grp",0 __3},
	{G,0,"terran/units/nuclear silo shadow","unit\\terran\\tnsShad.grp",0 __3},
	{G,0,"terran/units/bunker shadow","unit\\terran\\tpbShad.grp",0 __3},
	{G,0,"terran/units/physics lab shadow","unit\\terran\\tplShad.grp",0 __3},
	{G,0,"terran/units/refinery shadow","unit\\terran\\treShad.grp",0 __3},
	{G,0,"terran/units/science facility shadow","unit\\terran\\trlShad.grp",0 __3},
	{G,0,"terran/units/vulture spider mine shadow","unit\\terran\\tsmShad.grp",0 __3},
	{G,0,"terran/units/starport shadow","unit\\terran\\tspShad.grp",0 __3},
	{G,0,"terran/units/siege tank siege shadow","unit\\terran\\tstShad.grp",0 __3},
	{G,0,"terran/units/siege tank tank shadow","unit\\terran\\ttaShad.grp",0 __3},
	{G,0,"terran/units/science vessel shadow","unit\\terran\\tveShad.grp",0 __3},
	{G,0,"terran/units/engineering bay shadow","unit\\terran\\twpShad.grp",0 __3},
	{G,0,"terran/units/kerrigan","unit\\terran\\ughost.grp",0 __3},
	{G,0,"terran/units/kerrigan shadow","unit\\terran\\ughShad.grp",0 __3},
	{G,0,"terran/units/vulture","unit\\terran\\Vulture.grp",0 __3},
	{G,0,"terran/units/engineering bay","unit\\terran\\weaponpl.grp",0 __3},
	{G,0,"terran/units/engineering bay-t","unit\\terran\\weaponpT.grp",0 __3},
	{G,0,"terran/units/science vessel","unit\\terran\\wessel.grp",0 __3},
	{G,0,"terran/units/science vessel-t","unit\\terran\\wesselt.grp",0 __3},

	{G,0,"terran/units/building construction large","unit\\terran\\TBldLrg.grp",0 __3},
	{G,0,"terran/units/building construction medium","unit\\terran\\tBldMed.grp",0 __3},
	{G,0,"terran/units/building construction small","unit\\terran\\TBldSml.grp",0 __3},
	{G,0,"terran/units/building construction small shadow","unit\\terran\\tb1Shad.grp",0 __3},
	{G,0,"terran/units/building construction large shadow","unit\\terran\\tb2Shad.grp",0 __3},
	{G,0,"terran/units/building construction medium shadow","unit\\terran\\tb3Shad.grp",0 __3},
	{G,0,"terran/units/rubble large","unit\\thingy\\RubbleL.grp",0 __3},
	{G,0,"terran/units/rubble small","unit\\thingy\\RubbleS.grp",0 __3},
	{G,0,"terran/explosion small","unit\\thingy\\tbangs.grp",3 __3},
	{G,0,"terran/explosion medium","unit\\thingy\\tbangl.grp",3 __3},
	{G,0,"terran/explosion large","unit\\thingy\\tbangx.grp",3 __3},
	{G,0,"terran/dark swarm","unit\\thingy\\Dswarm.grp",3 __3},
	{G,0,"terran/spider mine explosion","unit\\thingy\\tmnExplo.grp",3 __3},
	{G,0,"terran/spider mine smoke","unit\\thingy\\GreSmoke.grp",3 __3},
	{G,0,"terran/spider mine hit","unit\\thingy\\efgHit.grp",3 __3},
	{G,0,"terran/gemini missile trail","unit\\thingy\\smoke.grp",3 __3},
	{G,0,"terran/tank turret attack overlay","unit\\thingy\\esiFire.grp",3 __3},
	{G,0,"terran/tank turret attack overlay2","unit\\thingy\\ettFlash.grp",3 __3},
	{G,0,"terran/laser","unit\\thingy\\elbfireW.grp",3 __3},
	{G,0,"terran/laser2","unit\\thingy\\elbfire.grp",3 __3},

	// Protoss unit graphics
	{G,0,"protoss/units/rubble large","unit\\thingy\\prubblel.grp",0 __3},
	{G,0,"protoss/units/rubble small","unit\\thingy\\prubbles.grp",0 __3},
	{G,0,"protoss/units/arbiter","unit\\protoss\\arbiter.grp",0 __3},
	{G,0,"protoss/units/templar archives","unit\\protoss\\archives.grp",0 __3},
	{G,0,"protoss/units/archon","unit\\protoss\\archon.grp",0 __3},
	{G,0,"protoss/units/archon-t","unit\\protoss\\archonT.grp",0 __3},
	{G,0,"protoss/units/archon-t2","unit\\protoss\\archonT2.grp",0 __3},
	{G,0,"protoss/units/assimilator","unit\\protoss\\assim.grp",0 __3},
	{G,0,"protoss/units/observatory","unit\\protoss\\beacon.grp",0 __3},
	{G,0,"protoss/units/carrier","unit\\protoss\\carrier.grp",0 __3},
	{G,0,"protoss/units/citadel of adun","unit\\protoss\\citadel.grp",0 __3},
	{G,0,"protoss/units/dragoon","unit\\protoss\\dragoon.grp",0 __3},
	{G,0,"protoss/units/dark templar","unit\\protoss\\dtemplar.grp",0 __3},
	{G,0,"protoss/units/forge","unit\\protoss\\forge.grp",0 __3},
	{G,0,"protoss/units/forge-t","unit\\protoss\\forgeT.grp",0 __3},
	{G,0,"protoss/units/gateway","unit\\protoss\\gateway.grp",0 __3},
	{G,0,"protoss/units/cybernetics core","unit\\protoss\\gencore.grp",0 __3},
	{G,0,"protoss/units/cybernetics core-t","unit\\protoss\\gencoreT.grp",0 __3},
	{G,0,"protoss/units/intercep","unit\\protoss\\Intercep.grp",0 __3},
	{G,0,"protoss/units/lowm/arbiter","unit\\protoss\\LowM\\arbiter.grp",0 __3},
	{G,0,"protoss/units/lowm/scout","unit\\protoss\\LowM\\scout.grp",0 __3},
	{G,0,"protoss/units/lowm/shuttle","unit\\protoss\\LowM\\shuttle.grp",0 __3},
	{G,0,"protoss/units/lowm/texture","unit\\protoss\\LowM\\texture.grp",0 __3},
	{G,0,"protoss/units/lowm/observer","unit\\protoss\\LowM\\witness.grp",0 __3},
	{G,0,"protoss/units/nexus","unit\\protoss\\nexus.grp",0 __3},
	{G,0,"protoss/units/pacshad","unit\\protoss\\pacShad.grp",0 __3},
	{G,0,"protoss/units/passhad","unit\\protoss\\pasShad.grp",0 __3},
	{G,0,"protoss/units/paushad","unit\\protoss\\pauShad.grp",0 __3},
	{G,0,"protoss/units/pb1glow","unit\\protoss\\pb1Glow.grp",0 __3},
	{G,0,"protoss/units/pbaglow","unit\\protoss\\pbaGlow.grp",0 __3},
	{G,0,"protoss/units/pbashad","unit\\protoss\\pbaShad.grp",0 __3},
	{G,0,"protoss/units/pbeshad","unit\\protoss\\pbeShad.grp",0 __3},
	{G,0,"protoss/units/pcirglow","unit\\protoss\\pCirGlow.grp",0 __3},
	{G,0,"protoss/units/pcishad","unit\\protoss\\pciShad.grp",0 __3},
	{G,0,"protoss/units/pdrdeath","unit\\protoss\\pdrDeath.grp",0 __3},
	{G,0,"protoss/units/pdrshad","unit\\protoss\\pdrShad.grp",0 __3},
	{G,0,"protoss/units/pfoshad","unit\\protoss\\pfoShad.grp",0 __3},
	{G,0,"protoss/units/pgashad","unit\\protoss\\pgaShad.grp",0 __3},
	{G,0,"protoss/units/pgcshad","unit\\protoss\\pgcShad.grp",0 __3},
	{G,0,"protoss/units/photon cannon","unit\\protoss\\photon.grp",0 __3},
	{G,0,"protoss/units/beacon","unit\\protoss\\pMarker.grp",0 __3},
	{G,0,"protoss/units/pneglow","unit\\protoss\\pneGlow.grp",0 __3},
	{G,0,"protoss/units/pneshad","unit\\protoss\\pneShad.grp",0 __3},
	{G,0,"protoss/units/ppbshad","unit\\protoss\\ppbShad.grp",0 __3},
	{G,0,"protoss/units/ppyshad","unit\\protoss\\ppyShad.grp",0 __3},
	{G,0,"protoss/units/arbiter tribunal","unit\\protoss\\prism.grp",0 __3},
	{G,0,"protoss/units/probe","unit\\protoss\\probe.grp",0 __3},
	{G,0,"protoss/units/proshad","unit\\protoss\\proShad.grp",0 __3},
	{G,0,"protoss/units/psgglow","unit\\protoss\\psgGlow.grp",0 __3},
	{G,0,"protoss/units/psgshad","unit\\protoss\\psgShad.grp",0 __3},
	{G,0,"protoss/units/pstshad","unit\\protoss\\pstShad.grp",0 __3},
	{G,0,"protoss/units/pteshad","unit\\protoss\\pteShad.grp",0 __3},
	{G,0,"protoss/units/ptrshad","unit\\protoss\\ptrShad.grp",0 __3},
	{G,0,"protoss/units/pwashad","unit\\protoss\\pwaShad.grp",0 __3},
	{G,0,"protoss/units/pylon","unit\\protoss\\pylon.grp",0 __3},
	{G,0,"protoss/units/pzeshad","unit\\protoss\\pzeShad.grp",0 __3},
	{G,0,"protoss/units/robotics facility","unit\\protoss\\robotic.grp",0 __3},
	{G,0,"protoss/units/sapper","unit\\protoss\\sapper.grp",0 __3},
	{G,0,"protoss/units/shield battery","unit\\protoss\\sbattery.grp",0 __3},
	{G,0,"protoss/units/scout","unit\\protoss\\scout.grp",0 __3},
	{G,0,"protoss/units/shuttle","unit\\protoss\\shuttle.grp",0 __3},
	{G,0,"protoss/units/stargate","unit\\protoss\\stargate.grp",0 __3},
	{G,0,"protoss/units/robotics support bay","unit\\protoss\\stasis.grp",0 __3},
	{G,0,"protoss/units/high templar","unit\\protoss\\templar.grp",0 __3},
	{G,0,"protoss/units/texture","unit\\protoss\\texture.grp",0 __3},
	{G,0,"protoss/units/reaver","unit\\protoss\\trilob.grp",0 __3},
	{G,0,"protoss/units/fleet beacon","unit\\protoss\\warp.grp",0 __3},
	{G,0,"protoss/units/observer","unit\\protoss\\witness.grp",0 __3},
	{G,0,"protoss/units/zealot","unit\\protoss\\zealot.grp",0 __3},
	{G,0,"protoss/units/shield","unit\\thingy\\pshield.grp",0 __3},
	{G,0,"protoss/units/bluetrail","unit\\thingy\\HKTrail.grp",0 __3},
	{G,0,"protoss/units/scout glow","unit\\thingy\\pscGlow.grp",0 __3},
	{G,0,"protoss/units/shuttle glow","unit\\thingy\\pshGlow.grp",0 __3},
	{G,0,"protoss/units/carrier glow","unit\\thingy\\pcaGlow.grp",0 __3},
	{G,0,"protoss/units/scarab explode","unit\\thingy\\psaExplo.grp",0 __3},
	{G,0,"protoss/units/anti-matter missle","unit\\thingy\\HKexplod.grp",0 __3},
	{G,0,"protoss/units/plasma shields?","unit\\thingy\\plasma.grp",0 __3},
	{G,0,"protoss/units/psionic shock wave","unit\\thingy\\emsHit.grp",0 __3},
	{G,0,"protoss/units/haluciantion cast","unit\\thingy\\eveCast.grp",0 __3},
	{G,0,"protoss/units/halucination cast 2","unit\\thingy\\halmind.grp",0 __3},
	{G,0,"protoss/units/psionic storm","unit\\thingy\\psiStorm.grp",0 __3},

	// Zerg unit graphics
	{G,0,"zerg/units/rubble large","unit\\thingy\\ZRubbleL.grp",0 __3},
	{G,0,"zerg/units/rubble small","unit\\thingy\\ZRubbleS.grp",0 __3},
	{G,0,"zerg/units/scourge","unit\\zerg\\avenger.grp",0 __3},
	{G,0,"zerg/units/scourge birth","unit\\zerg\\zavBirth.grp",0 __3},
	{G,0,"zerg/units/scourge death","unit\\zerg\\zavDeath.grp",0 __3},
	{G,0,"zerg/units/scourge explosion","unit\\zerg\\zavExplo.grp",0 __3},
	{G,0,"zerg/units/broodling","unit\\zerg\\brood.grp",0 __3},
	{G,0,"zerg/units/broodling shadow","unit\\zerg\\zbrShad.grp",0 __3},
	{G,0,"zerg/units/broodling death","unit\\zerg\\zbrDeath.grp",0 __3},
	{G,0,"zerg/units/infested terran","unit\\zerg\\bugguy.grp",0 __3},
	{G,0,"zerg/units/infested terran shadow","unit\\zerg\\zbgShad.grp",0 __3},
	{G,0,"zerg/units/evolution chamber","unit\\zerg\\cerebrat.grp",0 __3},
	{G,0,"zerg/units/evolution chamber shadow","unit\\zerg\\zceShad.grp",0 __3},
	{G,0,"zerg/units/spawning pool","unit\\zerg\\chrysal.grp",0 __3},
	{G,0,"zerg/units/spawning pool shadow","unit\\zerg\\zchShad.grp",0 __3},
	{G,0,"zerg/units/cocoon","unit\\zerg\\cocoon.grp",0 __3},
	{G,0,"zerg/units/defiler","unit\\zerg\\defiler.grp",0 __3},
	{G,0,"zerg/units/defiler birth","unit\\zerg\\zdebirth.grp",0 __3},
	{G,0,"zerg/units/defiler death","unit\\zerg\\zdeDeath.grp",0 __3},
	{G,0,"zerg/units/drone","unit\\zerg\\drone.grp",0 __3},
	{G,0,"zerg/units/drone birth","unit\\zerg\\zdrbirth.grp",0 __3},
	{G,0,"zerg/units/drone death","unit\\zerg\\zdrDeath.grp",0 __3},
	{G,0,"zerg/units/egg","unit\\zerg\\egg.grp",0 __3},
	{G,0,"zerg/units/egg shadow","unit\\zerg\\zegShad.grp",0 __3},
	{G,0,"zerg/units/egg spawn","unit\\zerg\\zegspawn.grp",0 __3},
	{G,0,"zerg/units/egg death","unit\\zerg\\zegDeath.grp",0 __3},
	{G,0,"zerg/units/extractor","unit\\zerg\\Extract.grp",0 __3},
	{G,0,"zerg/units/extractor shadow","unit\\zerg\\zreShad.grp",0 __3},
	{G,0,"zerg/units/creep colony","unit\\zerg\\fcolony.grp",0 __3},
	{G,0,"zerg/units/creep colony shadow","unit\\zerg\\zfcShad.grp",0 __3},
	{G,0,"zerg/units/guardian","unit\\zerg\\guardian.grp",0 __3},
	{G,0,"zerg/units/guardian death","unit\\zerg\\zguDeath.grp",0 __3},
	{G,0,"zerg/units/hatchery","unit\\zerg\\hatchery.grp",0 __3},
	{G,0,"zerg/units/hatchery shadow","unit\\zerg\\zhaShad.grp",0 __3},
	{G,0,"zerg/units/hive","unit\\Zerg\\Hive.grp",0 __3},
	{G,0,"zerg/units/hive shadow","unit\\zerg\\zhiShad.grp",0 __3},
	{G,0,"zerg/units/hydralisk","unit\\zerg\\hydra.grp",0 __3},
	{G,0,"zerg/units/hydralisk shadow","unit\\zerg\\zhyShad.grp",0 __3},
	{G,0,"zerg/units/hydralisk birth","unit\\zerg\\zhybirth.grp",0 __3},
	{G,0,"zerg/units/hydralisk death","unit\\zerg\\zhyDeath.grp",0 __3},
	{G,0,"zerg/units/infested command center","unit\\zerg\\Infest03.grp",0 __3},
	{G,0,"zerg/units/lair","unit\\zerg\\Lair.grp",0 __3},
	{G,0,"zerg/units/lair shadow","unit\\zerg\\zlrShad.grp",0 __3},
	{G,0,"zerg/units/larva","unit\\zerg\\larva.grp",0 __3},
	{G,0,"zerg/units/larva death","unit\\zerg\\zlaDeath.grp",0 __3},
	{G,0,"zerg/units/sunken colony","unit\\zerg\\Lurker.grp",0 __3},
	{G,0,"zerg/units/sunken colony shadow","unit\\zerg\\zluShad.grp",0 __3},
	{G,0,"zerg/units/greater spire","unit\\zerg\\MutaCham.grp",0 __3},
	{G,0,"zerg/units/greater spire shadow","unit\\zerg\\zmcShad.grp",0 __3},
	{G,0,"zerg/units/mutalisk","unit\\zerg\\mutalid.grp",0 __3},
	{G,0,"zerg/units/mutalisk birth","unit\\zerg\\zmubirth.grp",0 __3},
	{G,0,"zerg/units/mutalisk death","unit\\zerg\\zmuDeath.grp",0 __3},
	{G,0,"zerg/units/defiler mound","unit\\zerg\\Mutapit.grp",0 __3},
	{G,0,"zerg/units/defiler mound shadow","unit\\zerg\\zmhShad.grp",0 __3},
	{G,0,"zerg/units/queen's nest","unit\\zerg\\nest.grp",0 __3},
	{G,0,"zerg/units/queen's nest shadow","unit\\zerg\\zneShad.grp",0 __3},
	{G,0,"zerg/units/nydus canal","unit\\zerg\\NydusPit.grp",0 __3},
	{G,0,"zerg/units/nydus canal shadow","unit\\zerg\\znyShad.grp",0 __3},
	{G,0,"zerg/units/overmind shell","unit\\zerg\\Over1.grp",0 __3},
	{G,0,"zerg/units/overmind shell shadow","unit\\zerg\\zo1Shad.grp",0 __3},
	{G,0,"zerg/units/overmind","unit\\zerg\\Over2.grp",0 __3},
	{G,0,"zerg/units/overmind shadow","unit\\zerg\\zo2Shad.grp",0 __3},
	{G,0,"zerg/units/overlord","unit\\zerg\\overlord.grp",0 __3},
	{G,0,"zerg/units/overlord birth","unit\\zerg\\zovBirth.grp",0 __3},
	{G,0,"zerg/units/overlord death","unit\\zerg\\zovDeath.grp",0 __3},
	{G,0,"zerg/units/lowm/overlord","unit\\zerg\\LowM\\Overlord.grp",0 __3},
	{G,0,"zerg/units/queen","unit\\zerg\\queen.grp",0 __3},
	{G,0,"zerg/units/queen birth","unit\\zerg\\zquBirth.grp",0 __3},
	{G,0,"zerg/units/queen death","unit\\zerg\\zquDeath.grp",0 __3},
	{G,0,"zerg/units/ultralisk cavern","unit\\zerg\\RCluster.grp",0 __3},
	{G,0,"zerg/units/ultralisk cavern shadow","unit\\zerg\\zrcShad.grp",0 __3},
	{G,0,"zerg/units/spore colony","unit\\zerg\\SColony.grp",0 __3},
	{G,0,"zerg/units/spore colony shadow","unit\\zerg\\zscShad.grp",0 __3},
	{G,0,"zerg/units/zergling","unit\\zerg\\zergling.grp",0 __3},
	{G,0,"zerg/units/zergling shadow","unit\\zerg\\zzeShad.grp",0 __3},
	{G,0,"zerg/units/zergling birth","unit\\zerg\\zzebirth.grp",0 __3},
	{G,0,"zerg/units/zergling death","unit\\zerg\\zzeDeath.grp",0 __3},
	{G,0,"zerg/units/hydralisk den","unit\\zerg\\Snakey.grp",0 __3},
	{G,0,"zerg/units/hydralisk den shadow","unit\\zerg\\zsbShad.grp",0 __3},
	{G,0,"zerg/units/spire","unit\\zerg\\spire.grp",0 __3},
	{G,0,"zerg/units/spire shadow","unit\\zerg\\zspShad.grp",0 __3},
	{G,0,"zerg/units/cerebrate","unit\\zerg\\UCereb.grp",0 __3},
	{G,0,"zerg/units/cerebrate shadow","unit\\zerg\\zucShad.grp",0 __3},
	{G,0,"zerg/units/infested kerrigan","unit\\zerg\\uikerr.grp",0 __3},
	{G,0,"zerg/units/infested kerrigan shadow","unit\\zerg\\uikShad.grp",0 __3},
	{G,0,"zerg/units/ultralisk","unit\\zerg\\ultra.grp",0 __3},
	{G,0,"zerg/units/ultralisk shadow","unit\\zerg\\zulShad.grp",0 __3},
	{G,0,"zerg/units/ultralisk birth","unit\\zerg\\zulbirth.grp",0 __3},
	{G,0,"zerg/units/ultralisk death","unit\\zerg\\zulDeath.grp",0 __3},
	{G,0,"zerg/units/building morph","unit\\zerg\\ZBuild.grp",0 __3},
	{G,0,"zerg/units/building morph shadow","unit\\zerg\\ZBShad.grp",0 __3},
	{G,0,"zerg/units/beacon","unit\\zerg\\zmarker.grp",0 __3},
	{G,0,"zerg/units/beacon overlay","unit\\zerg\\zCirGlow.grp",0 __3},
	{G,0,"zerg/units/building spawn1","unit\\zerg\\zSpawn01.grp",0 __3},
	{G,0,"zerg/units/building spawn2","unit\\zerg\\zSpawn02.grp",0 __3},
	{G,0,"zerg/units/building spawn3","unit\\zerg\\zSpawn03.grp",0 __3},
	{G,0,"zerg/units/building blood1","unit\\thingy\\bblood01.grp",0 __3},
	{G,0,"zerg/units/building blood2","unit\\thingy\\bblood02.grp",0 __3},
	{G,0,"zerg/units/building blood3","unit\\thingy\\bblood03.grp",0 __3},
	{G,0,"zerg/units/building blood4","unit\\thingy\\bblood04.grp",0 __3},
	{G,0,"zerg/units/bdust","unit\\thingy\\bDust.grp",0 __3},
	{G,0,"zerg/units/spores","unit\\thingy\\gSmoke.grp",0 __3},
	{G,0,"zerg/units/glave wurm","unit\\thingy\\SpoTrail.grp",0 __3},
	{G,0,"zerg/units/guardian attack overlay","unit\\thingy\\eplMuzz.grp",0 __3},

	// Terran sounds
	{W,0,"terran/building place","sound\\misc\\tbldgplc.wav" __4},
	{W,0,"terran/on fire large","sound\\terran\\bldg\\onfirlrg.wav" __4},
	{W,0,"terran/land","sound\\misc\\land.wav" __4},
	{W,0,"terran/liftoff","sound\\misc\\liftoff.wav" __4},
	{W,0,"terran/power down","sound\\misc\\tpwrdown.wav" __4},
	{W,0,"terran/rescue","sound\\misc\\trescue.wav" __4},
	{W,0,"terran/units/advisor/err00","sound\\terran\\advisor\\taderr00.wav" __4},
	{W,0,"terran/units/advisor/err01","sound\\terran\\advisor\\taderr01.wav" __4},
	{W,0,"terran/units/advisor/err02","sound\\terran\\advisor\\taderr02.wav" __4},
	{W,0,"terran/units/advisor/err03","sound\\terran\\advisor\\taderr03.wav" __4},
	{W,0,"terran/units/advisor/err04","sound\\terran\\advisor\\taderr04.wav" __4},
	{W,0,"terran/units/advisor/err06","sound\\terran\\advisor\\taderr06.wav" __4},
	{W,0,"terran/units/advisor/upd00","sound\\terran\\advisor\\tadupd00.wav" __4},
	{W,0,"terran/units/advisor/upd01","sound\\terran\\advisor\\tadupd01.wav" __4},
	{W,0,"terran/units/advisor/upd02","sound\\terran\\advisor\\tadupd02.wav" __4},
	{W,0,"terran/units/advisor/upd03","sound\\terran\\advisor\\tadupd03.wav" __4},
	{W,0,"terran/units/advisor/upd04","sound\\terran\\advisor\\tadupd04.wav" __4},
	{W,0,"terran/units/advisor/upd05","sound\\terran\\advisor\\tadupd05.wav" __4},
	{W,0,"terran/units/advisor/upd06","sound\\terran\\advisor\\tadupd06.wav" __4},
	{W,0,"terran/units/advisor/upd07","sound\\terran\\advisor\\tadupd07.wav" __4},
	{W,0,"terran/units/battlecruiser/death/1","sound\\terran\\battle\\tbadth00.wav" __4},
	{W,0,"terran/units/battlecruiser/pissed/1","sound\\terran\\battle\\tbapss00.wav" __4},
	{W,0,"terran/units/battlecruiser/pissed/2","sound\\terran\\battle\\tbapss01.wav" __4},
	{W,0,"terran/units/battlecruiser/pissed/3","sound\\terran\\battle\\tbapss02.wav" __4},
	{W,0,"terran/units/battlecruiser/pissed/4","sound\\terran\\battle\\tbapss03.wav" __4},
	{W,0,"terran/units/battlecruiser/pissed/5","sound\\terran\\battle\\tbapss04.wav" __4},
	{W,0,"terran/units/battlecruiser/ready","sound\\terran\\battle\\tbardy00.wav" __4},
	{W,0,"terran/units/battlecruiser/selected/1","sound\\terran\\battle\\tbawht00.wav" __4},
	{W,0,"terran/units/battlecruiser/selected/2","sound\\terran\\battle\\tbawht01.wav" __4},
	{W,0,"terran/units/battlecruiser/selected/3","sound\\terran\\battle\\tbawht02.wav" __4},
	{W,0,"terran/units/battlecruiser/selected/4","sound\\terran\\battle\\tbawht03.wav" __4},
	{W,0,"terran/units/battlecruiser/yam01","sound\\terran\\battle\\tbayam01.wav" __4},
	{W,0,"terran/units/battlecruiser/yam02","sound\\terran\\battle\\tbayam02.wav" __4},
	{W,0,"terran/units/battlecruiser/acknowledgement/1","sound\\terran\\battle\\tbayes00.wav" __4},
	{W,0,"terran/units/battlecruiser/acknowledgement/2","sound\\terran\\battle\\tbayes01.wav" __4},
	{W,0,"terran/units/battlecruiser/acknowledgement/3","sound\\Terran\\BATTLE\\tbayes02.wav" __4},
	{W,0,"terran/units/battlecruiser/acknowledgement/4","sound\\terran\\battle\\tbayes03.wav" __4},
	{W,0,"terran/units/battlecruiser/yamato","sound\\Bullet\\tbaYam00.wav" __4},
	{W,0,"terran/units/civilian/death/1","sound\\terran\\civilian\\tcvdth00.wav" __4},
	{W,0,"terran/units/civilian/pissed/1","sound\\terran\\civilian\\tcvpss00.wav" __4},
	{W,0,"terran/units/civilian/pissed/2","sound\\terran\\civilian\\tcvpss01.wav" __4},
	{W,0,"terran/units/civilian/pissed/3","sound\\terran\\civilian\\tcvpss02.wav" __4},
	{W,0,"terran/units/civilian/pissed/4","sound\\terran\\civilian\\tcvpss03.wav" __4},
	{W,0,"terran/units/civilian/pissed/5","sound\\terran\\civilian\\tcvpss04.wav" __4},
	{W,0,"terran/units/civilian/ready","sound\\terran\\civilian\\tcvrdy00.wav" __4},
	{W,0,"terran/units/civilian/selected/1","sound\\terran\\civilian\\tcvwht00.wav" __4},
	{W,0,"terran/units/civilian/selected/2","sound\\terran\\civilian\\tcvwht01.wav" __4},
	{W,0,"terran/units/civilian/selected/3","sound\\terran\\civilian\\tcvwht02.wav" __4},
	{W,0,"terran/units/civilian/selected/4","sound\\terran\\civilian\\tcvwht03.wav" __4},
	{W,0,"terran/units/civilian/acknowledgement/1","sound\\terran\\civilian\\tcvyes00.wav" __4},
	{W,0,"terran/units/civilian/acknowledgement/2","sound\\terran\\civilian\\tcvyes01.wav" __4},
	{W,0,"terran/units/civilian/acknowledgement/3","sound\\terran\\civilian\\tcvyes02.wav" __4},
	{W,0,"terran/units/civilian/acknowledgement/4","sound\\terran\\civilian\\tcvyes03.wav" __4},
	{W,0,"terran/units/civilian/acknowledgement/5","sound\\terran\\civilian\\tcvyes04.wav" __4},
	{W,0,"terran/units/dropship/death/1","sound\\terran\\dropship\\tdrdth00.wav" __4},
	{W,0,"terran/units/dropship/pissed/1","sound\\terran\\dropship\\tdrpss00.wav" __4},
	{W,0,"terran/units/dropship/pissed/2","sound\\terran\\dropship\\tdrpss01.wav" __4},
	{W,0,"terran/units/dropship/pissed/3","sound\\terran\\dropship\\tdrpss02.wav" __4},
	{W,0,"terran/units/dropship/pissed/4","sound\\terran\\dropship\\tdrpss03.wav" __4},
	{W,0,"terran/units/dropship/ready","sound\\terran\\dropship\\tdrrdy00.wav" __4},
	{W,0,"terran/units/dropship/selected/1","sound\\terran\\dropship\\tdrwht00.wav" __4},
	{W,0,"terran/units/dropship/selected/2","sound\\terran\\dropship\\tdrwht01.wav" __4},
	{W,0,"terran/units/dropship/selected/3","sound\\terran\\dropship\\tdrwht02.wav" __4},
	{W,0,"terran/units/dropship/selected/4","sound\\terran\\dropship\\tdrwht03.wav" __4},
	{W,0,"terran/units/dropship/acknowledgement/1","sound\\terran\\dropship\\tdryes00.wav" __4},
	{W,0,"terran/units/dropship/acknowledgement/2","sound\\terran\\dropship\\tdryes01.wav" __4},
	{W,0,"terran/units/dropship/acknowledgement/3","sound\\terran\\dropship\\tdryes02.wav" __4},
	{W,0,"terran/units/dropship/acknowledgement/4","sound\\terran\\dropship\\tdryes03.wav" __4},
	{W,0,"terran/units/dropship/acknowledgement/5","sound\\terran\\dropship\\tdryes04.wav" __4},
	{W,0,"terran/units/dropship/acknowledgement/6","sound\\terran\\dropship\\tdryes05.wav" __4},
	{W,0,"terran/units/dropship/load","sound\\Misc\\TDrTra00.wav" __4},
	{W,0,"terran/units/dropship/unload","sound\\Misc\\TDrTra01.wav" __4},
	{W,0,"terran/units/dukeb/death/1","sound\\terran\\dukeb\\ududth00.wav" __4},
	{W,0,"terran/units/dukeb/pissed/1","sound\\terran\\dukeb\\udupss00.wav" __4},
	{W,0,"terran/units/dukeb/pissed/2","sound\\terran\\dukeb\\udupss01.wav" __4},
	{W,0,"terran/units/dukeb/pissed/3","sound\\terran\\dukeb\\udupss02.wav" __4},
	{W,0,"terran/units/dukeb/pissed/4","sound\\terran\\dukeb\\udupss03.wav" __4},
	{W,0,"terran/units/dukeb/pissed/5","sound\\terran\\dukeb\\udupss04.wav" __4},
	{W,0,"terran/units/dukeb/selected/1","sound\\terran\\dukeb\\uduwht00.wav" __4},
	{W,0,"terran/units/dukeb/selected/2","sound\\terran\\dukeb\\uduwht01.wav" __4},
	{W,0,"terran/units/dukeb/selected/3","sound\\terran\\dukeb\\uduwht02.wav" __4},
	{W,0,"terran/units/dukeb/selected/4","sound\\terran\\dukeb\\uduwht03.wav" __4},
	{W,0,"terran/units/dukeb/acknowledgement/1","sound\\terran\\dukeb\\uduyes00.wav" __4},
	{W,0,"terran/units/dukeb/acknowledgement/2","sound\\terran\\dukeb\\uduyes01.wav" __4},
	{W,0,"terran/units/dukeb/acknowledgement/3","sound\\terran\\dukeb\\uduyes02.wav" __4},
	{W,0,"terran/units/dukeb/acknowledgement/4","sound\\terran\\dukeb\\uduyes03.wav" __4},
	{W,0,"terran/units/dukeb/death/1","sound\\terran\\duket\\udtdth00.wav" __4},
	{W,0,"terran/units/dukeb/pissed/1","sound\\terran\\duket\\udtpss00.wav" __4},
	{W,0,"terran/units/dukeb/pissed/2","sound\\terran\\duket\\udtpss01.wav" __4},
	{W,0,"terran/units/dukeb/pissed/3","sound\\terran\\duket\\udtpss02.wav" __4},
	{W,0,"terran/units/dukeb/pissed/4","sound\\terran\\duket\\udtpss03.wav" __4},
	{W,0,"terran/units/dukeb/pissed/5","sound\\terran\\duket\\udtpss04.wav" __4},
	{W,0,"terran/units/dukeb/selected/1","sound\\terran\\duket\\udtwht00.wav" __4},
	{W,0,"terran/units/dukeb/selected/2","sound\\terran\\duket\\udtwht01.wav" __4},
	{W,0,"terran/units/dukeb/selected/3","sound\\terran\\duket\\udtwht02.wav" __4},
	{W,0,"terran/units/dukeb/selected/4","sound\\terran\\duket\\udtwht03.wav" __4},
	{W,0,"terran/units/dukeb/acknowledgement/1","sound\\terran\\duket\\udtyes00.wav" __4},
	{W,0,"terran/units/dukeb/acknowledgement/2","sound\\terran\\duket\\udtyes01.wav" __4},
	{W,0,"terran/units/dukeb/acknowledgement/3","sound\\terran\\duket\\udtyes02.wav" __4},
	{W,0,"terran/units/dukeb/acknowledgement/4","sound\\terran\\duket\\udtyes03.wav" __4},
	{W,0,"terran/units/firebat/death/1","sound\\terran\\firebat\\tfbdth00.wav" __4},
	{W,0,"terran/units/firebat/death/2","sound\\terran\\firebat\\tfbdth01.wav" __4},
	{W,0,"terran/units/firebat/death/3","sound\\terran\\firebat\\tfbdth02.wav" __4},
	{W,0,"terran/units/firebat/fire1","sound\\terran\\firebat\\tfbfir00.wav" __4},
	{W,0,"terran/units/firebat/fire2","sound\\terran\\firebat\\tfbfir01.wav" __4},
	{W,0,"terran/units/firebat/pissed/1","sound\\terran\\firebat\\tfbpss00.wav" __4},
	{W,0,"terran/units/firebat/pissed/2","sound\\terran\\firebat\\tfbpss01.wav" __4},
	{W,0,"terran/units/firebat/pissed/3","sound\\terran\\firebat\\tfbpss02.wav" __4},
	{W,0,"terran/units/firebat/pissed/4","sound\\terran\\firebat\\tfbpss03.wav" __4},
	{W,0,"terran/units/firebat/pissed/5","sound\\terran\\firebat\\tfbpss04.wav" __4},
	{W,0,"terran/units/firebat/pissed/6","sound\\terran\\firebat\\tfbpss05.wav" __4},
	{W,0,"terran/units/firebat/pissed/7","sound\\terran\\firebat\\tfbpss06.wav" __4},
	{W,0,"terran/units/firebat/ready","sound\\terran\\firebat\\tfbrdy00.wav" __4},
	{W,0,"terran/units/firebat/selected/1","sound\\terran\\firebat\\tfbwht00.wav" __4},
	{W,0,"terran/units/firebat/selected/2","sound\\terran\\firebat\\tfbwht01.wav" __4},
	{W,0,"terran/units/firebat/selected/3","sound\\terran\\firebat\\tfbwht02.wav" __4},
	{W,0,"terran/units/firebat/selected/4","sound\\terran\\firebat\\tfbwht03.wav" __4},
	{W,0,"terran/units/firebat/acknowledgement/1","sound\\terran\\firebat\\tfbyes00.wav" __4},
	{W,0,"terran/units/firebat/acknowledgement/2","sound\\terran\\firebat\\tfbyes01.wav" __4},
	{W,0,"terran/units/firebat/acknowledgement/3","sound\\terran\\firebat\\tfbyes02.wav" __4},
	{W,0,"terran/units/firebat/acknowledgement/4","sound\\terran\\firebat\\tfbyes03.wav" __4},
	{W,0,"terran/units/ghost/death/1","sound\\terran\\ghost\\tghdth00.wav" __4},
	{W,0,"terran/units/ghost/death/2","sound\\terran\\ghost\\tghdth01.wav" __4},
	{W,0,"terran/units/ghost/las00","sound\\terran\\ghost\\tghlas00.wav" __4},
	{W,0,"terran/units/ghost/lockdown","sound\\terran\\ghost\\tghlkd00.wav" __4},
	{W,0,"terran/units/ghost/pissed/1","sound\\terran\\ghost\\tghpss00.wav" __4},
	{W,0,"terran/units/ghost/pissed/2","sound\\terran\\ghost\\tghpss01.wav" __4},
	{W,0,"terran/units/ghost/pissed/3","sound\\terran\\ghost\\tghpss02.wav" __4},
	{W,0,"terran/units/ghost/pissed/4","sound\\terran\\ghost\\tghpss03.wav" __4},
	{W,0,"terran/units/ghost/ready","sound\\terran\\ghost\\tghrdy00.wav" __4},
	{W,0,"terran/units/ghost/selected/1","sound\\terran\\ghost\\tghwht00.wav" __4},
	{W,0,"terran/units/ghost/selected/2","sound\\terran\\ghost\\tghwht01.wav" __4},
	{W,0,"terran/units/ghost/selected/3","sound\\terran\\ghost\\tghwht02.wav" __4},
	{W,0,"terran/units/ghost/selected/4","sound\\Terran\\GHOST\\TGhWht03.wav" __4},
	{W,0,"terran/units/ghost/acknowledgement/1","sound\\terran\\ghost\\tghyes00.wav" __4},
	{W,0,"terran/units/ghost/acknowledgement/2","sound\\terran\\ghost\\tghyes01.wav" __4},
	{W,0,"terran/units/ghost/acknowledgement/3","sound\\terran\\ghost\\tghyes02.wav" __4},
	{W,0,"terran/units/ghost/acknowledgement/4","sound\\terran\\ghost\\tghyes03.wav" __4},
	{W,0,"terran/units/ghost/fire","sound\\bullet\\tghfir00.wav" __4},
	{W,0,"terran/units/goliath/death/1","sound\\terran\\goliath\\tgodth00.wav" __4},
	{W,0,"terran/units/goliath/pissed/1","sound\\terran\\goliath\\tgopss00.wav" __4},
	{W,0,"terran/units/goliath/pissed/2","sound\\terran\\goliath\\tgopss01.wav" __4},
	{W,0,"terran/units/goliath/pissed/3","sound\\terran\\goliath\\tgopss02.wav" __4},
	{W,0,"terran/units/goliath/pissed/4","sound\\terran\\goliath\\tgopss03.wav" __4},
	{W,0,"terran/units/goliath/pissed/5","sound\\terran\\goliath\\tgopss04.wav" __4},
	{W,0,"terran/units/goliath/pissed/6","sound\\terran\\goliath\\tgopss05.wav" __4},
	{W,0,"terran/units/goliath/ready","sound\\Terran\\GOLIATH\\TGoRdy00.wav" __4},
	{W,0,"terran/units/goliath/selected/1","sound\\terran\\goliath\\tgowht00.wav" __4},
	{W,0,"terran/units/goliath/selected/2","sound\\terran\\goliath\\tgowht01.wav" __4},
	{W,0,"terran/units/goliath/selected/3","sound\\terran\\goliath\\tgowht02.wav" __4},
	{W,0,"terran/units/goliath/selected/4","sound\\terran\\goliath\\tgowht03.wav" __4},
	{W,0,"terran/units/goliath/acknowledgement/1","sound\\terran\\goliath\\tgoyes00.wav" __4},
	{W,0,"terran/units/goliath/acknowledgement/2","sound\\terran\\goliath\\tgoyes01.wav" __4},
	{W,0,"terran/units/goliath/acknowledgement/3","sound\\terran\\goliath\\tgoyes02.wav" __4},
	{W,0,"terran/units/goliath/acknowledgement/4","sound\\terran\\goliath\\tgoyes03.wav" __4},
	{W,0,"terran/units/goliath/fire2","sound\\bullet\\tgofi200.wav" __4},
	{W,0,"terran/units/goliath/fire","sound\\bullet\\tgofir00.wav" __4},
	{W,0,"terran/units/goliath/hkmissile","sound\\bullet\\hkmissle.wav" __4},
	{W,0,"terran/units/kerrigan/death/1","sound\\terran\\kerrigan\\ukedth00.wav" __4},
	{W,0,"terran/units/kerrigan/death/2","sound\\terran\\kerrigan\\ukedth01.wav" __4},
	{W,0,"terran/units/kerrigan/pissed/1","sound\\terran\\kerrigan\\ukepss00.wav" __4},
	{W,0,"terran/units/kerrigan/pissed/2","sound\\terran\\kerrigan\\ukepss01.wav" __4},
	{W,0,"terran/units/kerrigan/pissed/3","sound\\terran\\kerrigan\\ukepss02.wav" __4},
	{W,0,"terran/units/kerrigan/pissed/4","sound\\terran\\kerrigan\\ukepss03.wav" __4},
	{W,0,"terran/units/kerrigan/pissed/5","sound\\terran\\kerrigan\\ukepss04.wav" __4},
	{W,0,"terran/units/kerrigan/selected/1","sound\\terran\\kerrigan\\ukewht00.wav" __4},
	{W,0,"terran/units/kerrigan/selected/2","sound\\terran\\kerrigan\\ukewht01.wav" __4},
	{W,0,"terran/units/kerrigan/selected/3","sound\\terran\\kerrigan\\ukewht02.wav" __4},
	{W,0,"terran/units/kerrigan/selected/4","sound\\terran\\kerrigan\\ukewht03.wav" __4},
	{W,0,"terran/units/kerrigan/acknowledgement/1","sound\\terran\\kerrigan\\ukeyes00.wav" __4},
	{W,0,"terran/units/kerrigan/acknowledgement/2","sound\\terran\\kerrigan\\ukeyes01.wav" __4},
	{W,0,"terran/units/kerrigan/acknowledgement/3","sound\\terran\\kerrigan\\ukeyes02.wav" __4},
	{W,0,"terran/units/kerrigan/acknowledgement/4","sound\\terran\\kerrigan\\ukeyes03.wav" __4},
	{W,0,"terran/units/marine/death/1","sound\\terran\\marine\\tmadth00.wav" __4},
	{W,0,"terran/units/marine/death/2","sound\\terran\\marine\\tmadth01.wav" __4},
	{W,0,"terran/units/marine/pissed/1","sound\\terran\\marine\\tmapss00.wav" __4},
	{W,0,"terran/units/marine/pissed/2","sound\\terran\\marine\\tmapss01.wav" __4},
	{W,0,"terran/units/marine/pissed/3","sound\\terran\\marine\\tmapss02.wav" __4},
	{W,0,"terran/units/marine/pissed/4","sound\\terran\\marine\\tmapss03.wav" __4},
	{W,0,"terran/units/marine/pissed/5","sound\\terran\\marine\\tmapss04.wav" __4},
	{W,0,"terran/units/marine/pissed/6","sound\\terran\\marine\\tmapss05.wav" __4},
	{W,0,"terran/units/marine/pissed/7","sound\\terran\\marine\\tmapss06.wav" __4},
	{W,0,"terran/units/marine/ready","sound\\terran\\marine\\tmardy00.wav" __4},
	{W,0,"terran/units/marine/sti00","sound\\terran\\marine\\tmasti00.wav" __4},
	{W,0,"terran/units/marine/sti01","sound\\terran\\marine\\tmasti01.wav" __4},
	{W,0,"terran/units/marine/selected/1","sound\\terran\\marine\\tmawht00.wav" __4},
	{W,0,"terran/units/marine/selected/2","sound\\terran\\marine\\tmawht01.wav" __4},
	{W,0,"terran/units/marine/selected/3","sound\\terran\\marine\\tmawht02.wav" __4},
	{W,0,"terran/units/marine/selected/4","sound\\terran\\marine\\tmawht03.wav" __4},
	{W,0,"terran/units/marine/acknowledgement/1","sound\\terran\\marine\\tmayes00.wav" __4},
	{W,0,"terran/units/marine/acknowledgement/2","sound\\terran\\marine\\tmayes01.wav" __4},
	{W,0,"terran/units/marine/acknowledgement/3","sound\\terran\\marine\\tmayes02.wav" __4},
	{W,0,"terran/units/marine/acknowledgement/4","sound\\terran\\marine\\tmayes03.wav" __4},
	{W,0,"terran/units/marine/fire","sound\\bullet\\tmafir00.wav" __4},
	{W,0,"terran/units/wraith/clo00","sound\\terran\\phoenix\\tphclo00.wav" __4},
	{W,0,"terran/units/wraith/clo01","sound\\terran\\phoenix\\tphclo01.wav" __4},
	{W,0,"terran/units/wraith/death/1","sound\\terran\\phoenix\\tphdth00.wav" __4},
	{W,0,"terran/units/wraith/pissed/1","sound\\terran\\phoenix\\tphpss00.wav" __4},
	{W,0,"terran/units/wraith/pissed/2","sound\\terran\\phoenix\\tphpss01.wav" __4},
	{W,0,"terran/units/wraith/pissed/3","sound\\terran\\phoenix\\tphpss02.wav" __4},
	{W,0,"terran/units/wraith/pissed/4","sound\\terran\\phoenix\\tphpss03.wav" __4},
	{W,0,"terran/units/wraith/pissed/5","sound\\terran\\phoenix\\tphpss04.wav" __4},
	{W,0,"terran/units/wraith/pissed/6","sound\\terran\\phoenix\\tphpss05.wav" __4},
	{W,0,"terran/units/wraith/pissed/7","sound\\terran\\phoenix\\tphpss06.wav" __4},
	{W,0,"terran/units/wraith/ready","sound\\terran\\phoenix\\tphrdy00.wav" __4},
	{W,0,"terran/units/wraith/selected/1","sound\\terran\\phoenix\\tphwht00.wav" __4},
	{W,0,"terran/units/wraith/selected/2","sound\\terran\\phoenix\\tphwht01.wav" __4},
	{W,0,"terran/units/wraith/selected/3","sound\\terran\\phoenix\\tphwht02.wav" __4},
	{W,0,"terran/units/wraith/selected/4","sound\\terran\\phoenix\\tphwht03.wav" __4},
	{W,0,"terran/units/wraith/acknowledgement/1","sound\\terran\\phoenix\\tphyes00.wav" __4},
	{W,0,"terran/units/wraith/acknowledgement/2","sound\\terran\\phoenix\\tphyes01.wav" __4},
	{W,0,"terran/units/wraith/acknowledgement/3","sound\\terran\\phoenix\\tphyes02.wav" __4},
	{W,0,"terran/units/wraith/acknowledgement/4","sound\\terran\\phoenix\\tphyes03.wav" __4},
	{W,0,"terran/units/wraith/fire100","sound\\bullet\\tphfi100.wav" __4},
	{W,0,"terran/units/wraith/fire200","sound\\bullet\\tphfi200.wav" __4},
	{W,0,"terran/units/wraith/fire201","sound\\bullet\\tphfi201.wav" __4},
	{W,0,"terran/units/raynorm/death/1","sound\\terran\\raynorm\\uradth00.wav" __4},
	{W,0,"terran/units/raynorm/death/2","sound\\Terran\\RAYNORM\\URaDth01.wav" __4},
	{W,0,"terran/units/raynorm/pissed/1","sound\\terran\\raynorm\\urapss00.wav" __4},
	{W,0,"terran/units/raynorm/pissed/2","sound\\terran\\raynorm\\urapss01.wav" __4},
	{W,0,"terran/units/raynorm/pissed/3","sound\\terran\\raynorm\\urapss02.wav" __4},
	{W,0,"terran/units/raynorm/pissed/4","sound\\terran\\raynorm\\urapss03.wav" __4},
	{W,0,"terran/units/raynorm/selected/1","sound\\terran\\raynorm\\urawht00.wav" __4},
	{W,0,"terran/units/raynorm/selected/2","sound\\terran\\raynorm\\urawht01.wav" __4},
	{W,0,"terran/units/raynorm/selected/3","sound\\terran\\raynorm\\urawht02.wav" __4},
	{W,0,"terran/units/raynorm/selected/4","sound\\terran\\raynorm\\urawht03.wav" __4},
	{W,0,"terran/units/raynorm/acknowledgement/1","sound\\terran\\raynorm\\urayes00.wav" __4},
	{W,0,"terran/units/raynorm/acknowledgement/2","sound\\terran\\raynorm\\urayes01.wav" __4},
	{W,0,"terran/units/raynorm/acknowledgement/3","sound\\terran\\raynorm\\urayes02.wav" __4},
	{W,0,"terran/units/raynorm/acknowledgement/4","sound\\terran\\raynorm\\urayes03.wav" __4},
	{W,0,"terran/units/raynorv/death/1","sound\\terran\\raynorv\\urvdth00.wav" __4},
	{W,0,"terran/units/raynorv/pissed/1","sound\\terran\\raynorv\\urvpss00.wav" __4},
	{W,0,"terran/units/raynorv/pissed/2","sound\\terran\\raynorv\\urvpss01.wav" __4},
	{W,0,"terran/units/raynorv/pissed/3","sound\\terran\\raynorv\\urvpss02.wav" __4},
	{W,0,"terran/units/raynorv/pissed/4","sound\\terran\\raynorv\\urvpss03.wav" __4},
	{W,0,"terran/units/raynorv/selected/1","sound\\terran\\raynorv\\urvwht00.wav" __4},
	{W,0,"terran/units/raynorv/selected/2","sound\\terran\\raynorv\\urvwht01.wav" __4},
	{W,0,"terran/units/raynorv/selected/3","sound\\terran\\raynorv\\urvwht02.wav" __4},
	{W,0,"terran/units/raynorv/selected/4","sound\\terran\\raynorv\\urvwht03.wav" __4},
	{W,0,"terran/units/raynorv/acknowledgement/1","sound\\terran\\raynorv\\urvyes00.wav" __4},
	{W,0,"terran/units/raynorv/acknowledgement/2","sound\\terran\\raynorv\\urvyes01.wav" __4},
	{W,0,"terran/units/raynorv/acknowledgement/3","sound\\terran\\raynorv\\urvyes02.wav" __4},
	{W,0,"terran/units/raynorv/acknowledgement/4","sound\\terran\\raynorv\\urvyes03.wav" __4},
	{W,0,"terran/units/scv/edrrep00","sound\\terran\\scv\\edrrep00.wav" __4},
	{W,0,"terran/units/scv/edrrep01","sound\\terran\\scv\\edrrep01.wav" __4},
	{W,0,"terran/units/scv/edrrep02","sound\\terran\\scv\\edrrep02.wav" __4},
	{W,0,"terran/units/scv/edrrep03","sound\\terran\\scv\\edrrep03.wav" __4},
	{W,0,"terran/units/scv/edrrep04","sound\\terran\\scv\\edrrep04.wav" __4},
	{W,0,"terran/units/scv/death/1","sound\\terran\\scv\\tscdth00.wav" __4},
	{W,0,"terran/units/scv/err00","sound\\terran\\scv\\tscerr00.wav" __4},
	{W,0,"terran/units/scv/err01","sound\\terran\\scv\\tscerr01.wav" __4},
	{W,0,"terran/units/scv/min00","sound\\terran\\scv\\tscmin00.wav" __4},
	{W,0,"terran/units/scv/min01","sound\\terran\\scv\\tscmin01.wav" __4},
	{W,0,"terran/units/scv/pissed/1","sound\\terran\\scv\\tscpss00.wav" __4},
	{W,0,"terran/units/scv/pissed/2","sound\\terran\\scv\\tscpss01.wav" __4},
	{W,0,"terran/units/scv/pissed/3","sound\\terran\\scv\\tscpss02.wav" __4},
	{W,0,"terran/units/scv/pissed/4","sound\\terran\\scv\\tscpss03.wav" __4},
	{W,0,"terran/units/scv/pissed/5","sound\\terran\\scv\\tscpss04.wav" __4},
	{W,0,"terran/units/scv/pissed/6","sound\\terran\\scv\\tscpss05.wav" __4},
	{W,0,"terran/units/scv/pissed/7","sound\\terran\\scv\\tscpss06.wav" __4},
	{W,0,"terran/units/scv/ready","sound\\terran\\scv\\tscrdy00.wav" __4},
	{W,0,"terran/units/scv/tra00","sound\\terran\\scv\\tsctra00.wav" __4},
	{W,0,"terran/units/scv/upd00","sound\\terran\\scv\\tscupd00.wav" __4},
	{W,0,"terran/units/scv/selected/1","sound\\terran\\scv\\tscwht00.wav" __4},
	{W,0,"terran/units/scv/selected/2","sound\\terran\\scv\\tscwht01.wav" __4},
	{W,0,"terran/units/scv/selected/3","sound\\terran\\scv\\tscwht02.wav" __4},
	{W,0,"terran/units/scv/selected/4","sound\\terran\\scv\\tscwht03.wav" __4},
	{W,0,"terran/units/scv/acknowledgement/1","sound\\terran\\scv\\tscyes00.wav" __4},
	{W,0,"terran/units/scv/acknowledgement/2","sound\\terran\\scv\\tscyes01.wav" __4},
	{W,0,"terran/units/scv/acknowledgement/3","sound\\terran\\scv\\tscyes02.wav" __4},
	{W,0,"terran/units/scv/acknowledgement/4","sound\\terran\\scv\\tscyes03.wav" __4},
	{W,0,"terran/units/tank/death/1","sound\\terran\\tank\\ttadth00.wav" __4},
	{W,0,"terran/units/tank/pissed/1","sound\\terran\\tank\\ttapss00.wav" __4},
	{W,0,"terran/units/tank/pissed/2","sound\\terran\\tank\\ttapss01.wav" __4},
	{W,0,"terran/units/tank/pissed/3","sound\\terran\\tank\\ttapss02.wav" __4},
	{W,0,"terran/units/tank/pissed/4","sound\\terran\\tank\\ttapss03.wav" __4},
	{W,0,"terran/units/tank/ready","sound\\terran\\tank\\ttardy00.wav" __4},
	{W,0,"terran/units/tank/tra00","sound\\terran\\tank\\ttatra00.wav" __4},
	{W,0,"terran/units/tank/tra01","sound\\terran\\tank\\ttatra01.wav" __4},
	{W,0,"terran/units/tank/selected/1","sound\\terran\\tank\\ttawht00.wav" __4},
	{W,0,"terran/units/tank/selected/2","sound\\terran\\tank\\ttawht01.wav" __4},
	{W,0,"terran/units/tank/selected/3","sound\\terran\\tank\\ttawht02.wav" __4},
	{W,0,"terran/units/tank/selected/4","sound\\terran\\tank\\ttawht03.wav" __4},
	{W,0,"terran/units/tank/acknowledgement/1","sound\\terran\\tank\\ttayes00.wav" __4},
	{W,0,"terran/units/tank/acknowledgement/2","sound\\terran\\tank\\ttayes01.wav" __4},
	{W,0,"terran/units/tank/acknowledgement/3","sound\\terran\\tank\\ttayes02.wav" __4},
	{W,0,"terran/units/tank/acknowledgement/4","sound\\terran\\tank\\ttayes03.wav" __4},
	{W,0,"terran/units/tank/fire2","sound\\bullet\\ttafi200.wav" __4},
	{W,0,"terran/units/tank/fire","sound\\Bullet\\TTaFir00.wav" __4},
	{W,0,"terran/units/tank/hit2","sound\\bullet\\TTaHi200.wav" __4},
	{W,0,"terran/units/tank/hit","sound\\bullet\\TTahit00.wav" __4},
	{W,0,"terran/units/science vessel/def00","sound\\terran\\vessel\\tvedef00.wav" __4},
	{W,0,"terran/units/science vessel/death/1","sound\\terran\\vessel\\tvedth00.wav" __4},
	{W,0,"terran/units/science vessel/emp00","sound\\terran\\vessel\\tveemp00.wav" __4},
	{W,0,"terran/units/science vessel/irr00","sound\\terran\\vessel\\tveirr00.wav" __4},
	{W,0,"terran/units/science vessel/pissed/1","sound\\terran\\vessel\\tvepss00.wav" __4},
	{W,0,"terran/units/science vessel/pissed/2","sound\\terran\\vessel\\tvepss01.wav" __4},
	{W,0,"terran/units/science vessel/pissed/3","sound\\terran\\vessel\\tvepss02.wav" __4},
	{W,0,"terran/units/science vessel/pissed/4","sound\\terran\\vessel\\tvepss03.wav" __4},
	{W,0,"terran/units/science vessel/pissed/5","sound\\terran\\vessel\\tvepss04.wav" __4},
	{W,0,"terran/units/science vessel/pissed/6","sound\\terran\\vessel\\tvepss05.wav" __4},
	{W,0,"terran/units/science vessel/pissed/7","sound\\terran\\vessel\\tvepss06.wav" __4},
	{W,0,"terran/units/science vessel/ready","sound\\terran\\vessel\\tverdy00.wav" __4},
	{W,0,"terran/units/science vessel/selected/1","sound\\terran\\vessel\\tvewht00.wav" __4},
	{W,0,"terran/units/science vessel/selected/2","sound\\terran\\vessel\\tvewht01.wav" __4},
	{W,0,"terran/units/science vessel/selected/3","sound\\terran\\vessel\\tvewht02.wav" __4},
	{W,0,"terran/units/science vessel/selected/4","sound\\terran\\vessel\\tvewht03.wav" __4},
	{W,0,"terran/units/science vessel/acknowledgement/1","sound\\terran\\vessel\\tveyes00.wav" __4},
	{W,0,"terran/units/science vessel/acknowledgement/2","sound\\terran\\vessel\\tveyes01.wav" __4},
	{W,0,"terran/units/science vessel/acknowledgement/3","sound\\terran\\vessel\\tveyes02.wav" __4},
	{W,0,"terran/units/science vessel/acknowledgement/4","sound\\terran\\vessel\\tveyes03.wav" __4},
	{W,0,"terran/units/vulture/death/1","sound\\terran\\vulture\\tvudth00.wav" __4},
	{W,0,"terran/units/vulture/min00","sound\\terran\\vulture\\tvumin00.wav" __4},
	{W,0,"terran/units/vulture/min01","sound\\terran\\vulture\\tvumin01.wav" __4},
	{W,0,"terran/units/vulture/pissed/1","sound\\terran\\vulture\\tvupss00.wav" __4},
	{W,0,"terran/units/vulture/pissed/2","sound\\terran\\vulture\\tvupss01.wav" __4},
	{W,0,"terran/units/vulture/pissed/3","sound\\terran\\vulture\\tvupss02.wav" __4},
	{W,0,"terran/units/vulture/pissed/4","sound\\terran\\vulture\\tvupss03.wav" __4},
	{W,0,"terran/units/vulture/ready","sound\\terran\\vulture\\tvurdy00.wav" __4},
	{W,0,"terran/units/vulture/selected/1","sound\\terran\\vulture\\tvuwht00.wav" __4},
	{W,0,"terran/units/vulture/selected/2","sound\\terran\\vulture\\tvuwht01.wav" __4},
	{W,0,"terran/units/vulture/selected/3","sound\\terran\\vulture\\tvuwht02.wav" __4},
	{W,0,"terran/units/vulture/selected/4","sound\\terran\\vulture\\tvuwht03.wav" __4},
	{W,0,"terran/units/vulture/acknowledgement/1","sound\\terran\\vulture\\tvuyes00.wav" __4},
	{W,0,"terran/units/vulture/acknowledgement/2","sound\\terran\\vulture\\tvuyes01.wav" __4},
	{W,0,"terran/units/vulture/acknowledgement/3","sound\\terran\\vulture\\tvuyes02.wav" __4},
	{W,0,"terran/units/vulture/acknowledgement/4","sound\\terran\\vulture\\tvuyes03.wav" __4},
	{W,0,"terran/units/vulture/fire","sound\\bullet\\tvufir00.wav" __4},
	{W,0,"terran/units/vulture/hit","sound\\bullet\\tvuhit00.wav" __4},
	{W,0,"terran/units/vulture/hit1","sound\\bullet\\tvuhit01.wav" __4},
	{W,0,"terran/units/vulture/hit2","sound\\bullet\\tvuhit02.wav" __4},
	{W,0,"terran/units/academy","sound\\terran\\bldg\\tacwht00.wav" __4},
	{W,0,"terran/units/armory","sound\\terran\\bldg\\tclwht00.wav" __4},
	{W,0,"terran/units/science facility","sound\\terran\\bldg\\tcssca00.wav" __4},
	{W,0,"terran/units/comsat station","sound\\Terran\\bldg\\tcswht00.wav" __4},
	{W,0,"terran/units/control tower","sound\\terran\\bldg\\tddwht00.wav" __4},
	{W,0,"terran/units/covert ops","sound\\terran\\bldg\\tglwht00.wav" __4},
	{W,0,"terran/units/machine shop","sound\\terran\\bldg\\tmswht00.wav" __4},
	{W,0,"terran/units/missile turret","sound\\terran\\bldg\\tmtwht00.wav" __4},
	{W,0,"terran/units/nuclear silo","sound\\terran\\bldg\\tnswht00.wav" __4},
	{W,0,"terran/units/supply depot","sound\\terran\\bldg\\tpgwht00.wav" __4},
	{W,0,"terran/units/bunker","sound\\terran\\bldg\\tplwht00.wav" __4},
	{W,0,"terran/units/refinery","sound\\terran\\bldg\\trewht00.wav" __4},
	{W,0,"terran/units/rf","sound\\terran\\bldg\\trfwht00.wav" __4},
	{W,0,"terran/units/factory","sound\\terran\\bldg\\trlwht00.wav" __4},
	{W,0,"terran/units/engineering bay","sound\\terran\\bldg\\twpwht00.wav" __4},
	{W,0,"terran/units/nuclear silo/fire","sound\\bullet\\tnsfir00.wav" __4},
	{W,0,"terran/units/nuclear silo/hit","sound\\bullet\\tnshit00.wav" __4},
	{W,0,"terran/units/tscfir00","sound\\bullet\\tscfir00.wav" __4},

	// Protoss sounds
	{W,0,"protoss/units/advisor/err00","sound\\protoss\\advisor\\paderr00.wav" __4},
	{W,0,"protoss/units/advisor/err01","sound\\protoss\\advisor\\paderr01.wav" __4},
	{W,0,"protoss/units/advisor/err02","sound\\protoss\\advisor\\paderr02.wav" __4},
	{W,0,"protoss/units/advisor/err06","sound\\Protoss\\Advisor\\PAdErr06.wav" __4},
	{W,0,"protoss/units/advisor/upd00","sound\\protoss\\advisor\\padupd00.wav" __4},
	{W,0,"protoss/units/advisor/upd01","sound\\protoss\\advisor\\padupd01.wav" __4},
	{W,0,"protoss/units/advisor/upd02","sound\\protoss\\advisor\\padupd02.wav" __4},
	{W,0,"protoss/units/advisor/upd04","sound\\protoss\\advisor\\padupd04.wav" __4},
	{W,0,"protoss/units/advisor/upd06","sound\\protoss\\advisor\\padupd06.wav" __4},
	{W,0,"protoss/units/arbiter/cag00","sound\\protoss\\arbiter\\pabcag00.wav" __4},
	{W,0,"protoss/units/arbiter/death/1","sound\\protoss\\arbiter\\pabdth00.wav" __4},
	{W,0,"protoss/units/arbiter/fol00","sound\\protoss\\arbiter\\pabfol00.wav" __4},
	{W,0,"protoss/units/arbiter/fol01","sound\\protoss\\arbiter\\pabfol01.wav" __4},
	{W,0,"protoss/units/arbiter/fol02","sound\\protoss\\arbiter\\pabfol02.wav" __4},
	{W,0,"protoss/units/arbiter/fol03","sound\\protoss\\arbiter\\pabfol03.wav" __4},
	{W,0,"protoss/units/arbiter/pissed/1","sound\\protoss\\arbiter\\pabpss00.wav" __4},
	{W,0,"protoss/units/arbiter/pissed/2","sound\\protoss\\arbiter\\pabpss01.wav" __4},
	{W,0,"protoss/units/arbiter/pissed/3","sound\\protoss\\arbiter\\pabpss02.wav" __4},
	{W,0,"protoss/units/arbiter/pissed/4","sound\\protoss\\arbiter\\pabpss03.wav" __4},
	{W,0,"protoss/units/arbiter/pissed/5","sound\\protoss\\arbiter\\pabpss04.wav" __4},
	{W,0,"protoss/units/arbiter/ready","sound\\protoss\\arbiter\\pabrdy00.wav" __4},
	{W,0,"protoss/units/arbiter/selected/1","sound\\protoss\\arbiter\\pabwht00.wav" __4},
	{W,0,"protoss/units/arbiter/selected/2","sound\\protoss\\arbiter\\pabwht01.wav" __4},
	{W,0,"protoss/units/arbiter/selected/3","sound\\protoss\\arbiter\\pabwht02.wav" __4},
	{W,0,"protoss/units/arbiter/selected/4","sound\\protoss\\arbiter\\pabwht03.wav" __4},
	{W,0,"protoss/units/arbiter/acknowledgement/1","sound\\protoss\\arbiter\\pabyes00.wav" __4},
	{W,0,"protoss/units/arbiter/acknowledgement/2","sound\\protoss\\arbiter\\pabyes01.wav" __4},
	{W,0,"protoss/units/arbiter/acknowledgement/3","sound\\protoss\\arbiter\\pabyes02.wav" __4},
	{W,0,"protoss/units/arbiter/acknowledgement/4","sound\\protoss\\arbiter\\pabyes03.wav" __4},
	{W,0,"protoss/units/archon/death/1","sound\\protoss\\archon\\pardth00.wav" __4},
	{W,0,"protoss/units/archon/min00","sound\\Protoss\\ARCHON\\PArMin00.wav" __4},
	{W,0,"protoss/units/archon/pissed/1","sound\\protoss\\archon\\parpss00.wav" __4},
	{W,0,"protoss/units/archon/pissed/2","sound\\protoss\\archon\\parpss01.wav" __4},
	{W,0,"protoss/units/archon/pissed/3","sound\\protoss\\archon\\parpss02.wav" __4},
	{W,0,"protoss/units/archon/pissed/4","sound\\protoss\\archon\\parpss03.wav" __4},
	{W,0,"protoss/units/archon/ready","sound\\Protoss\\ARCHON\\PArRdy00.wav" __4},
	{W,0,"protoss/units/archon/selected/1","sound\\protoss\\archon\\parwht00.wav" __4},
	{W,0,"protoss/units/archon/selected/2","sound\\protoss\\archon\\parwht01.wav" __4},
	{W,0,"protoss/units/archon/selected/3","sound\\protoss\\archon\\parwht02.wav" __4},
	{W,0,"protoss/units/archon/selected/4","sound\\protoss\\archon\\parwht03.wav" __4},
	{W,0,"protoss/units/archon/acknowledgement/1","sound\\protoss\\archon\\paryes00.wav" __4},
	{W,0,"protoss/units/archon/acknowledgement/2","sound\\protoss\\archon\\paryes01.wav" __4},
	{W,0,"protoss/units/archon/acknowledgement/3","sound\\protoss\\archon\\paryes02.wav" __4},
	{W,0,"protoss/units/archon/acknowledgement/4","sound\\protoss\\archon\\paryes03.wav" __4},
	{W,0,"protoss/units/archon/fir00","sound\\bullet\\parfir00.wav" __4},
	{W,0,"protoss/units/carrier/death/1","sound\\protoss\\carrier\\pcadth00.wav" __4},
	{W,0,"protoss/units/carrier/death/2","sound\\protoss\\carrier\\pcadth01.wav" __4},
	{W,0,"protoss/units/carrier/pissed/1","sound\\protoss\\carrier\\pcapss00.wav" __4},
	{W,0,"protoss/units/carrier/pissed/2","sound\\protoss\\carrier\\pcapss01.wav" __4},
	{W,0,"protoss/units/carrier/pissed/3","sound\\protoss\\carrier\\pcapss02.wav" __4},
	{W,0,"protoss/units/carrier/pissed/4","sound\\protoss\\carrier\\pcapss03.wav" __4},
	{W,0,"protoss/units/carrier/ready","sound\\protoss\\carrier\\pcardy00.wav" __4},
	{W,0,"protoss/units/carrier/selected/1","sound\\protoss\\carrier\\pcawht00.wav" __4},
	{W,0,"protoss/units/carrier/selected/2","sound\\protoss\\carrier\\pcawht01.wav" __4},
	{W,0,"protoss/units/carrier/selected/3","sound\\protoss\\carrier\\pcawht02.wav" __4},
	{W,0,"protoss/units/carrier/selected/4","sound\\protoss\\carrier\\pcawht03.wav" __4},
	{W,0,"protoss/units/carrier/acknowledgement/1","sound\\protoss\\carrier\\pcayes00.wav" __4},
	{W,0,"protoss/units/carrier/acknowledgement/2","sound\\protoss\\carrier\\pcayes01.wav" __4},
	{W,0,"protoss/units/carrier/acknowledgement/3","sound\\protoss\\carrier\\pcayes02.wav" __4},
	{W,0,"protoss/units/carrier/acknowledgement/4","sound\\protoss\\carrier\\pcayes03.wav" __4},
	{W,0,"protoss/units/dark templar/death/1","sound\\protoss\\darktemplar\\pdtdth00.wav" __4},
	{W,0,"protoss/units/dark templar/pissed/1","sound\\protoss\\darktemplar\\pdtpss00.wav" __4},
	{W,0,"protoss/units/dark templar/pissed/2","sound\\protoss\\darktemplar\\pdtpss01.wav" __4},
	{W,0,"protoss/units/dark templar/pissed/3","sound\\protoss\\darktemplar\\pdtpss02.wav" __4},
	{W,0,"protoss/units/dark templar/pissed/4","sound\\protoss\\darktemplar\\pdtpss03.wav" __4},
	{W,0,"protoss/units/dark templar/selected/1","sound\\protoss\\darktemplar\\pdtwht00.wav" __4},
	{W,0,"protoss/units/dark templar/selected/2","sound\\protoss\\darktemplar\\pdtwht01.wav" __4},
	{W,0,"protoss/units/dark templar/selected/3","sound\\protoss\\darktemplar\\pdtwht02.wav" __4},
	{W,0,"protoss/units/dark templar/selected/4","sound\\protoss\\darktemplar\\pdtwht03.wav" __4},
	{W,0,"protoss/units/dark templar/acknowledgement/1","sound\\protoss\\darktemplar\\pdtyes00.wav" __4},
	{W,0,"protoss/units/dark templar/acknowledgement/2","sound\\protoss\\darktemplar\\pdtyes01.wav" __4},
	{W,0,"protoss/units/dark templar/acknowledgement/3","sound\\protoss\\darktemplar\\pdtyes02.wav" __4},
	{W,0,"protoss/units/dark templar/acknowledgement/4","sound\\protoss\\darktemplar\\pdtyes03.wav" __4},
	{W,0,"protoss/units/dragoon/death/1","sound\\protoss\\dragoon\\pdrdth00.wav" __4},
	{W,0,"protoss/units/dragoon/pissed/1","sound\\protoss\\dragoon\\pdrpss00.wav" __4},
	{W,0,"protoss/units/dragoon/pissed/2","sound\\protoss\\dragoon\\pdrpss01.wav" __4},
	{W,0,"protoss/units/dragoon/pissed/3","sound\\protoss\\dragoon\\pdrpss02.wav" __4},
	{W,0,"protoss/units/dragoon/pissed/4","sound\\protoss\\dragoon\\pdrpss03.wav" __4},
	{W,0,"protoss/units/dragoon/ready","sound\\Protoss\\DRAGOON\\PDrRdy00.wav" __4},
	{W,0,"protoss/units/dragoon/selected/1","sound\\protoss\\dragoon\\pdrwht00.wav" __4},
	{W,0,"protoss/units/dragoon/selected/2","sound\\protoss\\dragoon\\pdrwht01.wav" __4},
	{W,0,"protoss/units/dragoon/selected/3","sound\\protoss\\dragoon\\pdrwht02.wav" __4},
	{W,0,"protoss/units/dragoon/selected/4","sound\\protoss\\dragoon\\pdrwht03.wav" __4},
	{W,0,"protoss/units/dragoon/selected/5","sound\\protoss\\dragoon\\pdrwht04.wav" __4},
	{W,0,"protoss/units/dragoon/selected/6","sound\\protoss\\dragoon\\pdrwht05.wav" __4},
	{W,0,"protoss/units/dragoon/selected/7","sound\\protoss\\dragoon\\pdrwht06.wav" __4},
	{W,0,"protoss/units/dragoon/selected/8","sound\\protoss\\dragoon\\pdrwht07.wav" __4},
	{W,0,"protoss/units/dragoon/acknowledgement/1","sound\\protoss\\dragoon\\pdryes00.wav" __4},
	{W,0,"protoss/units/dragoon/acknowledgement/2","sound\\protoss\\dragoon\\pdryes01.wav" __4},
	{W,0,"protoss/units/dragoon/acknowledgement/3","sound\\protoss\\dragoon\\pdryes02.wav" __4},
	{W,0,"protoss/units/dragoon/acknowledgement/4","sound\\protoss\\dragoon\\pdryes03.wav" __4},
	{W,0,"protoss/units/dragoon/acknowledgement/5","sound\\protoss\\dragoon\\pdryes04.wav" __4},
	{W,0,"protoss/units/dragoon/acknowledgement/6","sound\\protoss\\dragoon\\pdryes05.wav" __4},
	{W,0,"protoss/units/dragoon/acknowledgement/7","sound\\protoss\\dragoon\\pdryes06.wav" __4},
	{W,0,"protoss/units/dragoon/bull","sound\\bullet\\dragbull.wav" __4},
	{W,0,"protoss/units/fenixd/pissed/1","sound\\protoss\\fenixd\\ufdpss00.wav" __4},
	{W,0,"protoss/units/fenixd/pissed/2","sound\\protoss\\fenixd\\ufdpss01.wav" __4},
	{W,0,"protoss/units/fenixd/pissed/3","sound\\protoss\\fenixd\\ufdpss02.wav" __4},
	{W,0,"protoss/units/fenixd/pissed/4","sound\\protoss\\fenixd\\ufdpss03.wav" __4},
	{W,0,"protoss/units/fenixd/selected/1","sound\\protoss\\fenixd\\ufdwht00.wav" __4},
	{W,0,"protoss/units/fenixd/selected/2","sound\\protoss\\fenixd\\ufdwht01.wav" __4},
	{W,0,"protoss/units/fenixd/selected/3","sound\\protoss\\fenixd\\ufdwht02.wav" __4},
	{W,0,"protoss/units/fenixd/selected/4","sound\\protoss\\fenixd\\ufdwht03.wav" __4},
	{W,0,"protoss/units/fenixd/acknowledgement/1","sound\\protoss\\fenixd\\ufdyes00.wav" __4},
	{W,0,"protoss/units/fenixd/acknowledgement/2","sound\\protoss\\fenixd\\ufdyes01.wav" __4},
	{W,0,"protoss/units/fenixd/acknowledgement/3","sound\\protoss\\fenixd\\ufdyes02.wav" __4},
	{W,0,"protoss/units/fenixd/acknowledgement/4","sound\\protoss\\fenixd\\ufdyes03.wav" __4},
	{W,0,"protoss/units/fenixz/death/1","sound\\protoss\\fenixz\\ufedth00.wav" __4},
	{W,0,"protoss/units/fenixz/pissed/1","sound\\protoss\\fenixz\\ufepss00.wav" __4},
	{W,0,"protoss/units/fenixz/pissed/2","sound\\protoss\\fenixz\\ufepss01.wav" __4},
	{W,0,"protoss/units/fenixz/pissed/3","sound\\protoss\\fenixz\\ufepss02.wav" __4},
	{W,0,"protoss/units/fenixz/pissed/4","sound\\protoss\\fenixz\\ufepss03.wav" __4},
	{W,0,"protoss/units/fenixz/selected/1","sound\\protoss\\fenixz\\ufewht00.wav" __4},
	{W,0,"protoss/units/fenixz/selected/2","sound\\protoss\\fenixz\\ufewht01.wav" __4},
	{W,0,"protoss/units/fenixz/selected/3","sound\\protoss\\fenixz\\ufewht02.wav" __4},
	{W,0,"protoss/units/fenixz/selected/4","sound\\protoss\\fenixz\\ufewht03.wav" __4},
	{W,0,"protoss/units/fenixz/acknowledgement/1","sound\\protoss\\fenixz\\ufeyes00.wav" __4},
	{W,0,"protoss/units/fenixz/acknowledgement/2","sound\\protoss\\fenixz\\ufeyes01.wav" __4},
	{W,0,"protoss/units/fenixz/acknowledgement/3","sound\\protoss\\fenixz\\ufeyes02.wav" __4},
	{W,0,"protoss/units/fenixz/acknowledgement/4","sound\\protoss\\fenixz\\ufeyes03.wav" __4},
	{W,0,"protoss/units/gantrithor/pissed/1","sound\\protoss\\gantrithor\\utcpss00.wav" __4},
	{W,0,"protoss/units/gantrithor/pissed/2","sound\\protoss\\gantrithor\\utcpss01.wav" __4},
	{W,0,"protoss/units/gantrithor/pissed/3","sound\\protoss\\gantrithor\\utcpss02.wav" __4},
	{W,0,"protoss/units/gantrithor/pissed/4","sound\\protoss\\gantrithor\\utcpss03.wav" __4},
	{W,0,"protoss/units/gantrithor/selected/1","sound\\protoss\\gantrithor\\utcwht00.wav" __4},
	{W,0,"protoss/units/gantrithor/selected/2","sound\\protoss\\gantrithor\\utcwht01.wav" __4},
	{W,0,"protoss/units/gantrithor/selected/3","sound\\protoss\\gantrithor\\utcwht02.wav" __4},
	{W,0,"protoss/units/gantrithor/selected/4","sound\\protoss\\gantrithor\\utcwht03.wav" __4},
	{W,0,"protoss/units/gantrithor/acknowledgement/1","sound\\protoss\\gantrithor\\utcyes00.wav" __4},
	{W,0,"protoss/units/gantrithor/acknowledgement/2","sound\\protoss\\gantrithor\\utcyes01.wav" __4},
	{W,0,"protoss/units/gantrithor/acknowledgement/3","sound\\protoss\\gantrithor\\utcyes02.wav" __4},
	{W,0,"protoss/units/gantrithor/acknowledgement/4","sound\\protoss\\gantrithor\\utcyes03.wav" __4},
	{W,0,"protoss/units/interceptor/inlau00","sound\\protoss\\intercep\\pinlau00.wav" __4},
	{W,0,"protoss/units/probe/att00","sound\\protoss\\probe\\ppratt00.wav" __4},
	{W,0,"protoss/units/probe/att01","sound\\protoss\\probe\\ppratt01.wav" __4},
	{W,0,"protoss/units/probe/death/1","sound\\protoss\\probe\\pprdth00.wav" __4},
	{W,0,"protoss/units/probe/err00","sound\\protoss\\probe\\pprerr00.wav" __4},
	{W,0,"protoss/units/probe/err01","sound\\protoss\\probe\\pprerr01.wav" __4},
	{W,0,"protoss/units/probe/min00","sound\\protoss\\probe\\pprmin00.wav" __4},
	{W,0,"protoss/units/probe/pissed/1","sound\\protoss\\probe\\pprpss00.wav" __4},
	{W,0,"protoss/units/probe/pissed/2","sound\\protoss\\probe\\pprpss01.wav" __4},
	{W,0,"protoss/units/probe/pissed/3","sound\\protoss\\probe\\pprpss02.wav" __4},
	{W,0,"protoss/units/probe/pissed/4","sound\\protoss\\probe\\pprpss03.wav" __4},
	{W,0,"protoss/units/probe/ready","sound\\protoss\\probe\\pprrdy00.wav" __4},
	{W,0,"protoss/units/probe/selected/1","sound\\protoss\\probe\\pprwht00.wav" __4},
	{W,0,"protoss/units/probe/selected/2","sound\\protoss\\probe\\pprwht01.wav" __4},
	{W,0,"protoss/units/probe/selected/3","sound\\protoss\\probe\\pprwht02.wav" __4},
	{W,0,"protoss/units/probe/selected/4","sound\\protoss\\probe\\pprwht03.wav" __4},
	{W,0,"protoss/units/probe/acknowledgement/1","sound\\protoss\\probe\\ppryes00.wav" __4},
	{W,0,"protoss/units/probe/acknowledgement/2","sound\\protoss\\probe\\ppryes01.wav" __4},
	{W,0,"protoss/units/probe/acknowledgement/3","sound\\protoss\\probe\\ppryes02.wav" __4},
	{W,0,"protoss/units/probe/acknowledgement/4","sound\\protoss\\probe\\ppryes03.wav" __4},
	{W,0,"protoss/units/scout/death/1","sound\\protoss\\scout\\pscdth00.wav" __4},
	{W,0,"protoss/units/scout/pissed/1","sound\\protoss\\scout\\pscpss00.wav" __4},
	{W,0,"protoss/units/scout/pissed/2","sound\\protoss\\scout\\pscpss01.wav" __4},
	{W,0,"protoss/units/scout/pissed/3","sound\\protoss\\scout\\pscpss02.wav" __4},
	{W,0,"protoss/units/scout/pissed/4","sound\\protoss\\scout\\pscpss03.wav" __4},
	{W,0,"protoss/units/scout/pissed/5","sound\\protoss\\scout\\pscpss04.wav" __4},
	{W,0,"protoss/units/scout/ready","sound\\protoss\\scout\\pscrdy00.wav" __4},
	{W,0,"protoss/units/scout/selected/1","sound\\protoss\\scout\\pscwht00.wav" __4},
	{W,0,"protoss/units/scout/selected/2","sound\\protoss\\scout\\pscwht01.wav" __4},
	{W,0,"protoss/units/scout/selected/3","sound\\protoss\\scout\\pscwht02.wav" __4},
	{W,0,"protoss/units/scout/selected/4","sound\\protoss\\scout\\pscwht03.wav" __4},
	{W,0,"protoss/units/scout/acknowledgement/1","sound\\protoss\\scout\\pscyes00.wav" __4},
	{W,0,"protoss/units/scout/acknowledgement/2","sound\\protoss\\scout\\pscyes01.wav" __4},
	{W,0,"protoss/units/scout/acknowledgement/3","sound\\protoss\\scout\\pscyes02.wav" __4},
	{W,0,"protoss/units/scout/acknowledgement/4","sound\\protoss\\scout\\pscyes03.wav" __4},
	{W,0,"protoss/units/shuttle/bld00","sound\\protoss\\shuttle\\pshbld00.wav" __4},
	{W,0,"protoss/units/shuttle/bld01","sound\\protoss\\shuttle\\pshbld01.wav" __4},
	{W,0,"protoss/units/shuttle/bld02","sound\\protoss\\shuttle\\pshbld02.wav" __4},
	{W,0,"protoss/units/shuttle/bld03","sound\\protoss\\shuttle\\pshbld03.wav" __4},
	{W,0,"protoss/units/shuttle/bld04","sound\\protoss\\shuttle\\pshbld04.wav" __4},
	{W,0,"protoss/units/shuttle/death/1","sound\\protoss\\shuttle\\pshdth00.wav" __4},
	{W,0,"protoss/units/shuttle/pissed/1","sound\\protoss\\shuttle\\pshpss00.wav" __4},
	{W,0,"protoss/units/shuttle/pissed/2","sound\\protoss\\shuttle\\pshpss01.wav" __4},
	{W,0,"protoss/units/shuttle/pissed/3","sound\\protoss\\shuttle\\pshpss02.wav" __4},
	{W,0,"protoss/units/shuttle/pissed/4","sound\\protoss\\shuttle\\pshpss03.wav" __4},
	{W,0,"protoss/units/shuttle/pissed/5","sound\\protoss\\shuttle\\pshpss04.wav" __4},
	{W,0,"protoss/units/shuttle/ready","sound\\protoss\\shuttle\\pshrdy00.wav" __4},
	{W,0,"protoss/units/shuttle/selected/1","sound\\protoss\\shuttle\\pshwht00.wav" __4},
	{W,0,"protoss/units/shuttle/selected/2","sound\\protoss\\shuttle\\pshwht01.wav" __4},
	{W,0,"protoss/units/shuttle/selected/3","sound\\protoss\\shuttle\\pshwht02.wav" __4},
	{W,0,"protoss/units/shuttle/selected/4","sound\\protoss\\shuttle\\pshwht03.wav" __4},
	{W,0,"protoss/units/shuttle/acknowledgement/1","sound\\protoss\\shuttle\\pshyes00.wav" __4},
	{W,0,"protoss/units/shuttle/acknowledgement/2","sound\\protoss\\shuttle\\pshyes01.wav" __4},
	{W,0,"protoss/units/shuttle/acknowledgement/3","sound\\protoss\\shuttle\\pshyes02.wav" __4},
	{W,0,"protoss/units/shuttle/acknowledgement/4","sound\\protoss\\shuttle\\pshyes03.wav" __4},
	{W,0,"protoss/units/tassadar/death/1","sound\\protoss\\tassadar\\utadth00.wav" __4},
	{W,0,"protoss/units/tassadar/pissed/1","sound\\protoss\\tassadar\\utapss00.wav" __4},
	{W,0,"protoss/units/tassadar/pissed/2","sound\\protoss\\tassadar\\utapss01.wav" __4},
	{W,0,"protoss/units/tassadar/pissed/3","sound\\protoss\\tassadar\\utapss02.wav" __4},
	{W,0,"protoss/units/tassadar/pissed/4","sound\\protoss\\tassadar\\utapss03.wav" __4},
	{W,0,"protoss/units/tassadar/selected/1","sound\\protoss\\tassadar\\utawht00.wav" __4},
	{W,0,"protoss/units/tassadar/selected/2","sound\\protoss\\tassadar\\utawht01.wav" __4},
	{W,0,"protoss/units/tassadar/selected/3","sound\\protoss\\tassadar\\utawht02.wav" __4},
	{W,0,"protoss/units/tassadar/selected/4","sound\\protoss\\tassadar\\utawht03.wav" __4},
	{W,0,"protoss/units/tassadar/acknowledgement/1","sound\\protoss\\tassadar\\utayes00.wav" __4},
	{W,0,"protoss/units/tassadar/acknowledgement/2","sound\\protoss\\tassadar\\utayes01.wav" __4},
	{W,0,"protoss/units/tassadar/acknowledgement/3","sound\\protoss\\tassadar\\utayes02.wav" __4},
	{W,0,"protoss/units/tassadar/acknowledgement/4","sound\\protoss\\tassadar\\utayes03.wav" __4},
	{W,0,"protoss/units/templar/death/1","sound\\protoss\\templar\\ptedth00.wav" __4},
	{W,0,"protoss/units/templar/hal00","sound\\protoss\\templar\\ptehal00.wav" __4},
	{W,0,"protoss/units/templar/hal01","sound\\protoss\\templar\\ptehal01.wav" __4},
	{W,0,"protoss/units/templar/mov00","sound\\protoss\\templar\\ptemov00.wav" __4},
	{W,0,"protoss/units/templar/pissed/1","sound\\protoss\\templar\\ptepss00.wav" __4},
	{W,0,"protoss/units/templar/pissed/2","sound\\protoss\\templar\\ptepss01.wav" __4},
	{W,0,"protoss/units/templar/pissed/3","sound\\protoss\\templar\\ptepss02.wav" __4},
	{W,0,"protoss/units/templar/pissed/4","sound\\protoss\\templar\\ptepss03.wav" __4},
	{W,0,"protoss/units/templar/ready","sound\\protoss\\templar\\pterdy00.wav" __4},
	{W,0,"protoss/units/templar/sto00","sound\\protoss\\templar\\ptesto00.wav" __4},
	{W,0,"protoss/units/templar/sto01","sound\\protoss\\templar\\ptesto01.wav" __4},
	{W,0,"protoss/units/templar/sum00","sound\\protoss\\templar\\ptesum00.wav" __4},
	{W,0,"protoss/units/templar/selected/1","sound\\protoss\\templar\\ptewht00.wav" __4},
	{W,0,"protoss/units/templar/selected/2","sound\\protoss\\templar\\ptewht01.wav" __4},
	{W,0,"protoss/units/templar/selected/3","sound\\protoss\\templar\\ptewht02.wav" __4},
	{W,0,"protoss/units/templar/selected/4","sound\\protoss\\templar\\ptewht03.wav" __4},
	{W,0,"protoss/units/templar/acknowledgement/1","sound\\protoss\\templar\\pteyes00.wav" __4},
	{W,0,"protoss/units/templar/acknowledgement/2","sound\\protoss\\templar\\pteyes01.wav" __4},
	{W,0,"protoss/units/templar/acknowledgement/3","sound\\protoss\\templar\\pteyes02.wav" __4},
	{W,0,"protoss/units/templar/acknowledgement/4","sound\\protoss\\templar\\pteyes03.wav" __4},
	{W,0,"protoss/units/reaver/death/1","sound\\protoss\\trilobyte\\ptrdth00.wav" __4},
	{W,0,"protoss/units/reaver/pissed/1","sound\\protoss\\trilobyte\\ptrpss00.wav" __4},
	{W,0,"protoss/units/reaver/pissed/2","sound\\protoss\\trilobyte\\ptrpss01.wav" __4},
	{W,0,"protoss/units/reaver/pissed/3","sound\\protoss\\trilobyte\\ptrpss02.wav" __4},
	{W,0,"protoss/units/reaver/ready","sound\\protoss\\trilobyte\\ptrrdy00.wav" __4},
	{W,0,"protoss/units/reaver/selected/1","sound\\protoss\\trilobyte\\ptrwht00.wav" __4},
	{W,0,"protoss/units/reaver/selected/2","sound\\protoss\\trilobyte\\ptrwht01.wav" __4},
	{W,0,"protoss/units/reaver/selected/3","sound\\protoss\\trilobyte\\ptrwht02.wav" __4},
	{W,0,"protoss/units/reaver/selected/4","sound\\protoss\\trilobyte\\ptrwht03.wav" __4},
	{W,0,"protoss/units/reaver/acknowledgement/1","sound\\protoss\\trilobyte\\ptryes00.wav" __4},
	{W,0,"protoss/units/reaver/acknowledgement/2","sound\\protoss\\trilobyte\\ptryes01.wav" __4},
	{W,0,"protoss/units/reaver/acknowledgement/3","sound\\protoss\\trilobyte\\ptryes02.wav" __4},
	{W,0,"protoss/units/reaver/acknowledgement/4","sound\\protoss\\trilobyte\\ptryes03.wav" __4},
	{W,0,"protoss/units/observer/death/1","sound\\protoss\\witness\\pwidth00.wav" __4},
	{W,0,"protoss/units/observer/death/2","sound\\protoss\\witness\\pwidth01.wav" __4},
	{W,0,"protoss/units/observer/pissed/1","sound\\protoss\\witness\\pwipss00.wav" __4},
	{W,0,"protoss/units/observer/pissed/2","sound\\protoss\\witness\\pwipss01.wav" __4},
	{W,0,"protoss/units/observer/pissed/3","sound\\protoss\\witness\\pwipss02.wav" __4},
	{W,0,"protoss/units/observer/pissed/4","sound\\protoss\\witness\\pwipss03.wav" __4},
	{W,0,"protoss/units/observer/pissed/5","sound\\protoss\\witness\\pwipss04.wav" __4},
	{W,0,"protoss/units/observer/ready","sound\\protoss\\witness\\pwirdy00.wav" __4},
	{W,0,"protoss/units/observer/selected/1","sound\\protoss\\witness\\pwiwht00.wav" __4},
	{W,0,"protoss/units/observer/selected/2","sound\\protoss\\witness\\pwiwht01.wav" __4},
	{W,0,"protoss/units/observer/acknowledgement/1","sound\\protoss\\witness\\pwiyes00.wav" __4},
	{W,0,"protoss/units/observer/acknowledgement/2","sound\\protoss\\witness\\pwiyes01.wav" __4},
	{W,0,"protoss/units/zealot/att00","sound\\protoss\\zealot\\pzeatt00.wav" __4},
	{W,0,"protoss/units/zealot/att01","sound\\protoss\\zealot\\pzeatt01.wav" __4},
	{W,0,"protoss/units/zealot/death/1","sound\\protoss\\zealot\\pzedth00.wav" __4},
	{W,0,"protoss/units/zealot/hit00","sound\\protoss\\zealot\\pzehit00.wav" __4},
	{W,0,"protoss/units/zealot/pissed/1","sound\\protoss\\zealot\\pzepss00.wav" __4},
	{W,0,"protoss/units/zealot/pissed/2","sound\\protoss\\zealot\\pzepss01.wav" __4},
	{W,0,"protoss/units/zealot/pissed/3","sound\\protoss\\zealot\\pzepss02.wav" __4},
	{W,0,"protoss/units/zealot/rag00","sound\\protoss\\zealot\\pzerag00.wav" __4},
	{W,0,"protoss/units/zealot/ready","sound\\protoss\\zealot\\pzerdy00.wav" __4},
	{W,0,"protoss/units/zealot/selected/1","sound\\protoss\\zealot\\pzewht00.wav" __4},
	{W,0,"protoss/units/zealot/selected/2","sound\\protoss\\zealot\\pzewht01.wav" __4},
	{W,0,"protoss/units/zealot/selected/3","sound\\protoss\\zealot\\pzewht02.wav" __4},
	{W,0,"protoss/units/zealot/selected/4","sound\\protoss\\zealot\\pzewht03.wav" __4},
	{W,0,"protoss/units/zealot/acknowledgement/1","sound\\protoss\\zealot\\pzeyes00.wav" __4},
	{W,0,"protoss/units/zealot/acknowledgement/2","sound\\protoss\\zealot\\pzeyes01.wav" __4},
	{W,0,"protoss/units/zealot/acknowledgement/3","sound\\protoss\\zealot\\pzeyes02.wav" __4},
	{W,0,"protoss/units/zealot/acknowledgement/4","sound\\protoss\\zealot\\pzeyes03.wav" __4},
	{W,0,"protoss/units/zeratul/death/1","sound\\protoss\\zeratul\\uzedth00.wav" __4},
	{W,0,"protoss/units/zeratul/pissed/1","sound\\protoss\\zeratul\\uzepss00.wav" __4},
	{W,0,"protoss/units/zeratul/pissed/2","sound\\protoss\\zeratul\\uzepss01.wav" __4},
	{W,0,"protoss/units/zeratul/pissed/3","sound\\protoss\\zeratul\\uzepss02.wav" __4},
	{W,0,"protoss/units/zeratul/pissed/4","sound\\protoss\\zeratul\\uzepss03.wav" __4},
	{W,0,"protoss/units/zeratul/selected/1","sound\\protoss\\zeratul\\uzewht00.wav" __4},
	{W,0,"protoss/units/zeratul/selected/2","sound\\protoss\\zeratul\\uzewht01.wav" __4},
	{W,0,"protoss/units/zeratul/selected/3","sound\\protoss\\zeratul\\uzewht02.wav" __4},
	{W,0,"protoss/units/zeratul/selected/4","sound\\protoss\\zeratul\\uzewht03.wav" __4},
	{W,0,"protoss/units/zeratul/acknowledgement/1","sound\\protoss\\zeratul\\uzeyes00.wav" __4},
	{W,0,"protoss/units/zeratul/acknowledgement/2","sound\\protoss\\zeratul\\uzeyes01.wav" __4},
	{W,0,"protoss/units/zeratul/acknowledgement/3","sound\\protoss\\zeratul\\uzeyes02.wav" __4},
	{W,0,"protoss/units/zeratul/acknowledgement/4","sound\\protoss\\zeratul\\uzeyes03.wav" __4},
	{W,0,"protoss/units/acwht00","sound\\protoss\\bldg\\pacwht00.wav" __4},
	{W,0,"protoss/units/assimilator","sound\\protoss\\bldg\\paswht00.wav" __4},
	{W,0,"protoss/units/baact00","sound\\Protoss\\Bldg\\PbaAct00.wav" __4},
	{W,0,"protoss/units/bawht00","sound\\protoss\\bldg\\pbawht00.wav" __4},
	{W,0,"protoss/units/observatory","sound\\protoss\\bldg\\pbewht00.wav" __4},
	{W,0,"protoss/units/citadel","sound\\protoss\\bldg\\pciwht00.wav" __4},
	{W,0,"protoss/units/forge","sound\\protoss\\bldg\\pfowht00.wav" __4},
	{W,0,"protoss/units/gateway","sound\\protoss\\bldg\\pgawht00.wav" __4},
	{W,0,"protoss/units/cybernetics core","sound\\protoss\\bldg\\pgcwht00.wav" __4},
	{W,0,"protoss/units/nawht00","sound\\protoss\\bldg\\pnawht00.wav" __4},
	{W,0,"protoss/units/nexus","sound\\protoss\\bldg\\pnewht00.wav" __4},
	{W,0,"protoss/units/pbwht00","sound\\protoss\\bldg\\ppbwht00.wav" __4},
	{W,0,"protoss/units/pylon","sound\\protoss\\bldg\\ppywht00.wav" __4},
	{W,0,"protoss/units/robotics facility","sound\\protoss\\bldg\\prowht00.wav" __4},
	{W,0,"protoss/units/stwht00","sound\\protoss\\bldg\\pstwht00.wav" __4},
	{W,0,"protoss/units/trwht00","sound\\protoss\\bldg\\ptrwht00.wav" __4},
	{W,0,"protoss/units/fleet beacon","sound\\protoss\\bldg\\pwawht00.wav" __4},
	{W,0,"protoss/units/phofir00","sound\\Bullet\\Phofir00.wav" __4},
	{W,0,"protoss/units/phohit00","sound\\bullet\\phohit00.wav" __4},
	{W,0,"protoss/units/psahit00","sound\\bullet\\psahit00.wav" __4},
	{W,0,"protoss/units/pshield","sound\\bullet\\pshield.wav" __4},
	{W,0,"protoss/units/psiblade","sound\\bullet\\psiblade.wav" __4},
	{W,0,"protoss/units/psibolt","sound\\bullet\\psibolt.wav" __4},
	{W,0,"protoss/units/ptrfir00","sound\\bullet\\ptrfir00.wav" __4},
	{W,0,"protoss/units/ptrfir01","sound\\bullet\\ptrfir01.wav" __4},

	// Zerg sounds
	{W,0,"zerg/units/advisor/require minerals","sound\\zerg\\advisor\\zaderr00.wav" __4},
	{W,0,"zerg/units/advisor/require gas","sound\\zerg\\advisor\\zaderr01.wav" __4},
	{W,0,"zerg/units/advisor/spawn overlords","sound\\zerg\\advisor\\zaderr02.wav" __4},
	{W,0,"zerg/units/advisor/not enough energy","sound\\Zerg\\Advisor\\ZAdErr06.wav" __4},
	{W,0,"zerg/units/advisor/base attacked","sound\\zerg\\advisor\\zadupd00.wav" __4},
	{W,0,"zerg/units/advisor/units attacked","sound\\zerg\\advisor\\zadupd01.wav" __4},
	{W,0,"zerg/units/advisor/evolution complete","sound\\zerg\\advisor\\zadupd02.wav" __4},
	{W,0,"zerg/units/advisor/nuclear launch","sound\\zerg\\advisor\\zadupd04.wav" __4},
	{W,0,"zerg/units/scourge/att00","sound\\Zerg\\AVENGER\\ZAvAtt00.wav" __4},
	{W,0,"zerg/units/scourge/death/1","sound\\zerg\\avenger\\zavdth00.wav" __4},
	{W,0,"zerg/units/scourge/hit00","sound\\Zerg\\AVENGER\\ZAvHit00.wav" __4},
	{W,0,"zerg/units/scourge/pissed/1","sound\\zerg\\avenger\\zavpss00.wav" __4},
	{W,0,"zerg/units/scourge/pissed/2","sound\\zerg\\avenger\\zavpss01.wav" __4},
	{W,0,"zerg/units/scourge/ready","sound\\zerg\\avenger\\zavrdy00.wav" __4},
	{W,0,"zerg/units/scourge/selected/1","sound\\zerg\\avenger\\zavwht00.wav" __4},
	{W,0,"zerg/units/scourge/selected/2","sound\\zerg\\avenger\\zavwht01.wav" __4},
	{W,0,"zerg/units/scourge/acknowledgement/1","sound\\zerg\\avenger\\zavyes00.wav" __4},
	{W,0,"zerg/units/scourge/acknowledgement/2","sound\\zerg\\avenger\\zavyes01.wav" __4},
	{W,0,"zerg/units/building death","sound\\zerg\\bldg\\zbldgdth.wav" __4},
	{W,0,"zerg/units/cb","sound\\Zerg\\Bldg\\ZCbWht00.wav" __4},
	{W,0,"zerg/units/morph complete","sound\\zerg\\bldg\\zchrdy00.wav" __4},
	{W,0,"zerg/units/spawning pool selected","sound\\zerg\\bldg\\zchwht00.wav" __4},
	{W,0,"zerg/units/evolution chamber selected","sound\\zerg\\bldg\\zevwht00.wav" __4},
	{W,0,"zerg/units/creep colony selected","sound\\zerg\\bldg\\zfcwht00.wav" __4},
	{W,0,"zerg/units/hatchery selected","sound\\zerg\\bldg\\zhawht00.wav" __4},
	{W,0,"zerg/units/lair selected","sound\\zerg\\bldg\\zhiwht00.wav" __4},
	{W,0,"zerg/units/extractor selected","sound\\zerg\\bldg\\zigwht00.wav" __4},
	{W,0,"zerg/units/hive selected","sound\\zerg\\bldg\\zlrwht00.wav" __4},
	{W,0,"zerg/units/sunken colony selected","sound\\zerg\\bldg\\zluwht00.wav" __4},
	{W,0,"zerg/units/greater spire selected","sound\\zerg\\bldg\\zmcwht00.wav" __4},
	{W,0,"zerg/units/defiler mound selected","sound\\zerg\\bldg\\zmhwht00.wav" __4},
	{W,0,"zerg/units/queens nest selected","sound\\zerg\\bldg\\znewht00.wav" __4},
	{W,0,"zerg/units/nydus canal selected","sound\\zerg\\bldg\\znywht00.wav" __4},
	{W,0,"zerg/units/o1","sound\\zerg\\bldg\\zo1wht00.wav" __4},
	{W,0,"zerg/units/ultralisk cavern selected","sound\\zerg\\bldg\\zrcwht00.wav" __4},
	{W,0,"zerg/units/hydralisk den selected","sound\\zerg\\bldg\\zsbwht00.wav" __4},
	{W,0,"zerg/units/spore colony selected","sound\\zerg\\bldg\\zscwht00.wav" __4},
	{W,0,"zerg/units/spire selected","sound\\zerg\\bldg\\zspwht00.wav" __4},
	{W,0,"zerg/units/broodling/att00","sound\\zerg\\broodling\\zbratt00.wav" __4},
	{W,0,"zerg/units/broodling/death/1","sound\\zerg\\broodling\\zbrdth00.wav" __4},
	{W,0,"zerg/units/broodling/pissed/1","sound\\zerg\\broodling\\zbrpss00.wav" __4},
	{W,0,"zerg/units/broodling/pissed/2","sound\\zerg\\broodling\\zbrpss01.wav" __4},
	{W,0,"zerg/units/broodling/pissed/3","sound\\zerg\\broodling\\zbrpss02.wav" __4},
	{W,0,"zerg/units/broodling/pissed/4","sound\\zerg\\broodling\\zbrpss03.wav" __4},
	{W,0,"zerg/units/broodling/ready","sound\\zerg\\broodling\\zbrrdy00.wav" __4},
	{W,0,"zerg/units/broodling/selected/1","sound\\zerg\\broodling\\zbrwht00.wav" __4},
	{W,0,"zerg/units/broodling/selected/2","sound\\zerg\\broodling\\zbrwht01.wav" __4},
	{W,0,"zerg/units/broodling/selected/3","sound\\zerg\\broodling\\zbrwht02.wav" __4},
	{W,0,"zerg/units/broodling/selected/4","sound\\zerg\\broodling\\zbrwht03.wav" __4},
	{W,0,"zerg/units/broodling/acknowledgement/1","sound\\zerg\\broodling\\zbryes00.wav" __4},
	{W,0,"zerg/units/broodling/acknowledgement/2","sound\\zerg\\broodling\\zbryes01.wav" __4},
	{W,0,"zerg/units/broodling/acknowledgement/3","sound\\zerg\\broodling\\zbryes02.wav" __4},
	{W,0,"zerg/units/broodling/acknowledgement/4","sound\\zerg\\broodling\\zbryes03.wav" __4},
	{W,0,"zerg/units/infested terran/pissed/1","sound\\zerg\\bugguy\\zbgpss00.wav" __4},
	{W,0,"zerg/units/infested terran/pissed/2","sound\\zerg\\bugguy\\zbgpss01.wav" __4},
	{W,0,"zerg/units/infested terran/pissed/3","sound\\zerg\\bugguy\\zbgpss02.wav" __4},
	{W,0,"zerg/units/infested terran/pissed/4","sound\\zerg\\bugguy\\zbgpss03.wav" __4},
	{W,0,"zerg/units/infested terran/ready","sound\\zerg\\bugguy\\zbgrdy00.wav" __4},
	{W,0,"zerg/units/infested terran/selected/1","sound\\zerg\\bugguy\\zbgwht00.wav" __4},
	{W,0,"zerg/units/infested terran/selected/2","sound\\zerg\\bugguy\\zbgwht01.wav" __4},
	{W,0,"zerg/units/infested terran/selected/3","sound\\zerg\\bugguy\\zbgwht02.wav" __4},
	{W,0,"zerg/units/infested terran/selected/4","sound\\zerg\\bugguy\\zbgwht03.wav" __4},
	{W,0,"zerg/units/infested terran/acknowledgement/1","sound\\zerg\\bugguy\\zbgyes00.wav" __4},
	{W,0,"zerg/units/infested terran/acknowledgement/2","sound\\zerg\\bugguy\\zbgyes01.wav" __4},
	{W,0,"zerg/units/infested terran/acknowledgement/3","sound\\zerg\\bugguy\\zbgyes02.wav" __4},
	{W,0,"zerg/units/infested terran/acknowledgement/4","sound\\zerg\\bugguy\\zbgyes03.wav" __4},
	{W,0,"zerg/units/defiler/plague cast","sound\\zerg\\defiler\\zdeblo00.wav" __4},
	{W,0,"zerg/units/defiler/plague selected","sound\\zerg\\defiler\\zdeblo01.wav" __4},
	{W,0,"zerg/units/defiler/consume","sound\\zerg\\defiler\\zdecon00.wav" __4},
	{W,0,"zerg/units/defiler/death/1","sound\\zerg\\defiler\\zdedth00.wav" __4},
	{W,0,"zerg/units/defiler/pissed/1","sound\\zerg\\defiler\\zdepss00.wav" __4},
	{W,0,"zerg/units/defiler/pissed/2","sound\\zerg\\defiler\\zdepss01.wav" __4},
	{W,0,"zerg/units/defiler/pissed/3","sound\\zerg\\defiler\\zdepss02.wav" __4},
	{W,0,"zerg/units/defiler/pissed/4","sound\\zerg\\defiler\\zdepss03.wav" __4},
	{W,0,"zerg/units/defiler/ready","sound\\zerg\\defiler\\zderdy00.wav" __4},
	{W,0,"zerg/units/defiler/selected/1","sound\\zerg\\defiler\\zdewht00.wav" __4},
	{W,0,"zerg/units/defiler/selected/2","sound\\zerg\\defiler\\zdewht01.wav" __4},
	{W,0,"zerg/units/defiler/selected/3","sound\\zerg\\defiler\\zdewht02.wav" __4},
	{W,0,"zerg/units/defiler/selected/4","sound\\zerg\\defiler\\zdewht03.wav" __4},
	{W,0,"zerg/units/defiler/acknowledgement/1","sound\\zerg\\defiler\\zdeyes00.wav" __4},
	{W,0,"zerg/units/defiler/acknowledgement/2","sound\\zerg\\defiler\\zdeyes01.wav" __4},
	{W,0,"zerg/units/defiler/acknowledgement/3","sound\\zerg\\defiler\\zdeyes02.wav" __4},
	{W,0,"zerg/units/defiler/acknowledgement/4","sound\\zerg\\defiler\\zdeyes03.wav" __4},
	{W,0,"zerg/units/drone/death/1","sound\\Zerg\\DRONE\\ZDrDth00.wav" __4},
	{W,0,"zerg/units/drone/err00","sound\\zerg\\drone\\zdrerr00.wav" __4},
	{W,0,"zerg/units/drone/min00","sound\\zerg\\drone\\zdrmin00.wav" __4},
	{W,0,"zerg/units/drone/pissed/1","sound\\Zerg\\DRONE\\ZDrPss00.wav" __4},
	{W,0,"zerg/units/drone/pissed/2","sound\\Zerg\\DRONE\\ZDrPss01.wav" __4},
	{W,0,"zerg/units/drone/pissed/3","sound\\Zerg\\DRONE\\ZDrPss02.wav" __4},
	{W,0,"zerg/units/drone/ready","sound\\zerg\\drone\\zdrrdy00.wav" __4},
	{W,0,"zerg/units/drone/selected/1","sound\\zerg\\drone\\zdrwht00.wav" __4},
	{W,0,"zerg/units/drone/selected/2","sound\\zerg\\drone\\zdrwht01.wav" __4},
	{W,0,"zerg/units/drone/selected/3","sound\\zerg\\drone\\zdrwht02.wav" __4},
	{W,0,"zerg/units/drone/selected/4","sound\\zerg\\drone\\zdrwht03.wav" __4},
	{W,0,"zerg/units/drone/selected/5","sound\\zerg\\drone\\zdrwht04.wav" __4},
	{W,0,"zerg/units/drone/acknowledgement/1","sound\\zerg\\drone\\zdryes00.wav" __4},
	{W,0,"zerg/units/drone/acknowledgement/2","sound\\zerg\\drone\\zdryes01.wav" __4},
	{W,0,"zerg/units/drone/acknowledgement/3","sound\\zerg\\drone\\zdryes02.wav" __4},
	{W,0,"zerg/units/drone/acknowledgement/4","sound\\zerg\\drone\\zdryes03.wav" __4},
	{W,0,"zerg/units/drone/acknowledgement/5","sound\\zerg\\drone\\zdryes04.wav" __4},
	{W,0,"zerg/units/egg/death/1","sound\\zerg\\egg\\zegdth00.wav" __4},
	{W,0,"zerg/units/egg/pissed/1","sound\\Zerg\\Egg\\ZEgPss00.wav" __4},
	{W,0,"zerg/units/egg/ready","sound\\zerg\\egg\\zegrdy00.wav" __4},
	{W,0,"zerg/units/egg/selected/1","sound\\zerg\\egg\\zegwht00.wav" __4},
	{W,0,"zerg/units/egg/selected/2","sound\\zerg\\egg\\zegwht01.wav" __4},
	{W,0,"zerg/units/guardian/death/1","sound\\zerg\\guardian\\zgudth00.wav" __4},
	{W,0,"zerg/units/guardian/pissed/1","sound\\zerg\\guardian\\zgupss00.wav" __4},
	{W,0,"zerg/units/guardian/pissed/2","sound\\zerg\\guardian\\zgupss01.wav" __4},
	{W,0,"zerg/units/guardian/pissed/3","sound\\zerg\\guardian\\zgupss02.wav" __4},
	{W,0,"zerg/units/guardian/pissed/4","sound\\zerg\\guardian\\zgupss03.wav" __4},
	{W,0,"zerg/units/guardian/ready","sound\\zerg\\guardian\\zgurdy00.wav" __4},
	{W,0,"zerg/units/guardian/selected/1","sound\\zerg\\guardian\\zguwht00.wav" __4},
	{W,0,"zerg/units/guardian/selected/2","sound\\zerg\\guardian\\zguwht01.wav" __4},
	{W,0,"zerg/units/guardian/selected/3","sound\\zerg\\guardian\\zguwht02.wav" __4},
	{W,0,"zerg/units/guardian/selected/4","sound\\zerg\\guardian\\zguwht03.wav" __4},
	{W,0,"zerg/units/guardian/acknowledgement/1","sound\\zerg\\guardian\\zguyes00.wav" __4},
	{W,0,"zerg/units/guardian/acknowledgement/2","sound\\zerg\\guardian\\zguyes01.wav" __4},
	{W,0,"zerg/units/guardian/acknowledgement/3","sound\\zerg\\guardian\\zguyes02.wav" __4},
	{W,0,"zerg/units/guardian/acknowledgement/4","sound\\zerg\\guardian\\zguyes03.wav" __4},
	{W,0,"zerg/units/hydralisk/fir00","Sound\\Zerg\\Hydra\\SpiFir00.wav" __4},
	{W,0,"zerg/units/hydralisk/death/1","sound\\zerg\\hydra\\zhydth00.wav" __4},
	{W,0,"zerg/units/hydralisk/pissed/1","sound\\zerg\\hydra\\zhypss00.wav" __4},
	{W,0,"zerg/units/hydralisk/pissed/2","sound\\zerg\\hydra\\zhypss01.wav" __4},
	{W,0,"zerg/units/hydralisk/ready","sound\\zerg\\hydra\\zhyrdy00.wav" __4},
	{W,0,"zerg/units/hydralisk/selected/1","sound\\zerg\\hydra\\zhywht00.wav" __4},
	{W,0,"zerg/units/hydralisk/selected/2","sound\\zerg\\hydra\\zhywht01.wav" __4},
	{W,0,"zerg/units/hydralisk/selected/3","sound\\zerg\\hydra\\zhywht02.wav" __4},
	{W,0,"zerg/units/hydralisk/acknowledgement/1","sound\\zerg\\hydra\\zhyyes00.wav" __4},
	{W,0,"zerg/units/hydralisk/acknowledgement/2","sound\\zerg\\hydra\\zhyyes01.wav" __4},
	{W,0,"zerg/units/hydralisk/acknowledgement/3","sound\\zerg\\hydra\\zhyyes02.wav" __4},
	{W,0,"zerg/units/hydralisk/acknowledgement/4","sound\\zerg\\hydra\\zhyyes03.wav" __4},
	{W,0,"zerg/units/larva/death/1","sound\\zerg\\larva\\zladth00.wav" __4},
	{W,0,"zerg/units/larva/pissed/1","sound\\zerg\\larva\\zlapss00.wav" __4},
	{W,0,"zerg/units/larva/selected/1","sound\\zerg\\larva\\zlawht00.wav" __4},
	{W,0,"zerg/units/mutalisk/death/1","sound\\zerg\\mutalid\\zmudth00.wav" __4},
	{W,0,"zerg/units/mutalisk/pissed/1","sound\\zerg\\mutalid\\zmupss00.wav" __4},
	{W,0,"zerg/units/mutalisk/pissed/2","sound\\zerg\\mutalid\\zmupss01.wav" __4},
	{W,0,"zerg/units/mutalisk/pissed/3","sound\\zerg\\mutalid\\zmupss02.wav" __4},
	{W,0,"zerg/units/mutalisk/pissed/4","sound\\zerg\\mutalid\\zmupss03.wav" __4},
	{W,0,"zerg/units/mutalisk/ready","sound\\zerg\\mutalid\\zmurdy00.wav" __4},
	{W,0,"zerg/units/mutalisk/selected/1","sound\\zerg\\mutalid\\zmuwht00.wav" __4},
	{W,0,"zerg/units/mutalisk/selected/2","sound\\zerg\\mutalid\\zmuwht01.wav" __4},
	{W,0,"zerg/units/mutalisk/selected/3","sound\\zerg\\mutalid\\zmuwht02.wav" __4},
	{W,0,"zerg/units/mutalisk/selected/4","sound\\zerg\\mutalid\\zmuwht03.wav" __4},
	{W,0,"zerg/units/mutalisk/acknowledgement/1","sound\\zerg\\mutalid\\zmuyes00.wav" __4},
	{W,0,"zerg/units/mutalisk/acknowledgement/2","sound\\zerg\\mutalid\\zmuyes01.wav" __4},
	{W,0,"zerg/units/mutalisk/acknowledgement/3","sound\\zerg\\mutalid\\zmuyes02.wav" __4},
	{W,0,"zerg/units/mutalisk/acknowledgement/4","sound\\zerg\\mutalid\\zmuyes03.wav" __4},
	{W,0,"zerg/units/overlord/death/1","sound\\zerg\\overlord\\zovdth00.wav" __4},
	{W,0,"zerg/units/overlord/pissed/1","sound\\zerg\\overlord\\zovpss00.wav" __4},
	{W,0,"zerg/units/overlord/pissed/2","sound\\zerg\\overlord\\zovpss01.wav" __4},
	{W,0,"zerg/units/overlord/pissed/3","sound\\zerg\\overlord\\zovpss02.wav" __4},
	{W,0,"zerg/units/overlord/pissed/4","sound\\zerg\\overlord\\zovpss03.wav" __4},
	{W,0,"zerg/units/overlord/ready","sound\\zerg\\overlord\\zovrdy00.wav" __4},
	{W,0,"zerg/units/overlord/selected/1","sound\\zerg\\overlord\\zovwht00.wav" __4},
	{W,0,"zerg/units/overlord/selected/2","sound\\zerg\\overlord\\zovwht01.wav" __4},
	{W,0,"zerg/units/overlord/selected/3","sound\\zerg\\overlord\\zovwht02.wav" __4},
	{W,0,"zerg/units/overlord/selected/4","sound\\zerg\\overlord\\zovwht03.wav" __4},
	{W,0,"zerg/units/overlord/acknowledgement/1","sound\\zerg\\overlord\\zovyes00.wav" __4},
	{W,0,"zerg/units/overlord/acknowledgement/2","sound\\zerg\\overlord\\zovyes01.wav" __4},
	{W,0,"zerg/units/overlord/acknowledgement/3","sound\\zerg\\overlord\\zovyes02.wav" __4},
	{W,0,"zerg/units/overlord/acknowledgement/4","sound\\zerg\\overlord\\zovyes03.wav" __4},
	{W,0,"zerg/units/queen/death/1","sound\\zerg\\queen\\zqudth00.wav" __4},
	{W,0,"zerg/units/queen/death/2","sound\\zerg\\queen\\zqudth01.wav" __4},
	{W,0,"zerg/units/queen/death/3","sound\\zerg\\queen\\zqudth02.wav" __4},
	{W,0,"zerg/units/queen/ensnare cast","sound\\Zerg\\Queen\\ZQuEns00.wav" __4},
	{W,0,"zerg/units/queen/pissed/1","sound\\zerg\\queen\\zqupss00.wav" __4},
	{W,0,"zerg/units/queen/pissed/2","sound\\zerg\\queen\\zqupss01.wav" __4},
	{W,0,"zerg/units/queen/pissed/3","sound\\zerg\\queen\\zqupss02.wav" __4},
	{W,0,"zerg/units/queen/pissed/4","sound\\zerg\\queen\\zqupss03.wav" __4},
	{W,0,"zerg/units/queen/ready","sound\\zerg\\queen\\zqurdy00.wav" __4},
	{W,0,"zerg/units/queen/swm00","sound\\zerg\\queen\\zquswm00.wav" __4},
	{W,0,"zerg/units/queen/swm01","sound\\zerg\\queen\\zquswm01.wav" __4},
	{W,0,"zerg/units/queen/tag00","sound\\zerg\\queen\\zqutag00.wav" __4},
	{W,0,"zerg/units/queen/parasite cast","sound\\zerg\\queen\\zqutag01.wav" __4},
	{W,0,"zerg/units/queen/selected/1","sound\\zerg\\queen\\zquwht00.wav" __4},
	{W,0,"zerg/units/queen/selected/2","sound\\zerg\\queen\\zquwht01.wav" __4},
	{W,0,"zerg/units/queen/selected/3","sound\\zerg\\queen\\zquwht02.wav" __4},
	{W,0,"zerg/units/queen/selected/4","sound\\zerg\\queen\\zquwht03.wav" __4},
	{W,0,"zerg/units/queen/acknowledgement/1","sound\\zerg\\queen\\zquyes00.wav" __4},
	{W,0,"zerg/units/queen/acknowledgement/2","sound\\zerg\\queen\\zquyes01.wav" __4},
	{W,0,"zerg/units/queen/acknowledgement/3","sound\\zerg\\queen\\zquyes02.wav" __4},
	{W,0,"zerg/units/queen/acknowledgement/4","sound\\zerg\\queen\\zquyes03.wav" __4},
	{W,0,"zerg/units/ultralisk/att00","sound\\zerg\\ultra\\zulatt00.wav" __4},
	{W,0,"zerg/units/ultralisk/att01","sound\\zerg\\ultra\\zulatt01.wav" __4},
	{W,0,"zerg/units/ultralisk/att02","sound\\zerg\\ultra\\zulatt02.wav" __4},
	{W,0,"zerg/units/ultralisk/death/1","sound\\zerg\\ultra\\zuldth00.wav" __4},
	{W,0,"zerg/units/ultralisk/hit00","sound\\zerg\\ultra\\zulhit00.wav" __4},
	{W,0,"zerg/units/ultralisk/hit01","sound\\zerg\\ultra\\zulhit01.wav" __4},
	{W,0,"zerg/units/ultralisk/pissed/1","sound\\zerg\\ultra\\zulpss00.wav" __4},
	{W,0,"zerg/units/ultralisk/pissed/2","sound\\zerg\\ultra\\zulpss01.wav" __4},
	{W,0,"zerg/units/ultralisk/pissed/3","sound\\zerg\\ultra\\zulpss02.wav" __4},
	{W,0,"zerg/units/ultralisk/ready","sound\\zerg\\ultra\\zulrdy00.wav" __4},
	{W,0,"zerg/units/ultralisk/ror00","sound\\zerg\\ultra\\zulror00.wav" __4},
	{W,0,"zerg/units/ultralisk/selected/1","sound\\zerg\\ultra\\zulwht00.wav" __4},
	{W,0,"zerg/units/ultralisk/selected/2","sound\\zerg\\ultra\\zulwht01.wav" __4},
	{W,0,"zerg/units/ultralisk/selected/3","sound\\zerg\\ultra\\zulwht02.wav" __4},
	{W,0,"zerg/units/ultralisk/selected/1","sound\\zerg\\ultra\\zulwht03.wav" __4},
	{W,0,"zerg/units/ultralisk/acknowledgement/1","sound\\zerg\\ultra\\zulyes00.wav" __4},
	{W,0,"zerg/units/ultralisk/acknowledgement/2","sound\\zerg\\ultra\\zulyes01.wav" __4},
	{W,0,"zerg/units/ultralisk/acknowledgement/3","sound\\zerg\\ultra\\zulyes02.wav" __4},
	{W,0,"zerg/units/ultralisk/acknowledgement/4","sound\\zerg\\ultra\\zulyes03.wav" __4},
	{W,0,"zerg/units/kerrigan/death/1","sound\\Zerg\\ZERGKERRI\\UKiDth00.wav" __4},
	{W,0,"zerg/units/kerrigan/pissed/1","sound\\Zerg\\ZERGKERRI\\UKiPss00.wav" __4},
	{W,0,"zerg/units/kerrigan/pissed/2","sound\\Zerg\\ZERGKERRI\\UKiPss01.wav" __4},
	{W,0,"zerg/units/kerrigan/pissed/3","sound\\Zerg\\ZERGKERRI\\UKiPss02.wav" __4},
	{W,0,"zerg/units/kerrigan/pissed/4","sound\\Zerg\\ZERGKERRI\\UKiPss03.wav" __4},
	{W,0,"zerg/units/kerrigan/selected/1","sound\\Zerg\\ZERGKERRI\\UKiWht00.wav" __4},
	{W,0,"zerg/units/kerrigan/selected/2","sound\\Zerg\\ZERGKERRI\\UKiWht01.wav" __4},
	{W,0,"zerg/units/kerrigan/selected/3","sound\\Zerg\\ZERGKERRI\\UKiWht02.wav" __4},
	{W,0,"zerg/units/kerrigan/selected/4","sound\\Zerg\\ZERGKERRI\\UKiWht03.wav" __4},
	{W,0,"zerg/units/kerrigan/acknowledgement/1","sound\\Zerg\\ZERGKERRI\\UKiYes00.wav" __4},
	{W,0,"zerg/units/kerrigan/acknowledgement/2","sound\\Zerg\\ZERGKERRI\\UKiYes01.wav" __4},
	{W,0,"zerg/units/kerrigan/acknowledgement/3","sound\\Zerg\\ZERGKERRI\\UKiYes02.wav" __4},
	{W,0,"zerg/units/kerrigan/acknowledgement/4","sound\\Zerg\\ZERGKERRI\\UKiYes03.wav" __4},
	{W,0,"zerg/units/zergling/death/1","sound\\zerg\\zergling\\zzedth00.wav" __4},
	{W,0,"zerg/units/zergling/pissed/1","sound\\zerg\\zergling\\zzepss00.wav" __4},
	{W,0,"zerg/units/zergling/pissed/2","sound\\zerg\\zergling\\zzepss01.wav" __4},
	{W,0,"zerg/units/zergling/pissed/3","sound\\zerg\\zergling\\zzepss02.wav" __4},
	{W,0,"zerg/units/zergling/ready","sound\\zerg\\zergling\\zzerdy00.wav" __4},
	{W,0,"zerg/units/zergling/selected/1","sound\\zerg\\zergling\\zzewht00.wav" __4},
	{W,0,"zerg/units/zergling/selected/2","sound\\zerg\\zergling\\zzewht01.wav" __4},
	{W,0,"zerg/units/zergling/selected/3","sound\\zerg\\zergling\\zzewht02.wav" __4},
	{W,0,"zerg/units/zergling/selected/4","sound\\zerg\\zergling\\zzewht03.wav" __4},
	{W,0,"zerg/units/zergling/acknowledgement/1","sound\\zerg\\zergling\\zzeyes00.wav" __4},
	{W,0,"zerg/units/zergling/acknowledgement/2","sound\\zerg\\zergling\\zzeyes01.wav" __4},
	{W,0,"zerg/units/zergling/acknowledgement/3","sound\\zerg\\zergling\\zzeyes02.wav" __4},
	{W,0,"zerg/units/zergling/acknowledgement/4","sound\\zerg\\zergling\\zzeyes03.wav" __4},
	{W,0,"zerg/units/bghit00","sound\\Bullet\\ZBGHit00.wav" __4},
	{W,0,"zerg/units/deatt00","sound\\bullet\\zdeatt00.wav" __4},
	{W,0,"zerg/units/drhit00","sound\\bullet\\zdrhit00.wav" __4},
	{W,0,"zerg/units/guardian/fir00","sound\\Bullet\\ZGuFir00.wav" __4},
	{W,0,"zerg/units/guardian/hit00","sound\\Bullet\\ZGuHit00.wav" __4},
	{W,0,"zerg/units/hyfir00","sound\\bullet\\zhyfir00.wav" __4},
	{W,0,"zerg/units/hyhit00","sound\\bullet\\zhyhit00.wav" __4},
	{W,0,"zerg/units/lufir00","sound\\bullet\\zlufir00.wav" __4},
	{W,0,"zerg/units/luhit00","sound\\bullet\\zluhit00.wav" __4},
	{W,0,"zerg/units/mutalisk/fir00","sound\\bullet\\zmufir00.wav" __4},
	{W,0,"zerg/units/qufir00","sound\\bullet\\zqufir00.wav" __4},
	{W,0,"zerg/units/quhit00","sound\\bullet\\zquhit00.wav" __4},
	{W,0,"zerg/units/quhit01","sound\\bullet\\zquhit01.wav" __4},
	{W,0,"zerg/units/quhit02","sound\\bullet\\zquhit02.wav" __4},

	// Misc sounds
	{W,0,"misc/explo1","sound\\misc\\explo1.wav" __4},
	{W,0,"misc/explo2","sound\\misc\\explo2.wav" __4},
	{W,0,"misc/explo3","sound\\misc\\explo3.wav" __4},
	{W,0,"misc/explo4","sound\\misc\\explo4.wav" __4},
	{W,0,"misc/explo5","sound\\misc\\explo5.wav" __4},
	{W,0,"misc/explolrg","sound\\misc\\explolrg.wav" __4},
	{W,0,"misc/explomed","sound\\misc\\explomed.wav" __4},
	{W,0,"misc/explosm","sound\\misc\\explosm.wav" __4},
};


//	{G,0,"neutral/smmissile","unit\\bullet\\sMmissle.grp",1 __3},
//	{G,0,"neutral/spike","unit\\bullet\\Spike.grp",1 __3},
//	{G,0,"neutral/units/Generate","unit\\neutral\\Generate.grp",1 __3},
//	{G,0,"neutral/units/Icritter","unit\\neutral\\Icritter.grp",0 __3},
//	{G,0,"neutral/units/Kcritter","unit\\neutral\\Kcritter.grp",0 __3},
//	{G,0,"neutral/units/khalis","unit\\neutral\\khalis.grp",1 __3},
//	{G,0,"neutral/units/ncicShad","unit\\neutral\\ncicShad.grp",1 __3},
//	{G,0,"neutral/units/nckShad","unit\\neutral\\nckShad.grp",1 __3},
//	{G,0,"neutral/units/NrcDeath","unit\\neutral\\NrcDeath.grp",1 __3},
//	{G,0,"neutral/units/psi disruptor","unit\\neutral\\PsiDisr.grp",1 __3},
//	{G,0,"neutral/units/Scritter","unit\\neutral\\Scritter.grp",0 __3},
//	{G,0,"neutral/units/tgnShad","unit\\neutral\\tgnShad.grp",1 __3},
//	{G,0,"neutral/units/tpdShad","unit\\neutral\\tpdShad.grp",1 __3},
//	{G,0,"neutral/units/uraj","unit\\neutral\\uraj.grp",1 __3},


/**
**		File names.
*/
char* UnitNames[110];

unsigned char SC_Unit_Palette[]={
0x00,0x00,0x00,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,
0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0xFF,0x00,0xFF,0xDE,0x00,0xDE,0xBD,0x00,
0xBD,0x9C,0x00,0x9C,0x7C,0x00,0x7C,0x5B,0x00,0x5B,0x3A,0x00,0x3A,0x19,0x00,0x19,
0x2C,0x24,0x18,0x48,0x24,0x14,0x5C,0x2C,0x14,0x70,0x30,0x14,0x68,0x3C,0x24,0x7C,
0x40,0x18,0x78,0x4C,0x2C,0xA8,0x08,0x08,0x8C,0x54,0x30,0x84,0x60,0x44,0xA0,0x54,
0x1C,0xC4,0x4C,0x18,0xBC,0x68,0x24,0xB4,0x70,0x3C,0xD0,0x64,0x20,0xDC,0x94,0x34,
0xE0,0x94,0x54,0xEC,0xC4,0x54,0x34,0x44,0x28,0x40,0x6C,0x3C,0x48,0x6C,0x50,0x4C,
0x80,0x50,0x50,0x8C,0x5C,0x5C,0xA0,0x78,0x00,0x00,0x18,0x00,0x10,0x34,0x00,0x08,
0x50,0x24,0x34,0x48,0x30,0x40,0x54,0x14,0x34,0x7C,0x34,0x4C,0x6C,0x40,0x58,0x74,
0x48,0x68,0x8C,0x00,0x70,0x9C,0x58,0x80,0xA4,0x40,0x68,0xD4,0x18,0xAC,0xB8,0x24,
0x24,0xFC,0x64,0x94,0xBC,0x70,0xA8,0xCC,0x8C,0xC0,0xD8,0x94,0xDC,0xF4,0xAC,0xDC,
0xE8,0xAC,0xFC,0xFC,0xCC,0xF8,0xF8,0xFC,0xFC,0x00,0xF4,0xE4,0x90,0xFC,0xFC,0xC0,
0x0C,0x0C,0x0C,0x18,0x14,0x10,0x1C,0x1C,0x20,0x28,0x28,0x30,0x38,0x30,0x24,0x38,
0x3C,0x44,0x4C,0x40,0x30,0x4C,0x4C,0x4C,0x5C,0x50,0x40,0x58,0x58,0x58,0x68,0x68,
0x68,0x78,0x84,0x6C,0x68,0x94,0x6C,0x74,0xA4,0x7C,0x98,0x94,0x8C,0x90,0xB8,0x94,
0x98,0xC4,0xA8,0xB0,0xB0,0xB0,0xAC,0xCC,0xB0,0xC4,0xC0,0xBC,0xCC,0xE0,0xD0,0xF0,
0xF0,0xF0,0x1C,0x10,0x08,0x28,0x18,0x0C,0x34,0x10,0x08,0x34,0x20,0x0C,0x38,0x10,
0x20,0x34,0x28,0x20,0x44,0x34,0x08,0x48,0x30,0x18,0x60,0x00,0x00,0x54,0x28,0x20,
0x50,0x40,0x14,0x5C,0x54,0x14,0x84,0x04,0x04,0x68,0x4C,0x34,0x7C,0x38,0x30,0x70,
0x64,0x20,0x7C,0x50,0x50,0xA4,0x34,0x1C,0x94,0x6C,0x00,0x98,0x5C,0x40,0x8C,0x80,
0x34,0x98,0x74,0x54,0xB8,0x54,0x44,0xB0,0x90,0x18,0xB0,0x74,0x5C,0xF4,0x04,0x04,
0xC8,0x78,0x54,0xFC,0x68,0x54,0xE0,0xA4,0x84,0xFC,0x94,0x68,0xFC,0xCC,0x2C,0x10,
0xFC,0x18,0x0C,0x00,0x20,0x1C,0x1C,0x2C,0x24,0x24,0x4C,0x28,0x2C,0x68,0x2C,0x30,
0x84,0x20,0x18,0xB8,0x34,0x3C,0xAC,0x68,0x68,0x94,0x64,0x90,0xFC,0x7C,0xAC,0xFC,
0x00,0xE4,0xFC,0x9C,0x90,0x40,0xA8,0x94,0x54,0xBC,0xA4,0x5C,0xCC,0xB8,0x60,0xE8,
0xD8,0x80,0xEC,0xC4,0xB0,0xFC,0xFC,0x38,0xFC,0xFC,0x7C,0xFC,0xFC,0xA4,0x08,0x08,
0x08,0x10,0x10,0x10,0x18,0x18,0x18,0x28,0x28,0x28,0x34,0x34,0x34,0x4C,0x3C,0x38,
0x44,0x44,0x44,0x48,0x48,0x58,0x58,0x58,0x68,0x74,0x68,0x38,0x78,0x64,0x5C,0x60,
0x60,0x7C,0x84,0x74,0x74,0x84,0x84,0x9C,0xAC,0x8C,0x7C,0xAC,0x98,0x94,0x90,0x90,
0xB8,0xB8,0xB8,0xE8,0xF8,0x8C,0x14,0x10,0x54,0x3C,0x20,0x90,0x70,0x2C,0xB4,0x94,
0x04,0x20,0x64,0x48,0x1C,0x50,0x08,0x34,0x98,0x68,0x30,0x78,0x88,0x40,0x9C,0x0C,
0x48,0xCC,0xBC,0xB8,0x34,0xDC,0xDC,0x3C,0x10,0x00,0x00,0x24,0x00,0x00,0x34,0x00,
0x00,0x48,0x00,0x00,0x60,0x18,0x04,0x8C,0x28,0x08,0xC8,0x18,0x18,0xE0,0x2C,0x2C,
0xE8,0x20,0x20,0xE8,0x50,0x14,0xFC,0x20,0x20,0xE8,0x78,0x24,0xF8,0xAC,0x3C,0x00,
0x14,0x00,0x00,0x28,0x00,0x00,0x44,0x00,0x00,0x64,0x00,0x08,0x80,0x08,0x24,0x98,
0x24,0x3C,0x9C,0x3C,0x58,0xB0,0x58,0x68,0xB8,0x68,0x80,0xC4,0x80,0x94,0xD4,0x94,
0x0C,0x14,0x24,0x24,0x3C,0x64,0x30,0x50,0x84,0x38,0x5C,0x94,0x48,0x74,0xB4,0x54,
0x84,0xC4,0x60,0x94,0xD4,0x78,0xB4,0xEC,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,
0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,
0xFC,0xFC,0x38,0x10,0xFC,0x18,0xF8,0x8C,0x14,0xC8,0x18,0x18,0x23,0x23,0xFF,0x23,
0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0xFC,0xFC,0x38,0x10,0xFC,0x18,0xF8,0x8C,
0x14,0xC8,0x18,0x18,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,
0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,
0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,
0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,
0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,
0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,
0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0xFF,0xFF,0xFF,
};

unsigned char Terrain_Palette[]={
0x00,0x00,0x00,0x27,0x27,0x3B,0x27,0x27,0x3B,0x2F,0x2F,0x47,0x37,0x3B,0x53,0x2F,
0x33,0x4B,0x2B,0x2B,0x43,0x57,0x5F,0x83,0x63,0x6B,0x93,0x6B,0x77,0xA3,0x53,0x57,
0x77,0x4B,0x4F,0x6F,0x47,0x4B,0x67,0x4F,0x53,0x73,0x3A,0x00,0x3A,0x19,0x00,0x19,
0x2C,0x24,0x18,0x48,0x24,0x14,0x5C,0x2C,0x14,0x70,0x30,0x14,0x68,0x3C,0x24,0x7C,
0x40,0x18,0x78,0x4C,0x2C,0xA8,0x08,0x08,0x8C,0x54,0x30,0x84,0x60,0x44,0xA0,0x54,
0x1C,0xC4,0x4C,0x18,0xBC,0x68,0x24,0xB4,0x70,0x3C,0xD0,0x64,0x20,0xDC,0x94,0x34,
0xE0,0x94,0x54,0xEC,0xC4,0x54,0x34,0x44,0x28,0x40,0x6C,0x3C,0x48,0x6C,0x50,0x4C,
0x80,0x50,0x50,0x8C,0x5C,0x5C,0xA0,0x78,0x00,0x00,0x18,0x00,0x10,0x34,0x00,0x08,
0x50,0x24,0x34,0x48,0x30,0x40,0x54,0x14,0x34,0x7C,0x34,0x4C,0x6C,0x40,0x58,0x74,
0x48,0x68,0x8C,0x00,0x70,0x9C,0x58,0x80,0xA4,0x40,0x68,0xD4,0x18,0xAC,0xB8,0x24,
0x24,0xFC,0x64,0x94,0xBC,0x70,0xA8,0xCC,0x8C,0xC0,0xD8,0x94,0xDC,0xF4,0xAC,0xDC,
0xE8,0xAC,0xFC,0xFC,0xCC,0xF8,0xF8,0xFC,0xFC,0x00,0xF4,0xE4,0x90,0xFC,0xFC,0xC0,
0x0C,0x0C,0x0C,0x18,0x14,0x10,0x1C,0x1C,0x20,0x28,0x28,0x30,0x38,0x30,0x24,0x38,
0x3C,0x44,0x4C,0x40,0x30,0x4C,0x4C,0x4C,0x5C,0x50,0x40,0x58,0x58,0x58,0x68,0x68,
0x68,0x78,0x84,0x6C,0x68,0x94,0x6C,0x74,0xA4,0x7C,0x98,0x94,0x8C,0x90,0xB8,0x94,
0x98,0xC4,0xA8,0xB0,0xB0,0xB0,0xAC,0xCC,0xB0,0xC4,0xC0,0xBC,0xCC,0xE0,0xD0,0xF0,
0xF0,0xF0,0x1C,0x10,0x08,0x28,0x18,0x0C,0x34,0x10,0x08,0x34,0x20,0x0C,0x38,0x10,
0x20,0x34,0x28,0x20,0x44,0x34,0x08,0x48,0x30,0x18,0x60,0x00,0x00,0x54,0x28,0x20,
0x50,0x40,0x14,0x5C,0x54,0x14,0x84,0x04,0x04,0x68,0x4C,0x34,0x7C,0x38,0x30,0x70,
0x64,0x20,0x7C,0x50,0x50,0xA4,0x34,0x1C,0x94,0x6C,0x00,0x98,0x5C,0x40,0x8C,0x80,
0x34,0x98,0x74,0x54,0xB8,0x54,0x44,0xB0,0x90,0x18,0xB0,0x74,0x5C,0xF4,0x04,0x04,
0xC8,0x78,0x54,0xFC,0x68,0x54,0xE0,0xA4,0x84,0xFC,0x94,0x68,0xFC,0xCC,0x2C,0x10,
0xFC,0x18,0x0C,0x00,0x20,0x1C,0x1C,0x2C,0x24,0x24,0x4C,0x28,0x2C,0x68,0x2C,0x30,
0x84,0x20,0x18,0xB8,0x34,0x3C,0xAC,0x68,0x68,0x94,0x64,0x90,0xFC,0x7C,0xAC,0xFC,
0x00,0xE4,0xFC,0x9C,0x90,0x40,0xA8,0x94,0x54,0xBC,0xA4,0x5C,0xCC,0xB8,0x60,0xE8,
0xD8,0x80,0xEC,0xC4,0xB0,0xFC,0xFC,0x38,0xFC,0xFC,0x7C,0xFC,0xFC,0xA4,0x08,0x08,
0x08,0x10,0x10,0x10,0x18,0x18,0x18,0x28,0x28,0x28,0x34,0x34,0x34,0x4C,0x3C,0x38,
0x44,0x44,0x44,0x48,0x48,0x58,0x58,0x58,0x68,0x74,0x68,0x38,0x78,0x64,0x5C,0x60,
0x60,0x7C,0x84,0x74,0x74,0x84,0x84,0x9C,0xAC,0x8C,0x7C,0xAC,0x98,0x94,0x90,0x90,
0xB8,0xB8,0xB8,0xE8,0xF8,0x8C,0x14,0x10,0x54,0x3C,0x20,0x90,0x70,0x2C,0xB4,0x94,
0x04,0x20,0x64,0x48,0x1C,0x50,0x08,0x34,0x98,0x68,0x30,0x78,0x88,0x40,0x9C,0x0C,
0x48,0xCC,0xBC,0xB8,0x34,0xDC,0xDC,0x3C,0x10,0x00,0x00,0x24,0x00,0x00,0x34,0x00,
0x00,0x48,0x00,0x00,0x60,0x18,0x04,0x8C,0x28,0x08,0xC8,0x18,0x18,0xE0,0x2C,0x2C,
0xE8,0x20,0x20,0xE8,0x50,0x14,0xFC,0x20,0x20,0xE8,0x78,0x24,0xF8,0xAC,0x3C,0x00,
0x14,0x00,0x00,0x28,0x00,0x00,0x44,0x00,0x00,0x64,0x00,0x08,0x80,0x08,0x24,0x98,
0x24,0x3C,0x9C,0x3C,0x58,0xB0,0x58,0x68,0xB8,0x68,0x80,0xC4,0x80,0x94,0xD4,0x94,
0x0C,0x14,0x24,0x24,0x3C,0x64,0x30,0x50,0x84,0x38,0x5C,0x94,0x48,0x74,0xB4,0x54,
0x84,0xC4,0x60,0x94,0xD4,0x78,0xB4,0xEC,0x14,0x10,0x08,0x18,0x14,0x0C,0x28,0x30,
0x0C,0x10,0x10,0x18,0x14,0x14,0x20,0x2C,0x2C,0x40,0x44,0x4C,0x68,0x04,0x04,0x04,
0x1C,0x18,0x10,0x20,0x1C,0x14,0x24,0x20,0x1C,0x30,0x28,0x1C,0x40,0x38,0x2C,0x54,
0x48,0x34,0x68,0x5C,0x4C,0x90,0x7C,0x64,0x28,0x20,0x10,0x2C,0x24,0x14,0x34,0x2C,
0x18,0x38,0x2C,0x1C,0x3C,0x30,0x1C,0x40,0x34,0x20,0x44,0x38,0x24,0x50,0x44,0x24,
0x58,0x4C,0x28,0x64,0x58,0x2C,0x0C,0x10,0x04,0x14,0x18,0x04,0x1C,0x20,0x08,0x20,
0x28,0x0C,0x34,0x3C,0x10,0x40,0x48,0x10,0x20,0x20,0x30,0x14,0x14,0x14,0x20,0x18,
0x1C,0x20,0x20,0x20,0x28,0x20,0x18,0x28,0x24,0x24,0x30,0x2C,0x2C,0x3C,0x30,0x38,
0x3C,0x38,0x3C,0x48,0x3C,0x30,0x44,0x34,0x40,0x54,0x40,0x48,0x5C,0x64,0x64,0x6C,
0x74,0x78,0x58,0x4E,0x2F,0x4D,0x43,0x2C,0x4B,0x53,0x6F,0x53,0x5B,0x7B,0x5B,0x63,
0x87,0x47,0x3B,0x2B,0x4B,0x3F,0x2F,0x53,0x43,0x33,0x43,0x4B,0x67,0xFF,0xFF,0xFF,
};

unsigned char Cmdicons_Palette[]={
0x00,0x00,0x00,0xFC,0xFC,0x38,0xE7,0xE9,0x2F,0xFD,0xD1,0x39,0xFC,0xCC,0x2C,0xFC,
0xCC,0x2C,0xBC,0xB8,0x34,0xB0,0x90,0x18,0x8C,0x80,0x34,0x70,0x64,0x20,0x5C,0x54,
0x14,0x50,0x40,0x14,0x34,0x20,0x0C,0x28,0x18,0x0C,0x1C,0x10,0x08,0x19,0x00,0x19,
0x2C,0x24,0x18,0x48,0x24,0x14,0x5C,0x2C,0x14,0x70,0x30,0x14,0x68,0x3C,0x24,0x7C,
0x40,0x18,0x78,0x4C,0x2C,0xA8,0x08,0x08,0x8C,0x54,0x30,0x84,0x60,0x44,0xA0,0x54,
0x1C,0xC4,0x4C,0x18,0xBC,0x68,0x24,0xB4,0x70,0x3C,0xD0,0x64,0x20,0xDC,0x94,0x34,
0xE0,0x94,0x54,0xEC,0xC4,0x54,0x34,0x44,0x28,0x40,0x6C,0x3C,0x48,0x6C,0x50,0x4C,
0x80,0x50,0x50,0x8C,0x5C,0x5C,0xA0,0x78,0x00,0x00,0x18,0x00,0x10,0x34,0x00,0x08,
0x50,0x24,0x34,0x48,0x30,0x40,0x54,0x14,0x34,0x7C,0x34,0x4C,0x6C,0x40,0x58,0x74,
0x48,0x68,0x8C,0x00,0x70,0x9C,0x58,0x80,0xA4,0x40,0x68,0xD4,0x18,0xAC,0xB8,0x24,
0x24,0xFC,0x64,0x94,0xBC,0x70,0xA8,0xCC,0x8C,0xC0,0xD8,0x94,0xDC,0xF4,0xAC,0xDC,
0xE8,0xAC,0xFC,0xFC,0xCC,0xF8,0xF8,0xFC,0xFC,0x00,0xF4,0xE4,0x90,0xFC,0xFC,0xC0,
0x0C,0x0C,0x0C,0x18,0x14,0x10,0x1C,0x1C,0x20,0x28,0x28,0x30,0x38,0x30,0x24,0x38,
0x3C,0x44,0x4C,0x40,0x30,0x4C,0x4C,0x4C,0x5C,0x50,0x40,0x58,0x58,0x58,0x68,0x68,
0x68,0x78,0x84,0x6C,0x68,0x94,0x6C,0x74,0xA4,0x7C,0x98,0x94,0x8C,0x90,0xB8,0x94,
0x98,0xC4,0xA8,0xB0,0xB0,0xB0,0xAC,0xCC,0xB0,0xC4,0xC0,0xBC,0xCC,0xE0,0xD0,0xF0,
0xF0,0xF0,0x1C,0x10,0x08,0x28,0x18,0x0C,0x34,0x10,0x08,0x34,0x20,0x0C,0x38,0x10,
0x20,0x34,0x28,0x20,0x44,0x34,0x08,0x48,0x30,0x18,0x60,0x00,0x00,0x54,0x28,0x20,
0x50,0x40,0x14,0x5C,0x54,0x14,0x84,0x04,0x04,0x68,0x4C,0x34,0x7C,0x38,0x30,0x70,
0x64,0x20,0x7C,0x50,0x50,0xA4,0x34,0x1C,0x94,0x6C,0x00,0x98,0x5C,0x40,0x8C,0x80,
0x34,0x98,0x74,0x54,0xB8,0x54,0x44,0xB0,0x90,0x18,0xB0,0x74,0x5C,0xF4,0x04,0x04,
0xC8,0x78,0x54,0xFC,0x68,0x54,0xE0,0xA4,0x84,0xFC,0x94,0x68,0xFC,0xCC,0x2C,0x10,
0xFC,0x18,0x0C,0x00,0x20,0x1C,0x1C,0x2C,0x24,0x24,0x4C,0x28,0x2C,0x68,0x2C,0x30,
0x84,0x20,0x18,0xB8,0x34,0x3C,0xAC,0x68,0x68,0x94,0x64,0x90,0xFC,0x7C,0xAC,0xFC,
0x00,0xE4,0xFC,0x9C,0x90,0x40,0xA8,0x94,0x54,0xBC,0xA4,0x5C,0xCC,0xB8,0x60,0xE8,
0xD8,0x80,0xEC,0xC4,0xB0,0xFC,0xFC,0x38,0xFC,0xFC,0x7C,0xFC,0xFC,0xA4,0x08,0x08,
0x08,0x10,0x10,0x10,0x18,0x18,0x18,0x28,0x28,0x28,0x34,0x34,0x34,0x4C,0x3C,0x38,
0x44,0x44,0x44,0x48,0x48,0x58,0x58,0x58,0x68,0x74,0x68,0x38,0x78,0x64,0x5C,0x60,
0x60,0x7C,0x84,0x74,0x74,0x84,0x84,0x9C,0xAC,0x8C,0x7C,0xAC,0x98,0x94,0x90,0x90,
0xB8,0xB8,0xB8,0xE8,0xF8,0x8C,0x14,0x10,0x54,0x3C,0x20,0x90,0x70,0x2C,0xB4,0x94,
0x04,0x20,0x64,0x48,0x1C,0x50,0x08,0x34,0x98,0x68,0x30,0x78,0x88,0x40,0x9C,0x0C,
0x48,0xCC,0xBC,0xB8,0x34,0xDC,0xDC,0x3C,0x10,0x00,0x00,0x24,0x00,0x00,0x34,0x00,
0x00,0x48,0x00,0x00,0x60,0x18,0x04,0x8C,0x28,0x08,0xC8,0x18,0x18,0xE0,0x2C,0x2C,
0xE8,0x20,0x20,0xE8,0x50,0x14,0xFC,0x20,0x20,0xE8,0x78,0x24,0xF8,0xAC,0x3C,0x00,
0x14,0x00,0x00,0x28,0x00,0x00,0x44,0x00,0x00,0x64,0x00,0x08,0x80,0x08,0x24,0x98,
0x24,0x3C,0x9C,0x3C,0x58,0xB0,0x58,0x68,0xB8,0x68,0x80,0xC4,0x80,0x94,0xD4,0x94,
0x0C,0x14,0x24,0x24,0x3C,0x64,0x30,0x50,0x84,0x38,0x5C,0x94,0x48,0x74,0xB4,0x54,
0x84,0xC4,0x60,0x94,0xD4,0x78,0xB4,0xEC,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,
0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,
0xFC,0xFC,0x38,0x10,0xFC,0x18,0xF8,0x8C,0x14,0xC8,0x18,0x18,0x23,0x23,0xFF,0x23,
0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0xFC,0xFC,0x38,0x10,0xFC,0x18,0xF8,0x8C,
0x14,0xC8,0x18,0x18,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,
0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,
0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,
0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,
0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,
0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,
0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0x23,0x23,0xFF,0xFF,0xFF,0xFF,
};

unsigned char Orange_Palette[]={
0x00,0x00,0x00,
0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x10,0x00,0x00,0x10,
0x00,0x00,0x08,0x08,0x08,0x10,0x00,0x00,0x1C,0x10,0x08,0x24,0x00,0x00,0x34,0x10,
0x08,0x34,0x10,0x08,0x28,0x18,0x0C,0x34,0x10,0x08,0x34,0x10,0x08,0x48,0x24,0x14,
0x60,0x18,0x04,0x60,0x18,0x04,0x48,0x24,0x14,0x54,0x28,0x20,0x70,0x30,0x14,0x70,
0x30,0x14,0x70,0x30,0x14,0x70,0x30,0x14,0x8C,0x28,0x08,0x7C,0x40,0x18,0xA4,0x34,
0x1C,0x7C,0x40,0x18,0x78,0x4C,0x2C,0xA4,0x34,0x1C,0xA0,0x54,0x1C,0xC4,0x4C,0x18,
0xA0,0x54,0x1C,0xC4,0x4C,0x18,0xBC,0x68,0x24,0xD0,0x64,0x20,0xB4,0x70,0x3C,0xBC,
0x68,0x24,0xBC,0x68,0x24,0xDC,0x94,0x34,0xE0,0x94,0x54,0xDC,0x94,0x34,0xF8,0xAC,
0x3C,0xEC,0xC4,0x54,0xF4,0xE4,0x90,0xFC,0xFC,0xC0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,
0xCC,0xE0,0xD0,0xB0,0xB0,0xB0,0x98,0x94,0x8C,0x84,0x74,0x74,0x68,0x68,0x68,0x5C,
0x64,0x64,0x58,0x58,0x58,0x4C,0x4C,0x4C,0x44,0x44,0x44,0x34,0x34,0x34,0x30,0x2C,
0x2C,0x20,0x20,0x20,0x18,0x18,0x18,0x0C,0x0C,0x0C,0x04,0x04,0x04,
};

unsigned char *Palettes[] = {
	SC_Unit_Palette,
	Terrain_Palette,
	Cmdicons_Palette,
	Orange_Palette,
};

//----------------------------------------------------------------------------
//		TOOLS
//----------------------------------------------------------------------------

/**
**		Check if path exists, if not make all directories.
*/
void CheckPath(const char* path)
{
	char* cp;
	char* s;

	cp=strdup(path);
	s=strrchr(cp,'/');
	if( s ) {
		*s='\0';						// remove file
		s=cp;
		for( ;; ) {						// make each path element
			s=strchr(s,'/');
			if( s ) {
				*s='\0';
			}
#ifdef WIN32
			mkdir(cp);
#else
			mkdir(cp,0777);
#endif
			if( s ) {
				*s++='/';
			} else {
				break;
			}
		}
	}
	free(cp);
}

//----------------------------------------------------------------------------
//		PNG
//----------------------------------------------------------------------------

/**
**  Save a png file.
**
**  @param name         File name
**  @param image        Graphic data
**  @param w            Graphic width
**  @param h            Graphic height
**  @param pal          Palette
**  @param transparent  Image uses transparency
*/
int SavePNG(const char *name, unsigned char *image, int w, int h,
	unsigned char *pal, int transparent)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned char **lines;
	int i;

	if (!(fp = fopen(name, "wb"))) {
		fprintf(stderr,"%s:", name);
		perror("Can't open file");
		return 1;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fclose(fp);
		return 1;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(fp);
		return 1;
	}

	if (setjmp(png_ptr->jmpbuf)) {
		// FIXME: must free buffers!!
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}
	png_init_io(png_ptr, fp);

	// zlib parameters
	png_set_compression_level(png_ptr ,Z_BEST_COMPRESSION);

	// prepare the file information
	info_ptr->width = w;
	info_ptr->height = h;
	info_ptr->bit_depth = 8;
	info_ptr->color_type = PNG_COLOR_TYPE_PALETTE;
	info_ptr->interlace_type = 0;
	info_ptr->valid |= PNG_INFO_PLTE;
	info_ptr->palette = (png_colorp)pal;
	info_ptr->num_palette = 256;

	if (transparent != -1) {
		png_byte trans[256];

		memset(trans, 0xFF, sizeof(trans));
		trans[transparent] = 0x0;
		png_set_tRNS(png_ptr, info_ptr, trans, 256, 0);
	}

	// write the file header information
	png_write_info(png_ptr, info_ptr);  // write the file header information

	// set transformation

	// prepare image
	lines = (unsigned char **)malloc(h * sizeof(*lines));
	if (!lines) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}

	for (i = 0; i < h; ++i) {
		lines[i] = image + i * w;
	}

	png_write_image(png_ptr, lines);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	free(lines);

	return 0;
}

//----------------------------------------------------------------------------
//		Archive
//----------------------------------------------------------------------------

/**
**  Open the archive file.
**
**  @param file  Archive file name
**  @param type  Archive type requested
*/
int OpenArchive(const char *file)
{
	//
	//  Open the archive file
	//
	MpqFD = fopen(file, "rb");
	if (!MpqFD) {
		printf("Can't open %s\n", file);
		return -1;
	}

	char buf[1024];
	sprintf(buf, "%s/mpqlist.txt", Dir);

	if (Mpq->ReadInfo(MpqFD, buf)) {
		printf("MpqReadInfo failed\n");
		return -1;
	}

	return 0;
}

/**
**  Extract/uncompress entry.
**
**  @param name  Name of the entry to extract
**
**  @return      Pointer to uncompressed entry
*/
unsigned char *ExtractEntry(unsigned char *name)
{
	int i;
	unsigned char *buf;

	buf = NULL;
	for (i = 0; i < Mpq->FileCount; ++i) {
		if (!strcmp((char *)name, Mpq->FilenameTable + i * PATH_MAX)) {
			EntrySize = Mpq->BlockTable[i * 4 + 2];
			buf = (unsigned char *)malloc(EntrySize + 1);
			Mpq->ExtractTo(buf, i, MpqFD);
			printf("extracted: %s (%d, %d bytes)\n", name, i, EntrySize);
			break;
		}
	}
	if (i == Mpq->FileCount) {
		printf("Not found: %s\n", name);
		exit(-1);
	}

	return buf;
}

/**
**		Close the archive file.
*/
int CloseArchive(void)
{
	if (MpqFD) {
		fclose(MpqFD);
		MpqFD = NULL;
	}
	return 0;
}

//----------------------------------------------------------------------------
//		Map
//----------------------------------------------------------------------------

/**
**  Convert map
*/
int ConvertMap(char *listfile, char *file)
{
	FILE *fd;
	unsigned char *p;
	char buf[1024];

	sprintf(buf, "%s/%s", Dir, file);
	CheckPath(buf);
	p = ExtractEntry((unsigned char *)listfile);
	fd = fopen(buf, "wb");
	if (!fd) {
		free(p);
		return -1;
	}
	fwrite(p, EntrySize, 1, fd);
	fclose(fd);
	free(p);

	ConvertScm(buf, buf);

	return 0;
}

//----------------------------------------------------------------------------
//		Palette
//----------------------------------------------------------------------------

/**
**		Convert rgbx to rgb
*/
unsigned char* ConvertPaletteRGBXtoRGB(unsigned char* pal)
{
	int i;
	int j;

	for( i=0; i<256; ++i ) {
		for( j=0; j<3; ++j ) {
			pal[i*3+j]=pal[i*4+j];
		}
	}

	return pal;
}

/**
**  Convert rgb to my format.
*/
int ConvertRgb(char *listfile, char *file)
{
	unsigned char *palp;
	char buf[1024];
	FILE *f;
	int i;

	sprintf(buf, "%s.wpe", listfile);
	palp = ExtractEntry((unsigned char *)buf);
	ConvertPaletteRGBXtoRGB(palp);

	//
	//		Generate RGB File.
	//
	sprintf(buf, "%s/%s/%s.rgb", Dir, TILESET_PATH, file);
	CheckPath(buf);
	f = fopen(buf, "wb");
	if (!f) {
		perror("");
		printf("Can't open %s\n", buf);
		exit(-1);
	}
	if (fwrite(palp, 1, 256 * 3, f) != 256 * 3) {
		printf("Can't write %d bytes\n", 256 * 3);
	}

	fclose(f);

	//
	//  Generate GIMP palette
	//
	sprintf(buf, "%s/%s/%s.gimp", Dir, TILESET_PATH, file);
	CheckPath(buf);
	f = fopen(buf, "wb");
	if (!f) {
		perror("");
		printf("Can't open %s\n", buf);
		exit(-1);
	}
	fprintf(f, "GIMP Palette\n# Stratagus %c%s -- GIMP Palette file\n",
		toupper(*file), file + 1);

	for (i = 0; i < 256; ++i) {
		// FIXME: insert nice names!
		fprintf(f, "%d %d %d\t#%d\n", palp[i * 3], palp[i * 3 + 1], palp[i * 3 + 2], i);
	}
	fclose(f);

	free(palp);

	return 0;
}

//----------------------------------------------------------------------------
//		Tileset
//----------------------------------------------------------------------------

#ifdef MAKE_CCL
void SaveCCL(const unsigned char *map __attribute__((unused)),
	const int *map2tile, int mapl)
{
	int i;
	FILE *f;
	static int savecount = 0;
	char buf[1024];

	sprintf(buf, "save%02d.ccl", savecount++);
	f = fopen(buf, "w");

	fprintf(f, "DefineTileset(\n");
	fprintf(f, "  \"name\", \"\",\n");
	fprintf(f, "  \"image\", \"tilesets/.png\",\n");
	fprintf(f, "  \"slots\", {\n");

	fprintf(f,"   \"solid\", { \"light-grass\", \"land\", {\n");
	for (i = 0; i < mapl / 52 * 16; ++i) {
		if (i & 15) {
			fprintf(f, " ");
		} else if (i) {
			fprintf(f, "\t-- %03X\n",i - 16);
		}
		fprintf(f, "%4d,", map2tile[i]);
	}

	fprintf(f, "\n}}})\n");

	fclose(f);
}

/**
**		Count used mega tiles for map.
*/
int CountUsedTiles(const unsigned char *map, const unsigned char *mega,
	int *map2tile, int mapl)
{
	int i;
	int j;
	int used;
	const unsigned char *tp;
	int *img2tile;

	img2tile = (int *)malloc(mapl / 52 * 16 * sizeof(int));

	memset(map2tile, 0, sizeof(map2tile));

	//
	//		Build conversion table.
	//
	for (i = 0; i < mapl / 52; ++i) {
		tp = map + i * 52 + 20;
		for (j = 0; j< 0x10; ++j ) {
			if (((i << 4) | j) > mapl) {
				break;
			}
			map2tile[(i << 4) | j] = AccessLE16(tp + j * 2);
		}
	}

	//
	//  Mark all used mega tiles.
	//
	used = 0;
	for (i = 0; i < mapl / 52 * 16; ++i) {
		if (!map2tile[i]) {
			continue;
		}
		for (j = 0; j < used; ++j) {
			if (img2tile[j] == map2tile[i]) {
				break;
			}
		}
		if (j == used) {
			//
			//  Check unique mega tiles.
			//
			for (j = 0; j < used; ++j) {
				if (!memcmp(mega + img2tile[j] * 32, mega + map2tile[i] * 32, 32)) {
					break;
				}
			}
			if (j == used) {
				img2tile[used++] = map2tile[i];
			}
		}
	}
#if 0
	for (i = 0; i < used; ++i) {
		if (!(i % 16)) {
			DebugLevel1("\n");
		}
		DebugLevel1("%3d " _C_ img2tile[i]);
	}
	DebugLevel1("\n");
#endif

	return used;
}
#endif

/**
**  Decode a minitile into the image.
*/
void DecodeMiniTile(unsigned char *image, int ix, int iy, int iadd,
	unsigned char *mini, int index, int flipx, int flipy)
{
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			image[(y + iy * 8) * iadd + ix * 8 + x] =
				mini[index + (flipy ? (7 - y) : y) * 8 + (flipx ? (7 - x) : x)];
		}
	}
}

/**
**		Convert tiles into image.
*/
unsigned char *ConvertTile(unsigned char *mini, const char *mega, int msize,
	const char *map __attribute__((unused)),
	int mapl __attribute__((unused)), int *wp, int *hp)
{
	unsigned char *image;
	const unsigned short *mp;
	int height;
	int width;
	int i;
	int x;
	int y;
	int offset;
	int numtiles;
#ifdef MAKE_CCL
	int *map2tile;

	map2tile = (int *)malloc(mapl / 52 * 16 * sizeof(int));
	CountUsedTiles((unsigned char *)map, (unsigned char *)mega, map2tile, mapl);
#endif
	numtiles = msize / 32;

	width = TILE_PER_ROW * 32;
	height = ((numtiles + TILE_PER_ROW - 1) / TILE_PER_ROW) * 32;
	image = (unsigned char *)calloc(1, height * width);

	for (i = 0; i < numtiles; ++i) {
		//mp = (const unsigned short *)(mega + img2tile[i] * 32);
		mp = (const unsigned short *)(mega + i * 32);
		for (y = 0; y < 4; ++y) {
			for (x = 0; x < 4; ++x) {
				offset = ConvertLE16(mp[x + y * 4]);
				DecodeMiniTile(image,
					x + ((i % TILE_PER_ROW) * 4), y + (i / TILE_PER_ROW) * 4,
					width, mini, (offset / 2) * 64, offset & 1, 0);
			}
		}
	}

	*wp = width;
	*hp = height;
#ifdef MAKE_CCL
	SaveCCL((unsigned char *)map, map2tile, mapl);
	free(map2tile);
#endif
	return image;
}

/**
**  Convert a tileset to my format.
*/
int ConvertTileset(char *listfile, char *file)
{
	unsigned char *palp;
	unsigned char *megp;
	unsigned char *minp;
	unsigned char *mapp;
	unsigned char *flagp;
	unsigned char *image;
	int w;
	int h;
	int megl;
	int mapl;
	int flagl;
	char buf[1024];

	if (!strcmp(listfile, "tileset\\Install")) {
		sprintf(buf, "tileset\\install.wpe");
		palp = ExtractEntry((unsigned char *)buf);
		sprintf(buf, "tileset\\install.vr4");
		minp = ExtractEntry((unsigned char *)buf);
	} else {
		sprintf(buf, "%s.wpe", listfile);
		palp = ExtractEntry((unsigned char *)buf);
		sprintf(buf, "%s.vr4", listfile);
		minp = ExtractEntry((unsigned char *)buf);
	}
	sprintf(buf, "%s.vx4", listfile);
	megp = ExtractEntry((unsigned char *)buf);
	megl = EntrySize;
	sprintf(buf, "%s.cv5", listfile);
	mapp = ExtractEntry((unsigned char *)buf);
	mapl = EntrySize;

	sprintf(buf, "%s.vf4", listfile);
	flagp = ExtractEntry((unsigned char *)buf);
	flagl = EntrySize;

	image = ConvertTile(minp, (char *)megp, megl, (char *)mapp, mapl, &w, &h);

#ifdef DEBUG
	sprintf(buf, "%s/%s-flags.txt", Dir, strstr(listfile, "\\") + 1);
	FILE *fd = fopen(buf, "w");
	int i, j, tiles, start = -1;
	for (i = 0; i < flagl / 32; ++i) {
		unsigned short *s = (unsigned short *)(flagp + 32 * i);
		tiles = 0;
		for (j = 0; j < 16; ++j) {
			if (s[j] == 0) {
				++tiles;
			}
		}
		if (tiles >= 2) {
			if (start == -1) {
				start = i;
			}
			fprintf(fd, "tile %d is unpassable\n", i);
		}
		if (i == flagl / 32 - 1 || tiles < 2) {
			if (i == flagl / 32 - 1) ++i;
			if (start != -1) {
				if (start != i - 1) {
					fprintf(fd, "tile %d-%d unpassable\n", start, i - 1);
				} else {
					fprintf(fd, "tile %d unpassable\n", start);
				}
				start = -1;
			}
		}
	}
	fclose(fd);
#endif

	free(megp);
	free(minp);
	free(mapp);
	free(flagp);

	ConvertPaletteRGBXtoRGB(palp);

	sprintf(buf, "%s/%s/%s.png", Dir, TILESET_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 0);

	free(image);
	free(palp);

	return 0;
}

//----------------------------------------------------------------------------
//		Graphics
//----------------------------------------------------------------------------

/**
**		Decode a entry(frame) into image.
*/
void DecodeGfxEntry(int index,unsigned char* start
		,unsigned char* image,int ix,int iy,int iadd)
{
	unsigned char* bp;
	unsigned char* sp;
	unsigned char* dp;
	int xoff;
	int yoff;
	int width;
	int height;
	int offset;
	unsigned char* rows;
	int h;
	int w;
	int ctrl;

	bp=start+index*8;
	xoff=FetchByte(bp);
	yoff=FetchByte(bp);
	width=FetchByte(bp);
	height=FetchByte(bp);
	offset=FetchLE32(bp);

	rows=start+offset-6;
	dp=image+xoff-ix+(yoff-iy)*iadd;

	for( h=0; h<height; ++h ) {
		sp=rows+AccessLE16(rows+h*2);
		for( w=0; w<width; ) {
			ctrl=*sp++;
			if( ctrl&0x80 ) {				// transparent
				ctrl&=0x7F;
				memset(dp+h*iadd+w,255,ctrl);
				w+=ctrl;
			} else if( ctrl&0x40 ) {		// repeat
				ctrl&=0x3F;
				memset(dp+h*iadd+w,*sp++,ctrl);
				w+=ctrl;
			} else {						// set pixels
				ctrl&=0x3F;
				memcpy(dp+h*iadd+w,sp,ctrl);
				sp+=ctrl;
				w+=ctrl;
			}
		}
		//dp[h*iadd+width-1]=0;
	}
}

/**
**		Decode a entry(frame) into image.
*/
void DecodeGfuEntry(int index,unsigned char* start
		,unsigned char* image,int ix,int iy,int iadd)
{
	unsigned char* bp;
	unsigned char* sp;
	unsigned char* dp;
	int i;
	int xoff;
	int yoff;
	int width;
	int height;
	int offset;

	bp=start+index*8;
	xoff=FetchByte(bp);
	yoff=FetchByte(bp);
	width=FetchByte(bp);
	height=FetchByte(bp);
	offset=FetchLE32(bp);
	if( offset<0 ) {						// High bit of width
		offset&=0x7FFFFFFF;
		width+=256;
	}

	sp=start+offset-6;
	dp=image+xoff-ix+(yoff-iy)*iadd;
	for( i=0; i<height; ++i ) {
		memcpy(dp,sp,width);
		dp+=iadd;
		sp+=width;
	}
}
/**
**		Convert graphics into image.
*/
unsigned char* ConvertGraphic(int gfx,unsigned char* bp,int *wp,int *hp
		,unsigned char* bp2,int start2)
{
	int i;
	int count;
	int length;
	int max_width;
	int max_height;
	int minx;
	int miny;
	int best_width;
	int best_height;
	unsigned char* image;
	int IPR;

	int endereco;

	if (bp2) {		// Init pointer to 2nd animation
		count=FetchLE16(bp2);
		max_width=FetchLE16(bp2);
		max_height=FetchLE16(bp2);
	}
	count=FetchLE16(bp);
	max_width=FetchLE16(bp);
	max_height=FetchLE16(bp);


	// Find best image size
	minx=999;
	miny=999;
	best_width=0;
	best_height=0;
	for( i=0; i<count; ++i ) {
		unsigned char* p;
		int xoff;
		int yoff;
		int width;
		int height;

		p=bp+i*8;
		xoff=FetchByte(p);
		yoff=FetchByte(p);
		width=FetchByte(p);
		height=FetchByte(p);
		endereco = FetchLE32(p);
		if( endereco&0x80000000 ) {		// high bit of width
			width+=256;
		}
		if( xoff<minx ) minx=xoff;
		if( yoff<miny ) miny=yoff;
		if( xoff+width>best_width ) best_width=xoff+width;
		if( yoff+height>best_height ) best_height=yoff+height;
	}
	// FIXME: the image isn't centered!!

#if 0
	// Taken out, must be rewritten.
	if( max_width-best_width<minx ) {
		minx=max_width-best_width;
		best_width-=minx;
	} else {
		best_width=max_width-minx;
	}
	if( max_height-best_height<miny ) {
		miny=max_height-best_height;
		best_height-=miny;
	} else {
		best_height=max_width-miny;
	}

	//best_width-=minx;
	//best_height-=miny;
#endif

	minx=0;
	miny=0;

	if( gfx ) {
		best_width=max_width;
		best_height=max_height;
		IPR=17;								// st*rcr*ft 17!
		if( count<IPR ) {				// images per row !!
			IPR=1;
			length=count;
		} else {
			length=((count+IPR-1)/IPR)*IPR;
		}
	} else {
		max_width=best_width;
		max_height=best_height;
		IPR=1;
		length=count;
	}

	image = (unsigned char *)malloc(best_width * best_height * length);

	//		Image:		0, 1, 2, 3, 4,
	//				5, 6, 7, 8, 9, ...
	if( !image ) {
		printf("Can't allocate image\n");
		exit(-1);
	}
	// Set all to transparent.
	memset(image,255,best_width*best_height*length);

	if( gfx ) {
		for( i=0; i<count; ++i ) {
	// Hardcoded support for worker with resource repairing
			if (i>=start2 && bp2) DecodeGfxEntry(i,bp2
				,image+best_width*(i%IPR)+best_height*best_width*IPR*(i/IPR)
				,minx,miny,best_width*IPR);
			else DecodeGfxEntry(i,bp
				,image+best_width*(i%IPR)+best_height*best_width*IPR*(i/IPR)
				,minx,miny,best_width*IPR);
		}
	} else {
		for( i=0; i<count; ++i ) {
			DecodeGfuEntry(i,bp
				,image+best_width*(i%IPR)+best_height*best_width*IPR*(i/IPR)
				,minx,miny,best_width*IPR);
		}
	}

	*wp=best_width*IPR;
	*hp=best_height*(length/IPR);

	return image;
}

void ConvertPal3(unsigned char* image, int w, int h)
{
	int i;

	// FIXME: this isn't correct, there should be partial transparency
	for (i = 0; i < w * h; ++i) {
		if (image[i] < 16 || image[i] > 62) {
			image[i] = 255;
		}
	}
}

/**
**  Convert a graphic to my format.
*/
int ConvertGfx(char* listfile, char* file, int pale)
{
	unsigned char* palp;
	unsigned char* gfxp;
	unsigned char* gfxp2;
	unsigned char* image;
	int w;
	int h;
	char buf[1024];

	gfxp = ExtractEntry((unsigned char *)listfile);

	gfxp2 = NULL;
	image = ConvertGraphic(1, gfxp, &w, &h, gfxp2, 0);

	palp = Palettes[pale];

	free(gfxp);

	if (pale == 3) {
		ConvertPal3(image, w, h);
	}

	sprintf(buf, "%s/%s/%s.png", Dir, UNIT_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 255);

	free(image);

	return 0;
}

/**
**  Convert an uncompressed graphic to my format.
*/
int ConvertGfu(char* listfile, char* file, int pale)
{
	unsigned char* palp;
	unsigned char* gfup;
	unsigned char* gfup2;
	unsigned char* image;
	int w;
	int h;
	char buf[1024];
	unsigned char* p;
	unsigned char* end;

	gfup = ExtractEntry((unsigned char *)listfile);

	gfup2 = NULL;
	image = ConvertGraphic(0, gfup, &w, &h, gfup2, 0);

	// 0 and 255 are transparent
	p = image;
	end = image + w * h;
	while (p < end) {
		if (!*p) {
			*p = 0xFF;
		}
		++p;
	}

	palp = Palettes[pale];

	free(gfup);

	sprintf(buf, "%s/%s/%s.png", Dir, UNIT_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 255);

	free(image);

	return 0;
}

void SaveImage(char *name, unsigned char *image, unsigned char *palp, int id, int w, int h)
{
	unsigned char *buf = (unsigned char *)malloc(w * h);
	int i;

	for (i = 0; i < h; ++i) {
		memcpy(buf + w*i, image + id*28*64 + 64*i, w);
	}

	SavePNG(name, buf, w, h, palp, 255);

	free(buf);
}


void SaveButton(char *name, unsigned char *image, unsigned char *palp, int size, int id)
{
	unsigned char *button;
	int i, j;

	button = (unsigned char *)malloc(size * 28);

#define copyimage(dst, src) \
	for (j = 0; j < 28; ++j) { \
		memcpy((dst + size*j), (src + 64*j), 8); \
	}

	copyimage(button + 0, image + (id - 1) * 28 * 64);
	for (i = 8; i < size - 8; i += 8) {
		copyimage(button + i, image + id * 28 * 64);
	}
	copyimage(button + size - 8, image + (id + 1) * 28 * 64);

	for (i = 0; i < size * 28; ++i) {
		if (button[i] == 41) {
			button[i] = 255;
		}
	}

	SavePNG(name, button, size, 28, palp, 255);

	free(button);
}

int ConvertWidgets(char* listfile, char* file, int pale)
{
	unsigned char* palp;
	unsigned char* gfup;
	unsigned char* gfup2;
	unsigned char* image;
	int w;
	int h;
	char buf[1024];
	unsigned char* p;
	unsigned char* end;

	gfup = ExtractEntry((unsigned char *)listfile);

	gfup2 = NULL;
	image = ConvertGraphic(0, gfup, &w, &h, gfup2, 0);

	// 0 and 255 are transparent
	p = image;
	end = image + w * h;
	while (p < end) {
		if (!*p) {
			*p = 0xFF;
		}
		++p;
	}

	palp = Palettes[pale];

	free(gfup);

	sprintf(buf, "%s/graphics/%s/", Dir, file);
	CheckPath(buf);

	sprintf(buf, "%s/graphics/%s/menu.png", Dir, file);
	SaveImage(buf, image, palp, 1, 64, 20);

	sprintf(buf, "%s/graphics/%s/menu pressed.png", Dir, file);
	SaveImage(buf, image, palp, 2, 64, 20);


	sprintf(buf, "%s/graphics/%s/minimap terrain disabled.png", Dir, file);
	SaveImage(buf, image, palp, 3, 64, 20);

	sprintf(buf, "%s/graphics/%s/minimap terrain.png", Dir, file);
	SaveImage(buf, image, palp, 4, 64, 20);

	sprintf(buf, "%s/graphics/%s/minimap terrain pressed.png", Dir, file);
	SaveImage(buf, image, palp, 5, 64, 20);


	sprintf(buf, "%s/graphics/%s/diplomacy disabled.png", Dir, file);
	SaveImage(buf, image, palp, 83, 64, 20);

	sprintf(buf, "%s/graphics/%s/diplomacy.png", Dir, file);
	SaveImage(buf, image, palp, 84, 64, 20);

	sprintf(buf, "%s/graphics/%s/diplomacy pressed.png", Dir, file);
	SaveImage(buf, image, palp, 85, 64, 20);


	sprintf(buf, "%s/graphics/%s/button left disabled 224x28.png", Dir, file);
	SaveButton(buf, image, palp, 224, 104);

	sprintf(buf, "%s/graphics/%s/button left 224x28.png", Dir, file);
	SaveButton(buf, image, palp, 224, 107);

	sprintf(buf, "%s/graphics/%s/button left pressed 224x28.png", Dir, file);
	SaveButton(buf, image, palp, 224, 110);


	sprintf(buf, "%s/graphics/%s/button left disabled 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 104);

	sprintf(buf, "%s/graphics/%s/button left 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 107);

	sprintf(buf, "%s/graphics/%s/button left pressed 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 110);


	sprintf(buf, "%s/graphics/%s/button disabled 224x28.png", Dir, file);
	SaveButton(buf, image, palp, 224, 113);

	sprintf(buf, "%s/graphics/%s/button 224x28.png", Dir, file);
	SaveButton(buf, image, palp, 224, 116);

	sprintf(buf, "%s/graphics/%s/button pressed 224x28.png", Dir, file);
	SaveButton(buf, image, palp, 224, 119);


	sprintf(buf, "%s/graphics/%s/button disabled 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 113);

	sprintf(buf, "%s/graphics/%s/button 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 116);

	sprintf(buf, "%s/graphics/%s/button pressed 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 119);


	sprintf(buf, "%s/graphics/%s/button right disabled 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 122);

	sprintf(buf, "%s/graphics/%s/button right 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 125);

	sprintf(buf, "%s/graphics/%s/button right pressed 104x28.png", Dir, file);
	SaveButton(buf, image, palp, 104, 128);


	free(image);

	return 0;
}

struct PCXheader {
	unsigned char Manufacturer;
	unsigned char Version;
	unsigned char Encoding;
	unsigned char BitsPerPixel;
	short Xmin, Ymin, Xmax, Ymax;
	short HDpi, VDpi;
	unsigned char Colormap[48];
	unsigned char Reserved;
	unsigned char NPlanes;
	short BytesPerLine;
	short PaletteInfo;
	short HscreenSize;
	short VscreenSize;
	unsigned char Filler[54];
};

/**
**  Convert 8 bit pcx file to raw image
*/
void ConvertPcxToRaw(unsigned char *pcx, unsigned char **raw, unsigned char **pal,
	int *w, int *h)
{
	struct PCXheader pcxh;
	int y;
	int i;
	int count;
	unsigned char *src;
	unsigned char *dest;
	unsigned char ch;

	ch=0;
	memcpy(&pcxh, pcx, sizeof(struct PCXheader));
	pcxh.Xmin = ConvertLE16(pcxh.Xmin);
	pcxh.Ymin = ConvertLE16(pcxh.Ymin);
	pcxh.Xmax = ConvertLE16(pcxh.Xmax);
	pcxh.Ymax = ConvertLE16(pcxh.Ymax);
	pcxh.BytesPerLine = ConvertLE16(pcxh.BytesPerLine);

	*w = pcxh.Xmax - pcxh.Xmin + 1;
	*h = pcxh.Ymax - pcxh.Ymin + 1;

	*raw = (unsigned char *)malloc(*w * *h);
	src = pcx + sizeof(struct PCXheader);

	for (y = 0; y < *h; ++y) {
		count = 0;
		dest = *raw + y * *w;
		for (i = 0; i < *w; ++i) {
			if (!count) {
				ch = *src++;
				if ((ch & 0xc0) == 0xc0) {
					count = ch & 0x3f;
					ch = *src++;
				} else {
					count = 1;
				}
			}
			dest[i] = ch;
			--count;
		}
	}

	*pal = (unsigned char *)malloc(256 * 3);
	dest = *pal;
	do {
		ch = *src++;
	} while (ch != 12);

	for (i = 0; i < 256 * 3; ++i) {
		*dest++ = *src++;
	}
}

/**
**  Convert a pcx graphic to my format
*/
void ConvertPcx(char *listfile, char *file)
{
	unsigned char *palp;
	unsigned char *pcxp;
	unsigned char *image;
	char buf[1024];
	int w;
	int h;

	pcxp = ExtractEntry((unsigned char *)listfile);

	ConvertPcxToRaw(pcxp, &image, &palp, &w, &h);
	free(pcxp);

	sprintf(buf, "%s/%s/%s.png", Dir, UNIT_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 0);

	free(image);
	free(palp);
}

//----------------------------------------------------------------------------
//		Font
//----------------------------------------------------------------------------

/**
**  Convert font into image.
*/
unsigned char *ConvertFnt(unsigned char *start, int *wp, int *hp) {
	int i;
	int count;
	int max_width;
	int max_height;
	int width;
	int height;
	int w;
	int h;
	int xoff;
	int yoff;
	unsigned char *bp;
	unsigned char *dp;
	unsigned char *image;
	unsigned *offsets;

	bp = start + 5;  // skip "FONT "
	count = FetchByte(bp);
	count -= 32;
	max_width = FetchByte(bp);
	max_height = FetchByte(bp);


	offsets = (unsigned *)malloc(count * sizeof(u_int32_t));
	for (i = 0; i < count; ++i) {
		offsets[i] = FetchLE32(bp);
	}

	image = (unsigned char *)malloc(max_width * max_height * count);
	if (!image) {
		printf("Can't allocate image\n");
		exit(-1);
	}
	memset(image, 255, max_width * max_height * count);

	for (i = 0; i < count; ++i) {
		if (!offsets[i]) {
			continue;
		}
		bp = start + offsets[i];
		width = FetchByte(bp);
		height = FetchByte(bp);
		xoff = FetchByte(bp);
		yoff = FetchByte(bp);
		dp = image + xoff + yoff * max_width + i * (max_width * max_height);
		h = w = 0;
		for (;;) {
			int ctrl;
			ctrl = FetchByte(bp);
			w += (ctrl >> 3) & 0x1F;
			if (w >= width) {
				w -= width;
				++h;
				if (h >= height) {
					break;
				}
			}
			dp[h * max_width + w] = ctrl & 0x07;
			++w;
			if (w >= width) {
				w -= width;
				++h;
				if (h >= height) {
					break;
				}
			}
		}
	}
	free(offsets);

	*wp = max_width;
	*hp = max_height * count;

	return image;
}

/**
**  Convert a font to my format.
*/
int ConvertFont(char* listfile, char* file, int pale, int fnte __attribute__((unused))) {
	unsigned char* palp;
	unsigned char* fntp;
	unsigned char* image;
	int w;
	int h;
	char buf[1024];

	palp = Palettes[pale];
	fntp = ExtractEntry((unsigned char *)listfile);

	image = ConvertFnt(fntp, &w, &h);
	free(fntp);

	sprintf(buf, "%s/%s/%s.png", Dir, FONT_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 255);

	free(image);

	return 0;
}

//----------------------------------------------------------------------------
//		Wav
//----------------------------------------------------------------------------

/**
**  Convert pud to my format.
*/
int ConvertWav(char *listfile, char *file, int wave __attribute__((unused)))
{
	unsigned char *wavp;
	char buf[1024];
	gzFile gf;

	wavp = ExtractEntry((unsigned char *)listfile);

	sprintf(buf, "%s/%s/%s.wav.gz", Dir, SOUND_PATH, file);
	CheckPath(buf);
	gf = gzopen(buf, "wb9");
	if (!gf) {
		perror("");
		printf("Can't open %s\n", buf);
		exit(-1);
	}
	if (EntrySize != gzwrite(gf, wavp, EntrySize)) {
		printf("Can't write %d bytes\n", EntrySize);
	}

	free(wavp);

	gzclose(gf);

	return 0;
}

/**
**  Raw extraction
*/
int RawExtract(char *listfile, char *file)
{
	FILE *fd;
	unsigned char *p;
	char buf[1024];

	sprintf(buf, "%s/%s", Dir, file);
	CheckPath(buf);
	p = ExtractEntry((unsigned char *)listfile);
	fd = fopen(buf, "wb");
	if (!fd) {
		free(p);
		return -1;
	}
	fwrite(p, EntrySize, 1, fd);
	fclose(fd);
	free(p);
	return 0;
}

//----------------------------------------------------------------------------
//		Panels
//----------------------------------------------------------------------------

unsigned char *CreatePanel(int width, int height)
{
	unsigned char *buf;
	int i, j;

	buf = (unsigned char *)malloc(width * height * 4);
	memset(buf, 0, width * height * 4);

#define pixel2(i, j, r, g, b, a) \
	buf[(j) * width * 4 + (i) * 4 + 0] = r; \
	buf[(j) * width * 4 + (i) * 4 + 1] = g; \
	buf[(j) * width * 4 + (i) * 4 + 2] = b; \
	buf[(j) * width * 4 + (i) * 4 + 3] = a;

#define pixel(i, j) \
	pixel2((i), (j), 0x0, 0x8, 0x40, 0xff)

	for (j = 1; j < height - 1; ++j) {
		for (i = 1; i < width - 1; ++i) {
			pixel2(i, j, 0x0, 0x8, 0x40, 0x80);
		}
	}
	for (i = 3; i < width - 3; ++i) {
		pixel(i, 0);
		pixel(i, height - 1);
	}
	for (i = 3; i < height - 3; ++i) {
		pixel(0, i);
		pixel(width - 1, i);
	}
	// top left
	pixel(1, 1);
	pixel(2, 1);
	pixel(1, 2);
	// top right
	pixel(width - 3, 1);
	pixel(width - 2, 1);
	pixel(width - 2, 2);
	// bottom left
	pixel(1, height - 3);
	pixel(1, height - 2);
	pixel(2, height - 2);
	// bottom right
	pixel(width - 3, height - 2);
	pixel(width - 2, height - 2);
	pixel(width - 2, height - 3);

#undef pixel
#undef pixel2

	return buf;
}

int SavePanel(int width, int height)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned char **lines;
	int i;
	char name[256];
	unsigned char *buf;

	sprintf(name, "%s/graphics/ui/panels/%dx%d.png", Dir, width, height);
	CheckPath(name);

	if (!(fp = fopen(name, "wb"))) {
		fprintf(stderr,"%s:", name);
		perror("Can't open file");
		return 1;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fclose(fp);
		return 1;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(fp);
		return 1;
	}

	if (setjmp(png_ptr->jmpbuf)) {
		// FIXME: must free buffers!!
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}
	png_init_io(png_ptr, fp);

	// zlib parameters
	png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

	// prepare the file information
	info_ptr->width = width;
	info_ptr->height = height;
	info_ptr->bit_depth = 8;
	info_ptr->color_type = PNG_COLOR_TYPE_RGB_ALPHA;
	info_ptr->interlace_type = 0;

	buf = CreatePanel(width, height);

	// write the file header information
	png_write_info(png_ptr, info_ptr);  // write the file header information

	// set transformation

	// prepare image
	lines = (unsigned char **)malloc(height * sizeof(*lines));
	if (!lines) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		free(buf);
		return 1;
	}

	for (i = 0; i < height; ++i) {
		lines[i] = buf + i * width * 4;
	}

	png_write_image(png_ptr, lines);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	free(lines);
	free(buf);

	return 0;
}

void CreatePanels()
{
	SavePanel(264, 288);
	SavePanel(384, 256);
	SavePanel(312, 312);
	SavePanel(288, 128);
	SavePanel(296, 336);
}

//----------------------------------------------------------------------------
//		Main loop
//----------------------------------------------------------------------------

/**
**		Display the usage.
*/
void Usage(const char* name)
{
	printf("%s\n\
Usage: %s archive-directory [destination-directory]\n\
\t-V\tShow version\n\
\t-h\tShow usage\n\
archive-directory\tDirectory which includes the archives stardat.mpq...\n\
destination-directory\tDirectory where the extracted files are placed.\n"
	,NameLine, name);
}

/**
**		Main
*/
#undef main
int main(int argc, char **argv)
{
	unsigned u;
	char *archivedir;
	char buf[1024];
	int video;
	int a;
	int i;
	FILE * f;

	a = 1;
	video = 0;

	while (argc >= 2) {
		if (!strcmp(argv[a], "-v")) {
			video = 1;
			++a;
			--argc;
			continue;
		}
		if (!strcmp(argv[a], "-V")) {
			printf(VERSION "\n");
			++a;
			--argc;
			exit(0);
		}
		if (!strcmp(argv[a], "-h")) {
			Usage(argv[0]);
			++a;
			--argc;
			continue;
		}
		break;
	}

	if (argc != 2 && argc != 3) {
		Usage(argv[0]);
		exit(-1);
	}

	archivedir = argv[a];
	if (argc == 3) {
		Dir = argv[a + 1];
	} else {
		Dir = "data";
	}

	sprintf(buf, "%s/extracted", Dir);
	f = fopen(buf, "r");
	if (f) {
		char version[20];
		fgets(version, 20, f);
		fclose(f);
		if (strcmp(version, VERSION) == 0)
			printf("Note: Data is already extracted in Dir %s with this version of startool\n", Dir);
	}

	Mpq = new CMpq;

#if 0
	{
		FILE *fd;
		unsigned char* p;
		char buf[PATH_MAX];
		sprintf(buf, "%s/%s", archivedir, "stardat.mpq");
		OpenArchive(buf);
		p = ExtractEntry((unsigned char *)"rez\\minimap.bin");
		fd = fopen("minimap.bin", "wb");
		fwrite(p, EntrySize, 1, fd);
		fclose(fd);
		free(p);
		CloseArchive();
		exit(0);
	}
#endif

#ifdef DEBUG
	printf("Extract from \"%s\" to \"%s\"\n", archivedir, Dir);
#endif
	for (i = 0; i < 2; ++i) {
		Control *c;
		unsigned len;

		if (i == 0) {				// CD install.exe
			c = CDTodo;
			len=sizeof(CDTodo) / sizeof(*CDTodo);
		} else {				// stardat.mpq from cd or hard drive
			c = Todo;
			len = sizeof(Todo) / sizeof(*Todo);
		}

		for (u = 0; u < len; ++u) {
#ifdef DEBUG
			printf("%s:\n", c[u].File);
#endif
			switch (c[u].Type) {
				case F:
					if( !strncmp(c[u].ListFile,"remove-",7) ) {
						sprintf(buf, "%s/%s", Dir, c[u].ListFile);
					} else {
						sprintf(buf, "%s/%s", archivedir, c[u].ListFile);
					}
#ifdef DEBUG
					printf("Archive \"%s\"\n", buf);
#endif
					if (OpenArchive(buf) == -1) {
#ifdef DEBUG
						printf("Could not open archive \"%s\", skipping\n", buf);
#endif
						u=len;
					} else {
						if (c == CDTodo) {
#ifdef DEBUG
							printf("%s:\n", "remove-stardat.mpq");
#endif
							RawExtract("files\\stardat.mpq", "remove-stardat.mpq");
							Todo[0].ListFile = "remove-stardat.mpq";
						}
					}
					break;
				case M:
					ConvertMap(c[u].ListFile, c[u].File);
					break;
				case R:
					ConvertRgb(c[u].ListFile, c[u].File);
					break;
				case T:
					ConvertTileset(c[u].ListFile, c[u].File);
					break;
				case G:
					ConvertGfx(c[u].ListFile, c[u].File, c[u].Arg1);
					break;
				case U:
					ConvertGfu(c[u].ListFile, c[u].File, c[u].Arg1);
					break;
				case I:
					ConvertWidgets(c[u].ListFile, c[u].File, c[u].Arg1);
					break;
				case N:
					ConvertFont(c[u].ListFile, c[u].File, 2, c[u].Arg1);
					break;
				case W:
					ConvertWav(c[u].ListFile, c[u].File, c[u].Arg1);
					break;
				case H:
					ConvertPcx(c[u].ListFile, c[u].File);
					break;
				case E:
					RawExtract(c[u].ListFile, c[u].File);
					break;
				default:
					break;
			}
		}

		if( MpqFD ) {
			CloseArchive();
		}

		if( !strncmp(c[0].ListFile,"remove-",7) ) {
			sprintf(buf,"%s/%s",Dir,c[0].ListFile);
			printf("removing \"%s\"\n",buf);
			unlink(buf);
		}
	}
	delete Mpq;

	CreatePanels();

	sprintf(buf, "%s/extracted", Dir);
	f = fopen(buf, "w");
	fprintf(f, VERSION "\n");
	fclose(f);

	printf("DONE!\n");

	return 0;
}

//@}
