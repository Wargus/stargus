/*
 * SfxConverter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "SfxConverter.h"
#include "Storage.h"
#include "Preferences.h"
#include "FileUtil.h"
#include "Sfx.h"
#include "Wav.h"
#include "Logger.h"
#include "StringUtil.h"

// system
#include <iostream>
#include <fstream>

using namespace std;

static Logger logger = Logger("startool.dat.SfxConverter");

namespace dat
{

SfxConverter::SfxConverter(std::shared_ptr<Hurricane> hurricane, DataHub &datahub) :
  Converter(hurricane),
  mDatahub(datahub)
{

}

SfxConverter::~SfxConverter()
{

}

bool SfxConverter::convert()
{
  bool result = true;

  Preferences &preferences = Preferences::getInstance();

  Storage sounds;
  sounds.setDataPath(preferences.getDestDir());
  sounds.setDataType("sounds/unit");

  /*Storage luagen;
  luagen.setDataPath(preferences.getDestDir());
  luagen.setDataType("luagen/sounds");
  CheckPath(luagen.getFullPath());

  ofstream lua_include;
  lua_include.open (luagen("luagen-sounds.lua").getFullPath());
  string lua_include_str;*/

  // start with i=1 as 0=none and couldn't be read
  for(unsigned int i = 1; i < static_cast<unsigned int>(mDatahub.sfxdata->num_lines()); i++)
  {
    Sfx sfx(mDatahub, i);

    string sound_id;

    /*Storage lua_file_store(luagen("sound-" + sound_id + ".lua"));
    ofstream lua_file;
    lua_file.open (lua_file_store.getFullPath());*/

    TblEntry sound_file = sfx.sound_file_tbl();

    string sound_arcfile("sound\\" + sound_file.name1);
    string sound_file_base(sound_file.name1);
    replaceString("\\", "/", sound_file_base);
    sound_file_base = cutFileEnding(to_lower(sound_file_base), ".wav");

    LOG4CXX_TRACE(logger, "sound_arcfile: " + sound_arcfile);
    LOG4CXX_TRACE(logger, "sound_file_base: " + sound_file_base);

    Wav wav(mHurricane);

    bool case_func = wav.convert(sound_arcfile, sounds(sound_file_base));
    printf("...%s\n", case_func ? "ok" : "nok");
  }

  //lua_include << lua_include_str;
  //lua_include.close();

  return result;
}

} /* namespace dat */
