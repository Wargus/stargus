/*
 * Sound.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "Sfx.h"
#include "Logger.h"

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.Sound");

Sfx::Sfx(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

Sfx::~Sfx()
{

}

uint32_t Sfx::sound_file()
{
  uint32_t sound_file_id = mDatahub.sfxdata->sound_file()->at(mId);
  LOG4CXX_TRACE(logger, string("sound_file(") + to_string(sound_file_id) + ")");

  return sound_file_id;
}

TblEntry Sfx::sound_file_tbl()
{
  uint32_t sound_file_id = sound_file();

  TblEntry tbl_entry = mDatahub.sfxdata_tbl_vec.at(sound_file_id-1);

  LOG4CXX_TRACE(logger, string("sound_file(") + tbl_entry.name1 + ")");

  return tbl_entry;
}

} /* namespace dat */
