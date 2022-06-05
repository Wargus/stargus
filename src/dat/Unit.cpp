/*
 * Unit.cpp
 *
 *      Author: Andreas Volz
 */

#include "Unit.h"
#include "Logger.h"

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.Unit");

Unit::Unit(DataHub &datahub, uint8_t id) :
  mDatahub(datahub),
  mId(id)
{
}

Unit::~Unit()
{
}

Flingy Unit::flingy()
{
  uint8_t flingy_id = mDatahub.units->flingy()->at(mId);
  LOG4CXX_TRACE(logger, string("flingy(") + to_string(flingy_id) + ")");

  Flingy flingy(mDatahub, flingy_id);

  return flingy;
}

TblEntry Unit::name()
{
  LOG4CXX_TRACE(logger, string("name(") + to_string(mId) + ")");

  TblEntry tbl_entry = mDatahub.stat_txt_vec.at(mId);

  return tbl_entry;
}

uint32_t Unit::hitpoints()
{
  uint32_t hitpoints = mDatahub.units->hit_points()->at(mId)->hitpoints();

  LOG4CXX_TRACE(logger, string("hitpoints(") + to_string(hitpoints) + ")");

  return hitpoints;
}

Portrait Unit::portrait()
{
  uint16_t portrait_id = mDatahub.units->portrait()->at(mId);
  if (portrait_id == Unit::portrait_none)
  {
    throw NoPortraitException(portrait_id);
  }
  LOG4CXX_TRACE(logger, string("portrait(") + to_string(portrait_id) + ")");

  Portrait portrait(mDatahub, portrait_id);

  return portrait;
}

const char *NoPortraitException::what() const throw()
{
  static string s;
  s = "Portrait id not existing: ";
  s += to_string(m_portraid_id);

  return static_cast <const char *>(s.c_str());
}


} /* namespace dat */
