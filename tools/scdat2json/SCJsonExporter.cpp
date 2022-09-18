/*
 * SCJsonExporter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "SCJsonExporter.h"

// system
#include <iostream>

using namespace std;

SCJsonExporter::SCJsonExporter(dat::DataHub &datahub) :
  mDatahub(datahub)
{

}

SCJsonExporter::~SCJsonExporter()
{

}

void to_json(json &j, units_dat_t::hit_points_type_t* t)
{
  j = json{ {"hitpoints", t->hitpoints()} };
}

void to_json(json &j, units_dat_t::special_ability_flags_type_t* t)
{
  j = json{
    {"building", t->building()},
    {"addon", t->addon()},
    {"flyer", t->flyer()},
    {"resourceminer", t->resourceminer()},
    {"subunit", t->subunit()},
    {"flyingbuilding", t->flyingbuilding()},
    {"hero", t->hero()},
    {"regenerate", t->regenerate()},
    {"animatedidle", t->animatedidle()},
    {"cloakable", t->cloakable()},
    {"twounitsinoneegg", t->twounitsinoneegg()},
    {"singleentity", t->singleentity()},
    {"resourcedepot", t->resourcedepot()},
    {"resourcecontainter", t->resourcecontainter()},
    {"robotic", t->robotic()},
    {"detector", t->detector()},
    {"organic", t->organic()},
    {"requirescreep", t->requirescreep()},
    {"unused", t->unused()},
    {"requirespsi", t->requirespsi()},
    {"burrowable", t->burrowable()},
    {"spellcaster", t->spellcaster()},
    {"permanentcloak", t->permanentcloak()},
    {"pickupitem", t->pickupitem()},
    {"ignoresupplycheck", t->ignoresupplycheck()},
    {"usemediumoverlays", t->usemediumoverlays()},
    {"uselargeoverlays", t->uselargeoverlays()},
    {"battlereactions", t->battlereactions()},
    {"fullautoattack", t->fullautoattack()},
    {"invincible", t->invincible()},
    {"mechanical", t->mechanical()},
    {"producesunits", t->producesunits()}
  };
}

void to_json(json &j, units_dat_t::staredit_placement_box_type_t* t)
{
  j = json{ {"width", t->width()}, {"height", t->height()} };
}

void to_json(json &j, units_dat_t::addon_position_type_t* t)
{
  j = json{ {"horizontal", t->horizontal()}, {"vertical", t->vertical()} };
}

void to_json(json &j, units_dat_t::unit_dimension_type_t* t)
{
  j = json{ {"left", t->left()}, {"up", t->up()}, {"right", t->right()}, {"down", t->down()} };
}

void to_json(json &j, units_dat_t::staredit_group_flags_type_t* t)
{
  j = json{
    {"zerg", t->zerg()},
    {"terran", t->terran()},
    {"protoss", t->protoss()},
    {"men", t->men()},
    {"building", t->building()},
    {"factory", t->factory()},
    {"independent", t->independent()},
    {"neutral", t->neutral()}
  };
}

void to_json(json &j, units_dat_t::staredit_availability_flags_type_t* t)
{
  j = json{
    {"non_neutral", t->non_neutral()},
    {"unit_listing", t->unit_listing()},
    {"mission_briefing", t->mission_briefing()},
    {"player_settings", t->player_settings()},
    {"all_races", t->all_races()},
    {"set_doodad_state", t->set_doodad_state()},
    {"non_location_triggers", t->non_location_triggers()},
    {"unit_hero_settings", t->unit_hero_settings()},
    {"location_triggers", t->location_triggers()},
    {"brood_war_only", t->brood_war_only()}
  };
}

bool SCJsonExporter::export_unit_dat()
{
  bool result = true;

  std::shared_ptr<units_dat_t> units = mDatahub.units;

  json j;

  json j_flingy(*units->flingy());
  j["flingy"] = j_flingy;

  json j_subunit1(*units->subunit1());
  j["subunit1"] = j_subunit1;

  json j_subunit2(*units->subunit2());
  j["subunit2"] = j_subunit2;

  json j_infestation(*units->infestation());
  j["infestation"] = j_infestation;

  json j_construction_animation(*units->construction_animation());
  j["construction_animation"] = j_construction_animation;

  json j_unit_direction(*units->unit_direction());
  j["unit_direction"] = j_unit_direction;

  json j_shield_enable(*units->shield_enable());
  j["shield_enable"] = j_shield_enable;

  json j_shield_amount(*units->shield_amount());
  j["shield_amount"] = j_shield_amount;

  json j_hit_points(*units->hit_points());
  j["hit_points"] = j_hit_points;

  json j_elevation_level(*units->elevation_level());
  j["elevation_level"] = j_elevation_level;

  json j_unknown(*units->unknown());
  j["unknown"] = j_unknown;

  json j_rank(*units->rank());
  j["rank"] = j_rank;

  json j_ai_computer_idle(*units->ai_computer_idle());
  j["ai_computer_idle"] = j_ai_computer_idle;

  json j_ai_human_idle(*units->ai_human_idle());
  j["ai_human_idle"] = j_ai_human_idle;

  json j_ai_return_to_idle(*units->ai_return_to_idle());
  j["ai_return_to_idle"] = j_ai_return_to_idle;

  json j_ai_attack_unit(*units->ai_attack_unit());
  j["ai_attack_unit"] = j_ai_attack_unit;

  json j_ai_attack_move(*units->ai_attack_move());
  j["ai_attack_move"] = j_ai_attack_move;

  json j_ground_weapon(*units->ground_weapon());
  j["ground_weapon"] = j_ground_weapon;

  if(units->is_format_bw())
  {
    json j_max_ground_hits(*units->max_ground_hits());
    j["max_ground_hits"] = j_max_ground_hits;
  }

  json j_air_weapon(*units->air_weapon());
  j["air_weapon"] = j_air_weapon;

  if(units->is_format_bw())
  {
    json j_max_air_hits(*units->max_air_hits());
    j["max_air_hits"] = j_max_air_hits;
  }

  json j_ai_internal(*units->ai_internal());
  j["ai_internal"] = j_ai_internal;

  json j_special_ability_flags(*units->special_ability_flags());
  j["special_ability_flags"] = j_special_ability_flags;

  json j_target_acquisition_range(*units->target_acquisition_range());
  j["target_acquisition_range"] = j_target_acquisition_range;

  json j_sight_range(*units->sight_range());
  j["sight_range"] = j_sight_range;

  json j_armor_upgrade(*units->armor_upgrade());
  j["armor_upgrade"] = j_armor_upgrade;

  json j_unit_size(*units->unit_size());
  j["unit_size"] = j_unit_size;

  json j_armor(*units->armor());
  j["armor"] = j_armor;

  json j_right_click_action(*units->right_click_action());
  j["right_click_action"] = j_right_click_action;

  json j_ready_sound(*units->ready_sound());
  j["ready_sound"] = j_ready_sound;

  json j_what_sound_start(*units->what_sound_start());
  j["what_sound_start"] = j_what_sound_start;

  json j_what_sound_end(*units->what_sound_end());
  j["what_sound_end"] = j_what_sound_end;

  json j_piss_sound_start(*units->piss_sound_start());
  j["piss_sound_start"] = j_piss_sound_start;

  json j_piss_sound_end(*units->piss_sound_end());
  j["piss_sound_end"] = j_piss_sound_end;

  json j_yes_sound_start(*units->yes_sound_start());
  j["yes_sound_start"] = j_yes_sound_start;

  json j_yes_sound_end(*units->yes_sound_end());
  j["yes_sound_end"] = j_yes_sound_end;

  json j_staredit_placement_box(*units->staredit_placement_box());
  j["staredit_placement_box"] = j_staredit_placement_box;

  json j_addon_position(*units->addon_position());
  j["addon_position"] = j_addon_position;

  json j_unit_dimension(*units->unit_dimension());
  j["unit_dimension"] = j_unit_dimension;

  json j_portrait(*units->portrait());
  j["portrait"] = j_portrait;

  json j_mineral_cost(*units->mineral_cost());
  j["mineral_cost"] = j_mineral_cost;

  json j_vespene_cost(*units->vespene_cost());
  j["vespene_cost"] = j_vespene_cost;

  json j_build_time(*units->build_time());
  j["build_time"] = j_build_time;

  json j_requirements(*units->requirements());
  j["requirements"] = j_requirements;

  json j_staredit_group_flags(*units->staredit_group_flags());
  j["staredit_group_flags"] = j_staredit_group_flags;

  json j_supply_provided(*units->supply_provided());
  j["supply_provided"] = j_supply_provided;

  json j_supply_required(*units->supply_required());
  j["supply_required"] = j_supply_required;

  json j_space_required(*units->space_required());
  j["space_required"] = j_space_required;

  json j_space_provided(*units->space_provided());
  j["space_provided"] = j_space_provided;

  json j_build_score(*units->build_score());
  j["build_score"] = j_build_score;

  json j_destroy_score(*units->destroy_score());
  j["destroy_score"] = j_destroy_score;

  json j_unit_map_string(*units->unit_map_string());
  j["unit_map_string"] = j_unit_map_string;

  if(units->is_format_bw())
  {
    json j_broodwar_flag(*units->broodwar_flag());
    j["broodwar_flag"] = j_broodwar_flag;
  }

  json j_staredit_availability_flags(*units->staredit_availability_flags());
  j["staredit_availability_flags"] = j_staredit_availability_flags;

  cout << std::setw(4) << j << endl;

  return result;
}
