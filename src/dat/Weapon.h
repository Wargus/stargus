/*
 * Weapon.h
 *
  *      Author: Andreas Volz
 */

#ifndef WEAPON_H
#define WEAPON_H

#include "DataHub.h"
#include "ObjectAccess.h"
#include "PropertyNotAvailableException.h"
#include "Flingy.h"

namespace dat
{

class Weapon : public ObjectAccess
{
public:
  Weapon(DataHub &datahub, unsigned int id);
  virtual ~Weapon();

  uint16_t label();
  TblEntry label_tbl();

  uint32_t graphics();
  Flingy graphics_obj();

  // TODO: make enum as return
  uint8_t explosion();

  uint16_t target_flags();

  uint32_t minimum_range();

  uint32_t maximum_range();

  // TODO: Pointer to [upgrades.dat]
  uint8_t damage_upgrade();

  uint8_t weapon_type();

  // TODO: make enum as return
  uint8_t weapon_behaviour();

  uint8_t remove_after();

  // TODO: make enum as return
  uint8_t explosive_type();

  uint16_t inner_splash_range();

  uint16_t medium_splash_range();

  uint16_t outer_splash_range();

  uint16_t damage_amount();

  uint16_t damage_bonus();

  uint8_t weapon_cooldown();

  uint8_t damage_factor();

  uint8_t attack_angle();

  uint8_t launch_spin();

  uint8_t x_offset();

  uint8_t y_offset();

  uint16_t error_message();

  TblEntry error_message_tbl();

  uint16_t icon();

  /* constants */

  static const int graphics_none = 0;

private:

};

} /* namespace dat */

#endif /* WEAPON_H */
