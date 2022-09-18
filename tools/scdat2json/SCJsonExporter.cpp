/*
 * SCJsonExporter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "SCJsonExporter.h"

// system
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// to_json() -> units_dat.ksy

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

// to_json() -> file_tbl.ksy

void to_json(json &j, TblEntry t)
{
  j = json{
    {"name1", t.name1},
    {"name2", t.name2},
    {"name3", t.name3},
    {"shortcut_pos", t.shortcut_pos},
    {"shortcut", t.shortcut}
  };
}

SCJsonExporter::SCJsonExporter(dat::DataHub &datahub) :
  mDatahub(datahub)
{

}

SCJsonExporter::~SCJsonExporter()
{

}

json SCJsonExporter::export_unit_dat()
{
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

  return j;
}

json SCJsonExporter::export_orders_dat()
{
  std::shared_ptr<orders_dat_t> orders = mDatahub.orders;

  json j;

  json j_label(*orders->label());
  j["label"] = j_label;

  json j_use_weapon_targeting(*orders->use_weapon_targeting());
  j["use_weapon_targeting"] = j_use_weapon_targeting;

  json j_unknown2(*orders->unknown2());
  j["unknown2"] = j_unknown2;

  json j_unknown3(*orders->unknown3());
  j["unknown3"] = j_unknown3;

  json j_unknown4(*orders->unknown4());
  j["unknown4"] = j_unknown4;

  json j_unknown5(*orders->unknown5());
  j["unknown5"] = j_unknown5;

  json j_interruptible(*orders->interruptible());
  j["interruptible"] = j_interruptible;

  json j_unknown7(*orders->unknown7());
  j["unknown7"] = j_unknown7;

  json j_queueable(*orders->queueable());
  j["queueable"] = j_queueable;

  json j_unknown9(*orders->unknown9());
  j["unknown9"] = j_unknown9;

  json j_unknown10(*orders->unknown10());
  j["unknown10"] = j_unknown10;

  json j_unknown11(*orders->unknown11());
  j["unknown11"] = j_unknown11;

  json j_unknown12(*orders->unknown12());
  j["unknown12"] = j_unknown12;

  json j_targeting(*orders->targeting());
  j["targeting"] = j_targeting;

  json j_energy(*orders->energy());
  j["energy"] = j_energy;

  json j_animation(*orders->animation());
  j["animation"] = j_animation;

  json j_highlight(*orders->highlight());
  j["highlight"] = j_highlight;

  json j_unknown17(*orders->unknown17());
  j["unknown17"] = j_unknown17;

  json j_obscured_order(*orders->obscured_order());
  j["obscured_order"] = j_obscured_order;

  return j;
}

json SCJsonExporter::export_weapons_dat()
{
  std::shared_ptr<weapons_dat_t> weapons = mDatahub.weapons;

  json j;

  json j_label(*weapons->label());
  j["label"] = j_label;

  json j_graphics(*weapons->graphics());
  j["graphics"] = j_graphics;

  json j_explosion(*weapons->explosion());
  j["explosion"] = j_explosion;

  json j_target_flags(*weapons->target_flags());
  j["target_flags"] = j_target_flags;

  json j_minimum_range(*weapons->minimum_range());
  j["minimum_range"] = j_minimum_range;

  json j_maximum_range(*weapons->maximum_range());
  j["maximum_range"] = j_maximum_range;

  json j_damage_upgrade(*weapons->damage_upgrade());
  j["damage_upgrade"] = j_damage_upgrade;

  json j_weapon_type(*weapons->weapon_type());
  j["weapon_type"] = j_weapon_type;

  json j_weapon_behaviour(*weapons->weapon_behaviour());
  j["weapon_behaviour"] = j_weapon_behaviour;

  json j_remove_after(*weapons->remove_after());
  j["remove_after"] = j_remove_after;

  json j_explosive_type(*weapons->explosive_type());
  j["explosive_type"] = j_explosive_type;

  json j_inner_splash_range(*weapons->inner_splash_range());
  j["inner_splash_range"] = j_inner_splash_range;

  json j_medium_splash_range(*weapons->medium_splash_range());
  j["medium_splash_range"] = j_medium_splash_range;

  json j_outer_splash_range(*weapons->outer_splash_range());
  j["outer_splash_range"] = j_outer_splash_range;

  json j_damage_amount(*weapons->damage_amount());
  j["damage_amount"] = j_damage_amount;

  json j_damage_bonus(*weapons->damage_bonus());
  j["damage_bonus"] = j_damage_bonus;

  json j_weapon_cooldown(*weapons->weapon_cooldown());
  j["weapon_cooldown"] = j_weapon_cooldown;

  json j_damage_factor(*weapons->damage_factor());
  j["damage_factor"] = j_damage_factor;

  json j_attack_angle(*weapons->attack_angle());
  j["attack_angle"] = j_attack_angle;

  json j_launch_spin(*weapons->launch_spin());
  j["launch_spin"] = j_launch_spin;

  json j_x_offset(*weapons->x_offset());
  j["x_offset"] = j_x_offset;

  json j_y_offset(*weapons->y_offset());
  j["y_offset"] = j_y_offset;

  json j_error_message(*weapons->error_message());
  j["error_message"] = j_error_message;

  json j_icon(*weapons->icon());
  j["icon"] = j_icon;

  return j;
}

json SCJsonExporter::export_flingy_dat()
{
  std::shared_ptr<flingy_dat_t> flingy = mDatahub.flingy;

  json j;

  json j_sprite(*flingy->sprite());
  j["sprite"] = j_sprite;

  json j_speed(*flingy->speed());
  j["speed"] = j_speed;

  json j_acceleration(*flingy->acceleration());
  j["acceleration"] = j_acceleration;

  json j_halt_distance(*flingy->halt_distance());
  j["halt_distance"] = j_halt_distance;

  json j_turn_radius(*flingy->turn_radius());
  j["turn_radius"] = j_turn_radius;

  json j_unused(*flingy->unused());
  j["unused"] = j_unused;

  json j_movement_control(*flingy->movement_control());
  j["movement_control"] = j_movement_control;

  return j;
}

json SCJsonExporter::export_sprites_dat()
{
  std::shared_ptr<sprites_dat_t> sprites = mDatahub.sprites;

  json j;

  json j_image(*sprites->image());
  j["image"] = j_image;

  json j_health_bar(*sprites->health_bar());
  j["health_bar"] = j_health_bar;

  json j_unknown2(*sprites->unknown2());
  j["unknown2"] = j_unknown2;

  json j_is_visible(*sprites->is_visible());
  j["is_visible"] = j_is_visible;

  json j_select_circle_image_size(*sprites->select_circle_image_size());
  j["select_circle_image_size"] = j_select_circle_image_size;

  json j_select_circle_vertical_pos(*sprites->select_circle_vertical_pos());
  j["select_circle_vertical_pos"] = j_select_circle_vertical_pos;

  return j;
}

json SCJsonExporter::export_images_dat()
{
  std::shared_ptr<images_dat_t> images = mDatahub.images;

  json j;

  json j_grp(*images->grp());
  j["grp"] = j_grp;

  json j_gfx_turns(*images->gfx_turns());
  j["gfx_turns"] = j_gfx_turns;

  json j_clickable(*images->clickable());
  j["clickable"] = j_clickable;

  json j_use_full_iscript(*images->use_full_iscript());
  j["use_full_iscript"] = j_use_full_iscript;

  json j_draw_if_cloaked(*images->draw_if_cloaked());
  j["draw_if_cloaked"] = j_draw_if_cloaked;

  json j_draw_function(*images->draw_function());
  j["draw_function"] = j_draw_function;

  json j_remapping(*images->remapping());
  j["remapping"] = j_remapping;

  json j_iscript_id(*images->iscript_id());
  j["iscript_id"] = j_iscript_id;

  json j_shield_overlay(*images->shield_overlay());
  j["shield_overlay"] = j_shield_overlay;

  json j_attack_overlay(*images->attack_overlay());
  j["attack_overlay"] = j_attack_overlay;

  json j_damage_overlay(*images->damage_overlay());
  j["damage_overlay"] = j_damage_overlay;

  json j_special_overlay(*images->special_overlay());
  j["special_overlay"] = j_special_overlay;

  json j_landing_dust_overlay(*images->landing_dust_overlay());
  j["landing_dust_overlay"] = j_landing_dust_overlay;

  json j_lift_off_dust_overlay(*images->lift_off_dust_overlay());
  j["lift_off_dust_overlay"] = j_lift_off_dust_overlay;

  return j;
}

json SCJsonExporter::export_sfxdata_dat()
{
  std::shared_ptr<sfxdata_dat_t> sfxdata = mDatahub.sfxdata;

  json j;

  json j_sound_file(*sfxdata->sound_file());
  j["sound_file"] = j_sound_file;

  json j_unknown1(*sfxdata->unknown1());
  j["unknown1"] = j_unknown1;

  json j_unknown2(*sfxdata->unknown2());
  j["unknown2"] = j_unknown2;

  json j_unknown3(*sfxdata->unknown3());
  j["unknown3"] = j_unknown3;

  json j_unknown4(*sfxdata->unknown4());
  j["unknown4"] = j_unknown4;

  return j;
}

json SCJsonExporter::export_portdata_dat()
{
  std::shared_ptr<portdata_dat_t> portdata = mDatahub.portdata;

  json j;

  json j_video_idle(*portdata->video_idle());
  j["video_idle"] = j_video_idle;

  json j_video_talking(*portdata->video_talking());
  j["video_talking"] = j_video_talking;

  json j_change_idle(*portdata->change_idle());
  j["change_idle"] = j_change_idle;

  json j_unknown1_idle(*portdata->unknown1_idle());
  j["unknown1_idle"] = j_unknown1_idle;

  json j_unknown1_talking(*portdata->unknown1_talking());
  j["unknown1_talking"] = j_unknown1_talking;

  return j;
}

json SCJsonExporter::export_upgrades_dat()
{
  std::shared_ptr<upgrades_dat_t> upgrades = mDatahub.upgrades;

  json j;

  json j_mineral_cost_base(*upgrades->mineral_cost_base());
  j["mineral_cost_base"] = j_mineral_cost_base;

  json j_mineral_cost_factor(*upgrades->mineral_cost_factor());
  j["mineral_cost_factor"] = j_mineral_cost_factor;

  json j_vespene_cost_base(*upgrades->vespene_cost_base());
  j["vespene_cost_base"] = j_vespene_cost_base;

  json j_vespene_cost_factor(*upgrades->vespene_cost_factor());
  j["vespene_cost_factor"] = j_vespene_cost_factor;

  json j_research_time_base(*upgrades->research_time_base());
  j["research_time_base"] = j_research_time_base;

  json j_research_time_factor(*upgrades->research_time_factor());
  j["research_time_factor"] = j_research_time_factor;

  json j_unknown6(*upgrades->unknown6());
  j["unknown6"] = j_unknown6;

  json j_icon(*upgrades->icon());
  j["icon"] = j_icon;

  json j_label(*upgrades->label());
  j["label"] = j_label;

  json j_race(*upgrades->race());
  j["race"] = j_race;

  json j_max_repeats(*upgrades->max_repeats());
  j["max_repeats"] = j_max_repeats;

  if(upgrades->has_broodwar_flag())
  {
    json j_broodwar_flags(*upgrades->broodwar_flags());
    j["broodwar_flags"] = j_broodwar_flags;
  }

  return j;
}

json SCJsonExporter::export_techdata_dat()
{
  std::shared_ptr<techdata_dat_t> techdata = mDatahub.techdata;

  json j;

  json j_mineral_cost(*techdata->mineral_cost());
  j["mineral_cost"] = j_mineral_cost;

  json j_vespene_cost(*techdata->vespene_cost());
  j["vespene_cost"] = j_vespene_cost;

  json j_research_time(*techdata->research_time());
  j["research_time"] = j_research_time;

  json j_energy_required(*techdata->energy_required());
  j["energy_required"] = j_energy_required;

  json j_unknown4(*techdata->unknown4());
  j["unknown4"] = j_unknown4;

  json j_icon(*techdata->icon());
  j["icon"] = j_icon;

  json j_label(*techdata->label());
  j["label"] = j_label;

  json j_race(*techdata->race());
  j["race"] = j_race;

  json j_unused(*techdata->unused());
  j["unused"] = j_unused;

  if(techdata->has_broodwar_flag())
  {
    json j_broodwar_flag(*techdata->broodwar_flag());
    j["broodwar_flag"] = j_broodwar_flag;
  }

  return j;
}

json SCJsonExporter::export_mapdata_dat()
{
  std::shared_ptr<mapdata_dat_t> mapdata = mDatahub.mapdata;

  json j;

  json j_mission_dir(*mapdata->mission_dir());
  j["mission_dir"] = j_mission_dir;

  return j;
}

json SCJsonExporter::export_file_tbl(std::vector<TblEntry> &tblentry_vec)
{
  json j(tblentry_vec);

  return j;
}

void SCJsonExporter::save(json &j, const std::string &file, bool pretty)
{
  std::ofstream filestream(file);

  if(pretty)
  {
    filestream << std::setw(4) << j;
  }
  else
  {
    filestream << j;
  }
}
