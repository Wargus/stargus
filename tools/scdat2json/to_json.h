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

void to_json(json &j, iscript_bin_t::opcode_type_t* opcode);
void to_json(json &j, std::vector<iscript_bin_t::opcode_type_t*> opcode_vec);
void to_json(json &j, iscript_bin_t::u2_type_t *u2);
void to_json(json &j, iscript_bin_t::u1_type_t *u1);
void to_json(json &j, iscript_bin_t::pos_type_t *pos);
void to_json(json &j, iscript_bin_t::playsndbtwn_type_t *snd);
void to_json(json &j, iscript_bin_t::trgcondjmp_type_t *trgcondjmp);
void to_json(json &j, iscript_bin_t::imgl_type_t *imgl);
void to_json(json &j, iscript_bin_t::sprl_type_t *sprl);
void to_json(json &j, iscript_bin_t::trgtrangecondjmp_type_t *ttcj);
void to_json(json &j, iscript_bin_t::randcondjmp_type_t *rcj);
void to_json(json &j, iscript_bin_t::playsounds_type_t *ps);
void to_json(json &j, iscript_bin_t::sprov_type_t *sprov);

// -> file_tbl.ksy

// -> specific wrapper objects in dat namespace

namespace dat {

void to_json(json &j, TblEntry t);
void to_json(json &j, Upgrade u);
void to_json(json &j, Techdata t);
void to_json(json &j, Order o);
void to_json(json &j, Weapon w);
void to_json(json &j, Sfx s);
void to_json(json &j, Portrait p);
void to_json(json &j, Image i);
void to_json(json &j, Sprite s);
void to_json(json &j, Flingy f);
void to_json(json &j, Unit u);
void to_json(json &j, IScript i);

} /* namespace dat */

#endif /* TO_JSON_H_ */
