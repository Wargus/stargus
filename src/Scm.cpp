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
/**@name Scm.cpp - The scm. */
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
//	$Id$

//@{

// Lcoal
#include "Scm.h"
#include "Chk.h"
#include "Hurricane.h"
#include "endian.h"
#include "FileUtil.h"
#include "Preferences.h"
#include "Storm.h"

// System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <string>
#include <libgen.h>

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

using namespace std;

Scm::Scm(std::shared_ptr<Hurricane> hurricane) :
	mHurricane (hurricane)
{

}

Scm::~Scm()
{

}

bool Scm::convert(const std::string &arcfile, const std::string &file)
{
	char buf[1024];
	bool result = true;

	Preferences &preferences = Preferences::getInstance ();
	sprintf(buf, "%s/%sscm", preferences.getDestDir().c_str(), file.c_str());

	result = mHurricane->extractFile(arcfile, buf);
	if (result)
	{
		// call the Chk converter with temp file...
		shared_ptr<Storm> storm = make_shared<Storm>(buf);
		Chk chk(storm);
		result = chk.convert("staredit\\scenario.chk", file.c_str());

		// delete the temporary .chk file -> below don't access 'breeze' any more!
		//unlink(buf);
	}

	return result;
}

/**
**  Load scm
**
**  @param scm  Name of the scm file
**  @param map  The map
*/
/*void Scm::load(const char *mpqfile, const char *dir)
{
	unsigned char *chkdata = NULL;
	size_t chklen = 0;

	Storm mpq(mpqfile);
	bool result = mpq.extractMemory("staredit\\scenario.chk", &chkdata, &chklen);
	if (result)
	{
		chk.loadFromBuffer(chkdata, chklen);
	}

	free(chkdata);

}*/

#ifdef STAND_ALONE
void usage()
{
	fprintf(stderr, "%s\n%s\n",
		"scmconvert V" VERSION,
		"usage: scmconvert inputfile [ outputdir ]\n");
	exit(-1);
}

int main(int argc, char **argv)
{
	char *infile;
	char *outdir;

	if (argc < 2 || argc > 3) {
		usage();
	}

	infile = argv[1];
	if (argc == 3) {
		outdir = argv[2];
	} else {
		outdir = strdup(".");
	}

	if (strstr(infile, ".scm\0")) {
		char *tmp;
		char newname[1024];

		sprintf(newname, "%s/", outdir);
		if ((tmp = strrchr(infile, '/'))) {
			strcat(newname, tmp + 1);
		} else if ((tmp = strrchr(infile, '\\'))) {
			strcat(newname, tmp + 1);
		} else {
			strcat(newname, infile);
		}

		// TODO: fix this standalone version
		convert(infile);

	} else if (strstr(infile, ".chk\0")) {
		FILE *f;
		struct stat sb;
		unsigned int len;
		unsigned char *buf;

		if (stat(infile, &sb) == -1) {
			fprintf(stderr, "error finding file: %s\n", infile);
			return -1;
		}
		len = sb.st_size;

		f = fopen(infile, "rb");
		if (f == NULL) {
			fprintf(stderr, "error opening file: %s\n", infile);
			return -1;
		}

		buf = (unsigned char *)malloc(len);
		if (fread(buf, 1, len, f) != len) {
			fprintf(stderr, "error reading from file: %s\n", infile);
			free(buf);
			return -1;
		}

		if (fclose(f)) {
			fprintf(stderr, "error closing file: %s\n", infile);
			free(buf);
			return -1;
		}

		char *tmp;
		char newname[1024];

		sprintf(newname, "%s/", outdir);
		if ((tmp = strrchr(infile, '/'))) {
			strcat(newname, tmp + 1);
		} else if ((tmp = strrchr(infile, '\\'))) {
			strcat(newname, tmp + 1);
		} else {
			strcat(newname, infile);
		}

		ConvertChk(newname, buf, len);

		free(buf);
	} else {
		fprintf(stderr, "Invalid input file: %s\n", infile);
		return -1;
	}

	return 0;
}
#endif

