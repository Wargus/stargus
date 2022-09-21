/*
 * Unit.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "Unit.h"
#include "Logger.h"

// system
#include <iostream>

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

std::string Unit::getIDString()
{
  return mIdentString;
}

TblEntry Unit::name_tbl()
{
  return mDatahub.stat_txt_tbl_vec.at(mId);;
}

uint8_t Unit::flingy()
{
  return mDatahub.units->flingy()->at(mId);
}

Flingy Unit::flingy_obj()
{
  return Flingy(mDatahub, flingy());
}

uint16_t Unit::subunit1()
{
  return mDatahub.units->subunit1()->at(mId);
}

Unit Unit::subunit1_obj()
{
  uint16_t subunit_id = subunit1();

  if(subunit_id == Unit::subunit_none)
  {
    throw UnitPropertyNotAvailableException(mId, "subunit1");
  }

  return Unit(mDatahub, subunit_id, "<unknown>");
}

uint16_t Unit::subunit2()
{
  return mDatahub.units->subunit2()->at(mId);
}

Unit Unit::subunit2_obj()
{
  uint16_t subunit_id = subunit2();

  if(subunit_id == Unit::subunit_none)
  {
    throw UnitPropertyNotAvailableException(mId, "subunit2");
  }

  return Unit(mDatahub, subunit_id, "<unknown>");
}

uint16_t Unit::infestation()
{
  uint16_t infestation = 0;

  try
  {
    // only for units of ID 106-201 (buildings)
    infestation = mDatahub.units->infestation()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_ERROR(logger, string("Exception: infestation(") + to_string(infestation) + ")");
    throw UnitPropertyNotAvailableException(mId, "infestation");
  }

  return infestation;
}

Unit Unit::infestation_obj()
{
  uint16_t infestation_id = infestation();

  if(infestation_id == Unit::infestation_none)
  {
    throw UnitPropertyNotAvailableException(mId, "infestation_obj");
  }

  return Unit(mDatahub, infestation_id, "<unknown>");
}

uint32_t Unit::construction_animation()
{
  return mDatahub.units->construction_animation()->at(mId);
}

Image Unit::construction_animation_obj()
{
  return Image(mDatahub, construction_animation());
}

uint8_t Unit::unit_direction()
{
  return mDatahub.units->unit_direction()->at(mId);
}

uint8_t Unit::shield_enable()
{
  return mDatahub.units->shield_enable()->at(mId);
}

uint16_t Unit::shield_amount()
{
  return mDatahub.units->shield_amount()->at(mId);
}

uint32_t Unit::hitpoints()
{
  return mDatahub.units->hit_points()->at(mId)->hitpoints();
}

uint8_t Unit::elevation_level()
{
  return mDatahub.units->elevation_level()->at(mId);
}

uint8_t Unit::unknown()
{
  return mDatahub.units->unknown()->at(mId);
}

uint8_t Unit::rank()
{
  return mDatahub.units->rank()->at(mId);
}

uint8_t Unit::ai_computer_idle()
{
  return mDatahub.units->ai_computer_idle()->at(mId);
}

uint8_t Unit::ai_human_idle()
{
  return mDatahub.units->ai_human_idle()->at(mId);
}

uint8_t Unit::ai_return_to_idle()
{
  return mDatahub.units->ai_return_to_idle()->at(mId);
}

uint8_t Unit::ai_attack_unit()
{
  return mDatahub.units->ai_attack_unit()->at(mId);
}

uint8_t Unit::ai_attack_move()
{
  return mDatahub.units->ai_attack_move()->at(mId);
}

uint8_t Unit::ground_weapon()
{
  return mDatahub.units->ground_weapon()->at(mId);
}

uint8_t Unit::max_ground_hits()
{
  return mDatahub.units->max_ground_hits()->at(mId);
}

uint8_t Unit::air_weapon()
{
  return mDatahub.units->air_weapon()->at(mId);
}

uint8_t Unit::max_air_hits()
{
  return mDatahub.units->max_air_hits()->at(mId);
}

uint8_t Unit::ai_internal()
{
  return mDatahub.units->ai_internal()->at(mId);
}

units_dat_t::special_ability_flags_type_t* Unit::special_ability_flags()
{
  return mDatahub.units->special_ability_flags()->at(mId);
}

uint8_t Unit::target_acquisition_range()
{
  return mDatahub.units->target_acquisition_range()->at(mId);
}

uint8_t Unit::sight_range()
{
  return mDatahub.units->sight_range()->at(mId);
}

uint8_t Unit::armor_upgrade()
{
  return mDatahub.units->armor_upgrade()->at(mId);
}

units_dat_t::unit_size_enum_t Unit::unit_size()
{
  return mDatahub.units->unit_size()->at(mId);
}

uint8_t Unit::armor()
{
  return mDatahub.units->armor()->at(mId);
}

units_dat_t::right_click_action_enum_t Unit::right_click_action()
{
  return mDatahub.units->right_click_action()->at(mId);
}

uint16_t Unit::ready_sound()
{
  uint16_t ready_sound = 0;

  try
  {
    // only unit IDs < 106 have ready_sound
    ready_sound = mDatahub.units->ready_sound()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_ERROR(logger, string("Exception: ready_sound(") + to_string(ready_sound) + ")");
    throw UnitPropertyNotAvailableException(mId, "ready_sound");
  }

  return ready_sound;
}

Sfx Unit::ready_sound_obj()
{
  uint16_t ready_sound_id = ready_sound();

  if(ready_sound_id == Unit::sound_none)
  {
    LOG4CXX_ERROR(logger, string("Exception: ready_sound_obj(") + to_string(ready_sound_id) + ")");
    throw UnitPropertyNotAvailableException(mId, "ready_sound_obj");
  }

  Sfx sfx(mDatahub, ready_sound_id);

  return sfx;
}

uint16_t Unit::what_sound_start()
{
  return mDatahub.units->what_sound_start()->at(mId);
}

uint16_t Unit::what_sound_end()
{
  return mDatahub.units->what_sound_end()->at(mId);
}

std::vector<Sfx> Unit::what_sound_obj()
{
  std::vector<Sfx> sfx_vector;

  uint16_t what_sound_start_id = what_sound_start();
  uint16_t what_sound_end_id = what_sound_end();

  if((what_sound_start_id || what_sound_end_id) == Unit::sound_none)
  {
    LOG4CXX_ERROR(logger, string("Exception: what_sound_obj(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "what_sound_obj");
  }

  for(unsigned int i = what_sound_start_id; i <= what_sound_end_id; i++)
  {
    Sfx sfx(mDatahub, i);
    sfx_vector.push_back(sfx);
  }

  return sfx_vector;
}

uint16_t Unit::piss_sound_start()
{
  uint16_t piss_sound_start = 0;

  try
  {
    // only unit IDs < 106 have piss_sound_start
    piss_sound_start = mDatahub.units->piss_sound_start()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_ERROR(logger, string("Exception: piss_sound_start(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "piss_sound_start");
  }

  return piss_sound_start;
}

uint16_t Unit::piss_sound_end()
{
  uint16_t piss_sound_end = 0;

  try
  {
    // only unit IDs < 106 have piss_sound_end
    piss_sound_end = mDatahub.units->piss_sound_end()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_ERROR(logger, string("Exception: piss_sound_end(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "piss_sound_end");
  }

  return piss_sound_end;
}

std::vector<Sfx> Unit::piss_sound_obj()
{
  std::vector<Sfx> sfx_vector;

  uint16_t piss_sound_start_id = piss_sound_start();
  uint16_t piss_sound_end_id = piss_sound_end();

  if((piss_sound_start_id || piss_sound_end_id) == Unit::sound_none)
  {
    LOG4CXX_ERROR(logger, string("Exception: piss_sound_obj(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "piss_sound_obj");
  }

  for(unsigned int i = piss_sound_start_id; i <= piss_sound_end_id; i++)
  {
    Sfx sfx(mDatahub, i);
    sfx_vector.push_back(sfx);
  }

  return sfx_vector;
}

uint16_t Unit::yes_sound_start()
{
  uint16_t yes_sound_start = 0;

  try
  {
    // only unit IDs < 106 have yes_sound_start
    yes_sound_start = mDatahub.units->yes_sound_start()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_ERROR(logger, string("Exception: piss_sound_start(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "yes_sound_start");
  }

  return yes_sound_start;
}

uint16_t Unit::yes_sound_end()
{
  uint16_t yes_sound_end = 0;

  try
  {
    // only unit IDs < 106 have yes_sound_end
    yes_sound_end = mDatahub.units->yes_sound_end()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_ERROR(logger, string("Exception: yes_sound_end(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "yes_sound_end");
  }

  return yes_sound_end;
}

std::vector<Sfx> Unit::yes_sound_obj()
{
  std::vector<Sfx> sfx_vector;

  uint16_t yes_sound_start_id = yes_sound_start();
  uint16_t yes_sound_end_id = yes_sound_end();

  if((yes_sound_start_id || yes_sound_end_id) == Unit::sound_none)
  {
    LOG4CXX_ERROR(logger, string("Exception: yes_sound_obj(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "yes_sound_obj");
  }

  for(unsigned int i = yes_sound_start_id; i <= yes_sound_end_id; i++)
  {
    Sfx sfx(mDatahub, i);
    sfx_vector.push_back(sfx);
  }

  return sfx_vector;
}

units_dat_t::staredit_placement_box_type_t* Unit::staredit_placement_box()
{
  return mDatahub.units->staredit_placement_box()->at(mId);
}

units_dat_t::addon_position_type_t* Unit::addon_position()
{
  units_dat_t::addon_position_type_t* addon = nullptr;

  try
  {
    // Exists only for units of ID 106-201 (buildings)
    addon = mDatahub.units->addon_position()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_ERROR(logger, string("Exception: addon_position(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "addon_position");
  }

  return addon;
}

units_dat_t::unit_dimension_type_t *Unit::unit_dimension()
{
  return mDatahub.units->unit_dimension()->at(mId);
}

uint16_t Unit::portrait()
{
  return mDatahub.units->portrait()->at(mId);
}

Portrait Unit::portrait_obj()
{
  uint16_t portrait_id = portrait();

  if (portrait_id == Unit::portrait_none)
  {
    LOG4CXX_ERROR(logger, string("Exception: portrait_obj(") + to_string(mId) + ")");
    throw UnitPropertyNotAvailableException(mId, "portrait_obj");
  }

  Portrait portrait(mDatahub, portrait_id);

  return portrait;
}


uint16_t Unit::mineral_cost()
{
  return mDatahub.units->mineral_cost()->at(mId);
}

uint16_t Unit::vespene_cost()
{
  return mDatahub.units->vespene_cost()->at(mId);
}


uint16_t Unit::build_time()
{
  return mDatahub.units->build_time()->at(mId);
}

uint16_t Unit::requirements()
{
  return mDatahub.units->requirements()->at(mId);
}

units_dat_t::staredit_group_flags_type_t* Unit::staredit_group_flags()
{
  return mDatahub.units->staredit_group_flags()->at(mId);
}

uint8_t Unit::supply_required()
{
  return mDatahub.units->supply_required()->at(mId);
}

uint8_t Unit::space_provided()
{
  return mDatahub.units->space_provided()->at(mId);
}

uint16_t Unit::build_score()
{
  return mDatahub.units->build_score()->at(mId);
}

uint16_t Unit::destroy_score()
{
  return mDatahub.units->destroy_score()->at(mId);
}

// TODO: a unit_map_string_string_tbl() might be helpful...
uint16_t Unit::unit_map_string()
{
  return mDatahub.units->unit_map_string()->at(mId);
}

uint8_t Unit::broodwar_flag()
{
  return mDatahub.units->broodwar_flag()->at(mId);
}

units_dat_t::staredit_availability_flags_type_t* Unit::staredit_availability_flags()
{
  return mDatahub.units->staredit_availability_flags()->at(mId);
}

bool Unit::is_format_bw()
{
  return mDatahub.units->is_format_bw();
}

/* Exceptions */

const char *UnitPropertyNotAvailableException::what() const throw()
{
  static string s;
  s = "Property '";
  s += m_property;
  s += "' not existing for unit: ";
  s += to_string(m_unit_id);

  return static_cast <const char *>(s.c_str());
}

} /* namespace dat */
