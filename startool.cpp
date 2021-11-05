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
//      (c) Copyright 2002-2012 by Jimmy Salmon and Pali Rohár
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

//@{

/*----------------------------------------------------------------------------
--  Includes
----------------------------------------------------------------------------*/

#include "endian.h"
#include "startool.h"
#include "optionparser.h"
#include "Preferences.h"
#include "Scm.h"
#include "FileUtil.h"
#include "Pcx.h"
#include "Font.h"
#include "Grp.h"
#include "Png.h"
#include "Terrain.h"
#include "Panel.h"
#include "Palettes.h"

//stratagus
#include <stratagus-gameutils.h>

//----------------------------------------------------------------------------

/**
**  Palette N27, for credits cursor
*/
//static unsigned char* Pal27;

//#define MAKE_CCL 1

//----------------------------------------------------------------------------
//		Map
//----------------------------------------------------------------------------

/**
**  Convert map
**
**  @extracted in case of installation the map files are yet extracted from mpq file
*/
bool ConvertMap(const char *mpqfile, const char *arcfile, const char *file, bool extracted)
{
	FILE *fd;
	char buf[1024];
	char buf2[1024];
	bool result = true;

	Preferences &preferences = Preferences::getInstance ();
	sprintf(buf, "%s/%s", preferences.getDestDir().c_str(), file);

	if(!extracted)
	{
		Storm mpq(mpqfile);
		result = mpq.extractFile(arcfile, buf, false);
		if (result)
		{
			Scm scm;
			scm.convert(buf);
			unlink(buf); // delete temp mpq after conversation
		}
	}
	else // local installation filesystem case
	{
		//sprintf(buf2, "%s/%s", ArchiveDir.c_str(), file);
		//CheckPath(buf2);

		//ConvertScm(buf2, buf, mpq_listfile);
	}

	return result;
}

//----------------------------------------------------------------------------
//		Map
//----------------------------------------------------------------------------

/**
**  Convert map
**
**  @extracted in case of installation the map files are yet extracted from mpq file
*/
bool ConvertCampaign(const char *mpqfile, const char *arcfile, const char *file)
{
	FILE *fd;
	char buf[1024];
	char buf2[1024];
	bool result = true;
	unsigned char *chkdata;
	size_t chklen;

	Preferences &preferences = Preferences::getInstance ();
	sprintf(buf, "%s/%s", preferences.getDestDir().c_str(), file);

	// TODO: The .chk files could be deleted after conversation
	Storm mpq(mpqfile);
	result = mpq.extractMemory(arcfile, &chkdata, &chklen);
	if (result)
	{
		Chk chk;
		chk.ConvertChk(buf, chkdata, chklen);
	}

	return result;
}

//----------------------------------------------------------------------------
//  Palette
//----------------------------------------------------------------------------

/**
**  Convert palette.
**
**  @param pal  Pointer to palette
**
**  @return     Pointer to palette
*/
// TODO: not needed??
/*unsigned char* ConvertPalette(unsigned char* pal)
{
	int i;

	// PNG needs 0-256
	for (i = 0; i < 768; ++i) {
		pal[i] <<= 2;
	}

	return pal;
}*/



//----------------------------------------------------------------------------
//  Font
//----------------------------------------------------------------------------





//----------------------------------------------------------------------------
//		Wav
//----------------------------------------------------------------------------

/**
**  Convert wav to gzipped format
**
**  @param arcfile File identifier in the MPQ file
**  @param file Place to save the file on the drive (relative)
*/
bool ConvertWav(const char *mpqfile, const char *arcfile, const char *file)
{
	char buf[8192] = {'\0'};
	bool result = true;

	Preferences &preferences = Preferences::getInstance ();
	sprintf(buf, "%s/%s/%s.wav.gz", preferences.getDestDir().c_str(), SOUND_PATH, file);

	Storm mpq(mpqfile);
	result = mpq.extractFile(arcfile, buf, true);

	return result;
}

/**
**  Raw extraction
**
**  @param arcfile File identifier in the MPQ file
**  @param file Place to save the file on the drive (relative)
*/
bool RawExtract(const char *mpqfile, const char *arcfile, const char *file)
{
	char buf[8192] = {'\0'};
	bool result = true;
	Preferences &preferences = Preferences::getInstance ();
	sprintf(buf, "%s/%s", preferences.getDestDir().c_str(), file);

	Storm mpq(mpqfile);
	result = mpq.extractFile(arcfile, buf, false);

	return result;
}

/**
**  MPQ Sub-extraction
**
**  @param arcfile File identifier in the MPQ file
**  @param file Place to save the file on the drive (relative)
*/
bool MPQSubExtract(const char *mpqfile, const char *arcfile, const char *file)
{
	return RawExtract(mpqfile, arcfile, file);
}

//----------------------------------------------------------------------------
//  Video
//----------------------------------------------------------------------------

/**
**  Convert SMK video to OGV
*/
bool ConvertVideo(const char *mpqfile, const char *arcfile, const char *file)
{
	char buf[8192] = {'\0'};
	bool result = true;

	Preferences &preferences = Preferences::getInstance ();
	snprintf(buf,sizeof(buf),"%s/%s/%s.smk", preferences.getDestDir().c_str(), VIDEO_PATH, file);

	Storm mpq(mpqfile);
	result = mpq.extractFile(arcfile, buf, false);

	string ffmpeg_str = string("ffmpeg -y -i ") + buf + " -codec:v libtheora -qscale:v 31 -codec:a libvorbis -qscale:a 15 -pix_fmt yuv420p " + preferences.getDestDir() + "/" + VIDEO_PATH + "/" + file;

	//cout << "video: " << ffmpeg_str << endl;

	int sys_call = system(ffmpeg_str.c_str());
	if(sys_call != 0)
	{
		result = false;
	}

	remove(buf);

	return result;
}

void CreatePanels()
{
	Panel panel;
	panel.save(264, 288);
	panel.save(384, 256);
	panel.save(312, 312);
	panel.save(288, 128);
	panel.save(296, 336);
}

bool CheckCASCDataFolder(const std::string &dir)
{
	return FileExists(dir + "/.build.info");
}

//----------------------------------------------------------------------------
//  Main loop
//----------------------------------------------------------------------------

/** option parser **/
struct Arg: public option::Arg
{
  static void printError(const char* msg1, const option::Option& opt, const char* msg2)
  {
    fprintf(stderr, "%s", msg1);
    fwrite(opt.name, opt.namelen, 1, stderr);
    fprintf(stderr, "%s", msg2);
  }

  static option::ArgStatus Unknown(const option::Option& option, bool msg)
  {
    if (msg) printError("Unknown option '", option, "'\n");

    return option::ARG_ILLEGAL;
  }

  static option::ArgStatus Required(const option::Option& option, bool msg)
  {
    if (option.arg != 0)
      return option::ARG_OK;

    if (msg) printError("Option '", option, "' requires an argument\n");
    return option::ARG_ILLEGAL;
  }

  static option::ArgStatus NonEmpty(const option::Option& option, bool msg)
  {
    if (option.arg != 0 && option.arg[0] != 0)
      return option::ARG_OK;

    if (msg) printError("Option '", option, "' requires a non-empty argument\n");
    return option::ARG_ILLEGAL;
  }

  static option::ArgStatus Numeric(const option::Option& option, bool msg)
  {
    char* endptr = 0;
    if (option.arg != 0 && strtol(option.arg, &endptr, 10)){};
    if (endptr != option.arg && *endptr == 0)
      return option::ARG_OK;

    if (msg) printError("Option '", option, "' requires a numeric argument\n");
    return option::ARG_ILLEGAL;
  }
};

enum  optionIndex { UNKNOWN, HELP, VIDEO, VERSIONPARAM };
 const option::Descriptor usage[] =
 {
  {UNKNOWN, 0,"" , ""    ,option::Arg::None, "USAGE: stargus archive-directory [destination-directory]\n\n"
                                             "Options:" },
  {HELP,    0,"h" , "help",option::Arg::None, "  --help, -h  \t\tPrint usage and exit" },
  {VIDEO,	0,"v" , "video",Arg::None, "  --video, -v  \t\tExtract and convert videos" },
  {VERSIONPARAM, 	0,"V" , "version",Arg::None, "  --version, -V  \t\tShow version" },
  {UNKNOWN, 0,""  ,  ""   ,option::Arg::None, "\narchive-directory \t\tDirectory which include the archive install.exe or stardat.mpq...\n"
                                              "destination-directory \t\tDirectory where the extracted files are placed.\n""mpqlist-file \t\tmpqlist.txt file which contains mpq file names\n"},
  {0,0,0,0,0,0}
 };

int parseOptions(int argc, const char **argv)
{
  Preferences &preferences = Preferences::getInstance ();
  argc -= (argc > 0); argv += (argc > 0); // skip program name argv[0] if present
  option::Stats  stats(usage, argc, argv);
  option::Option options[stats.options_max], buffer[stats.buffer_max];
  option::Parser parse(usage, argc, argv, options, buffer);

  if(parse.error())
	  exit(0);

  if(options[HELP])
  {
    option::printUsage(std::cout, usage);
    exit(0);
  }

  // parse options
  if(options[VIDEO].count() > 0)
  {
	  preferences.setVideoExtraction(true);
  }

  if(options[VERSIONPARAM].count() > 0)
  {
	  printf(VERSION "\n");
	  exit(0);
  }

  for(option::Option* opt = options[UNKNOWN]; opt; opt = opt->next())
    std::cout << "Unknown option: " << opt->name << "\n";

  for(int i = 0; i < parse.nonOptionsCount(); ++i)
  {
	  switch(i) {
	  	  case 0:
	  		cout << "archive-directory #" << i << ": " << parse.nonOption(i) << "\n";
	  		preferences.setArchiveDir(parse.nonOption(i));
	  		break;
	  	  case 1:
	  		cout << "destination-directory #" << i << ": " << parse.nonOption(i) << "\n";
	  		preferences.setDestDir(parse.nonOption(i));
	  		break;
	  	  default:
	  		break;
	  }
  }

  if(preferences.getArchiveDir().empty()) {
	  cerr << "Error: 'archive-directory' not given!" << endl <<  endl;
	  option::printUsage(std::cout, usage);
	  exit(1);
  }

  return 0;
}

/**
**		Main
*/
int main(int argc, const char** argv)
{
	unsigned u;
	char buf[8192] = {'\0'};
	int i;
	FILE* f;

	Preferences &preferences = Preferences::getInstance ();
	preferences.init(); // initialize all properties once in the beginning of the application

	parseOptions(argc, argv);

	sprintf(buf, "%s/extracted", preferences.getDestDir().c_str());
	f = fopen(buf, "r");
	if (f) {
		char version[20];
		int len = 0;
		if (fgets(version, 20, f))
			len = 1;
		fclose(f);
		if (len != 0 && strcmp(version, VERSION) == 0) {
			printf("Note: Data is already extracted in Dir \"%s\" with this version of startool\n", preferences.getDestDir().c_str());
			fflush(stdout);
		}
	}

	printf("Extract from \"%s\" to \"%s\"\n", preferences.getArchiveDir().c_str(), preferences.getDestDir().c_str());
	printf("Please be patient, the data may take a couple of minutes to extract...\n\n");
	fflush(stdout);

	string mpqfile;
	string submpqfile;

	for (i = 0; i <= 1; ++i)
	{
		Control *c;
		unsigned len;
		bool extracted = false;

		//i = 0;
		switch (i)
		{
		case 0:
			// CD install.exe renamed to StarCraft.mpq or other main mpq file
			c = CDTodo;
			len = sizeof(CDTodo) / sizeof(*CDTodo);
			extracted = false;
			break;
		case 1:
			// StarDat.mpq or stardat.mpq from CD or hard drive
			c = Todo;
			len = sizeof(Todo) / sizeof(*Todo);
			extracted = true;
			break;
		}

		bool case_func = false;
		for (u = 0; u < len; ++u)
		{
			switch (c[u].Type)
			{
				case F:
					if(submpqfile.empty())
					{
						sprintf(buf, "%s/%s", preferences.getArchiveDir().c_str(), c[u].ArcFile);
					}
					else
					{
						sprintf(buf, "%s", submpqfile.c_str());
					}
					printf("FileExists: %s", buf);
					case_func = FileExists(buf);
					if(case_func) {
						mpqfile = buf;
					}
					printf("...%s\n", case_func ? "ok" : "nok");
					break;
				case Q:
					printf("MPQSubExtract: %s, %s", c[u].File, c[u].ArcFile);
					case_func = MPQSubExtract(mpqfile.c_str(), c[u].ArcFile, c[u].File);
					if(case_func) {
						sprintf(buf, "%s/%s", preferences.getDestDir().c_str(), c[u].File);
						submpqfile = buf;
					}
					printf("...%s\n", case_func ? "ok" : "nok");
					break;
				case M: // WORKS!
					printf("ConvertMap: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					case_func = ConvertMap(mpqfile.c_str(), c[u].ArcFile, c[u].File, extracted);
					printf("...%s\n", case_func ? "ok" : "nok");
					break;
				case R: // UNUSED?
				{
					printf("ConvertRgb: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					Terrain terrain;
					case_func = terrain.ConvertRgb(mpqfile.c_str(), c[u].ArcFile, c[u].File);
					printf("...%s\n", case_func ? "ok" : "nok");
				}
					break;
				case T:  // WORKS!
				{
					printf("ConvertTileset: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					Terrain terrain;
					case_func = terrain.ConvertTileset(mpqfile.c_str(), c[u].ArcFile, c[u].File);
					printf("...%s\n", case_func ? "ok" : "nok");
				}
					break;
				case G: // WORKS!
				{
					printf("ConvertGfx: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					Grp grpGfx;
					case_func = grpGfx.ConvertGfx(mpqfile.c_str(), c[u].ArcFile, c[u].File, c[u].Arg1);
					printf("...%s\n", case_func ? "ok" : "nok");
				}
					break;
				case U: // WORKS!
				{
					printf("ConvertGfu: %s, %s, %s",mpqfile.c_str(),  c[u].File, c[u].ArcFile);
					Grp grpGfu;
					case_func = grpGfu.ConvertGfu(mpqfile.c_str(), c[u].ArcFile, c[u].File, c[u].Arg1);
					printf("...%s\n", case_func ? "ok" : "nok");
				}
					break;
				case I: // WORKS!
				{
					printf("ConvertWidgets: %s, %s, %s",mpqfile.c_str(),  c[u].File, c[u].ArcFile);
					Grp grpWidgets;
					case_func = grpWidgets.ConvertWidgets(mpqfile.c_str(), c[u].ArcFile, c[u].File, c[u].Arg1);
					printf("...%s\n", case_func ? "ok" : "nok");
				}
					break;
				case N: // WORKS!
				{
					printf("ConvertFont: %s, %s, %s",mpqfile.c_str(), c[u].File, c[u].ArcFile);
					Font font;
					case_func = font.convert(mpqfile.c_str(), c[u].ArcFile, c[u].File, 2);
					printf("...%s\n", case_func ? "ok" : "nok");
				}
					break;
				case W: // WORKS!
					printf("ConvertWav: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					case_func = ConvertWav(mpqfile.c_str(), c[u].ArcFile, c[u].File);
					printf("...%s\n", case_func ? "ok" : "nok");
					break;
				case V: // WORKS!
					if(preferences.getVideoExtraction()) {
						printf("ConvertVideo: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
						case_func = ConvertVideo(mpqfile.c_str(), c[u].ArcFile, c[u].File);
						printf("...%s\n", case_func ? "ok" : "nok");
					}
					break;
				case H: // WORKS!
				{
					printf("ConvertPcx: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					Pcx pcx;
					case_func = pcx.convert(mpqfile.c_str(), c[u].ArcFile, c[u].File);
					printf("...%s\n", case_func ? "ok" : "nok");
				}
					break;
				case E: // WORKS
					printf("RawExtract: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					// TBD: I think campaigns this must be somehow converted to stratagus
					case_func = RawExtract(mpqfile.c_str(), c[u].ArcFile, c[u].File);
					printf("...%s\n", case_func ? "ok" : "nok");
					break;
				case L:
					printf("ConvertCampaign: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					case_func = ConvertCampaign(mpqfile.c_str(), c[u].ArcFile, c[u].File);
					printf("...%s\n", case_func ? "ok" : "nok");
					break;
				default:
					break;
			}
		}
	}

	// remove temporary sub files
	if (!submpqfile.empty())
	{
		unlink(submpqfile.c_str());
	}
	
	CreatePanels();

	sprintf(buf, "%s/extracted", preferences.getDestDir().c_str());
	f = fopen(buf, "w");
	fprintf(f, VERSION "\n");
	fclose(f);

	printf("New Done.\n");

	return 0;
}


