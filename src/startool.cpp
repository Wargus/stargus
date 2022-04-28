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

#include "Smacker.h"
#include "Palette.h"
#include <Tbl.h>
#include "endian.h"
#include "startool.h"
#include "Preferences.h"
#include "Scm.h"
#include "FileUtil.h"
#include "Pcx.h"
#include "Font.h"
#include "Grp.h"
#include "Png.h"
#include "Panel.h"
#include "Widgets.h"
#include "Tileset.h"
#include "DataChunk.h"
#include "Casc.h"
#include "Dds.h"
#include "Logger.h"
#include "Breeze.h"
#include "DataHub.h"
#include "Storage.h"
#include "Wav.h"

// as this is 3rd party code I don't fix it ->
#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif
#include "optionparser.h"
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif
// <-

// System
#include <memory>
#include <map>

// activate local debug messages
#define DEBUG 1

using namespace std;

Logger logger("startool.main");

// test only
void testHook();
bool dev_hack = false;

//----------------------------------------------------------------------------

/**
 **  Raw extraction
 **
 **  @param arcfile File identifier in the MPQ file
 **  @param file Place to save the file on the drive (relative)
 */
bool RawExtract(std::shared_ptr<Hurricane> hurricane, const char *arcfile, Storage storage)
{
  bool result = true;

  result = hurricane->extractFile(arcfile, storage.getFullPath(), false);

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
  UNKNOWN, HELP, VIDEO, VERSIONPARAM, DEV, DEV2
};
const option::Descriptor usage[] =
{
  {
    UNKNOWN, 0, "", "", option::Arg::None, "USAGE: startool archive-directory [destination-directory]\n\n"
    "Options:"
  },
  { HELP, 0, "h", "help", option::Arg::None, "  --help, -h  \t\tPrint usage and exit" },
  { VIDEO, 0, "v", "video", Arg::None, "  --video, -v  \t\tExtract and convert videos" },
  {
    DEV, 0, "d", "dev", Arg::None,
    "  --dev, -d  \t\tSome test hooks while development. Don't use it if you don't know what it does!"
  },
  {
    DEV2, 0, "d2", "dev2", Arg::None,
    "  --dev2, -d2  \t\tSome test hooks while development. Don't use it if you don't know what it does!"
  },
  { VERSIONPARAM, 0, "V", "version", Arg::None, "  --version, -V  \t\tShow version" },
  {
    UNKNOWN, 0, "", "", option::Arg::None,
    "\narchive-directory \t\tDirectory which include the archive install.exe or stardat.mpq...\n"
    "destination-directory \t\tDirectory where the extracted files are placed.\n"
  },
  { 0, 0, 0, 0, 0, 0 }
};

int parseOptions(int argc, const char **argv)
{
  Preferences &preferences = Preferences::getInstance();
  argc -= (argc > 0);
  argv += (argc > 0); // skip program name argv[0] if present
  option::Stats stats(usage, argc, argv);
  std::unique_ptr<option::Option[]> options(new option::Option[stats.options_max]), buffer(new option::Option[stats.buffer_max]);
  option::Parser parse(usage, argc, argv, options.get(), buffer.get());

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
    dev_hack = true;
  }

  // parse options
  if (options[DEV2].count() > 0)
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
  Pcx pcx1(storm, "game\\tfontgam.pcx");
  pcx1.savePNG("/tmp/tunit.png");
  std::shared_ptr<Palette> pal = pcx1.getPalette();
  pal->createDataChunk()->write("/tmp/tunit.pal");

  // Image 2
  Pcx pcx2(storm, "unit\\cmdbtns\\ticon.pcx");
  pcx2.savePNG("/tmp/ticon.png");
  pcx2.mapIndexPalette(16, 0, 0);
  std::shared_ptr<Palette> pal2 = pcx2.getPalette();
  pal2->createDataChunk()->write("/tmp/ticon.pal");

  // Image 3
  Pcx pcx3(storm, "tileset\\ashworld\\ofire.pcx");
  pcx3.savePNG("/tmp/ofire.png");
  std::shared_ptr<Palette2D> pal2D_3 = pcx3.map2DPalette();
  std::shared_ptr<Palette> pal3 = pcx3.getPalette();
  pal3->createDataChunk()->write("/tmp/ofire.pal");

  // Image 4
  Pcx pcx4(storm, "tileset\\ashworld\\bfire.pcx");
  pcx4.savePNG("/tmp/bfire.png");
  std::shared_ptr<Palette2D> pal2D_4 = pcx4.map2DPalette();
  std::shared_ptr<Palette> pal4 = pcx4.getPalette();
  pal4->createDataChunk()->write("/tmp/bfire.pal");


  shared_ptr<DataChunk> terrainWPE = storm->extractDataChunk("tileset\\jungle.wpe");
  shared_ptr<Palette> terrainPalette = make_shared<Palette>(terrainWPE);
  terrainPalette->createDataChunk()->write("/tmp/terrainPalette.pal");

  //string grp_file = "unit\\protoss\\pbaGlow.grp";
  string grp_file = "unit\\thingy\\flamer.grp";
  Grp grp(storm, grp_file);
  grp.setPalette2D(pal2D_3);
  grp.setPalette(terrainPalette);
  //grp.setTransparent(200);
  grp.setRGBA(true);

  grp.save("/tmp/flamer.png");

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

  // set this to false for activating the SC remastered Casc code while development
  bool mpq = true;

  Storage graphics;
  graphics.setDataPath(preferences.getDestDir());
  graphics.setDataType("graphics");

  Storage videos;
  videos.setDataPath(preferences.getDestDir());
  videos.setDataType("videos");

  Storage fonts;
  fonts.setDataPath(preferences.getDestDir());
  fonts.setDataType("graphics/ui/fonts");

  Storage sounds;
  sounds.setDataPath(preferences.getDestDir());
  sounds.setDataType("sounds");

  Storage data;
  data.setDataPath(preferences.getDestDir());

  map<string, shared_ptr<Palette>> paletteMap;

  std::shared_ptr<Palette2D> pal2D;

  if (mpq)
  {
    Control *c = nullptr;
    unsigned int len = 0;
    bool case_func = false;
    shared_ptr<Storm> main_storm;
    shared_ptr<Storm> sub_storm;
    shared_ptr<Storm> storm;

    c = CDTodo_bootstrap;
    len = sizeof(CDTodo_bootstrap) / sizeof(*CDTodo_bootstrap);
    for (u = 0; u < len; ++u)
    {
      switch (c[u].Type)
      {
      case F:
      {
        string archiveFile = preferences.getArchiveDir() + "/" + c[u].ArcFile;
        case_func = FileExists(archiveFile);
        cout << "F: " << c[u].ArcFile << " : " << c[u].File << " : " << case_func << endl;
        if (case_func && !main_storm)
        {
          main_storm = make_shared<Storm>(archiveFile);
        }
      }
      break;
      case Q:
      {
        cout << "Q:" <<  c[u].ArcFile << " : " << c[u].File <<  endl;
        if (main_storm)
        {
          string file = preferences.getDestDir() + "/" + c[u].File;
          main_storm->extractFile(c[u].ArcFile, file, false);
        }
      }
      break;
      default:
        break;
      }
    }

    c = Todo_bootstrap;
    len = sizeof(Todo_bootstrap) / sizeof(*Todo_bootstrap);
    for (u = 0; u < len; ++u)
    {
      switch (c[u].Type)
      {
      case F:
      {
        string archiveFile = preferences.getDestDir() + "/" + c[u].ArcFile;
        case_func = FileExists(archiveFile);
        cout << "F: " << c[u].ArcFile << " : " << c[u].File << " : " << case_func << endl;
        if (case_func && !sub_storm)
        {
          sub_storm = make_shared<Storm>(archiveFile);
        }
      }
      break;
      default:
        break;
      }
    }

    for (i = 0; i <= 1; ++i)
    {
      switch (i)
      {
      case 0:
        // StarDat.mpq or stardat.mpq from inside files\\stardat.mpq
        c = Todo;
        len = sizeof(Todo) / sizeof(*Todo);
        storm = sub_storm;
        break;
      case 1:
        // CD install.exe renamed to StarCraft.mpq or other main mpq file
        c = CDTodo;
        len = sizeof(CDTodo) / sizeof(*CDTodo);
        storm = main_storm;
        break;
      }

      case_func = false;
      for (u = 0; u < len; ++u)
      {
        switch (c[u].Type)
        {
        case PAL:
        {
          printf("ConvertPal: %s, %s", c[u].File, c[u].ArcFile);

          Pcx pcx_palette(storm, c[u].ArcFile);

          switch(c[u].Arg1)
          {
            case 1:
              pcx_palette.mapIndexPaletteTypeIcon(0);
              break;

            case 2:
              pcx_palette.mapIndexPaletteTypeSelect(0);
              break;

            case 3:
               pal2D = pcx_palette.map2DPalette();
              break;

            case 0:
            default:
              break;
          }

          std::shared_ptr<Palette> pal = pcx_palette.getPalette();
          //pal->write(graphics(c[u].File) + ".pal");
          paletteMap[c[u].File] = pal;
        }
        break;
        case WPE:
        {
          printf("ConvertWpe: %s, %s", c[u].File, c[u].ArcFile);
          shared_ptr<DataChunk> dc_wpe = storm->extractDataChunk(c[u].ArcFile);
          std::shared_ptr<Palette> pal = make_shared<Palette>(dc_wpe);

          //pal->write(graphics(c[u].File) + ".pal");

          paletteMap[c[u].File] = pal;
        }
        break;
        case M: // WORKS!
        {
          printf("ConvertMap: %s, %s", c[u].File, c[u].ArcFile);
          Scm scm(storm);
          case_func = scm.convert(c[u].ArcFile, data(c[u].File));
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        /*case R: // FIXME: support Palette class or remove!
        {
          printf("ConvertRgb: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
          Tileset terrain(storm);
          case_func = terrain.ConvertRgb(c[u].ArcFile, c[u].File);
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;*/
        case T:  // WORKS!
        {
          printf("ConvertTileset: %s, %s", c[u].File, c[u].ArcFile);
          Tileset terrain(storm);
          case_func = terrain.ConvertTileset(c[u].ArcFile, c[u].File);
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case G: // WORKS!
        {
          printf("ConvertGfx: %s, %s", c[u].File, c[u].ArcFile);
          Grp grp(storm, c[u].ArcFile);
          std::shared_ptr<Palette> pal;

          if (c[u].Arg1 == 6)
          {
            pal = paletteMap.at("twire");
            grp.setPalette(pal);
          }
          else if (c[u].Arg1 == 5)
          {
            pal = paletteMap.at("ticon");
            grp.setPalette(pal);
            grp.setGFX(false);
          }
          else if (c[u].Arg1 == 4)
          {
            pal = paletteMap.at("ticon");
            grp.setPalette(pal);
            grp.setRGBA(true);
          }
          else if (c[u].Arg1 == 3)
          {
            pal = paletteMap.at("install");
            grp.setPalette2D(pal2D);
            grp.setPalette(pal);
            //grp.setTransparent(127);
            grp.setRGBA(true);
          }
          else if (c[u].Arg1 == 2)
          {
            pal = paletteMap.at("tselect");
            grp.setPalette(pal);
          }
          else if (c[u].Arg1 == 1)
          {
            pal = paletteMap.at("install");
            grp.setPalette(pal);
          }
          else // default palette
          {
            pal = paletteMap.at("install");
            grp.setPalette(pal);
          }

          case_func = grp.save(graphics(string(c[u].File) + ".png"));
          //grp.saveLUAConfig(graphics(string(c[u].File) + ".lua")); // FIXME: works only after save()
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case I: // WORKS!
        {
          printf("ConvertWidgets: %s, %s", c[u].File, c[u].ArcFile);
          Widgets widgets(storm);
          std::shared_ptr<Palette> pal = paletteMap.at("tunit");
          widgets.setPalette(pal);
          case_func = widgets.convert(c[u].ArcFile, c[u].File);
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case N: // WORKS!
        {
          printf("ConvertFont: %s, %s", c[u].File, c[u].ArcFile);
          Font font(storm);
          std::shared_ptr<Palette> pal = paletteMap.at("tfontgam");
          font.setPalette(pal);
          case_func = font.convert(c[u].ArcFile, fonts(string(c[u].File) + ".png"));
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case W: // WORKS!
          if (!dev_hack)
          {
            printf("ConvertWav: %s, %s", c[u].File, c[u].ArcFile);
            Wav wav(storm);
            case_func = wav.convert(c[u].ArcFile, sounds(c[u].File));
            printf("...%s\n", case_func ? "ok" : "nok");
          }
          break;
        case V: // WORKS!
          if (preferences.getVideoExtraction())
          {
            printf("ConvertSmacker: %s, %s", c[u].File, c[u].ArcFile);
            Smacker video(storm);
            case_func = video.ConvertVideo(c[u].ArcFile, videos(c[u].File));
            printf("...%s\n", case_func ? "ok" : "nok");
          }
          break;
        case P: // WORKS!
          if (preferences.getVideoExtraction())
          {
            printf("ConvertPortrait: %s, %s", c[u].File, c[u].ArcFile);
            Smacker video(storm);
            case_func = video.ConvertPortrait(c[u].ArcFile, videos(c[u].File));
            printf("...%s\n", case_func ? "ok" : "nok");
          }
          break;
        case H: // WORKS!
        {
          printf("ConvertPcx: %s, %s", c[u].File, c[u].ArcFile);
          Pcx pcx(storm, c[u].ArcFile);
          case_func = pcx.savePNG(graphics(string(c[u].File) + ".png"));
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case E: // WORKS
          printf("RawExtract: %s, %s", c[u].File, c[u].ArcFile);
          // TBD: I think campaigns this must be somehow converted to stratagus
          case_func = RawExtract(storm, c[u].ArcFile, data(c[u].File));
          printf("...%s\n", case_func ? "ok" : "nok");
          break;
        case L:
        {
          printf("ConvertCampaign (.chk): %s, %s", c[u].File, c[u].ArcFile);
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
#ifdef _MSC_VER
    _unlink(sub_storm->getArchiveName().c_str());
#else
    unlink(sub_storm->getArchiveName().c_str());
#endif

    CreatePanels();
  }
  else // Casc
  {
#ifdef HAVE_CASC_tmp
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
#endif /* HAVE_CASC */
  }

  sprintf(buf, "%s/extracted", preferences.getDestDir().c_str());
  f = fopen(buf, "w");
  fprintf(f, VERSION "\n");
  fclose(f);

  printf("New Done.\n");

  return 0;
}

