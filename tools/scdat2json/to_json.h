/*
 * to_json.h
 *
 *      Author: Andreas Volz
 */

#ifndef TO_JSON_H
#define TO_JSON_H

#include "dat/DataHub.h"
#include "dat/Unit.h"

// -> units_dat.ksy

void to_json(json &j, units_dat_t::hit_points_type_t* t);
void to_json(json &j, units_dat_t::special_ability_flags_type_t* t);
void to_json(json &j, units_dat_t::staredit_placement_box_type_t* t);
void to_json(json &j, units_dat_t::addon_position_type_t* t);
void to_json(json &j, units_dat_t::unit_dimension_type_t* t);
void to_json(json &j, units_dat_t::staredit_group_flags_type_t* t);
void to_json(json &j, units_dat_t::staredit_availability_flags_type_t* t);

// -> file_tbl.ksy

// -> specific wrapper objects in dat namespace

namespace dat {

void to_json(json &j, TblEntry t);
void to_json(json &j, Techdata t);
void to_json(json &j, Order o);
void to_json(json &j, Weapon w);
void to_json(json &j, Sfx s);
void to_json(json &j, Portrait p);
void to_json(json &j, Image i);
void to_json(json &j, Sprite s);
void to_json(json &j, Flingy f);
void to_json(json &j, Unit u);

} /* namespace dat */

#endif /* TO_JSON_H_ */
