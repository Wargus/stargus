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



/*----------------------------------------------------------------------------
--		Declarations
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

/**
**  Check if path exists, if not make all directories.
*/
void CheckPath(const char* path)
{
	char* cp;
	char* s;

#ifdef WIN32
	cp = _strdup(path);
#else
	cp = strdup(path);
#endif
	s = strrchr(cp, '/');
	if (s) {
		*s = '\0';  // remove file
		s = cp;
		for (;;) {  // make each path element
			s = strchr(s, '/');
			if (s) {
				*s = '\0';
			}
#if defined(_MSC_VER) || defined(WIN32)
			_mkdir(cp);
#else
			mkdir(cp, 0777);
#endif
			if (s) {
				*s++ = '/';
			} else {
				break;
			}
		}
	}
	free(cp);
}

/**
**  Extract a file from MPQ archive
**
**  @param szArchiveName Path to MPQ file to read from
**  @param szArchivedFile File identifier in the MPQ file
**  @param szFileName Place to save the file on the drive (absolute)
*/
int ExtractMPQFile(const char *szArchiveName, const char *szArchivedFile, const char *szFileName, bool compress)
{
	HANDLE hMpq   = NULL;          // Open archive handle
	HANDLE hFile  = NULL;          // Archived file handle
	FILE   *file  = NULL;          // Disk file handle
	gzFile gzfile = NULL;          // Compressed file handle
	int    nError = ERROR_SUCCESS; // Result value

	// Open an archive, e.g. "d2music.mpq"
	if(nError == ERROR_SUCCESS) {
		if(!SFileOpenArchive(szArchiveName, 0, STREAM_FLAG_READ_ONLY, &hMpq))
			nError = GetLastError();
	}

	// Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
	if(nError == ERROR_SUCCESS) {
		if(!SFileOpenFileEx(hMpq, szArchivedFile, 0, &hFile))
			nError = GetLastError();
	}

	// Create the target file
	if(nError == ERROR_SUCCESS) {
		CheckPath(szFileName);
		if (compress) {
			gzfile = gzopen(szFileName, "wb9");
		} else {
			file = fopen(szFileName, "wb");
		}
	}

	// Read the file from the archive
	if(nError == ERROR_SUCCESS) {
		char  szBuffer[0x10000];
		DWORD dwBytes = 1;

		while(dwBytes > 0) {
			SFileReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL);
			if(dwBytes > 0) {
				if (compress) {
					gzwrite(gzfile, szBuffer, dwBytes);
				} else {
					fwrite(szBuffer, 1, dwBytes, file);
				}
			}
		}
	}

	// Cleanup and exit
	if(file != NULL) {
		fclose(file);
	}
	if(gzfile != NULL) {
		gzclose(gzfile);
	}
	if(hFile != NULL)
		SFileCloseFile(hFile);
	if(hMpq != NULL)
		SFileCloseArchive(hMpq);

	return nError;
}

/**
**  Extract a file from MPQ archive
**
**  @param szArchiveName Path to MPQ file to read from
**  @param szArchivedFile File identifier in the MPQ file
**  @param szEntryBuffer Buffer to hold the uncompressed entry
**  @param bufferLen Buffer to hold the uncompressed entry
**
**  @return error code
*/
int ExtractMPQEntry(const char *szArchiveName, const char *szArchivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen)
{
	HANDLE hMpq   = NULL;          // Open archive handle
	HANDLE hFile  = NULL;          // Archived file handle
	int    nError = ERROR_SUCCESS; // Result value
	unsigned char *szEntryBuffer = NULL;

	if(nError == ERROR_SUCCESS) {
		if(!SFileOpenArchive(szArchiveName, 0, STREAM_FLAG_READ_ONLY, &hMpq))
			nError = GetLastError();
	}

	// Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
	if(nError == ERROR_SUCCESS) {
		if(!SFileOpenFileEx(hMpq, szArchivedFile, 0, &hFile))
			nError = GetLastError();
	}

	int i = 0;
	size_t len = 0;
	// Read the file from the archive
	if(nError == ERROR_SUCCESS) {
		char szBuffer[0x10000];
		szEntryBuffer = (unsigned char*) malloc(sizeof(szBuffer));
		DWORD dwBytes = 1;

		while(dwBytes > 0) {
			SFileReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL);
			if(dwBytes > 0) {
				len = len + dwBytes; // TODO old was: sizeof(szBuffer) * (i+1);
				//printf("pcx buffer len: %d\n", len);
				szEntryBuffer = (unsigned char*) realloc(szEntryBuffer, len);
				void *targetBuffer = (unsigned char*) memcpy(szEntryBuffer + (i*sizeof(szBuffer)), szBuffer, dwBytes);

			}
			i++;
		}
	}
	if(bufferLen != NULL)
	{
		*bufferLen = len;
	}

	if(hFile != NULL)
		SFileCloseFile(hFile);
	if(hMpq != NULL)
		SFileCloseArchive(hMpq);

	*szEntryBufferPrt = szEntryBuffer;
	return nError;
}



