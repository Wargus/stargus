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
#include <iostream>
#include <zlib.h>
#include <StormLib.h>

#include "Storm.h"
#include "FileUtil.h"

using namespace std;


Storm::Storm() :
	mMpqHandle(nullptr)
{

}

Storm::Storm(const std::string &archiveName)
: mMpqHandle(nullptr)
{
	openArchive(archiveName);
}

Storm::~Storm()
{
	closeArchive();
}

bool Storm::openArchive(const std::string &archiveName)
{
	bool result = true;

	// close it in case it's still open
	closeArchive();

	// Open an archive, e.g. "d2music.mpq"
	if(!SFileOpenArchive(archiveName.c_str(), 0, STREAM_FLAG_READ_ONLY, &mMpqHandle))
	{
		result = false;
	}
	else
	{
		mArchiveName = archiveName;
	}
	return result;
}

void Storm::closeArchive()
{
	if(mMpqHandle != nullptr)
	{
		SFileCloseArchive(mMpqHandle);
		mArchiveName.clear();
	}
}

std::shared_ptr<DataChunk> Storm::extractDataChunk(const std::string &archivedFile)
{
	size_t bufferLen = 0;
	unsigned char *szEntryBufferPrt;

	if(extractMemory(archivedFile, &szEntryBufferPrt, &bufferLen))
	{
		shared_ptr<DataChunk> data = make_shared<DataChunk>(&szEntryBufferPrt, bufferLen);
		return data;
	}
	return nullptr;
}

bool Storm::extractMemory(const std::string &archivedFile, unsigned char **szEntryBufferPrt, size_t *bufferLen)
{
	int nError = ERROR_SUCCESS;
	unsigned char *szEntryBuffer = NULL;
	HANDLE hFile  = nullptr;          // Archived file handle
	bool result = true;

	// Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
	if(nError == ERROR_SUCCESS) {
		if(!SFileOpenFileEx(mMpqHandle, archivedFile.c_str(), 0, &hFile))
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

	*szEntryBufferPrt = szEntryBuffer;

	if(nError != ERROR_SUCCESS)
		result = false;

	return result;
}

bool Storm::extractFile(const std::string &archivedFile,const std::string &extractedName, bool compress)
{
	HANDLE hFile  = nullptr;          // Archived file handle
	FILE   *file  = nullptr;          // Disk file handle
	gzFile gzfile = nullptr;          // Compressed file handle
	int nError = ERROR_SUCCESS;
	bool result = true;

	// Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
	if(nError == ERROR_SUCCESS) {
		if(!SFileOpenFileEx(mMpqHandle, archivedFile.c_str(), 0, &hFile))
			nError = GetLastError();
	}

	// Create the target file
	if(nError == ERROR_SUCCESS) {
		CheckPath(extractedName);
		if (compress) {
			gzfile = gzopen(extractedName.c_str(), "wb9");
		} else {
			file = fopen(extractedName.c_str(), "wb");
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

	if(nError != ERROR_SUCCESS)
		result = false;

	return result;
}

