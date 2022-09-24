/*
 * Weapon.cpp
 *
 *      Author: Andreas Volz
 */

#include "Weapon.h"
#include "Logger.h"

using namespace std;

static Logger logger = Logger("startool.dat.Weapon");

namespace dat
{

Weapon::Weapon(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

Weapon::~Weapon()
{

}

uint16_t Weapon::label()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->label()->at(mId);
}

TblEntry Weapon::label_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.stat_txt_weapons_tbl_vec.at(mId);
}

uint32_t Weapon::graphics()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->graphics()->at(mId);
}

Flingy Weapon::graphics_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  uint32_t graphics_id = graphics();


  if(graphics_id == Weapon::graphics_none)
  {
    throw PropertyNotAvailableException(mId, "graphics_obj");
  }

  return Flingy(mDatahub, graphics());
}

uint8_t Weapon::explosion()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->explosion()->at(mId);
}

uint16_t Weapon::target_flags()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->target_flags()->at(mId);
}

uint32_t Weapon::minimum_range()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->minimum_range()->at(mId);
}

uint32_t Weapon::maximum_range()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->maximum_range()->at(mId);
}

uint8_t Weapon::damage_upgrade()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->damage_upgrade()->at(mId);
}

uint8_t Weapon::weapon_type()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->weapon_type()->at(mId);
}

uint8_t Weapon::weapon_behaviour()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->weapon_behaviour()->at(mId);
}

uint8_t Weapon::remove_after()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->remove_after()->at(mId);
}

uint8_t Weapon::explosive_type()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->explosive_type()->at(mId);
}

uint16_t Weapon::inner_splash_range()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->inner_splash_range()->at(mId);
}

uint16_t Weapon::medium_splash_range()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->medium_splash_range()->at(mId);
}

uint16_t Weapon::outer_splash_range()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->outer_splash_range()->at(mId);
}

uint16_t Weapon::damage_amount()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->damage_amount()->at(mId);
}

uint16_t Weapon::damage_bonus()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->damage_amount()->at(mId);
}

uint8_t Weapon::weapon_cooldown()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->weapon_cooldown()->at(mId);
}

uint8_t Weapon::damage_factor()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->damage_factor()->at(mId);
}

uint8_t Weapon::attack_angle()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->attack_angle()->at(mId);
}

uint8_t Weapon::launch_spin()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->launch_spin()->at(mId);
}

uint8_t Weapon::x_offset()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->x_offset()->at(mId);
}


uint8_t Weapon::y_offset()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->y_offset()->at(mId);
}

uint16_t Weapon::error_message()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->error_message()->at(mId);
}

TblEntry Weapon::error_message_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.stat_txt_error_messages_tbl_vec.at(mId);
}

uint16_t Weapon::icon()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.weapons->icon()->at(mId);
}


} /* namespace dat */
