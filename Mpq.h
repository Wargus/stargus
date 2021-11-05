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
/**@name Mpq.h - The mpq headerfile. */
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
#ifndef MPQ_H_
#define MPQ_H_

// System
#include <stdint.h>
#include <StormLib.h>
#include <zlib.h>
#include <string>

class Mpq
{
public:
	Mpq();
	Mpq(const std::string &archiveName);
	virtual ~Mpq();

	bool openArchive(const std::string &archiveName);
	void closeArchive();

	/**
	 * Extract file from MPQ archive and create all directories if not existing
	 */
	bool extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress);

	/**
	 * Attention: This function malloc() bufferLen memory which you've to free yourself!
	 * TODO: better memory handling needed
	 */
	bool extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen);

private:
	HANDLE mMpqHandle; // Open archive handle


};






#endif /* MPQ_H_ */
