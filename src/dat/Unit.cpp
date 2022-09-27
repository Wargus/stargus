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
  // trace at least the id string that we know where we are
  LOG4CXX_TRACE(logger,  mIdentString + "=>" + LOG_CUR_FUNC + "()");
  return mIdentString;
}

TblEntry Unit::name_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.stat_txt_tbl_vec.at(mId);
}

uint8_t Unit::flingy()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->flingy()->at(mId);
}

Flingy Unit::flingy_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Flingy(mDatahub, flingy());
}

uint16_t Unit::subunit1()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->subunit1()->at(mId);
}

Unit Unit::subunit1_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t subunit_id = subunit1();

  if(subunit_id == Unit::subunit_none)
  {
    throw PropertyNotAvailableException(mId, "subunit1_obj");
  }

  return Unit(mDatahub, subunit_id, "<subunit2>");
}

uint16_t Unit::subunit2()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->subunit2()->at(mId);
}

Unit Unit::subunit2_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t subunit_id = subunit2();

  if(subunit_id == Unit::subunit_none)
  {
    throw PropertyNotAvailableException(mId, "subunit2_obj");
  }

  return Unit(mDatahub, subunit_id, "<subunit2>");
}

uint16_t Unit::infestation()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t infestation = 0;

  try
  {
    // only for units of ID 106-201 (buildings)
    infestation = mDatahub.units->infestation()->at(mId-106);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_DEBUG(logger, string("Exception: infestation(") + to_string(infestation) + ")");
    throw PropertyNotAvailableException(mId, "infestation");
  }

  return infestation;
}

Unit Unit::infestation_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t infestation_id = infestation();

  if(infestation_id == Unit::infestation_none)
  {
    throw PropertyNotAvailableException(mId, "infestation_obj");
  }

  return Unit(mDatahub, infestation_id, "<infestation>");
}

uint32_t Unit::construction_animation()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->construction_animation()->at(mId);
}

Image Unit::construction_animation_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  uint32_t construction_animation_id = construction_animation();

  if(construction_animation_id == Unit::construction_none)
  {
    throw PropertyNotAvailableException(mId, "construction_animation_obj");
  }

  return Image(mDatahub, construction_animation_id);
}

uint8_t Unit::unit_direction()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->unit_direction()->at(mId);
}

uint8_t Unit::shield_enable()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->shield_enable()->at(mId);
}

uint16_t Unit::shield_amount()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->shield_amount()->at(mId);
}

uint32_t Unit::hitpoints()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->hit_points()->at(mId)->hitpoints();
}

uint8_t Unit::elevation_level()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->elevation_level()->at(mId);
}

uint8_t Unit::unknown()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->unknown()->at(mId);
}

uint8_t Unit::rank()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->rank()->at(mId);
}

uint8_t Unit::ai_computer_idle()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->ai_computer_idle()->at(mId);
}

Order Unit::ai_computer_idle_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Order(mDatahub, ai_computer_idle());
}

uint8_t Unit::ai_human_idle()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->ai_human_idle()->at(mId);
}

Order Unit::ai_human_idle_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Order(mDatahub, ai_human_idle());
}

uint8_t Unit::ai_return_to_idle()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->ai_return_to_idle()->at(mId);
}

Order Unit::ai_return_to_idle_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Order(mDatahub, ai_return_to_idle());
}

uint8_t Unit::ai_attack_unit()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->ai_attack_unit()->at(mId);
}

Order Unit::ai_attack_unit_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Order(mDatahub, ai_attack_unit());
}

uint8_t Unit::ai_attack_move()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->ai_attack_move()->at(mId);
}

Order Unit::ai_attack_move_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Order(mDatahub, ai_attack_move());
}

uint8_t Unit::ground_weapon()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->ground_weapon()->at(mId);
}

Weapon Unit::ground_weapon_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  uint8_t ground_weapon_id = mDatahub.units->ground_weapon()->at(mId);

  // strange logic in the data. If the weapon links to a index bigger than weapon then it's 'none'
  if(ground_weapon_id >= mDatahub.weapons->label()->size())
  {
    LOG4CXX_TRACE(logger, string("Exception: ground_weapon_obj > size"));
    throw PropertyNotAvailableException(mId, "ground_weapon_obj");
  }

  return Weapon(mDatahub, ground_weapon_id);
}

uint8_t Unit::max_ground_hits()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->max_ground_hits()->at(mId);
}

uint8_t Unit::air_weapon()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->air_weapon()->at(mId);
}

Weapon Unit::air_weapon_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  uint8_t air_weapon_id = mDatahub.units->air_weapon()->at(mId);

  // strange logic in the data. If the weapon links to a index bigger than weapon then it's 'none'
  if(air_weapon_id >= mDatahub.weapons->label()->size())
  {
    LOG4CXX_TRACE(logger, string("Exception: air_weapon_obj > size"));
    throw PropertyNotAvailableException(mId, "air_weapon_obj");
  }

  return Weapon(mDatahub, air_weapon_id);
}

uint8_t Unit::max_air_hits()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->max_air_hits()->at(mId);
}

uint8_t Unit::ai_internal()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->ai_internal()->at(mId);
}

units_dat_t::special_ability_flags_type_t* Unit::special_ability_flags()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->special_ability_flags()->at(mId);
}

uint8_t Unit::target_acquisition_range()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->target_acquisition_range()->at(mId);
}

uint8_t Unit::sight_range()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->sight_range()->at(mId);
}

uint8_t Unit::armor_upgrade()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->armor_upgrade()->at(mId);
}

units_dat_t::unit_size_enum_t Unit::unit_size()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->unit_size()->at(mId);
}

uint8_t Unit::armor()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->armor()->at(mId);
}

units_dat_t::right_click_action_enum_t Unit::right_click_action()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->right_click_action()->at(mId);
}

uint16_t Unit::ready_sound()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t ready_sound = 0;

  try
  {
    // only unit IDs < 106 have ready_sound
    ready_sound = mDatahub.units->ready_sound()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: ready_sound(") + to_string(ready_sound) + ")");
    throw PropertyNotAvailableException(mId, "ready_sound");
  }

  return ready_sound;
}

Sfx Unit::ready_sound_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t ready_sound_id = ready_sound();

  if(ready_sound_id == Unit::sound_none)
  {
    LOG4CXX_TRACE(logger, string("Exception: ready_sound_obj(") + to_string(ready_sound_id) + ")");
    throw PropertyNotAvailableException(mId, "ready_sound_obj");
  }

  Sfx sfx(mDatahub, ready_sound_id);

  return sfx;
}

uint16_t Unit::what_sound_start()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->what_sound_start()->at(mId);
}

uint16_t Unit::what_sound_end()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->what_sound_end()->at(mId);
}

std::vector<Sfx> Unit::what_sound_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  std::vector<Sfx> sfx_vector;

  uint16_t what_sound_start_id = what_sound_start();
  uint16_t what_sound_end_id = what_sound_end();

  if((what_sound_start_id || what_sound_end_id) == Unit::sound_none)
  {
    LOG4CXX_TRACE(logger, string("Exception: what_sound_obj(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "what_sound_obj");
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
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t piss_sound_start = 0;

  try
  {
    // only unit IDs < 106 have piss_sound_start
    piss_sound_start = mDatahub.units->piss_sound_start()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: piss_sound_start(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "piss_sound_start");
  }

  return piss_sound_start;
}

uint16_t Unit::piss_sound_end()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t piss_sound_end = 0;

  try
  {
    // only unit IDs < 106 have piss_sound_end
    piss_sound_end = mDatahub.units->piss_sound_end()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: piss_sound_end(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "piss_sound_end");
  }

  return piss_sound_end;
}

std::vector<Sfx> Unit::piss_sound_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  std::vector<Sfx> sfx_vector;

  uint16_t piss_sound_start_id = piss_sound_start();
  uint16_t piss_sound_end_id = piss_sound_end();

  if((piss_sound_start_id || piss_sound_end_id) == Unit::sound_none)
  {
    LOG4CXX_TRACE(logger, string("Exception: piss_sound_obj(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "piss_sound_obj");
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
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t yes_sound_start = 0;

  try
  {
    // only unit IDs < 106 have yes_sound_start
    yes_sound_start = mDatahub.units->yes_sound_start()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: piss_sound_start(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "yes_sound_start");
  }

  return yes_sound_start;
}

uint16_t Unit::yes_sound_end()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t yes_sound_end = 0;

  try
  {
    // only unit IDs < 106 have yes_sound_end
    yes_sound_end = mDatahub.units->yes_sound_end()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: yes_sound_end(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "yes_sound_end");
  }

  return yes_sound_end;
}

std::vector<Sfx> Unit::yes_sound_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  std::vector<Sfx> sfx_vector;

  uint16_t yes_sound_start_id = yes_sound_start();
  uint16_t yes_sound_end_id = yes_sound_end();

  if((yes_sound_start_id || yes_sound_end_id) == Unit::sound_none)
  {
    LOG4CXX_TRACE(logger, string("Exception: yes_sound_obj(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "yes_sound_obj");
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
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->staredit_placement_box()->at(mId);
}

units_dat_t::addon_position_type_t* Unit::addon_position()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  units_dat_t::addon_position_type_t* addon = nullptr;

  try
  {
    // Exists only for units of ID 106-201 (buildings)
    addon = mDatahub.units->addon_position()->at(mId-106);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: addon_position(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "addon_position");
  }

  return addon;
}

units_dat_t::unit_dimension_type_t *Unit::unit_dimension()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->unit_dimension()->at(mId);
}

uint16_t Unit::portrait()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->portrait()->at(mId);
}

Portrait Unit::portrait_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t portrait_id = portrait();

  if (portrait_id == Unit::portrait_none)
  {
    LOG4CXX_TRACE(logger, string("Exception: portrait_obj(") + to_string(mId) + ")");
    throw PropertyNotAvailableException(mId, "portrait_obj");
  }

  Portrait portrait(mDatahub, portrait_id);

  return portrait;
}


uint16_t Unit::mineral_cost()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->mineral_cost()->at(mId);
}

uint16_t Unit::vespene_cost()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->vespene_cost()->at(mId);
}


uint16_t Unit::build_time()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->build_time()->at(mId);
}

uint16_t Unit::requirements()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->requirements()->at(mId);
}

units_dat_t::staredit_group_flags_type_t* Unit::staredit_group_flags()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->staredit_group_flags()->at(mId);
}

uint8_t Unit::supply_required()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->supply_required()->at(mId);
}

uint8_t Unit::space_provided()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->space_provided()->at(mId);
}

uint16_t Unit::build_score()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->build_score()->at(mId);
}

uint16_t Unit::destroy_score()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->destroy_score()->at(mId);
}

// TODO: a unit_map_string_string_tbl() might be helpful...
uint16_t Unit::unit_map_string()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->unit_map_string()->at(mId);
}

uint8_t Unit::broodwar_flag()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->broodwar_flag()->at(mId);
}

units_dat_t::staredit_availability_flags_type_t* Unit::staredit_availability_flags()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.units->staredit_availability_flags()->at(mId);
}

bool Unit::is_format_bw()
{
  return mDatahub.units->is_format_bw();
}

} /* namespace dat */
