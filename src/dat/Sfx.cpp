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

std::shared_ptr<TblEntry> Sfx::sound_file()
{
  uint32_t sound_file_id = mDatahub.sfxdata->sound_file()->at(mId);
  LOG4CXX_TRACE(logger, string("sound_file(") + to_string(sound_file_id) + ")");

  shared_ptr<TblEntry> tbl_entry;

  if(sound_file_id > 0)
  {
    tbl_entry = mDatahub.sfxdata_tbl_vec.at(sound_file_id-1);
  }

  return tbl_entry;
}

} /* namespace dat */
