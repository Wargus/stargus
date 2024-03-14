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

// project
#include <UnitsConverter.h>
#include <PortraitsConverter.h>
#include "dat/DataHub.h"
#include "tileset/TilesetHub.h"
#include "PngExporter.h"
#include "Smacker.h"
#include "Palette.h"
#include "endian.h"
#include "startool.h"
#include "Preferences.h"
#include "Scm.h"
#include "FileUtil.h"
#include "Pcx.h"
#include "Font.h"
#include "Grp.h"
#include "Panel.h"
#include "Widgets.h"
#include "DataChunk.h"
#include "Casc.h"
#include "Dds.h"
#include "Logger.h"
#include "Breeze.h"
#include "Storage.h"
#include "Wav.h"
#include "tileset/TilesetHub.h"
#include "platform.h"
#include "UIConsole.h"
#include "StringUtil.h"
#include "pacman.h"
#include "ImagesConverter.h"
#include "SfxConverter.h"
#include "optparser.h"

// system
#include <nlohmann/json.hpp>
#include <fstream>
#include <map>

using json = nlohmann::json;

// <-

// System
#include <memory>
#include <map>

// activate local debug messages
#define DEBUG 1

using namespace std;

static Logger logger("startool.main");

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
  UNKNOWN, HELP, VIDEO, SOUND, VERSIONPARAM, DEV
};
const option::Descriptor usage[] =
{
  {
    UNKNOWN, 0, "", "", option::Arg::None, "USAGE: startool archive-directory [destination-directory]\n\n"
    "Options:"
  },
  { HELP, 0, "h", "help", option::Arg::None, "  --help, -h  \t\tPrint usage and exit" },
  { VIDEO, 0, "v", "video", Arg::None, "  --video, -v  \t\tExtract and convert videos" },
  { SOUND, 0, "s", "sound", Arg::None, "  --sound, -s  \t\tExtract and convert sounds" },
  { DEV, 0, "d", "dev", Arg::None,
    "  --dev, -d  \t\tSome test hooks while development. Don't use it if you don't know what it does!"},
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

  if (options[SOUND].count() > 0)
  {
    preferences.setSoundExtraction(true);
  }

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


void loadPalettes(std::shared_ptr<Hurricane> hurricane,
                  Storage palStorage,
                  std::map<std::string, std::shared_ptr<AbstractPalette>> &paletteMap)
{
  // read in the json file
  std::ifstream json_file(pacman::searchFile("dataset/palettes.json"));

  json palettes_json; //create unitiialized json object

  json_file >> palettes_json; // initialize json object with what was read from file

  //std::cout << units_json << std::endl; // prints json object to screen

  vector<string> wpeNames;

  /** WPE **/
  auto &wpe_section = palettes_json.at("WPE");

  for(auto &wpe_array : wpe_section)
  {
    string name = wpe_array.at("name");
    string wpe_arcfile = wpe_array.at("arcfile");
    string pal_palette = wpe_array.at("palette");

    shared_ptr<DataChunk> dataWPE = hurricane->extractDataChunk(wpe_arcfile);

    if (dataWPE) // load from WPE palette
    {
      shared_ptr<Palette> pal = make_shared<Palette>(dataWPE);
      paletteMap[name] = pal;
      wpeNames.push_back(name);

      string pal_file(palStorage.getFullPath() + pal_palette);
      CheckPath(pal_file);
      pal->write(pal_file);
    }
    else // load from stored .pal palette
    {
      Breeze localPal(palStorage.getFullPath());
      shared_ptr<DataChunk> dataPal = localPal.extractDataChunk(pal_palette);

      if(dataPal)
      {
        std::shared_ptr<Palette> pal = make_shared<Palette>(dataPal);
        paletteMap[name] = pal;
      }
    }

    //cout << wpe_array << endl;
  }

  /** PCX **/
  auto &pcx_section = palettes_json.at("PCX");

  for(auto &pcx_array : pcx_section)
  {
    string name = pcx_array.at("name");
    string pcx_arcfile = pcx_array.at("arcfile");
    string pal_palette = pcx_array.at("palette");

    Pcx pcx(hurricane, pcx_arcfile);

    if(!pcx.getSize().isEmpty()) // load from PCX palette
    {
      std::shared_ptr<Palette> pal;
      try
      {
        auto &pcx_mapping = pcx_array.at("mapping");

        int length = pcx_mapping.at("length");
        int start = pcx_mapping.at("start");
        int index = pcx_mapping.at("index");

        pal = pcx.mapIndexPalette(length, start, index);
      }
      catch (const nlohmann::detail::out_of_range &json_range)
      {
        pal = pcx.getPalette();
      }

      string pal_file(palStorage.getFullPath() + pal_palette);
      CheckPath(pal_file);
      pal->write(pal_file);

      paletteMap[name] = pal;
    }
    else // load from stored .pal palette
    {
      Breeze localPal(palStorage.getFullPath());
      shared_ptr<DataChunk> dataPal = localPal.extractDataChunk(pal_palette);

      if(dataPal)
      {
        std::shared_ptr<Palette> pal = make_shared<Palette>(dataPal);
        paletteMap[name] = pal;
      }
    }

    //cout << pcx_array << endl;
  }

  /** PCX2D (after WPE block has been read in) **/
  auto &pcx2d_section = palettes_json.at("PCX2D");

  for(auto &pcx_array : pcx2d_section)
  {
    string pcx_name = pcx_array.at("name");
    string pcx_arcfile = pcx_array.at("arcfile");
    string pal_palette = pcx_array.at("palette");

    // replace this with the first of the WPE palettes. Which one doesn't care for the palette logic.
    replaceString("<?>", *wpeNames.begin(), pcx_arcfile);

    Pcx pcx(hurricane, pcx_arcfile);

    std::shared_ptr<Palette2D> pal2D = pcx.map2DPalette();

    string pal_file(palStorage.getFullPath() + pal_palette);
    CheckPath(pal_file);
    pal2D->write(pal_file);

    paletteMap[pcx_name] = pal2D;

    //cout << pcx_array << endl;
  }


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

  shared_ptr<Storm> storm = make_shared<Storm>("/home/andreas/Games/DOS/Starcraft/Original_Backup/starcraft_install.exe_MPQ/files/stardat.mpq");
  //shared_ptr<Storm> storm = make_shared<Storm>("/home/andreas/Games/DOS/Starcraft/Original_Backup/broodwar_install.exe_MPQ/files/broodat.mpq");
  //shared_ptr<Breeze> breeze = make_shared<Breeze>("/home/andreas/Games/DOS/Starcraft/Original_Backup/starcraft_install.exe_MPQ");
  dat::DataHub datahub(storm);

  dat::Unit unit(datahub, 0, "test");
  cout << "unit: " << unit.name_tbl().name1() << endl;

  dat::IScript is = unit.flingy_obj().sprite_obj().image_obj().iscript_obj();

  int animation_count = is.getAnimationCount();

  cout << "animation_count: " << to_string(animation_count) << endl;

  for(int i = 0; i < animation_count; i++)
  //int i = 8;
  {
    cout << "animation: " << i << endl;
    std::vector<iscript_bin_t::opcode_type_t*> opcode_vec =
        unit.flingy_obj().sprite_obj().image_obj().iscript_obj().getAnimationScript(i);

    for(auto opcode : opcode_vec)
    {
      cout << "code: " << hex << opcode->code() << endl;
    }
  }

  dat::Sfx sfx = unit.ready_sound_obj();
  sfx.sound_file_tbl();

  dat::Portrait portrait = unit.portrait_obj();

  portrait.video_talking_tbl();
  portrait.video_idle_tbl();

  /// Image 1
  Pcx pcx1(storm, "game\\tunit.pcx");
  pcx1.savePNG("/tmp/tunit.png");
  std::shared_ptr<Palette> pal = pcx1.mapIndexPalette(8, 8, 2);
  pal->createDataChunk()->write("/tmp/tunit.pal");

  // Image 2
  Pcx pcx2(storm, "unit\\cmdbtns\\ticon.pcx");
  pcx2.savePNG("/tmp/ticon.png");
  std::shared_ptr<Palette> pal2 = pcx2.mapIndexPalette(16, 0, 0);
  pal2->createDataChunk()->write("/tmp/ticon.pal");

  // Image 3
  Pcx pcx3(storm, "tileset\\ashworld\\ofire.pcx");
  pcx3.savePNG("/tmp/ofire.png");
  std::shared_ptr<Palette2D> pal2D_3 = pcx3.map2DPalette();
  std::shared_ptr<Palette> pal3 = pcx3.getPalette();
  pal3->createDataChunk()->write("/tmp/ofire.pal");

  // Image 4
  Pcx pcx4(storm, "tileset\\ashworld\\ofire.pcx");
  pcx4.savePNG("/tmp/bfire.png");
  std::shared_ptr<Palette2D> pal2D_4 = pcx4.map2DPalette();
  std::shared_ptr<Palette> pal4 = pcx4.getPalette();
  pal4->createDataChunk()->write("/tmp/ofire.pal");
  pal2D_4->write("/tmp/ofire.pal2d");


  shared_ptr<DataChunk> terrainWPE = storm->extractDataChunk("tileset\\jungle.wpe");
  shared_ptr<Palette> terrainPalette = make_shared<Palette>(terrainWPE);
  terrainPalette->createDataChunk()->write("/tmp/terrainPalette.pal");

  //string grp_file = "unit\\protoss\\pbaGlow.grp";
  string grp_file = "unit\\thingy\\ofirec.grp";
  Grp grp(storm, grp_file);
  grp.setPalette(pal2D_4);
  grp.setRGBA(true);
  //grp.setPalette(terrainPalette);
  //grp.setTransparent(200);
  //grp.setRGBA(true);

  // read in the json file
  std::ifstream json_file(pacman::searchFile("dataset/dlgs_race.json"));

  json dlgsRaceJson; //create unitiialized json object

  json_file >> dlgsRaceJson; // initialize json object with what was read from file

  Widgets widgets(storm);
  widgets.setPalette(pal);
  widgets.convert("dlgs\\terran.grp", "/tmp/widgets2/", dlgsRaceJson);


  grp.save("/tmp/ofirec.png");

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

  Storage tilesets;
  tilesets.setDataPath(preferences.getDestDir());
  tilesets.setDataType("graphics/tilesets");

  Storage luagen;
  luagen.setDataPath(preferences.getDestDir());
  luagen.setDataType("luagen");

  Storage palStorage;
  palStorage.setDataPath(preferences.getDestDir());
  palStorage.setDataType("palette");

  Storage data;
  data.setDataPath(preferences.getDestDir());

  map<string, shared_ptr<AbstractPalette>> paletteMap;

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

    dat::DataHub datahub(sub_storm);

    // read in the json file
    std::ifstream json_file(pacman::searchFile("dataset/units.json"));

    json units_json; //create unitiialized json object

    json_file >> units_json; // initialize json object with what was read from file

    //std::cout << units_json << std::endl; // prints json object to screen

    vector<string> unitNames;
    for(auto &array : units_json)
    {
      string unit_name = array.at("name");
      unitNames.push_back(unit_name);
    }

    loadPalettes(sub_storm, palStorage, paletteMap);

    if (preferences.getVideoExtraction())
    {
      PortraitsConverter portraitsConverter(sub_storm, datahub);
      portraitsConverter.convert();
    }

    dat::UnitsConverter unitsConverter(sub_storm, datahub);
    unitsConverter.convert(units_json);

    ImagesConverter imagesConverter(sub_storm, datahub);
    imagesConverter.convert(paletteMap);

    if(preferences.getSoundExtraction())
    {
      SfxConverter sfxConverter(sub_storm, datahub);
      sfxConverter.convert();
    }

    // read in the json file
    std::ifstream dlgsRaceJsonStream(pacman::searchFile("dataset/dlgs_race.json"));
    json dlgsRaceJson; //create unitiialized json object
    dlgsRaceJsonStream >> dlgsRaceJson; // initialize json object with what was read from file

    Widgets widgets(sub_storm);
    widgets.setPalette(paletteMap["tunit"]);
    widgets.convert("dlgs\\terran.grp", graphics("ui/terran"), dlgsRaceJson);
    widgets.convert("dlgs\\zerg.grp", graphics("ui/zerg"), dlgsRaceJson);
    widgets.convert("dlgs\\protoss.grp", graphics("ui/protoss"), dlgsRaceJson);

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
        case M: // WORKS!
        {
          printf("ConvertMap: %s, %s", c[u].File, c[u].ArcFile);
          Scm scm(storm);
          case_func = scm.convert(c[u].ArcFile, unitNames, data(c[u].File));
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case T: // WORKS!
        {
          printf("ConvertTileset: %s, %s", c[u].File, c[u].ArcFile);
          tileset::TilesetHub terrain(storm, c[u].ArcFile);
          case_func = terrain.convert(paletteMap.at(c[u].File), tilesets(c[u].File));

          string luafile(string("tilesets/") + c[u].File + ".lua");
          string pngfile(string("tilesets/") + c[u].File + "/" + c[u].File + ".png");
          terrain.generateLua(c[u].File, pngfile, luagen(luafile));

          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case G: // WORKS!
        {
          printf("ConvertGfx: %s, %s, %d", c[u].File, c[u].ArcFile, c[u].Arg1);
          Grp grp(storm, c[u].ArcFile);
          std::shared_ptr<AbstractPalette> pal;

          if (c[u].Arg1 == 6)
          {
            pal = paletteMap.at("twire");
            grp.setPalette(pal);
          }
          else if (c[u].Arg1 == 5)
          {
            pal = paletteMap.at("ticon-0");
            grp.setPalette(pal);
          }
          else if (c[u].Arg1 == 4)
          {
            pal = paletteMap.at("ticon-0");
            grp.setPalette(pal);
            grp.setRGBA(true);
          }
          else if (c[u].Arg1 == 3)
          {
            pal = paletteMap.at("ofire");
            grp.setPalette(pal);
            grp.setRGBA(true);
          }
          else if (c[u].Arg1 == 2)
          {
            pal = paletteMap.at("tselect-0");
            grp.setPalette(pal);
          }
          else if (c[u].Arg1 == 1)
          {
            pal = paletteMap.begin()->second;
            grp.setPalette(pal);
          }
          else // default palette
          {
            pal = paletteMap.begin()->second;
            grp.setPalette(pal);
          }

          case_func = grp.save(graphics(string(c[u].File) + ".png"));
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        /*case I: // WORKS!
        {
          printf("ConvertWidgets: %s, %s", c[u].File, c[u].ArcFile);
          Widgets widgets(storm);
          std::shared_ptr<AbstractPalette> pal = paletteMap.at("tunit");
          widgets.setPalette(pal);
          case_func = widgets.convert(c[u].ArcFile, c[u].File);
          printf("...%s\n", case_func ? "ok" : "nok");
        }*/
        break;
        case N: // WORKS!
        {
          printf("ConvertFont: %s, %s", c[u].File, c[u].ArcFile);
          Font font(storm);
          std::shared_ptr<AbstractPalette> pal = paletteMap.at("tfontgam");
          font.setPalette(pal);
          case_func = font.convert(c[u].ArcFile, fonts(string(c[u].File) + ".png"));
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case W: // WORKS!
          if (preferences.getSoundExtraction())
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
            case_func = video.convertOGV(c[u].ArcFile, videos(c[u].File));
            printf("...%s\n", case_func ? "ok" : "nok");
          }
          break;
        case P: // WORKS!
          if (preferences.getVideoExtraction())
          {
            printf("ConvertPortrait: %s, %s", c[u].File, c[u].ArcFile);
            Smacker video(storm);
            case_func = video.convertMNG(c[u].ArcFile, videos(c[u].File));
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
        {
          printf("Extract text: %s, %s", c[u].File, c[u].ArcFile);
          auto chunk = storm->extractDataChunk(c[u].ArcFile);
          char *utf8 = iconvISO2UTF8(reinterpret_cast<char*>(chunk->getDataPointer()));
          if (utf8) {
            chunk->replaceData(reinterpret_cast<unsigned char*>(utf8), strlen(utf8), 0);
            free(utf8);
            case_func = chunk->write(data(c[u].File).getFullPath());
          } else {
            case_func = false;
          }
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        case L:
        {
          printf("ConvertCampaign (.chk): %s, %s", c[u].File, c[u].ArcFile);
          Chk chk(storm);
          chk.setUnitNames(unitNames);
          case_func = chk.convert(c[u].ArcFile, data(c[u].File));
          printf("...%s\n", case_func ? "ok" : "nok");
        }
        break;
        default:
          break;
        }
      }
    }

    UIConsole uic(sub_storm);

    // Terran console
    string console = "ui/tconsole";
    //pixel count from left
    int left = 275;
    int right = 296;

    printf("UIConsole: %s", console.c_str());
    uic.convert(graphics(console), left, right);
    printf("...%s\n", case_func ? "ok" : "nok");

    // Zerg console
    console = "ui/zconsole";
    left = 274;
    right = 281;

    printf("UIConsole: %s", console.c_str());
    uic.convert(graphics(console), left, right);
    printf("...%s\n", case_func ? "ok" : "nok");

    // Protoss console
    console = "ui/pconsole";
    left = 227;
    right = 265;

    printf("UIConsole: %s", console.c_str());
    uic.convert(graphics(console), left, right);
    printf("...%s\n", case_func ? "ok" : "nok");

    // remove temporary sub files
    platform::unlink(sub_storm->getArchiveName());

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

  printf("Done startool!\n");

  return 0;
}

