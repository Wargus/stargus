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
  return mDatahub.sfxdata->sound_file()->at(mId);
}

TblEntry Sfx::sound_file_tbl()
{
  return mDatahub.sfxdata_tbl_vec.at(sound_file()-1);
}

uint8_t Sfx::unknown1()
{
  return mDatahub.sfxdata->unknown1()->at(mId);
}

uint8_t Sfx::unknown2()
{
  return mDatahub.sfxdata->unknown2()->at(mId);
}

uint8_t Sfx::unknown3()
{
  return mDatahub.sfxdata->unknown3()->at(mId);
}

uint8_t Sfx::unknown4()
{
  return mDatahub.sfxdata->unknown4()->at(mId);
}

} /* namespace dat */
