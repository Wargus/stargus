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

#include <Palette.h>
#include <Tbl.h>
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
#include "Panel.h"
#include "Widgets.h"
#include "Gfu.h"
#include "Tileset.h"
#include "DataChunk.h"
#include "Casc.h"
#include "Dds.h"
#include "Logger.h"
#include "Breeze.h"
#include "Video.h"
#include "DataHub.h"

// System
#include <memory>

// TODO: move to sub-class logic?
#include <libgrp/libgrp.hpp>

// activate local debug messages
#define DEBUG 1

using namespace std;

Logger logger("startool.main");

// test only
void testHook();

//----------------------------------------------------------------------------

/**
 **  Palette N27, for credits cursor
 */
//static unsigned char* Pal27;
//#define MAKE_CCL 1
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
  char buf[8192] =
  { '\0' };
  bool result = true;

  Preferences &preferences = Preferences::getInstance();
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
  char buf[8192] =
  { '\0' };
  bool result = true;
  Preferences &preferences = Preferences::getInstance();
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
  static void printError(const char *msg1, const option::Option &opt, const char *msg2)
  {
    fprintf(stderr, "%s", msg1);
    fwrite(opt.name, opt.namelen, 1, stderr);
    fprintf(stderr, "%s", msg2);
  }

  static option::ArgStatus Unknown(const option::Option &option, bool msg)
  {
    if (msg)
      printError("Unknown option '", option, "'\n");

    return option::ARG_ILLEGAL;
  }

  static option::ArgStatus Required(const option::Option &option, bool msg)
  {
    if (option.arg != 0)
      return option::ARG_OK;

    if (msg)
      printError("Option '", option, "' requires an argument\n");
    return option::ARG_ILLEGAL;
  }

  static option::ArgStatus NonEmpty(const option::Option &option, bool msg)
  {
    if (option.arg != 0 && option.arg[0] != 0)
      return option::ARG_OK;

    if (msg)
      printError("Option '", option, "' requires a non-empty argument\n");
    return option::ARG_ILLEGAL;
  }

  static option::ArgStatus Numeric(const option::Option &option, bool msg)
  {
    char *endptr = 0;
    if (option.arg != 0 && strtol(option.arg, &endptr, 10))
    {
    };
    if (endptr != option.arg && *endptr == 0)
      return option::ARG_OK;

    if (msg)
      printError("Option '", option, "' requires a numeric argument\n");
    return option::ARG_ILLEGAL;
  }
};

enum optionIndex
{
  UNKNOWN, HELP, VIDEO, VERSIONPARAM, DEV
};
const option::Descriptor usage[] =
{
{ UNKNOWN, 0, "", "", option::Arg::None, "USAGE: stargus archive-directory [destination-directory]\n\n"
    "Options:" },
{ HELP, 0, "h", "help", option::Arg::None, "  --help, -h  \t\tPrint usage and exit" },
{ VIDEO, 0, "v", "video", Arg::None, "  --video, -v  \t\tExtract and convert videos" },
{ DEV, 0, "d", "dev", Arg::None,
    "  --dev, -d  \t\tSome test hooks while development. Don't use it if you don't know what it does!" },
{ VERSIONPARAM, 0, "V", "version", Arg::None, "  --version, -V  \t\tShow version" },
{ UNKNOWN, 0, "", "", option::Arg::None,
    "\narchive-directory \t\tDirectory which include the archive install.exe or stardat.mpq...\n"
        "destination-directory \t\tDirectory where the extracted files are placed.\n" },
{ 0, 0, 0, 0, 0, 0 } };

int parseOptions(int argc, const char **argv)
{
  Preferences &preferences = Preferences::getInstance();
  argc -= (argc > 0);
  argv += (argc > 0); // skip program name argv[0] if present
  option::Stats stats(usage, argc, argv);
  option::Option options[stats.options_max], buffer[stats.buffer_max];
  option::Parser parse(usage, argc, argv, options, buffer);

  if (parse.error())
    exit(0);

  if (options[HELP])
  {
    option::printUsage(std::cout, usage);
    exit(0);
  }

  // parse options
  if (options[VIDEO].count() > 0)
  {
    preferences.setVideoExtraction(true);
  }

  // parse options
  if (options[DEV].count() > 0)
  {
    testHook();
  }

  if (options[VERSIONPARAM].count() > 0)
  {
    printf(VERSION "\n");
    exit(0);
  }

  for (option::Option *opt = options[UNKNOWN]; opt; opt = opt->next())
    std::cout << "Unknown option: " << opt->name << "\n";

  for (int i = 0; i < parse.nonOptionsCount(); ++i)
  {
    switch (i)
    {
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

  if (preferences.getArchiveDir().empty())
  {
    cerr << "Error: 'archive-directory' not given!" << endl << endl;
    option::printUsage(std::cout, usage);
    exit(1);
  }

  return 0;
}

/**
 * The only purpose of this function is to have a hook to develop/test single functions and then exit
 */
void testHook()
{
  LOG4CXX_DEBUG(logger, "testHook()");

  /*string font_path = "/home/andreas/src/git/stargus/work_font/classic/files/font/";
   string font_path_rm = "/home/andreas/src/git/stargus/work_font/remastered/SD/font/";
   string font_path_hd = "/home/andreas/src/git/stargus/work_font/remastered/font/"; // problem!

   shared_ptr<Breeze> breeze = make_shared<Breeze>(font_path_rm);

   Font font(breeze);
   font.convert("font16.fnt", "font16");*/

  shared_ptr<Storm> storm = make_shared<Storm>(
      "/home/andreas/Downloads/Games/DOS/Starcraft/Original_Backup/starcraft_install.exe_MPQ/files/stardat.mpq");
  //shared_ptr<Breeze> storm = make_shared<Breeze>("/home/andreas/Downloads/Games/DOS/Starcraft/wintools/datedit/Default");
  DataHub datahub(storm);
  //datahub.convert("test", "test");

  /// Image 1
  Pcx pcx1(storm, "game\\tunit.pcx");
  pcx1.savePNG("/tmp/tunit.png");
  std::shared_ptr<Palette> pal = pcx1.getPalette();
  pal->getDataChunk()->write("/tmp/tunit.pal");

  // Image 2
  Pcx pcx2(storm, "unit\\cmdbtns\\ticon.pcx");
  pcx2.savePNG("/tmp/ticon.png");
  pcx2.copyIndexPalette(0, 16, 0);
  std::shared_ptr<Palette> pal2 = pcx2.getPalette();
  pal2->getDataChunk()->write("/tmp/ticon.pal");

  // Image 3
  Pcx pcx3(storm, "tileset\\ashworld\\ofire.pcx");
  pcx3.savePNG("/tmp/ofire.png");
  pcx3.copyIndexPalette(0, 256, -1);
  std::shared_ptr<Palette> pal3 = pcx3.getPalette();
  pal3->getDataChunk()->write("/tmp/ofire.pal");

  shared_ptr<DataChunk> terrainWPE = storm->extractDataChunk("tileset\\install.wpe");
  Tileset::ConvertPaletteRGBXtoRGB(terrainWPE->getDataPointer());
  shared_ptr<Palette> terrainPalette = make_shared<Palette>(terrainWPE);

  string grp_file = "unit\\neutral\\Cbattle.grp";
  Grp grp(storm, grp_file, terrainPalette);

  grp.save("/tmp/Cbattle-install.png");

  cout << "end testHook()" << endl;
  exit(0);
}

/**
 **		Main
 */
int main(int argc, const char **argv)
{
#ifdef HAVE_LOG4CXX
  if (FileExists("logging.prop"))
  {
    log4cxx::PropertyConfigurator::configure("logging.prop");
  }
  else
  {
    logger.off();
  }
#endif // HAVE_LOG4CXX

  unsigned u;
  char buf[8192] =
  { '\0' };
  int i;
  FILE *f;

  Preferences &preferences = Preferences::getInstance();
  preferences.init(); // initialize all properties once in the beginning of the application

  parseOptions(argc, argv);

  LOG4CXX_INFO(logger, "Application start");

  sprintf(buf, "%s/extracted", preferences.getDestDir().c_str());
  f = fopen(buf, "r");
  if (f)
  {
    char version[20];
    int len = 0;
    if (fgets(version, 20, f))
      len = 1;
    fclose(f);
    if (len != 0 && strcmp(version, VERSION) == 0)
    {
      printf("Note: Data is already extracted in Dir \"%s\" with this version of startool\n", preferences.getDestDir().c_str());
      fflush(stdout);
    }
  }

  printf("Extract from \"%s\" to \"%s\"\n", preferences.getArchiveDir().c_str(), preferences.getDestDir().c_str());
  printf("Please be patient, the data may take a couple of minutes to extract...\n\n");
  fflush(stdout);

  string mpqfile;
  string submpqfile;

  // set this to false for activating the SC remastered Casc code while development
  bool mpq = true;

  if (mpq)
  {
    for (i = 0; i <= 1; ++i)
    {
      Control *c;
      unsigned int len;
      bool extracted = false;

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
        // This is only for debugging single steps while development!!!
        //if(c[u].Type != F && c[u].Type != Q && c[u].Type != M)
        //continue;

        shared_ptr<Storm> storm = make_shared<Storm>(mpqfile);

        Pcx pcx_tunit(storm, "game\\tunit.pcx");
        std::shared_ptr<Palette> pal_tunit = pcx_tunit.getPalette();

        Pcx pcx_tselect(storm, "game\\tselect.pcx");
        pcx_tselect.copyIndexPalette(1, 8, 0);
        std::shared_ptr<Palette> pal_tselect = pcx_tselect.getPalette();

        // just select on orange fire palette as test
        Pcx pcx_ofire(storm, "tileset\\ashworld\\ofire.pcx");
        pcx_ofire.copyIndexPalette(0, 256, -1);
        std::shared_ptr<Palette> pal_ofire = pcx_ofire.getPalette();

        Pcx pcx_ticon(storm, "unit\\cmdbtns\\ticon.pcx");
        pcx_ticon.copyIndexPalette(0, 16, 0);
        std::shared_ptr<Palette> pal_ticon = pcx_ticon.getPalette();

        switch (c[u].Type)
        {
          case F:
            if (submpqfile.empty())
            {
              sprintf(buf, "%s/%s", preferences.getArchiveDir().c_str(), c[u].ArcFile);
            }
            else
            {
              sprintf(buf, "%s", submpqfile.c_str());
            }
            printf("FileExists: %s", buf);
            case_func = FileExists(buf);
            if (case_func)
            {
              mpqfile = buf;
            }
            printf("...%s\n", case_func ? "ok" : "nok");
            break;
          case Q:
            printf("MPQSubExtract: %s, %s", c[u].File, c[u].ArcFile);
            case_func = MPQSubExtract(mpqfile.c_str(), c[u].ArcFile, c[u].File);
            if (case_func)
            {
              sprintf(buf, "%s/%s", preferences.getDestDir().c_str(), c[u].File);
              submpqfile = buf;
            }
            printf("...%s\n", case_func ? "ok" : "nok");
            break;
          case M: // WORKS!
          {
            printf("ConvertMap: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Scm scm(storm);
            case_func = scm.convert(c[u].ArcFile, c[u].File);
            printf("...%s\n", case_func ? "ok" : "nok");
          }
            break;
          case R: // UNUSED?
          {
            printf("ConvertRgb: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Tileset terrain(storm);
            case_func = terrain.ConvertRgb(c[u].ArcFile, c[u].File);
            printf("...%s\n", case_func ? "ok" : "nok");
          }
            break;
          case T:  // WORKS!
          {
            printf("ConvertTileset: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Tileset terrain(storm);
            case_func = terrain.ConvertTileset(c[u].ArcFile, c[u].File);
            printf("...%s\n", case_func ? "ok" : "nok");
          }
            break;
          case G: // WORKS!
          {
            printf("ConvertGfx: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Grp grp(storm, c[u].ArcFile);

            if (c[u].Arg1 == 4)
            {
              grp.setPalette(pal_ticon);
              grp.setRGBA(true);
            }
            else if (c[u].Arg1 == 3)
            {
              grp.setPalette(pal_ofire);
            }
            else if (c[u].Arg1 == 2)
            {
              grp.setPalette(pal_tselect);
            }
            else if (c[u].Arg1 == 1)
            {
              shared_ptr<Storm> storm2 = make_shared<Storm>(mpqfile);
              shared_ptr<DataChunk> terrainWPE = storm2->extractDataChunk("tileset\\install.wpe");
              Tileset::ConvertPaletteRGBXtoRGB(terrainWPE->getDataPointer());
              shared_ptr<Palette> terrainPalette = make_shared<Palette>(terrainWPE);

              grp.setPalette(terrainPalette);
            }
            else // default palette
            {
              shared_ptr<Storm> storm2 = make_shared<Storm>(mpqfile);
              shared_ptr<DataChunk> terrainWPE = storm2->extractDataChunk("tileset\\install.wpe");
              Tileset::ConvertPaletteRGBXtoRGB(terrainWPE->getDataPointer());
              shared_ptr<Palette> terrainPalette = make_shared<Palette>(terrainWPE);

              grp.setPalette(terrainPalette);
            }

            case_func = grp.save(string(c[u].File) + ".png");
            printf("...%s\n", case_func ? "ok" : "nok");
          }
            break;
          case U: // WORKS!
          {
            printf("ConvertGfu: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Gfu gfu(storm);
            case_func = gfu.convert(mpqfile.c_str(), c[u].ArcFile, c[u].File, c[u].Arg1);
            printf("...%s\n", case_func ? "ok" : "nok");
          }
            break;
          case I: // WORKS!
          {
            printf("ConvertWidgets: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Widgets widgets(storm);
            case_func = widgets.convert(mpqfile.c_str(), c[u].ArcFile, c[u].File, c[u].Arg1);
            printf("...%s\n", case_func ? "ok" : "nok");
          }
            break;
          case N: // WORKS!
          {
            printf("ConvertFont: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Font font(storm);
            case_func = font.convert(c[u].ArcFile, c[u].File);
            printf("...%s\n", case_func ? "ok" : "nok");
          }
            break;
            /*case W: // WORKS!
             printf("ConvertWav: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
             case_func = ConvertWav(mpqfile.c_str(), c[u].ArcFile, c[u].File);
             printf("...%s\n", case_func ? "ok" : "nok");
             break;*/
          case V: // WORKS!
            if (preferences.getVideoExtraction())
            {
              printf("ConvertVideo: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
              Video video(storm);
              case_func = video.ConvertVideo(c[u].ArcFile, c[u].File);
              printf("...%s\n", case_func ? "ok" : "nok");
            }
            break;
          case H: // WORKS!
          {
            printf("ConvertPcx: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Pcx pcx(storm, c[u].ArcFile);
            case_func = pcx.savePNG(string(c[u].File) + ".png");
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
          {
            printf("ConvertCampaign (.chk): %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
            Chk chk(storm);
            case_func = chk.convert(c[u].ArcFile, c[u].File);
            printf("...%s\n", case_func ? "ok" : "nok");
          }
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
  }
  else // Casc
  {
    unsigned int len = sizeof(RMTodo) / sizeof(*RMTodo);
    shared_ptr<Casc> hurricane = make_shared<Casc>("/home/andreas/BigSpace/Games/StarCraft");
    preferences.setDestDir("data.Stargus.RM");
    Control *c = RMTodo;

    bool case_func = false;
    for (u = 0; u < len; ++u)
    {
      switch (c[u].Type)
      {
        case D: // WORKS
        {
          printf("ConvertDds: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);

          Dds dds(hurricane);
          case_func = dds.convert(c[1].ArcFile, c[1].File);
          printf("...%s\n", case_func ? "ok" : "nok");
        }
          break;
        case N: // WORKS!
        {
          printf("ConvertFont: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);

          Font font(hurricane);
          case_func = font.convert(c[u].ArcFile, c[u].File);
          printf("...%s\n", case_func ? "ok" : "nok");
        }
          break;
      }
    }

  }

  sprintf(buf, "%s/extracted", preferences.getDestDir().c_str());
  f = fopen(buf, "w");
  fprintf(f, VERSION "\n");
  fclose(f);

  printf("New Done.\n");

  return 0;
}

