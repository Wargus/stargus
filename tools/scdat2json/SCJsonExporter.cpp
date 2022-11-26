/*
 * SCJsonExporter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "SCJsonExporter.h"
#include "to_json.h"

// system
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace dat;



SCJsonExporter::SCJsonExporter(dat::DataHub &datahub) :
  mDatahub(datahub)
{

}

SCJsonExporter::~SCJsonExporter()
{

}

json SCJsonExporter::export_unit_dat()
{
  // TODO: check if to_json() method for units_dat_t is good
  std::shared_ptr<units_dat_t> units = mDatahub.units;

  json j;

  j["flingy"] = json(*units->flingy());

  j["subunit1"] = json(*units->subunit1());

  j["subunit2"] = json(*units->subunit2());

  j["infestation"] = json(*units->infestation());

  j["construction_animation"] = json(*units->construction_animation());

  j["unit_direction"] = json(*units->unit_direction());

  j["shield_enable"] = json(*units->shield_enable());

  j["shield_amount"] = json(*units->shield_amount());

  j["hit_points"] = json(*units->hit_points());

  j["elevation_level"] = json(*units->elevation_level());

  j["unknown"] = json(*units->unknown());

  j["rank"] = json(*units->rank());

  j["ai_computer_idle"] = json(*units->ai_computer_idle());

  j["ai_human_idle"] = json(*units->ai_human_idle());

  j["ai_return_to_idle"] = json(*units->ai_return_to_idle());

  j["ai_attack_unit"] = json(*units->ai_attack_unit());

  j["ai_attack_move"] = json(*units->ai_attack_move());

  j["ground_weapon"] = json(*units->ground_weapon());

  if(units->is_format_bw())
  {
    j["max_ground_hits"] = json(*units->max_ground_hits());
  }

  j["air_weapon"] = json(*units->air_weapon());

  if(units->is_format_bw())
  {
    j["max_air_hits"] = json(*units->max_air_hits());
  }

  j["ai_internal"] = json(*units->ai_internal());

  j["special_ability_flags"] = json(*units->special_ability_flags());

  j["target_acquisition_range"] = json(*units->target_acquisition_range());

  j["sight_range"] = json(*units->sight_range());

  j["armor_upgrade"] = json(*units->armor_upgrade());

  j["unit_size"] = json(*units->unit_size());

  j["armor"] = json(*units->armor());

  j["right_click_action"] = json(*units->right_click_action());

  j["ready_sound"] = json(*units->ready_sound());

  j["what_sound_start"] = json(*units->what_sound_start());

  j["what_sound_end"] = json(*units->what_sound_end());

  j["piss_sound_start"] = json(*units->piss_sound_start());

  j["piss_sound_end"] = json(*units->piss_sound_end());

  j["yes_sound_start"] = json(*units->yes_sound_start());

  j["yes_sound_end"] = json(*units->yes_sound_end());

  j["staredit_placement_box"] = json(*units->staredit_placement_box());

  j["addon_position"] = json(*units->addon_position());

  j["unit_dimension"] = json(*units->unit_dimension());

  j["portrait"] = json(*units->portrait());

  j["mineral_cost"] = json(*units->mineral_cost());

  j["vespene_cost"] = json(*units->vespene_cost());

  j["build_time"] = json(*units->build_time());

  j["requirements"] = json(*units->requirements());

  j["staredit_group_flags"] = json(*units->staredit_group_flags());

  j["supply_provided"] = json(*units->supply_provided());

  j["supply_required"] = json(*units->supply_required());

  j["space_required"] = json(*units->space_required());

  j["space_provided"] = json(*units->space_provided());

  j["build_score"] = json(*units->build_score());

  j["destroy_score"] = json(*units->destroy_score());

  j["unit_map_string"] = json(*units->unit_map_string());

  if(units->is_format_bw())
  {
    j["broodwar_flag"] = json(*units->broodwar_flag());
  }

  j["staredit_availability_flags"] = json(*units->staredit_availability_flags());

  return j;
}

json SCJsonExporter::export_orders_dat()
{
  std::shared_ptr<orders_dat_t> orders = mDatahub.orders;

  json j;

  j["label"] = json(*orders->label());

  j["use_weapon_targeting"] = json(*orders->use_weapon_targeting());

  j["unknown2"] = json(*orders->unknown2());

  j["unknown3"] = json(*orders->unknown3());

  j["unknown4"] = json(*orders->unknown4());

  j["unknown5"] = json(*orders->unknown5());

  j["interruptible"] = json(*orders->interruptible());

  j["unknown7"] = json(*orders->unknown7());

  j["queueable"] = json(*orders->queueable());

  j["unknown9"] = json(*orders->unknown9());

  j["unknown10"] = json(*orders->unknown10());

  j["unknown11"] = json(*orders->unknown11());

  j["unknown12"] = json(*orders->unknown12());

  j["targeting"] = json(*orders->targeting());

  j["energy"] = json(*orders->energy());

  j["animation"] = json(*orders->animation());

  j["highlight"] = json(*orders->highlight());

  j["unknown17"] = json(*orders->unknown17());

  j["obscured_order"] = json(*orders->obscured_order());

  return j;
}

json SCJsonExporter::export_weapons_dat()
{
  std::shared_ptr<weapons_dat_t> weapons = mDatahub.weapons;

  json j;

  j["label"] = json(*weapons->label());

  j["graphics"] = json(*weapons->graphics());

  j["explosion"] = json(*weapons->explosion());

  j["target_flags"] = json(*weapons->target_flags());

  j["minimum_range"] = json(*weapons->minimum_range());

  j["maximum_range"] = json(*weapons->maximum_range());

  j["damage_upgrade"] = json(*weapons->damage_upgrade());

  j["weapon_type"] = json(*weapons->weapon_type());

  j["weapon_behaviour"] = json(*weapons->weapon_behaviour());

  j["remove_after"] = json(*weapons->remove_after());

  j["explosive_type"] = json(*weapons->explosive_type());

  j["inner_splash_range"] = json(*weapons->inner_splash_range());

  j["medium_splash_range"] = json(*weapons->medium_splash_range());

  j["outer_splash_range"] = json(*weapons->outer_splash_range());

  j["damage_amount"] = json(*weapons->damage_amount());

  j["damage_bonus"] = json(*weapons->damage_bonus());

  j["weapon_cooldown"] = json(*weapons->weapon_cooldown());

  j["damage_factor"] = json(*weapons->damage_factor());

  j["attack_angle"] = json(*weapons->attack_angle());

  j["launch_spin"] = json(*weapons->launch_spin());

  j["x_offset"] = json(*weapons->x_offset());

  j["y_offset"] = json(*weapons->y_offset());

  j["error_message"] = json(*weapons->error_message());

  j["icon"] = json(*weapons->icon());

  return j;
}

json SCJsonExporter::export_flingy_dat()
{
  std::shared_ptr<flingy_dat_t> flingy = mDatahub.flingy;

  json j;

  j["sprite"] = json(*flingy->sprite());

  j["speed"] = json(*flingy->speed());

  j["acceleration"] = json(*flingy->acceleration());

  j["halt_distance"] = json(*flingy->halt_distance());

  j["turn_radius"] = json(*flingy->turn_radius());

  j["unused"] = json(*flingy->unused());

  j["movement_control"] = json(*flingy->movement_control());

  return j;
}

json SCJsonExporter::export_sprites_dat()
{
  std::shared_ptr<sprites_dat_t> sprites = mDatahub.sprites;

  json j;

  j["image"] = json(*sprites->image());

  j["health_bar"] = json(*sprites->health_bar());

  j["unknown2"] = json(*sprites->unknown2());

  j["is_visible"] = json(*sprites->is_visible());

  j["select_circle_image_size"] = json(*sprites->select_circle_image_size());

  j["select_circle_vertical_pos"] = json(*sprites->select_circle_vertical_pos());

  return j;
}

json SCJsonExporter::export_images_dat()
{
  std::shared_ptr<images_dat_t> images = mDatahub.images;

  json j;

  j["grp"] = json(*images->grp());

  j["gfx_turns"] = json(*images->gfx_turns());

  j["clickable"] = json(*images->clickable());

  j["use_full_iscript"] = json(*images->use_full_iscript());

  j["draw_if_cloaked"] = json(*images->draw_if_cloaked());

  j["draw_function"] = json(*images->draw_function());

  j["remapping"] = json(*images->remapping());

  j["iscript"] = json(*images->iscript());

  j["shield_overlay"] = json(*images->shield_overlay());

  j["attack_overlay"] =  json(*images->attack_overlay());

  j["damage_overlay"] = json(*images->damage_overlay());

  j["special_overlay"] = json(*images->special_overlay());

  j["landing_dust_overlay"] = json(*images->landing_dust_overlay());

  j["lift_off_dust_overlay"] = json(*images->lift_off_dust_overlay());

  return j;
}

json SCJsonExporter::export_sfxdata_dat()
{
  std::shared_ptr<sfxdata_dat_t> sfxdata = mDatahub.sfxdata;

  json j;

  j["sound_file"] = json(*sfxdata->sound_file());

  j["unknown1"] = json(*sfxdata->unknown1());

  j["unknown2"] = json(*sfxdata->unknown2());

  j["unknown3"] = json(*sfxdata->unknown3());

  j["unknown4"] = json(*sfxdata->unknown4());

  return j;
}

json SCJsonExporter::export_portdata_dat()
{
  std::shared_ptr<portdata_dat_t> portdata = mDatahub.portdata;

  json j;

  j["video_idle"] = json(*portdata->video_idle());

  j["video_talking"] = json(*portdata->video_talking());

  j["change_idle"] = json(*portdata->change_idle());

  j["unknown1_idle"] = json(*portdata->unknown1_idle());

  j["unknown1_talking"] = json(*portdata->unknown1_talking());

  return j;
}

json SCJsonExporter::export_upgrades_dat()
{
  std::shared_ptr<upgrades_dat_t> upgrades = mDatahub.upgrades;

  json j;

  j["mineral_cost_base"] = json(*upgrades->mineral_cost_base());

  j["mineral_cost_factor"] = json(*upgrades->mineral_cost_factor());

  j["vespene_cost_base"] = json(*upgrades->vespene_cost_base());

  j["vespene_cost_factor"] = json(*upgrades->vespene_cost_factor());

  j["research_time_base"] = json(*upgrades->research_time_base());

  j["research_time_factor"] = json(*upgrades->research_time_factor());

  j["unknown6"] = json(*upgrades->unknown6());

  j["icon"] = json(*upgrades->icon());

  j["label"] = json(*upgrades->label());

  j["race"] = json(*upgrades->race());

  j["max_repeats"] = json(*upgrades->max_repeats());

  if(upgrades->has_broodwar_flag())
  {
    j["broodwar_flags"] = json(*upgrades->broodwar_flags());
  }

  return j;
}

json SCJsonExporter::export_techdata_dat()
{
  std::shared_ptr<techdata_dat_t> techdata = mDatahub.techdata;

  json j;

  j["mineral_cost"] = json(*techdata->mineral_cost());

  j["vespene_cost"] = json(*techdata->vespene_cost());

  j["research_time"] = json(*techdata->research_time());

  j["energy_required"] = json(*techdata->energy_required());

  j["unknown4"] = json(*techdata->unknown4());

  j["icon"] = json(*techdata->icon());

  j["label"] = json(*techdata->label());

  j["race"] = json(*techdata->race());

  j["unused"] = json(*techdata->unused());

  if(techdata->has_broodwar_flag())
  {
    j["broodwar_flag"] = json(*techdata->broodwar_flag());
  }

  return j;
}

json SCJsonExporter::export_mapdata_dat()
{
  std::shared_ptr<mapdata_dat_t> mapdata = mDatahub.mapdata;

  json j;

  j["mission_dir"] = json(*mapdata->mission_dir());

  return j;
}

json SCJsonExporter::export_file_tbl(std::vector<TblEntry> &tblentry_vec)
{
  json j(tblentry_vec);

  return j;
}

