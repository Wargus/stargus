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
//      (c) Copyright 2002-2012 by Jimmy Salmon, Lutz Sammer and Pali Rohár
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

#ifndef __MPQ_H__
#define __MPQ_H__

//@{

/*----------------------------------------------------------------------------
--  Defines
----------------------------------------------------------------------------*/

#include <stdint.h>

#include <StormLib.h>
#include <zlib.h>

/*----------------------------------------------------------------------------
--  Declarations
----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

extern void ConvertScm(const char *mpqfile);

int ExtractMPQEntry(const char *szArchiveName, const char *szArchivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen);
int ExtractMPQFile(const char *szArchiveName, const char *szArchivedFile, const char *szFileName, bool compress);
void CheckPath(const char* path);
//@}

#endif // !__MPQ_H__
