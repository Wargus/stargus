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
/**@name mpq.c - Mpq. */
//
//      (c) Copyright 1998-2012 by Lutz Sammer, Jimmy Salmon and Pali Rohár
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

#include "mpq.h"
#include "huff.h"


/*----------------------------------------------------------------------------
--		Declarations
----------------------------------------------------------------------------*/

#define DCL_NO_ERROR	0L
#define DCL_ERROR_1	 1L
#define DCL_ERROR_2	 2L
#define DCL_ERROR_3	 3L
#define DCL_ERROR_4	 4L

#define DEFAULT_LIST		"mpqlist.txt"

typedef struct {
	UInt8 *buf_in;
	UInt8 *buf_out;
} params;

static UInt16 __explode_1(UInt8 * buf, UIntPtr *length_write);
static UInt16 __explode_2(UInt8 * buf);
static UInt16 __explode_3(UInt8 * buf, UInt16 result);
static UInt16 __explode_4(UInt8 * buf, UInt32 flag);
static void __explode_5(UInt16 count, UInt8 * buf_1, const UInt8 * table, UInt8 * buf_2);
static void __explode_6(UInt8 * buf, const UInt8 * table);
static void __explode_7(UInt8 * buf, const UInt8 * table, UInt32 count);

static UInt32 Crc(char *string, UInt32 * massive_base, UInt32 massive_base_offset);
static void Decode(UInt32 * data_in, UInt32 * massive_base, UInt32 crc, UInt32 length);
static UInt16 read_data(UInt8 *buffer, UInt16 size, void *crap);
static void write_data(UInt8 * buffer, UInt16 size, void *crap, UIntPtr *length_write);


UIntPtr		ExtWavUnp1(UIntPtr,UIntPtr,UIntPtr,UIntPtr);
UIntPtr		ExtWavUnp2(UIntPtr,UIntPtr,UIntPtr,UIntPtr);
UIntPtr		ExtWavUnp3(UIntPtr,UIntPtr,UIntPtr,UIntPtr);
UIntPtr		Sub_WavUnp13(UIntPtr,UIntPtr,UIntPtr,UIntPtr,UIntPtr);



/*----------------------------------------------------------------------------
--  Variables
----------------------------------------------------------------------------*/

static UInt32 avail_metods[4] = { 0x08, 0x01, 0x40, 0x80 };
extern const unsigned char dcl_table[];
extern const UInt32 small_tbl1[90];
extern const UInt32 small_tbl2[32];


/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

/**
**  Analyzing archive
*/
int CMpq::ReadInfo(FILE *fpMpq, const char * list)
{
	UInt32 mpq_header[2] = { 0x1a51504d, 0x00000020 };
	int i, j;
	UInt32 detected = 0;
	UInt32 tmp, scrc1, scrc2, scrc3, pointer_ht;
	FILE *fpList = NULL;
	char prnbuf[PATH_MAX+100];
	static char name_htable[] = "(hash table)";		// Name of hash table (used to decode hash table)
	static char name_btable[] = "(block table)";		// Name of block table (used to decode block table)

	while (fread(&tmp, sizeof(UInt32), 1, fpMpq)) {
		if (mpq_header[0] == tmp) {
			if (fread(&tmp, sizeof(UInt32), 1, fpMpq) == 0)
				return -1;
			if (mpq_header[1] == tmp) {
				detected = 1;
				break;
			}
		}
	}
	if (!detected) {
		printf("Error: File is not valid MPQ archive\n");
		return -1;
	}
	offset_mpq = ftell(fpMpq) - 8;
	if (fread(&length_mpq_part, sizeof(UInt32), 1, fpMpq) == 0)
		return -1;
	fseek(fpMpq, offset_mpq + 16, SEEK_SET);
	if (fread(&offset_htbl, sizeof(UInt32), 1, fpMpq) == 0)
		return -1;
	if (fread(&offset_btbl, sizeof(UInt32), 1, fpMpq) == 0)
		return -1;
	if (fread(&length_htbl, sizeof(UInt32), 1, fpMpq) == 0)
		return -1;
	length_htbl *= 4;
	if (fread(&length_btbl, sizeof(UInt32), 1, fpMpq) == 0)
		return -1;
	FileCount = length_btbl;
	length_btbl *= 4;

	BuildBaseMassive();
	if (InitializeLocals()) {
		return -2;
	}

	fseek(fpMpq, offset_mpq + offset_htbl, SEEK_SET);
	if (fread(hash_table, sizeof(UInt32), length_htbl, fpMpq) == 0)
		return -1;
	fseek(fpMpq, offset_mpq + offset_btbl, SEEK_SET);
	if (fread(BlockTable, sizeof(UInt32), length_btbl, fpMpq) == 0)
		return -1;
	tmp = Crc(name_htable, massive_base, 0x300);
	Decode(hash_table, massive_base, tmp, length_htbl);
	tmp = Crc(name_btable, massive_base, 0x300);
	Decode(BlockTable, massive_base, tmp, length_btbl);

	if (list)
		fpList = fopen(list, "rt");

	if (list && !fpList) {
		fprintf(stderr, "Error: Can't open specified list: %s\n", list);
		return -1;
	}

	if (!fpList)
		fpList = fopen(DEFAULT_LIST, "rt");

	if (fpList) {
		while (fgets(prnbuf, PATH_MAX, fpList) != 0) {
			if (*(prnbuf + strlen(prnbuf) - 1) == '\n') {
				*(prnbuf + strlen(prnbuf) - 1) = 0;
			}
			if (*(prnbuf + strlen(prnbuf) - 1) == '\r') {
				*(prnbuf + strlen(prnbuf) - 1) = 0;
			}
			scrc1 = Crc(prnbuf, massive_base, 0);
			scrc2 = Crc(prnbuf, massive_base, 0x100);
			scrc3 = Crc(prnbuf, massive_base, 0x200);
			pointer_ht = (scrc1 & (length_htbl / 4 - 1)) * 4;
			for (; pointer_ht < length_htbl; pointer_ht += 4) {
				if ((*(hash_table + pointer_ht) == scrc2)
					&& (*(hash_table + pointer_ht + 1) == scrc3)) {
					// - fill FilenameTable
					int offset = *(hash_table + pointer_ht + 3);
					if (offset < 0) {
						fprintf(stderr, "Cannot add %s to filename table\n", prnbuf);
						continue;
					}
					sprintf(FilenameTable + PATH_MAX * offset, "%s", prnbuf);
					// . fill IdentifyTable
					*(IdentifyTable + offset) = 1;
					break;
				}
			}
		}
		fclose(fpList);
	} else {
		fprintf(stderr, "Warning: Can't open default list: %s\n", DEFAULT_LIST);
	}

	j = 1;
	for (i = 0; i < FileCount; ++i) {		// if there are not identified files, then
		if (!*(IdentifyTable + i)) {				// fill MpqFilenameTable with "unknow\unknowN
			sprintf(FilenameTable + PATH_MAX * i, "unknow\\unk%05d.xxx", j);
			++j;
		}
	}
	return 0;
}

/**
**		Allocation of memory for hash_table,MpqBlockTable,
**		MpqFilenameTable,MpqIdentifyTable and working buffers
**		7to decompress files
*/
int CMpq::InitializeLocals(void)
{
	global_buffer = (UInt8 *) malloc(0x60000);		// Allocation 384 KB for global_buffer
	if (!global_buffer) {
		printf("\nError! Insufficient memory");
		return -1;
	}
	read_buffer_start = global_buffer;		// 4 KB for read_buffer
	write_buffer_start = global_buffer + 0x1000;		// 4 KB for write_buffer
	explode_buffer = global_buffer + 0x2000;		// 16 KB for explode_buffer
	file_header = (UInt32 *)(global_buffer + 0x6000);		// 360 KB for file_header (max size of unpacked file can't exceed 360 MB)

	hash_table = (UInt32 *)malloc(length_htbl * 4);
	BlockTable = (UInt32 *)malloc(length_btbl * 4);
	FilenameTable = (char *)calloc(length_btbl / 4, sizeof(char) * PATH_MAX);
	IdentifyTable = (char *)calloc(length_btbl / 4, sizeof(char));
	if (hash_table && BlockTable && FilenameTable && IdentifyTable) {
		return 0;
	} else {
		printf("\nError! Insufficient memory");
		return -1;
	}
}

/**
**
*/
CMpq::CMpq()
{
	global_buffer = NULL;
	hash_table = NULL;
	BlockTable = NULL;
	FilenameTable = NULL;
	IdentifyTable = NULL;
}

/**
**  Free memory
*/
CMpq::~CMpq()
{
	if (global_buffer) {
		free(global_buffer);
		global_buffer = NULL;
	}
	if (hash_table) {
		free(hash_table);
		hash_table = NULL;
	}
	if (BlockTable) {
		free(BlockTable);
		BlockTable = NULL;
	}
	if (FilenameTable) {
		free(FilenameTable);
		FilenameTable = NULL;
	}
	if (IdentifyTable) {
		free(IdentifyTable);
		IdentifyTable = NULL;
	}
	return;
}

/**
**		Fill massive_base
*/
void CMpq::BuildBaseMassive(void)
{
	UInt32 s1;
	int i, j;
	ldiv_t divres;

	divres.rem = 0x100001;
	for (i = 0; i < 0x100; ++i) {
		for (j = 0; j < 5; ++j) {
			divres = ldiv(divres.rem * 125 + 3, 0x002AAAAB);
			s1 = (divres.rem & 0xFFFFL) << 0x10;
			divres = ldiv(divres.rem * 125 + 3, 0x002AAAAB);
			s1 = s1 | (divres.rem & 0xFFFFL);
			massive_base[i + 0x100 * j] = s1;
		}
	}
	return;
}

/**
**		Calculate crc
*/
static UInt32 Crc(char *string, UInt32 *massive_base, UInt32 massive_base_offset)
{
	char byte;
	UInt32 crc = 0x7fed7fed;
	UInt32 s1 = 0xEEEEEEEE;

	byte = *string;
	while (byte) {
		if (byte > 0x60 && byte < 0x7B) {
			byte -= 0x20;
		}
		crc = *(massive_base + massive_base_offset + byte) ^ (crc + s1);
		s1 += crc + (s1 << 5) + byte + 3;
		string++;
		byte = *string;
	}
	return crc;
}

/**
**		(called by explode)
*/
UInt16 read_data(UInt8 *buffer, UInt16 size, void *crap)
{
	params *param;

	param = (params *)crap;
	memcpy(buffer, param->buf_in, size);
	param->buf_in += size;
	return size;
}

/**
**		(called by explode)
*/
void write_data(UInt8 * buffer, UInt16 size, void *crap, UIntPtr *length_write)
{
	params *param;

	param = (params *)crap;
	memcpy(param->buf_out, buffer, size);
	param->buf_out += size;
	*length_write += size;
}

/**
**		Decode data
*/
static void Decode(UInt32 * data_in, UInt32 * massive_base, UInt32 crc, UInt32 length)
{
	UInt32 i, dec;
	UInt32 s1;

	s1 = 0xEEEEEEEE;
	for (i = 0; i < length; i++) {
		s1 += *(massive_base + 0x400 + (crc & 0xFFL));
		dec = *(data_in + i) ^ (s1 + crc);
		s1 += dec + (s1 << 5) + 3;
		*(data_in + i) = dec;
		crc = (crc >> 0x0b) | (0x11111111 + ((crc ^ 0x7FFL) << 0x15));
	}
	return;
}

/**
**		Calculate crc for file without name
*/
UInt32 CMpq::GetUnknowCrc(UInt32 entry, FILE *fpMpq, UInt32 *BlockTable)
{
	UInt32 tmp, i, j, coded_dword, crc_file;
	UInt32 flag, size_unpack, num_block, offset_body;
	UInt32 sign_riff1 = 0x46464952;		// 'RIFF'
	UInt32 sign_riff3 = 0x45564157;		// 'WAVE'
	UInt32 sign_mpq1 = 0x1a51504d;		// 'MPQ'
	UInt32 sign_mpq2 = 0x00000020;
	ldiv_t divres;

	offset_body = *(BlockTable + entry * 4);		// get offset of analized file
	flag = *(BlockTable + entry * 4 + 3);		// get flag of analized file
	fseek(fpMpq, offset_mpq + offset_body, SEEK_SET);
	if (fread(&coded_dword, sizeof(UInt32), 1, fpMpq) == 0)		// read first coded dword from file
		return 0;

	if (flag & 0x200 || flag & 0x100) {		// IF FILE PACKED:
		size_unpack = *(BlockTable + entry * 4 + 2);		// . get size of unpacked file
		divres = ldiv(size_unpack - 1, 0x1000);
		num_block = divres.quot + 2;		// . calculate length of file header
		for (j = 0; j <= 0xff; j++) {		// . now we're gonna find crc_file of 0x100 possible variants
			crc_file = ((num_block * 4) ^ coded_dword) - 0xeeeeeeee - *(massive_base + 0x400 + j);		// . calculate possible crc
			if ((crc_file & 0xffL) == j) {		// . IF FIRST CHECK is succesfull - do second one
				fseek(fpMpq, offset_mpq + offset_body, SEEK_SET);
				if (fread(file_header, sizeof(UInt32), num_block, fpMpq) == 0)		// . read file header
					return 0;
				Decode(file_header, massive_base, crc_file, num_block);		// . decode file header with possible crc
				tmp = num_block * 4;		// . tmp = size header (bytes)
				if (tmp == *file_header) {		// . IF SECOND CHECK is succesfull - do third one
					for (i = 0; i < num_block - 1; i++) {
						tmp += *(file_header + i + 1) - *(file_header + i);
						if (*(file_header + i + 1) - *(file_header + i) >
							0x1000) {
							tmp = 0xffffffff;
							break;
						}
					}
					if (tmp != 0xffffffff) {		// . IF THIRD CHECK is succesfull
						crc_file++;		// . great! we got right crc_file
						break;
					}
				}
			}
			crc_file = 0;				// . if its impossible to get right crc return 0
		}

	} else {								// IF FILE IS NOT PACKED:
		for (j = 0; j <= 0xff; j++) {		// Calculate crc as if it was WAV FILE
			crc_file = (sign_riff1 ^ coded_dword) - 0xeeeeeeee - *(massive_base + 0x400 + j);		// . calculate possible crc
			if ((crc_file & 0xff) == j) {		// . IF FIRST CHECK is succesfull - do second one
				fseek(fpMpq, offset_mpq + offset_body, SEEK_SET);
				if (fread(file_header, sizeof(UInt32), 3, fpMpq) == 0)		// . read file file_header
					return 0;
				Decode(file_header, massive_base, crc_file, 3);		// . decode file file_header with possible crc
				if (sign_riff1 == *file_header) {
					if (sign_riff3 == *(file_header + 2)) {		// . IF SECOND CHECK is succesfull - we got right crc
						break;
					}
				}
			}
			crc_file = 0;				// . if its impossible to get right crc return 0
		}
		if (!crc_file) {				// Calculate crc as if it was MPQ FILE
			for (j = 0; j <= 0xff; j++) {
				crc_file =
					(sign_mpq1 ^ coded_dword) - 0xeeeeeeee - *(massive_base +
					0x400 + j);
				if ((crc_file & 0xffL) == j) {
					fseek(fpMpq, offset_mpq + offset_body, SEEK_SET);
					if (fread(file_header, sizeof(UInt32), 2, fpMpq) == 0)
						return 0;
					Decode(file_header, massive_base, crc_file, 2);
					if (sign_mpq1 == *file_header) {
						if (sign_mpq2 == *(file_header + 1)) {
							break;
						}
					}
				}
				crc_file = 0;
			}
		}
	}
	return crc_file;
}

/**
**		Extract file from archive
*/
int CMpq::ExtractTo(unsigned char *mpqbuf, UInt32 entry, FILE *fpMpq)
{
	UIntPtr size_pack, size_unpack;
	UInt8 *read_buffer, *write_buffer;
	UIntPtr i, j, offset_body, flag, crc_file;
	UIntPtr num_block, length_read, iteration;
	char *szNameFile;
	UInt8 metod;
	ldiv_t divres;
	params param;
	unsigned char *mpqptr;

	mpqptr = mpqbuf;

	offset_body = *(BlockTable + entry * 4);		// get offset of file in mpq
	size_unpack = *(BlockTable + entry * 4 + 2);		// get unpacked size of file
	flag = *(BlockTable + entry * 4 + 3);		// get flags for file
	crc_file = 0;

	if (flag & 0x30000) {				// If file is coded, calculate its crc
		if (*(IdentifyTable + entry) & 0x1) {		// . Calculate crc_file for identified file:
			szNameFile = FilenameTable + PATH_MAX * entry;		// . . get name of file
			if (strrchr(szNameFile, '\\')) {
				szNameFile = strrchr(szNameFile, '\\') + 1;
			}
			crc_file = Crc(szNameFile, massive_base, 0x300);		// . . calculate crc_file (for Diablo I MPQs)
			if ((flag & 0x20200) == 0x20200) {				// . . if flag indicates Starcraft MPQ
				crc_file = (crc_file + offset_body) ^ size_unpack;		// . . calculate crc_file (for Starcraft MPQs)
			}
		} else {
			crc_file = GetUnknowCrc(entry, fpMpq, BlockTable);		// . calculate crc_file for not identified file:
		}
	}

	if (flag & 0x200 || flag & 0x100) {		// IF FILE IS PACKED:
		divres = ldiv(size_unpack - 1, 0x1000);
		num_block = divres.quot + 2;		// . calculate length of file header
		fseek(fpMpq, offset_mpq + offset_body, SEEK_SET);
		if (fread(file_header, sizeof(UInt32), num_block, fpMpq) == 0)		// . read file header
			return 1;
		if (flag & 0x30000) {
			Decode(file_header, massive_base, (crc_file - 1), num_block);		// . decode file header (if file is coded)
		}
		read_buffer = read_buffer_start;
		for (j = 0; j < (num_block - 1); j++) {
			length_read = *(file_header + j + 1) - *(file_header + j);		// . get length of block to read
			if (fread(read_buffer, sizeof(char), length_read, fpMpq) == 0)		// . read block
				return 1;
			if (flag & 0x30000) {
				Decode((UInt32 *) read_buffer, massive_base, crc_file, length_read / 4);		// . decode block (if file is coded)
			}
			if (length_read == 0x1000 || (j == num_block - 2 && length_read == (size_unpack & 0xFFF))) {		// . if block is unpacked (its length=0x1000 or its last block and length=remainder)
				memcpy(mpqptr, read_buffer, length_read);
				mpqptr += length_read;
//				fwrite(read_buffer, sizeof(char), length_read, fp_new);		// . write block "as is"
			}
			else {						// . block is packed
				if (flag & 0x200) {		// . If this file is from Starcraft MPQ (or Diablo 2), then
					metod = *read_buffer;		// . . first byte determinates metod of packing
					iteration = 0;
					for (i = 0; i < 4; i++) {		// . . calculate number of iterations
						if (metod & avail_metods[i]) {
							iteration++;
						}
					}
					read_buffer += 1;
					length_read -= 1;
				} else {				// . Else: file is from Diablo I MPQ, then
					iteration = 1;
					metod = 8;				// . .file is compressed with DCL
				}
				write_buffer = write_buffer_start;
				if (metod & 0x08) {
					param.buf_in = read_buffer;
					param.buf_out = write_buffer;
					length_write = 0;
					explode(&param);
					length_read = length_write;
					iteration--;
					if (iteration) {
						read_buffer = write_buffer;
						write_buffer = read_buffer_start;
					}
				}
				if (metod & 0x01) { // Huffman
					length_read =
						ExtWavUnp1((UIntPtr) read_buffer,
						(UIntPtr) length_read, (UIntPtr) write_buffer,
						0x1000);
					iteration--;
					if (iteration) {
						read_buffer = write_buffer;
						write_buffer = read_buffer_start;
					}
				}
				if (metod & 0x40) { // Mono ADPCM Wave
					length_read =
						ExtWavUnp2((UIntPtr) read_buffer,
						(UIntPtr) length_read, (UIntPtr) write_buffer,
						0x1000);
				}
				if (metod & 0x80) { // Stereo ADPCM Wave
					length_read =
						ExtWavUnp3((UIntPtr) read_buffer,
						(UIntPtr) length_read, (UIntPtr) write_buffer,
						0x1000);
				}
				memcpy(mpqptr, write_buffer, length_read);
				mpqptr += length_read;
//				fwrite(write_buffer, 1, length_read, fp_new);
				read_buffer = read_buffer_start;
			}
			crc_file++;						// . calculate crc_file for next block
		}
	}

	else {								// IF FILE IS NOT PACKED
		size_pack = *(BlockTable + entry * 4 + 1);		// get size  of file
		if (flag & 0x30000) {
			length_read = 0x1000;		// if file is coded, length_read=0x1000 (4 KB)
		} else {
			length_read = 0x60000;		// if file is not coded, length_read=0x60000 (384KB)
		}
		if (size_pack < length_read) {
			length_read = size_pack;		// if size of file < length_read, length read = size of file
		}
		read_buffer = read_buffer_start;
		if (length_read) {
			divres = ldiv(size_pack, length_read);		// .
			num_block = divres.quot;		// .
		} else {						// .
			num_block = 0;				// .
			divres.rem = 0;				// .
		}
		fseek(fpMpq, offset_mpq + offset_body, SEEK_SET);
		for (j = 0; j < num_block; j++) {
			if (fread(read_buffer, 1, length_read, fpMpq) == 0)
				return 1;
			if (flag & 0x30000) {
				Decode((UInt32 *) read_buffer, massive_base, crc_file, length_read / 4);		// if file is coded, decode block
				crc_file++;				// and calculate crc_file for next block
			}
			memcpy(mpqptr, read_buffer, length_read);
			mpqptr += length_read;
//			fwrite(read_buffer, 1, length_read, fp_new);
		}
		if (divres.rem) {
			if (fread(read_buffer, 1, divres.rem, fpMpq) == 0)
				return 1;
			if (flag & 0x30000)
				Decode((UInt32 *) read_buffer, massive_base, crc_file,
					divres.rem / 4);
			memcpy(mpqptr, read_buffer, divres.rem);
			mpqptr += divres.rem;
//			fwrite(read_buffer, 1, divres.rem, fp_new);
		}
	}
	return 0;
}

/**
**
*/
UInt32 CMpq::explode(void *param)
{
	UIntPtr result;
	UInt16 read_result;
	const UInt8 *table = dcl_table;
	UInt8 *work_buff;

	work_buff = (UInt8 *) explode_buffer;

	*((void **)(work_buff + 0x12)) = param;
	*((UInt16 *) (work_buff + 0x0E)) = 0x0800;
	read_result = read_data(work_buff + 0x2222, 0x0800, param);
	if (read_result == DCL_ERROR_4) {
		result = DCL_ERROR_3;
	} else {
		UInt16 flag_0 = *(work_buff + 0x2222), flag_1 =
			*(work_buff + 0x2223), flag_2 = *(work_buff + 0x2224);

		*((UInt16 *) (work_buff + 0x02)) = flag_0;
		*((UInt16 *) (work_buff + 0x06)) = flag_1;
		*((UInt16 *) (work_buff + 0x0A)) = flag_2;
		*((UInt16 *) (work_buff + 0x0C)) = 0x00;
		*((UInt16 *) (work_buff + 0x0E)) = 0x03;
		*((UInt16 *) (work_buff + 0x10)) = read_result;
		if ((flag_1 < 0x04) || (flag_1 > 0x06)) {
			result = DCL_ERROR_1;
		} else {
			*((UInt16 *) (work_buff + 0x08)) =
				(UInt16) (0x0000FFFFL >> (0x0010 - flag_1));
			if (flag_0 > 0x01) {
				result = DCL_ERROR_2;
			} else {
				if (flag_0) {
					__explode_7(work_buff + 0x2FA2, table + 0x00D0, 0x0100);
					__explode_6(work_buff, table + 0x01D0);
				}
				__explode_7(work_buff + 0x30E2, table + 0x00B0, 0x0010);
				__explode_5(0x0010, work_buff + 0x30E2, table + 0x00C0,
					work_buff + 0x2B22);
				__explode_7(work_buff + 0x30F2, table + 0x0080, 0x0010);
				__explode_7(work_buff + 0x3102, table + 0x0090, 0x0020);
				__explode_7(work_buff + 0x30A2, table, 0x0040);
				__explode_5(0x0040, work_buff + 0x30A2, table + 0x0040,
					work_buff + 0x2A22);
				if (__explode_1(work_buff, &length_write) != 0x0306) {
					result = DCL_NO_ERROR;
				} else {
					result = DCL_ERROR_4;
				}
			}
		}
	}
//  free(work_buff);
	return result;
}

/**
**
*/
static UInt16 __explode_1(UInt8 * buf, UIntPtr *length_write)
{
	UIntPtr result, temp;
	UInt8 *s, *d;
	void *param;

	*((UInt16 *) (buf + 0x04)) = 0x1000;
	while (result = __explode_2(buf), (UInt16) result < 0x0305) {
		if ((UInt16) result < 0x0100) {
			temp = *((UInt16 *) (buf + 0x04));
			*((UInt16 *) (buf + 0x04)) = (UInt16) (temp + 0x01);
			*(buf + temp + 0x1E) = (UInt8) result;
		} else {
			result -= 0x00FE;
			s = (UInt8 *) (UIntPtr)__explode_3(buf, (UInt16) result);
			if (!s) {
				result = 0x0306;
				break;
			} else {
				temp = *((UInt16 *) (buf + 0x04));
				d = temp + 0x1E + buf;
				*((UInt16 *) (buf + 0x04)) = (UInt16) (temp + result);
				s = (UInt8 *) ((UIntPtr) d - (UIntPtr) s);
				do {
					result--;
					*(d++) = *(s++);
				} while (result);
			}
		}
		if (*((UInt16 *) (buf + 4)) >= 0x2000) {
			result = 0x1000;
			param = (void *)*((UIntPtr *) (buf + 0x12));
			write_data(buf + 0x101E, 0x1000, param, length_write);
			__explode_7(buf + 0x001E, buf + 0x101E,
				*((UInt16 *) (buf + 0x04)) - 0x1000);
			*((UInt16 *) (buf + 0x04)) -= 0x1000;
		}
	}
	param = (void *)*((UIntPtr *) (buf + 0x12));
	write_data(buf + 0x101E,
		(UInt16) (*((UInt16 *) (buf + 0x04)) - 0x1000), param, length_write);
	return (UInt16) result;
}

/**
**
*/
static UInt16 __explode_2(UInt8 * buf)
{
	UIntPtr result, flag, flag_1;

	if (*((UInt16 *) (buf + 0x0A)) & 0x01) {
		if (__explode_4(buf, 0x01)) {
			return 0x0306;
		}
		result = *(buf + ((UInt8) * ((UInt16 *) (buf + 0x0A))) + 0x2B22);
		if (__explode_4(buf, *(buf + ((UInt16) result) + 0x30E2))) {
			return 0x0306;
		}
		flag = *(buf + ((UInt16) result) + 0x30F2);
		if (flag) {
			flag_1 = (*((UInt16 *) (buf + 0x0A))) & ((0x01 << flag) - 0x01);
			if (__explode_4(buf, flag)) {
				if ((((UInt16) result) + ((UInt16) flag_1)) != 0x010E) {
					return 0x0306;
				}
			}
			result =
				*((UInt16 *) (buf + (((UInt16) result) << 0x01) +
					0x3102)) + flag_1;
		}
		result += 0x0100;
	} else {
		if (__explode_4(buf, 0x01)) {
			return 0x0306;
		}
		if (!*((UInt16 *) (buf + 0x02))) {
			result = (UInt8) * ((UInt16 *) (buf + 0x0A));
			if (__explode_4(buf, 0x08)) {
				return 0x0306;
			}
		} else {
			flag = *((UInt16 *) (buf + 0x0A));
			if ((UInt8) flag) {
				result = *(buf + ((UInt8) flag) + 0x2C22);
				if (((UInt16) result) == 0x00FF) {
					if (flag & 0x003F) {
						if (__explode_4(buf, 0x04)) {
							return 0x0306;
						}
						result =
							*(buf + ((UInt8) * ((UInt16 *) (buf + 0x0A))) +
							0x2D22);
					} else {
						if (__explode_4(buf, 0x06)) {
							return 0x0306;
						}
						result =
							*(buf + ((*((UInt16 *) (buf + 0x0A))) & 0x007F) +
							0x2E22);
					}
				}
			} else {
				if (__explode_4(buf, 0x08)) {
					return 0x0306;
				}
				result =
					*(buf + ((UInt8) * ((UInt16 *) (buf + 0x0A))) +
					0x2EA2);
			}
			flag = *(buf + ((UInt16) result) + 0x2FA2);
			if (__explode_4(buf, flag)) {
				return 0x0306;
			}
		}
	}
	return (UInt16) result;
}

/**
**
*/
static UInt16 __explode_3(UInt8 * buf, UInt16 flag)
{
	UIntPtr result, flag_1;

	result = *(buf + ((UInt8) * ((UInt16 *) (buf + 0x0A))) + 0x2A22);
	if (__explode_4(buf, *(buf + ((UInt16) result) + 0x30A2))) {
		return 0x00;
	}
	if (((UInt16) flag) == 0x02) {
		result <<= 0x02;
		result |= *((UInt16 *) (buf + 0x0A)) & 0x03;
		if (__explode_4(buf, 0x02)) {
			return 0x00;
		}
	} else {
		flag_1 = *((UInt16 *) (buf + 0x06));
		result <<= flag_1;
		result |= *((UInt16 *) (buf + 0x08)) & *((UInt16 *) (buf + 0x0A));
		if (__explode_4(buf, flag_1)) {
			return 0x00;
		}
	}
	return (UInt16) (result + 0x01);
}

/**
**
*/
static UInt16 __explode_4(UInt8 * buf, UInt32 flag)
{
	UIntPtr result;
	UInt16 read_result;
	void *param = (void *)*((UIntPtr *) (buf + 0x12));

	result = *((UInt16 *) (buf + 0x0C));
	if ((UInt16) flag <= result) {
		*((UInt16 *) (buf + 0x0A)) >>= flag;
		*((UInt16 *) (buf + 0x0C)) -= (UInt16) flag;
		result = 0x00;
	} else {
		*((UInt16 *) (buf + 0x0A)) >>= result;
		result = *((UInt16 *) (buf + 0x0E));
		if (result == *((UInt16 *) (buf + 0x10))) {
			*((UInt16 *) (buf + 0x0E)) = 0x0800;
			read_result = read_data(buf + 0x2222, 0x0800, param);
			*((UInt16 *) (buf + 0x10)) = read_result;
			if (!read_result) {
				return 0x01;
			}
			*((UInt16 *) (buf + 0x0E)) = 0x00;
		}
		result = *((UInt16 *) (buf + 0x0E)) + 0x2222;
		*((UInt16 *) (buf + 0x0A)) |= *(buf + result) << 0x08;
		*((UInt16 *) (buf + 0x0E)) += 0x01;
		*((UInt16 *) (buf + 0x0A)) >>= flag - *((UInt16 *) (buf + 0x0C));
		*((UInt16 *) (buf + 0x0C)) =
			(UInt16) (0x08 - (flag - *((UInt16 *) (buf + 0x0C))));
		result = 0x00;
	}
	return (UInt16) result;
}

/**
**
*/
static void __explode_5(UInt16 count, UInt8 * buf_1, const UInt8 * table,
	UInt8 * buf_2)
{
	SInt16 i = (SInt16) (count - 1);
	UIntPtr idx_1, idx_2;

	for (; i >= 0; i--) {
		idx_1 = *(table + i);
		idx_2 = 0x01 << *(buf_1 + i);
		for (;;) {
			*(buf_2 + (UInt16) idx_1) = (UInt8) i;
			idx_1 += idx_2;
			if ((UInt16) idx_1 >= 0x0100) {
				break;
			}
		}
	}
}

/**
**
*/
static void __explode_6(UInt8 * buf, const UInt8 * table)
{
	SInt16 i;
	UIntPtr idx_1, idx_2;

	for (i = 0x00FF; i >= 0; i--) {
		idx_1 = *(buf + i + 0x2FA2);
		if (idx_1 <= 0x08) {
			idx_2 = *((UInt16 *) (table + (i << 0x01)));
			idx_1 = 0x01 << idx_1;
			do {
				*(buf + idx_2 + 0x2C22) = (UInt8) i;
				idx_2 += idx_1;
			} while ((UInt16) idx_2 < 0x0100);
		} else {
			idx_2 = *((UInt16 *) (table + (i << 0x01)));
			if ((UInt8) idx_2) {

				*(buf + (UInt8) idx_2 + 0x2C22) = 0xFF;
				if (*((UInt16 *) (table + (i << 0x01))) & 0x003F) {
					*(buf + i + 0x2FA2) -= 0x04;
					idx_1 = 0x01 << *(buf + i + 0x2FA2);
					idx_2 = *((UInt16 *) (table + (i << 0x01))) >> 0x04;
					do {
						*(buf + idx_2 + 0x2D22) = (UInt8) i;
						idx_2 += idx_1;
					} while ((UInt16) idx_2 < 0x0100);
				} else {
					*(buf + i + 0x2FA2) -= 0x06;
					idx_1 = 0x01 << *(buf + i + 0x2FA2);
					idx_2 = *((UInt16 *) (table + (i << 0x01))) >> 0x06;
					do {
						*(buf + idx_2 + 0x2E22) = (UInt8) i;
						idx_2 += idx_1;
					} while ((UInt16) idx_2 < 0x0080);
				}
			} else {
				*(buf + i + 0x2FA2) -= 0x08;
				idx_1 = 0x01 << *(buf + i + 0x2FA2);
				idx_2 = *((UInt16 *) (table + (i << 0x01))) >> 0x08;
				do {
					*(buf + idx_2 + 0x2EA2) = (UInt8) i;
					idx_2 += idx_1;
				} while ((UInt16) idx_2 < 0x0100);
			}
		}
	}
}

/**
**
*/
static void __explode_7(UInt8 *buf, const UInt8 *table, UInt32 count)
{
	UIntPtr half_count;
	UInt8 *buf_end;

	half_count = count >> 0x02;
	if (half_count) {
		buf_end = buf + (half_count << 0x02);
		do {
			*((UInt32 *) buf) = *((UInt32 *) table);
			buf += 4;
			table += 4;
		} while (buf < buf_end);
	}
	switch (count - (half_count << 0x02)) {
		case 3:
			*(buf++) = *(table++);

		case 2:
			*(buf++) = *(table++);

		case 1:
			*buf = *table;

		default:
			break;
	}
}

/**
**
*/
UIntPtr ExtWavUnp3(UIntPtr buf_in, UIntPtr size_in, UIntPtr buf_out, UIntPtr size_out)
{
	return Sub_WavUnp13(buf_in, size_in, 2, buf_out, size_out);
}

/**
**
*/
UIntPtr ExtWavUnp2(UIntPtr buf_in, UIntPtr size_in, UIntPtr buf_out, UIntPtr size_out)
{
	return Sub_WavUnp13(buf_in, size_in, 1, buf_out, size_out);
}

/**
**
*/
UIntPtr Sub_WavUnp13(UIntPtr buf_in, UIntPtr size_in, UIntPtr flag, UIntPtr buf_out, UIntPtr size_out)
{
	UIntPtr var14,var18,var1c;
	UIntPtr tmp0,tmp1,tmp2,tmp3;
	UInt32 tmp4;
	UInt32 var8[2];
	UInt32 var10[2];

	var14=buf_in;
	size_in+=buf_in;
	tmp0=var14+2;
	var1c=size_out;
	tmp3=buf_out;
	var18=buf_out;
	var10[0]=0x2C;
	var10[1]=0x2C;
	if((SInt32)flag>0) {
		for(tmp2=0;tmp2<flag;tmp2++) {
			var8[tmp2]=(SInt32)*((SInt16 *)tmp0);
			tmp0+=2;
			if(size_out<2) {
				return tmp3-var18;
			}
			*((UInt16 *)tmp3)=(UInt16) var8[tmp2];
			tmp3+=2;
			var1c-=2;
		}
	}
	tmp2=flag-1;
	while(tmp0<size_in) {
		if(flag==2) {
			if(tmp2==0) {
				tmp2=1;
			} else {
				tmp2=0;
			}
		}
		tmp1=(UIntPtr)*((UInt8 *)tmp0);
		tmp0++;
		buf_in=tmp0;
		if(tmp1&0x80) {
			tmp1&=0x7F;
			tmp4=1;
			if(tmp1==0) {
				if(var10[tmp2]) {
					var10[tmp2]--;
				}
				if(var1c<2) {
					return tmp3-var18;
				}
				*((UInt16 *)tmp3)=(UInt16)var8[tmp2];
				tmp3+=2;
				var1c-=2;
				if((tmp4==0)&&(flag==2)) {
					if(tmp2==0) {
						tmp2=1;
					} else {
						tmp2=0;
					}
				}
			} else {
				tmp1--;
				if(tmp1==0)		{
					var10[tmp2]+=8;
					tmp4=var10[tmp2];
					if(tmp4>0x58) {
						var10[tmp2]=0x58;
					}
					tmp4=0;
					if(tmp4==0 && flag==2) {
						if(tmp2==0) {
							tmp2=1;
						} else {
							tmp2=0;
						}
					}
				} else {
					tmp1--;
					if(tmp1==0)		{
						var10[tmp2]+=0xFFFFFFF8;
						if((SInt32)var10[tmp2]<0) {
							var10[tmp2]=0;
						}
						tmp4=0;
					}
					if((tmp4==0)&&(flag==2)) {
						if(tmp2==0) {
							tmp2=1;
						} else {
							tmp2=0;
						}
					}
				}
			}
		} else {
			tmp0=small_tbl1[var10[tmp2]];
			tmp4=tmp0>>(*((UInt8 *)(var14+1)));
			if(tmp1&1) {
				tmp4+=tmp0;
			}
			if(tmp1&2) {
				tmp4+=tmp0>>1;
			}
			if(tmp1&4) {
				tmp4+=tmp0>>2;
			}
			if(tmp1&8) {
				tmp4+=tmp0>>3;
			}
			if(tmp1&0x10) {
				tmp4+=tmp0>>4;
			}
			if(tmp1&0x20) {
				tmp4+=tmp0>>5;
			}
			tmp0=var8[tmp2];
			if((tmp1&0xFF)&0x40) {
				tmp0-=tmp4;
				if((SInt32)tmp0<=(SInt32)0xFFFF8000) {
					tmp0=0xFFFF8000;
				}
			} else {
				tmp0+=tmp4;
				if((SInt32)tmp0>=0x7FFF) {
					tmp0=0x7FFF;
				}
			}
			var8[tmp2]=tmp0;
			tmp0=var1c;
			if(tmp0<2) {
				return tmp3-var18;
			}
			*((UInt16 *)tmp3)=(UInt16)var8[tmp2];
			tmp1&=0x1F;
			tmp3+=2;
			var1c-=2;
			tmp4=var10[tmp2]+small_tbl2[tmp1];
			var10[tmp2]=tmp4;
			if((SInt32)tmp4<0) {
				var10[tmp2]=0;
			} else {
				if(tmp4>0x58) {
					var10[tmp2]=0x58;
				}
			}
			tmp0=buf_in;
		}
	}
	return tmp3-var18;
}

/**
**
*/
UIntPtr ExtWavUnp1(UIntPtr buf_in, UIntPtr size_in,
		UIntPtr buf_out, UIntPtr size_out)
{
	THuffmannTree *tree;
	TInputStream *is;

	tree = new THuffmannTree;
	tree->InitTree(false);

	is = new TInputStream;
	is->pbInBuffer = (unsigned char *) buf_in;
	is->pbInBufferEnd = (unsigned char *) (buf_in + size_in);
	is->BitBuffer = 0;
	is->BitCount = 0;

	size_out = tree->DoDecompression((unsigned char *) buf_out, size_out, is);

	delete is;
	delete tree;

	return size_out;
}

const unsigned char dcl_table[] =
{
	0x02, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x03, 0x0D, 0x05, 0x19, 0x09, 0x11, 0x01, 0x3E,
	0x1E, 0x2E, 0x0E, 0x36, 0x16, 0x26, 0x06, 0x3A,
	0x1A, 0x2A, 0x0A, 0x32, 0x12, 0x22, 0x42, 0x02,
	0x7C, 0x3C, 0x5C, 0x1C, 0x6C, 0x2C, 0x4C, 0x0C,
	0x74, 0x34, 0x54, 0x14, 0x64, 0x24, 0x44, 0x04,
	0x78, 0x38, 0x58, 0x18, 0x68, 0x28, 0x48, 0x08,
	0xF0, 0x70, 0xB0, 0x30, 0xD0, 0x50, 0x90, 0x10,
	0xE0, 0x60, 0xA0, 0x20, 0xC0, 0x40, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
	0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00,
	0x04, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00,
	0x08, 0x00, 0x0A, 0x00, 0x0E, 0x00, 0x16, 0x00,
	0x26, 0x00, 0x46, 0x00, 0x86, 0x00, 0x06, 0x01,
	0x03, 0x02, 0x03, 0x03, 0x04, 0x04, 0x04, 0x05,
	0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x07, 0x07,
	0x05, 0x03, 0x01, 0x06, 0x0A, 0x02, 0x0C, 0x14,
	0x04, 0x18, 0x08, 0x30, 0x10, 0x20, 0x40, 0x00,
	0x0B, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x08, 0x07, 0x0C, 0x0C, 0x07, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x04, 0x0A, 0x08, 0x0C, 0x0A, 0x0C, 0x0A, 0x08,
	0x07, 0x07, 0x08, 0x09, 0x07, 0x06, 0x07, 0x08,
	0x07, 0x06, 0x07, 0x07, 0x07, 0x07, 0x08, 0x07,
	0x07, 0x08, 0x08, 0x0C, 0x0B, 0x07, 0x09, 0x0B,
	0x0C, 0x06, 0x07, 0x06, 0x06, 0x05, 0x07, 0x08,
	0x08, 0x06, 0x0B, 0x09, 0x06, 0x07, 0x06, 0x06,
	0x07, 0x0B, 0x06, 0x06, 0x06, 0x07, 0x09, 0x08,
	0x09, 0x09, 0x0B, 0x08, 0x0B, 0x09, 0x0C, 0x08,
	0x0C, 0x05, 0x06, 0x06, 0x06, 0x05, 0x06, 0x06,
	0x06, 0x05, 0x0B, 0x07, 0x05, 0x06, 0x05, 0x05,
	0x06, 0x0A, 0x05, 0x05, 0x05, 0x05, 0x08, 0x07,
	0x08, 0x08, 0x0A, 0x0B, 0x0B, 0x0C, 0x0C, 0x0C,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0D, 0x0C, 0x0D, 0x0D, 0x0D, 0x0C, 0x0D, 0x0D,
	0x0D, 0x0C, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0D,
	0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0D, 0x0D, 0x0D,
	0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D,
	0x90, 0x04, 0xE0, 0x0F, 0xE0, 0x07, 0xE0, 0x0B,
	0xE0, 0x03, 0xE0, 0x0D, 0xE0, 0x05, 0xE0, 0x09,
	0xE0, 0x01, 0xB8, 0x00, 0x62, 0x00, 0xE0, 0x0E,
	0xE0, 0x06, 0x22, 0x00, 0xE0, 0x0A, 0xE0, 0x02,
	0xE0, 0x0C, 0xE0, 0x04, 0xE0, 0x08, 0xE0, 0x00,
	0x60, 0x0F, 0x60, 0x07, 0x60, 0x0B, 0x60, 0x03,
	0x60, 0x0D, 0x60, 0x05, 0x40, 0x12, 0x60, 0x09,
	0x60, 0x01, 0x60, 0x0E, 0x60, 0x06, 0x60, 0x0A,
	0x0F, 0x00, 0x50, 0x02, 0x38, 0x00, 0x60, 0x02,
	0x50, 0x00, 0x60, 0x0C, 0x90, 0x03, 0xD8, 0x00,
	0x42, 0x00, 0x02, 0x00, 0x58, 0x00, 0xB0, 0x01,
	0x7C, 0x00, 0x29, 0x00, 0x3C, 0x00, 0x98, 0x00,
	0x5C, 0x00, 0x09, 0x00, 0x1C, 0x00, 0x6C, 0x00,
	0x2C, 0x00, 0x4C, 0x00, 0x18, 0x00, 0x0C, 0x00,
	0x74, 0x00, 0xE8, 0x00, 0x68, 0x00, 0x60, 0x04,
	0x90, 0x00, 0x34, 0x00, 0xB0, 0x00, 0x10, 0x07,
	0x60, 0x08, 0x31, 0x00, 0x54, 0x00, 0x11, 0x00,
	0x21, 0x00, 0x17, 0x00, 0x14, 0x00, 0xA8, 0x00,
	0x28, 0x00, 0x01, 0x00, 0x10, 0x03, 0x30, 0x01,
	0x3E, 0x00, 0x64, 0x00, 0x1E, 0x00, 0x2E, 0x00,
	0x24, 0x00, 0x10, 0x05, 0x0E, 0x00, 0x36, 0x00,
	0x16, 0x00, 0x44, 0x00, 0x30, 0x00, 0xC8, 0x00,
	0xD0, 0x01, 0xD0, 0x00, 0x10, 0x01, 0x48, 0x00,
	0x10, 0x06, 0x50, 0x01, 0x60, 0x00, 0x88, 0x00,
	0xA0, 0x0F, 0x07, 0x00, 0x26, 0x00, 0x06, 0x00,
	0x3A, 0x00, 0x1B, 0x00, 0x1A, 0x00, 0x2A, 0x00,
	0x0A, 0x00, 0x0B, 0x00, 0x10, 0x02, 0x04, 0x00,
	0x13, 0x00, 0x32, 0x00, 0x03, 0x00, 0x1D, 0x00,
	0x12, 0x00, 0x90, 0x01, 0x0D, 0x00, 0x15, 0x00,
	0x05, 0x00, 0x19, 0x00, 0x08, 0x00, 0x78, 0x00,
	0xF0, 0x00, 0x70, 0x00, 0x90, 0x02, 0x10, 0x04,
	0x10, 0x00, 0xA0, 0x07, 0xA0, 0x0B, 0xA0, 0x03,
	0x40, 0x02, 0x40, 0x1C, 0x40, 0x0C, 0x40, 0x14,
	0x40, 0x04, 0x40, 0x18, 0x40, 0x08, 0x40, 0x10,
	0x40, 0x00, 0x80, 0x1F, 0x80, 0x0F, 0x80, 0x17,
	0x80, 0x07, 0x80, 0x1B, 0x80, 0x0B, 0x80, 0x13,
	0x80, 0x03, 0x80, 0x1D, 0x80, 0x0D, 0x80, 0x15,
	0x80, 0x05, 0x80, 0x19, 0x80, 0x09, 0x80, 0x11,
	0x80, 0x01, 0x80, 0x1E, 0x80, 0x0E, 0x80, 0x16,
	0x80, 0x06, 0x80, 0x1A, 0x80, 0x0A, 0x80, 0x12,
	0x80, 0x02, 0x80, 0x1C, 0x80, 0x0C, 0x80, 0x14,
	0x80, 0x04, 0x80, 0x18, 0x80, 0x08, 0x80, 0x10,
	0x80, 0x00, 0x00, 0x1F, 0x00, 0x0F, 0x00, 0x17,
	0x00, 0x07, 0x00, 0x1B, 0x00, 0x0B, 0x00, 0x13,
	0xA0, 0x0D, 0xA0, 0x05, 0xA0, 0x09, 0xA0, 0x01,
	0xA0, 0x0E, 0xA0, 0x06, 0xA0, 0x0A, 0xA0, 0x02,
	0xA0, 0x0C, 0xA0, 0x04, 0xA0, 0x08, 0xA0, 0x00,
	0x20, 0x0F, 0x20, 0x07, 0x20, 0x0B, 0x20, 0x03,
	0x20, 0x0D, 0x20, 0x05, 0x20, 0x09, 0x20, 0x01,
	0x20, 0x0E, 0x20, 0x06, 0x20, 0x0A, 0x20, 0x02,
	0x20, 0x0C, 0x20, 0x04, 0x20, 0x08, 0x20, 0x00,
	0xC0, 0x0F, 0xC0, 0x07, 0xC0, 0x0B, 0xC0, 0x03,
	0xC0, 0x0D, 0xC0, 0x05, 0xC0, 0x09, 0xC0, 0x01,
	0xC0, 0x0E, 0xC0, 0x06, 0xC0, 0x0A, 0xC0, 0x02,
	0xC0, 0x0C, 0xC0, 0x04, 0xC0, 0x08, 0xC0, 0x00,
	0x40, 0x0F, 0x40, 0x07, 0x40, 0x0B, 0x40, 0x03,
	0x00, 0x03, 0x40, 0x0D, 0x00, 0x1D, 0x00, 0x0D,
	0x00, 0x15, 0x40, 0x05, 0x00, 0x05, 0x00, 0x19,
	0x00, 0x09, 0x40, 0x09, 0x00, 0x11, 0x00, 0x01,
	0x00, 0x1E, 0x00, 0x0E, 0x40, 0x01, 0x00, 0x16,
	0x00, 0x06, 0x00, 0x1A, 0x40, 0x0E, 0x40, 0x06,
	0x40, 0x0A, 0x00, 0x0A, 0x00, 0x12, 0x00, 0x02,
	0x00, 0x1C, 0x00, 0x0C, 0x00, 0x14, 0x00, 0x04,
	0x00, 0x18, 0x00, 0x08, 0x00, 0x10, 0x00, 0x00
};

const UInt32 small_tbl1[90] =
{
	0x7,		0x8,		0x9,		0xA,		0xB,		0xC,		0xD,		0xE,		0x10,		0x11,
	0x13,		0x15,		0x17,		0x19,		0x1C,		0x1F,		0x22,		0x25,		0x29,		0x2D,
	0x32,		0x37,		0x3C,		0x42,		0x49,		0x50,		0x58,		0x61,		0x6B,		0x76,
	0x82,		0x8F,		0x9D,		0xAD,		0xBE,		0xD1,		0xE6,		0xFD,		0x117,		0x133,
	0x151,		0x173,		0x198,		0x1C1,		0x1EE,		0x220,		0x256,		0x292,		0x2D4,		0x31C,
	0x36C,		0x3C3,		0x424,		0x48E,		0x502,		0x583,		0x610,		0x6AB,		0x756,		0x812,
	0x8E0,		0x9C3,		0xABD,		0xBD0,		0xCFF,		0xE4C,		0xFBA,		0x114C,		0x1307,		0x14EE,
	0x1706,		0x1954,		0x1BDC,		0x1EA5,		0x21B6,		0x2515,		0x28CA,		0x2CDF,		0x315B,		0x364B,
	0x3BB9,		0x41B2,		0x4844,		0x4F7E,		0x5771,		0x602F,		0x69CE,		0x7462,		0x7FFF,		0x0
};

const UInt32 small_tbl2[32] =
{
	0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x4, 0xFFFFFFFF, 0x2, 0xFFFFFFFF, 0x6,
	0xFFFFFFFF, 0x1, 0xFFFFFFFF, 0x5, 0xFFFFFFFF, 0x3, 0xFFFFFFFF, 0x7,
	0xFFFFFFFF, 0x1, 0xFFFFFFFF, 0x5, 0xFFFFFFFF, 0x3, 0xFFFFFFFF, 0x7,
	0xFFFFFFFF, 0x2, 0xFFFFFFFF, 0x4, 0xFFFFFFFF, 0x6, 0xFFFFFFFF, 0x8
};
