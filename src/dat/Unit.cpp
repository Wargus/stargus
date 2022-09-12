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

Unit::Unit(DataHub &datahub, unsigned int id, const std::string &identString) :
  ObjectAccess(datahub, id),
  mIdentString(identString)
{
}

Unit::~Unit()
{
}

std::string Unit::createID()
{
  return mIdentString;
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
  LOG4CXX_TRACE(logger, string("name(") + tbl_entry.name1 + ")");

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

uint8_t Unit::elevation_level()
{
  uint8_t elevation_level = mDatahub.units->elevation_level()->at(mId);

  LOG4CXX_TRACE(logger, string("elevation_level(") + to_string(elevation_level) + ")");

  return elevation_level;
}

units_dat_t::unit_dimension_type_t *Unit::unit_dimension()
{
  units_dat_t::unit_dimension_type_t *unit_dimension = mDatahub.units->unit_dimension()->at(mId);

  LOG4CXX_TRACE(logger, string("unit_dimension(") +
      " l: " + to_string(unit_dimension->left()) +
      " r: " + to_string(unit_dimension->right()) +
      " u: " + to_string(unit_dimension->up()) +
      " d: " + to_string(unit_dimension->down()) +
      ")");

  return unit_dimension;
}

uint8_t Unit::sight_range()
{
  uint8_t sight_range = mDatahub.units->sight_range()->at(mId);

  LOG4CXX_TRACE(logger, string("sight_range(") + to_string(sight_range) + ")");

  return sight_range;
}

units_dat_t::special_ability_flags_type_t *Unit::special_ability_flags()
{
  units_dat_t::special_ability_flags_type_t *special_ability_flags = mDatahub.units->special_ability_flags()->at(mId);

  LOG4CXX_TRACE(logger, string("special_ability_flags()"));

  return special_ability_flags;
}

uint16_t Unit::build_time()
{
  uint16_t build_time = mDatahub.units->build_time()->at(mId);

  LOG4CXX_TRACE(logger, string("build_time(") + to_string(build_time) + ")");

  return build_time;
}

uint16_t Unit::vespene_cost()
{
  uint16_t vespene_cost = mDatahub.units->vespene_cost()->at(mId);

  LOG4CXX_TRACE(logger, string("vespene_cost(") + to_string(vespene_cost) + ")");

  return vespene_cost;
}

uint16_t Unit::mineral_cost()
{
  uint16_t mineral_cost = mDatahub.units->mineral_cost()->at(mId);

  LOG4CXX_TRACE(logger, string("mineral_cost(") + to_string(mineral_cost) + ")");

  return mineral_cost;
}

Sfx Unit::ready_sound()
{
  if(mId >= 106) // only unit IDs < 106 have ready_sound
  {
    throw NoSfxException(mId);
  }

  uint16_t ready_sound_id = mDatahub.units->ready_sound()->at(mId);

  LOG4CXX_TRACE(logger, string("ready_sound(") + to_string(ready_sound_id) + ")");

  if(ready_sound_id == Unit::sound_none)
  {
    throw NoSfxException(Unit::sound_none);
  }

  Sfx sfx(mDatahub, ready_sound_id);

  return sfx;
}

std::vector<Sfx> Unit::what_sound()
{
  std::vector<Sfx> sfx_vector;

  uint16_t what_sound_start_id = mDatahub.units->what_sound_start()->at(mId);
  uint16_t what_sound_end_id = mDatahub.units->what_sound_end()->at(mId);

  LOG4CXX_TRACE(logger, string("what_sound_start(") + to_string(what_sound_start_id) + ")");
  LOG4CXX_TRACE(logger, string("what_sound_end(") + to_string(what_sound_end_id) + ")");

  if((what_sound_start_id || what_sound_end_id) == Unit::sound_none)
  {
    throw NoSfxException(Unit::sound_none);
  }

  for(unsigned int i = what_sound_start_id; i <= what_sound_end_id; i++)
  {
    Sfx sfx(mDatahub, i);
    sfx_vector.push_back(sfx);
  }

  return sfx_vector;
}

std::vector<Sfx> Unit::yes_sound()
{
  if(mId >= 106) // only unit IDs < 106 have ready_sound
  {
    throw NoSfxException(mId);
  }

  std::vector<Sfx> sfx_vector;

  uint16_t yes_sound_start_id = mDatahub.units->yes_sound_start()->at(mId);
  uint16_t yes_sound_end_id = mDatahub.units->yes_sound_end()->at(mId);

  LOG4CXX_TRACE(logger, string("yes_sound_start(") + to_string(yes_sound_start_id) + ")");
  LOG4CXX_TRACE(logger, string("yes_sound_end(") + to_string(yes_sound_end_id) + ")");

  if((yes_sound_start_id || yes_sound_end_id) == Unit::sound_none)
  {
    throw NoSfxException(Unit::sound_none);
  }

  for(unsigned int i = yes_sound_start_id; i <= yes_sound_end_id; i++)
  {
    Sfx sfx(mDatahub, i);
    sfx_vector.push_back(sfx);
  }

  return sfx_vector;
}

std::vector<Sfx> Unit::piss_sound()
{
  if(mId >= 106) // only unit IDs < 106 have ready_sound
  {
    throw NoSfxException(mId);
  }

  std::vector<Sfx> sfx_vector;

  uint16_t piss_sound_start_id = mDatahub.units->piss_sound_start()->at(mId);
  uint16_t piss_sound_end_id = mDatahub.units->piss_sound_end()->at(mId);

  LOG4CXX_TRACE(logger, string("piss_sound_start(") + to_string(piss_sound_start_id) + ")");
  LOG4CXX_TRACE(logger, string("piss_sound_end(") + to_string(piss_sound_end_id) + ")");

  if((piss_sound_start_id || piss_sound_end_id) == Unit::sound_none)
  {
    throw NoSfxException(Unit::sound_none);
  }

  for(unsigned int i = piss_sound_start_id; i <= piss_sound_end_id; i++)
  {
    Sfx sfx(mDatahub, i);
    sfx_vector.push_back(sfx);
  }

  return sfx_vector;
}

/* Exceptions */

const char *NoPortraitException::what() const throw()
{
  static string s;
  s = "Portrait id not existing: ";
  s += to_string(m_portraid_id);

  return static_cast <const char *>(s.c_str());
}

const char *NoSfxException::what() const throw()
{
  static string s;
  s = "Sfx id not existing: ";
  s += to_string(m_sfx_id);

  return static_cast <const char *>(s.c_str());
}


} /* namespace dat */
