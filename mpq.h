//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//         Stratagus - A free fantasy real time strategy game engine
//
/**@name mpq.h - The mpq headerfile. */
//
//      (c) Copyright 2002-2006 by Jimmy Salmon, Lutz Sammer
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
//      $Id: mpq.h 1182 2005-06-19 21:00:25Z jsalmon3 $

#ifndef __MPQ_H__
#define __MPQ_H__

//@{

/*----------------------------------------------------------------------------
--  Defines
----------------------------------------------------------------------------*/

#define UInt32 unsigned long

/*----------------------------------------------------------------------------
--  Declarations
----------------------------------------------------------------------------*/

	/// Block table
extern UInt32* MpqBlockTable;
	/// Filename table
extern char* MpqFilenameTable;
	/// Identify table
extern char* MpqIdentifyTable;
	/// File count
extern int MpqFileCount;


/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

	/// Read mpq info
extern int MpqReadInfo(FILE* fpMpq);
	/// Extract mpq entry
extern int MpqExtractTo(unsigned char* mpqbuf, UInt32 entry, FILE* fpMpq);
	/// Clean mpq
extern void CleanMpq(void);

extern void ConvertScm(const char *name);


//@}

#endif // !__MPQ_H__
