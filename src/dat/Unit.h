/*
 * Unit.h
 *
 *      Author: Andreas Volz
 */

#ifndef UNIT_H
#define UNIT_H

// project
#include "Flingy.h"
#include "ObjectAccess.h"
#include "Portrait.h"
#include "Sfx.h"
#include "PropertyNotAvailableException.h"
#include "Weapon.h"
#include "Order.h"

namespace dat
{

class Unit : public ObjectAccess
{
public:
  Unit(DataHub &datahub, unsigned int id, const std::string &identString);
  virtual ~Unit();

  TblEntry name_tbl();

  uint8_t flingy();
  Flingy flingy_obj();

  uint16_t subunit1();
  Unit subunit1_obj();

  uint16_t subunit2();
  Unit subunit2_obj();

  uint16_t infestation();
  Unit infestation_obj();

  uint32_t construction_animation();
  Image construction_animation_obj();

  uint8_t unit_direction();

  uint8_t shield_enable();

  uint16_t shield_amount();

  uint32_t hitpoints();

  uint8_t elevation_level();

  uint8_t unknown();

  uint8_t rank();

  uint8_t ai_computer_idle();
  Order ai_computer_idle_obj();

  uint8_t ai_human_idle();
  Order ai_human_idle_obj();

  uint8_t ai_return_to_idle();
  Order ai_return_to_idle_obj();

  uint8_t ai_attack_unit();
  Order ai_attack_unit_obj();

  uint8_t ai_attack_move();
  Order ai_attack_move_obj();

  uint8_t ground_weapon();
  Weapon ground_weapon_obj();

  uint8_t max_ground_hits();

  uint8_t air_weapon();
  Weapon air_weapon_obj();

  uint8_t max_air_hits();

  uint8_t ai_internal();

  units_dat_t::special_ability_flags_type_t* special_ability_flags();

  uint8_t target_acquisition_range();

  uint8_t sight_range();

  uint8_t armor_upgrade();

  units_dat_t::unit_size_enum_t unit_size();

  uint8_t armor();

  units_dat_t::right_click_action_enum_t right_click_action();

  uint16_t ready_sound();

  Sfx ready_sound_obj();

  uint16_t what_sound_start();

  uint16_t what_sound_end();

  std::vector<Sfx> what_sound_obj();

  uint16_t piss_sound_start();

  uint16_t piss_sound_end();

  std::vector<Sfx> piss_sound_obj();

  uint16_t yes_sound_start();

  uint16_t yes_sound_end();

  std::vector<Sfx> yes_sound_obj();

  units_dat_t::staredit_placement_box_type_t* staredit_placement_box();

  units_dat_t::addon_position_type_t* addon_position();

  units_dat_t::unit_dimension_type_t *unit_dimension();

  uint16_t portrait();

  Portrait portrait_obj();

  uint16_t mineral_cost();

  uint16_t vespene_cost();

  uint16_t build_time();

  uint16_t requirements();

  units_dat_t::staredit_group_flags_type_t* staredit_group_flags();

  uint8_t supply_required();

  uint8_t space_provided();

  uint16_t build_score();

  uint16_t destroy_score();

  uint16_t unit_map_string();

  uint8_t broodwar_flag();

  units_dat_t::staredit_availability_flags_type_t* staredit_availability_flags();

  bool is_format_bw();

  std::string getIDString();

  /* constants */
  static const int portrait_none = 65535;
  static const int sound_none = 0;
  static const int construction_none = 0;
  static const int subunit_none = 228;
  static const int infestation_none = 228;

private:
  std::string mIdentString;
};

} /* namespace dat */

#endif /* UNIT_H */
