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
//      (c) Copyright 2002-2007 by Jimmy Salmon, Lutz Sammer
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

#define UInt32 unsigned long

#define UInt8		unsigned char
#define UInt16		unsigned short
#define SInt16		short
#define UInt32		unsigned long
#define SInt32		int


/*----------------------------------------------------------------------------
--  Declarations
----------------------------------------------------------------------------*/

typedef UInt16 (*read_data_proc)(UInt8 *buffer, UInt16 size, void *param);
typedef void (*write_data_proc)(UInt8 *buffer, UInt16 size, void *param, UInt32 *length_write);

class CMpq
{
public:
	CMpq() {}
	~CMpq();

		/// Read mpq info
	int ReadInfo(FILE* fpMpq);
		/// Extract mpq entry
	int ExtractTo(unsigned char* mpqbuf, UInt32 entry, FILE* fpMpq);

		/// Block table
	UInt32* BlockTable;
		/// Filename table
	char* FilenameTable;
		/// Identify table
	char* IdentifyTable;
		/// File count
	int FileCount;

private:
	int InitializeLocals(void);
	void BuildBaseMassive(void);
	UInt32 GetUnknowCrc(UInt32 entry, FILE *fpMpq, UInt32 *BlockTable);
	UInt32 explode(read_data_proc read_data, write_data_proc write_data, void *param);

	UInt8 *global_buffer, *read_buffer_start, *write_buffer_start;
	UInt32 *file_header;

	UInt8 *explode_buffer;

	UInt32 offset_mpq;				/// Offset to MPQ file data
	UInt32 offset_htbl;				/// Offset to hash_table of MPQ
	UInt32 offset_btbl;				/// Offset to MpqBlockTable of MPQ
	UInt32 length_mpq_part;				/// Length of MPQ file data
	UInt32 length_htbl;				/// Length of hash table
	UInt32 length_btbl;				/// Length of block table
	UInt32 *hash_table;				/// Hash table
	UInt32 massive_base[0x500];		/// This massive is used to calculate crc and decode files

	UInt32 length_write;
};



/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

extern void ConvertScm(const char *scmname, const char *newname);


//@}

#endif // !__MPQ_H__
