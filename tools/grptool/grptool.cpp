/*
 * grptool.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "optparser.h"
#include "libgrp/libgrp.hpp"
#include "Logger.h"
#include "FileUtil.h"
#include "Breeze.h"
#include "NoValidPaletteException.h"

// system
#include <iostream>
#include <memory>

using namespace std;

/**
 * Description
 */

static Logger logger("grptool");

// some global variables
string palette_file;
string grp_file;
bool remove_duplicates = true;
bool single_stiched = true;
int image_per_row = 10;


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
  UNKNOWN, HELP, PALETTE, DUPLICATES, IMAGE_ROW, SINGLE_FRAMES
};
const option::Descriptor usage[] =
{
  {
    UNKNOWN, 0, "", "", option::Arg::None, "USAGE: grptool [options] grp-file\n\n"
    "Options:"
  },
  { HELP, 0, "h", "help", option::Arg::None, "  --help, -h  \t\tPrint usage and exit" },
  { DUPLICATES, 0, "d", "duplicates", Arg::None, "  --duplicates, -d  \t\tExport also the duplicate frame" },
  { PALETTE, 0, "p", "palette", Arg::Required, "  --palette, -p  \t\tSpecify the path to a palette file" },
  { IMAGE_ROW, 0, "i", "image-row", Arg::Numeric, "  --image-row, -i  \t\tIf stitching is enabled, how many images should be saved per row (default: 10)" },
  { SINGLE_FRAMES, 0, "s", "single-frames", Arg::None, "  --single-frames, -s  \t\tExport each frame into one image (default: all stitched together)" },
  {
    UNKNOWN, 0, "", "", option::Arg::None,
    "\ngrp-file \t\tThe GRP file which should be converted.\n"

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

  if ( options[DUPLICATES].count() > 0 )
  {
    remove_duplicates = false;
  }

  if ( options[IMAGE_ROW].count() > 0 )
  {
    image_per_row = stoi(options[IMAGE_ROW].arg);
  }

  if ( options[SINGLE_FRAMES].count() > 0 )
  {
    single_stiched = false;
  }

  if(options[PALETTE].count() > 0)
  {
    palette_file = options[PALETTE].arg;
  }
  else
  {
    cerr << "Error: 'palette' not given!" << endl << endl;
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
      grp_file = parse.nonOption(i);
      break;
    default:
      break;
    }
  }

  if (grp_file.empty())
  {
    cerr << "Error: 'archive' not given!" << endl << endl;
    option::printUsage(std::cout, usage);
    exit(1);
  }

  return 0;
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

  std::shared_ptr<Palette> myGRPPallete = make_shared<Palette>();
  bool pal_ok = false;

  try
  {
    pal_ok = myGRPPallete->read(palette_file);
  }
  catch(NoValidPaletteException &palEx)
  {
    cerr << palEx.what() << endl;
  }

  if(pal_ok)
  {
    myGRPPallete->write("test.pal");

    GRPImage myGRPImage(grp_file, remove_duplicates);
    myGRPImage.SetColorPalette(myGRPPallete);

    //image_per_row=17 => starcraft
    myGRPImage.SaveConvertedPNG("output_frame.png", 0, myGRPImage.getNumberOfFrames(), single_stiched, image_per_row);

    //myGRPImage.SaveConvertedImage("output_frame_magic.png", 0, myGRPImage.getNumberOfFrames(), single_stiched, image_per_row);

    //myGRPImage.LoadImage(grp_file, remove_duplicates);
    //myGRPImage.SaveConvertedImage("output_big_file.png", 0, myGRPImage.getNumberOfFrames(), false, 17);
  }
  else
  {
    cerr << "Palette not successful loaded - Exit!" << endl;
  }

  cerr << "Application finished!" << endl;

  return 0;
}
