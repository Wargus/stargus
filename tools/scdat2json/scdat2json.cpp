/*
 * scdat2json.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "Breeze.h"
#include "Storm.h"
#include "Casc.h"
#include "FileUtil.h"
#include "StringUtil.h"
#include "optparser.h"
#include "dat/DataHub.h"
#include "Storage.h"
#include "SCJsonExporter.h"
#include "UnitsJsonExporter.h"
#include "Logger.h"
#include "pacman.h"
#include "dat/Unit.h"
#include "to_json.h"

// system
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using namespace dat;

/**
 * The scdat2json tool idea is to export the data in all relevant *.dat and corresponding *.tbl in a raw format to JSON.
 * At this point of transformation isn't much format conversation done. Just put the data as in original data structures, but readable.
 * Only exception for now is that .tbl files get some basic control sequence parsing.
 */

static Logger logger("startool.scdat2json");

// some global variables
string backend;
string archive;
string destination_directory;
bool pretty = true;

bool CheckCASCDataFolder(const std::string &dir)
{
  return FileExists(dir + "/.build.info");
}

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
  UNKNOWN, HELP, BACKEND, PRETTY
};
const option::Descriptor usage[] =
{
  {
    UNKNOWN, 0, "", "", option::Arg::None, "USAGE: scdat2json [options] archive archive-file destination-directory\n\n"
    "Options:"
  },
  { HELP, 0, "h", "help", option::Arg::None, "  --help, -h  \t\tPrint usage and exit" },
  { PRETTY, 0, "p", "pretty", Arg::Required, "  --pretty=[yes/no], -p  \t\tPretty print the formated JSON file (default: yes)" },
  { BACKEND, 0, "b", "backend", Arg::Required, "  --backend, -b  \t\tChoose a backend (Storm=St*arcr*ft1/Br**dwar;Casc=Remastered;Breeze=Folder)" },
  {
    UNKNOWN, 0, "", "", option::Arg::None,
    "\narchive \t\tDestination to the archive (mpq, casc or dummy folder) based on backend.\n"
    "\ndestination-directory \t\tWhere to save the extracted file with same relative path.\n"

  },
  { 0, 0, 0, 0, 0, 0 }
};

int parseOptions(int argc, const char **argv)
{
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

  if ( options[PRETTY].count() > 0 )
  {
    if (string(options[PRETTY].arg) == "yes")
    {
      pretty = true;
    }
    else if (string(options[PRETTY].arg) == "no")
    {
      pretty = false;
    }
  }

  if(options[BACKEND].count() > 0)
  {
    backend = options[BACKEND].arg;
  }
  else
  {
    cerr << "Error: 'backend' not given!" << endl << endl;
    option::printUsage(std::cout, usage);
    exit(1);
  }

  // parse options

  for (option::Option *opt = options[UNKNOWN]; opt; opt = opt->next())
    std::cout << "Unknown option: " << opt->name << "\n";

  for (int i = 0; i < parse.nonOptionsCount(); ++i)
  {
    switch (i)
    {
    case 0:
      //cerr << "archive #" << i << ": " << parse.nonOption(i) << "\n";
      archive = parse.nonOption(i);
      break;
    case 1:
      //cerr << "destination-directory #" << i << ": " << parse.nonOption(i) << "\n";
      destination_directory = parse.nonOption(i);
      break;
    default:
      break;
    }
  }

  if (archive.empty())
  {
    cerr << "Error: 'archive' not given!" << endl << endl;
    option::printUsage(std::cout, usage);
    exit(1);
  }

  if (destination_directory.empty())
  {
    cerr << "Error: 'destination_directory' not given!" << endl << endl;
    option::printUsage(std::cout, usage);
    exit(1);
  }

  return 0;
}

void saveJson(json &j, const std::string &file, bool pretty)
{
  std::ofstream filestream(file);

  if(pretty)
  {
    filestream << std::setw(4) << j;
  }
  else
  {
    filestream << j;
  }
}

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

  parseOptions(argc, argv);
  CheckPath(destination_directory);

  bool archive_exists = FileExists(archive);
  if(!archive_exists)
  {
    cerr << "archive not existing - exit!" << endl;
    exit(1);
  }

  // read in the json file
  std::ifstream json_file(pacman::searchFile("dataset/units.json"));
  json units_json; //create unitiialized json object
  json_file >> units_json; // initialize json object with what was read from file

  shared_ptr<Hurricane> hurricane;

  if(to_lower(backend) == "breeze")
  {
    hurricane = make_shared<Breeze>(archive);
  }
  else if(to_lower(backend) == "storm")
  {
    hurricane = make_shared<Storm>(archive);
  }
  else if(to_lower(backend) == "casc")
  {
#ifdef HAVE_CASC
    if(CheckCASCDataFolder(archive))
    {
      hurricane = make_shared<Casc>(archive);
    }
    else
    {
      cerr << "Error: 'archive' is not a CASC archive!" << endl;
    }
#else
    cerr << "Error: No CASC support compiled into sauwetter!" << endl;
    exit(1);
#endif
  }

  dat::DataHub datahub(hurricane);

  Storage jsonStorage;
  jsonStorage.setDataPath(destination_directory);

  //UnitsJsonExporter unitsjsonexporter(datahub);
  for(auto &array : units_json)
  {
    string id_string = array.at("name");
    int id = array.at("id");
    //unitsjsonexporter.exportUnit(id, id_string);

    Unit unit(datahub, id, id_string);

    json j_unit(unit);

    saveJson(j_unit, jsonStorage(id_string + ".json"), pretty);
  }

  /*for(unsigned int i = 0; i < datahub.images->grp()->size(); i++)
  {
    Image image(datahub, i);

    json j_image(image);

    saveJson(j_image, jsonStorage(image.getIDString() + ".json"), pretty);
  }*/

  SCJsonExporter scjsonexporter(datahub);

  json j_unit_dat = scjsonexporter.export_unit_dat();
  saveJson(j_unit_dat, jsonStorage("units_dat.json"), pretty);

  json j_orders_dat = scjsonexporter.export_orders_dat();
  saveJson(j_orders_dat, jsonStorage("orders_dat.json"), pretty);

  json j_weapons_dat = scjsonexporter.export_weapons_dat();
  saveJson(j_weapons_dat, jsonStorage("weapons_dat.json"), pretty);

  json j_flingy_dat = scjsonexporter.export_flingy_dat();
  saveJson(j_flingy_dat, jsonStorage("flingy_dat.json"), pretty);

  json j_sprites_dat = scjsonexporter.export_sprites_dat();
  saveJson(j_sprites_dat, jsonStorage("sprites_dat.json"), pretty);

  json j_images_dat = scjsonexporter.export_images_dat();
  saveJson(j_images_dat, jsonStorage("images_dat.json"), pretty);

  json j_sfxdata_dat = scjsonexporter.export_sfxdata_dat();
  saveJson(j_sfxdata_dat, jsonStorage("sfxdata_dat.json"), pretty);

  json j_portdata_dat = scjsonexporter.export_portdata_dat();
  saveJson(j_portdata_dat, jsonStorage("portdata_dat.json"), pretty);

  json j_upgrades_dat = scjsonexporter.export_upgrades_dat();
  saveJson(j_upgrades_dat, jsonStorage("upgrades_dat.json"), pretty);

  json j_techdata_dat = scjsonexporter.export_techdata_dat();
  saveJson(j_techdata_dat, jsonStorage("techdata_dat.json"), pretty);

  json j_mapdata_dat = scjsonexporter.export_mapdata_dat();
  saveJson(j_mapdata_dat, jsonStorage("mapdata_dat.json"), pretty);

  // export all the .tbl ->

  json j_images_tbl = scjsonexporter.export_file_tbl(datahub.images_tbl_vec);
  saveJson(j_images_tbl, jsonStorage("images_tbl.json"), pretty);

  json j_sfxdata_tbl = scjsonexporter.export_file_tbl(datahub.sfxdata_tbl_vec);
  saveJson(j_sfxdata_tbl, jsonStorage("sfxdata_tbl.json"), pretty);

  json j_portdata_tbl = scjsonexporter.export_file_tbl(datahub.portdata_tbl_vec);
  saveJson(j_portdata_tbl, jsonStorage("portdata_tbl.json"), pretty);

  json j_mapdata_tbl = scjsonexporter.export_file_tbl(datahub.mapdata_tbl_vec);
  saveJson(j_mapdata_tbl, jsonStorage("mapdata_tbl.json"), pretty);

  /// save all the the stat_txt.tbl parts...


  json stat_txt_tbl = scjsonexporter.export_file_tbl(datahub.stat_txt_tbl_vec);
  saveJson(stat_txt_tbl, jsonStorage("stat_txt_tbl.json"), pretty);

  /*json stat_txt_units_tbl = scjsonexporter.export_file_tbl(datahub.stat_txt_units_tbl_vec);
  saveJson(stat_txt_units_tbl, jsonStorage("stat_txt_units_tbl.json"), pretty);

  json stat_txt_weapons_tbljson = scjsonexporter.export_file_tbl(datahub.stat_txt_weapons_tbl_vec);
  saveJson(stat_txt_weapons_tbljson, jsonStorage("stat_txt_weapons_tbl.json"), pretty);

  json stat_txt_error_messages_tbl = scjsonexporter.export_file_tbl(datahub.stat_txt_error_messages_tbl_vec);
  saveJson(stat_txt_error_messages_tbl, jsonStorage("stat_txt_error_messages_tbl.json"), pretty);

  json stat_txt_upgrades_tbl = scjsonexporter.export_file_tbl(datahub.stat_txt_upgrades_tbl_vec);
  saveJson(stat_txt_upgrades_tbl, jsonStorage("stat_txt_upgrades_tbl.json"), pretty);

  json stat_txt_orders_tbl = scjsonexporter.export_file_tbl(datahub.stat_txt_orders_tbl_vec);
  saveJson(stat_txt_orders_tbl, jsonStorage("stat_txt_orders_tbl.json"), pretty);

  json stat_txt_techdata_tbl = scjsonexporter.export_file_tbl(datahub.stat_txt_techdata_tbl_vec);
  saveJson(stat_txt_techdata_tbl, jsonStorage("stat_txt_techdata_tbl.json"), pretty);*/

  cerr << "Application finished!" << endl;

  return 0;
}
