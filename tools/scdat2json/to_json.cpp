#include "to_json.h"

#include <iostream>

using namespace std;
using namespace dat;

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

namespace dat {

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

void to_json(json &j, Sfx s)
{
  j = json{
    {"id", s.getID()},
    {"sound_file", s.sound_file()},
    {"sound_file_tbl", s.sound_file_tbl()}
  };
}

void to_json(json &j, Portrait p)
{
  j = json{
    {"id", p.getID()},
    {"video_idle", p.video_idle()},
    {"video_idle_tbl", p.video_idle_tbl()}
  };
}

void to_json(json &j, Image i)
{
  j["id"] = json(i.getID());
  j["grp"] = json(i.grp());
  j["grp_tbl"] = json(i.grp_tbl());
  j["gfx_turns"] = json(i.gfx_turns());
  j["clickable"] = json(i.clickable());
  j["use_full_iscript"] = json(i.use_full_iscript());
  j["draw_if_cloaked"] = json(i.draw_if_cloaked());
  j["draw_function"] = json(i.draw_function());
  j["remapping"] = json(i.remapping());
  j["iscript_id"] = json(i.iscript_id());

  j["shield_overlay"] = json(i.shield_overlay());
  try
  {
    j["shield_overlay_tbl"] = json(i.shield_overlay_tbl());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["attack_overlay"] = json(i.attack_overlay());
  try
  {
    j["attack_overlay_tbl"] = json(i.attack_overlay_tbl());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["damage_overlay"] = json(i.damage_overlay());
  try
  {
    j["damage_overlay_tbl"] = json(i.damage_overlay_tbl());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["special_overlay"] = json(i.special_overlay());
  try
  {
    j["special_overlay_tbl"] = json(i.special_overlay_tbl());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["landing_dust_overlay"] = json(i.landing_dust_overlay());
  try
  {
    j["landing_dust_overlay_tbl"] = json(i.landing_dust_overlay_tbl());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }
}

void to_json(json &j, Sprite s)
{
  j["id"] = json(s.getID());
  j["image"] = json(s.image());
  j["image_obj"] = json(s.image());

  try
  {
    j["health_bar"] = json(s.health_bar());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["unknown2"] = json(s.unknown2());
  j["is_visible"] = json(s.is_visible());

  try
  {
    j["select_circle_image_size"] = json(s.select_circle_image_size());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["select_circle_vertical_pos"] = json(s.select_circle_vertical_pos());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }
}

void to_json(json &j, Flingy f)
{
  j = json{
    {"id", f.getID()},
    {"sprite", f.sprite()},
    {"sprite_obj", f.sprite_obj()},
    {"speed", f.speed()},
    {"acceleration", f.acceleration()},
    {"halt_distance", f.halt_distance()},
    {"turn_radius", f.turn_radius()},
    {"unused", f.unused()},
    {"movement_control", f.movement_control()}
  };
}

void to_json(json &j, Unit u)
{
  j["id"] = json(u.getID());
  j["id_string"] = json(u.getIDString());
  j["name_tbl"] = json(u.name_tbl());
  j["flingy"] = json(u.flingy());
  j["flingy_obj"] = json(u.flingy_obj());
  j["subunit1"] = json(u.subunit1());

  try
  {
    j["subunit1_obj"] = json(u.subunit1_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["subunit2"] = json(u.subunit2());

  try
  {
    j["subunit2_obj"] = json(u.subunit2_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["infestation"] = json(u.infestation());
    j["infestation_obj"] = json(u.infestation_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["construction_animation"] = json(u.construction_animation());
    j["construction_animation_obj"] = json(u.construction_animation_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["unit_direction"] = json(u.unit_direction());
  j["shield_enable"] = json(u.shield_enable());
  j["shield_amount"] = json(u.shield_amount());
  j["hitpoints"] = json(u.hitpoints());
  j["elevation_level"] = json(u.elevation_level());
  j["unknown"] = json(u.unknown());
  j["rank"] = json(u.rank());
  j["ai_computer_idle"] = json(u.ai_computer_idle());
  j["ai_human_idle"] = json(u.ai_human_idle());
  j["ai_return_to_idle"] = json(u.ai_return_to_idle());
  j["ai_attack_unit"] = json(u.ai_attack_unit());
  j["ai_attack_move"] = json(u.ai_attack_move());
  j["ground_weapon"] = json(u.ground_weapon());

  if(u.is_format_bw())
  {
    j["max_ground_hits"] = json(u.max_ground_hits());
  }

  j["air_weapon"] = json(u.air_weapon());

  if(u.is_format_bw())
  {
    j["max_air_hits"] = json(u.max_air_hits());
  }

  j["ai_internal"] = json(u.ai_internal());
  j["special_ability_flags"] = json(u.special_ability_flags());
  j["target_acquisition_range"] = json(u.target_acquisition_range());
  j["sight_range"] = json(u.sight_range());
  j["armor_upgrade"] = json(u.armor_upgrade());
  j["unit_size"] = json(u.unit_size());
  j["armor"] = json(u.armor());
  j["right_click_action"] = json(u.right_click_action());

  try
  {
    j["ready_sound"] = json(u.ready_sound());
    j["ready_sound_obj"] = json(u.ready_sound_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["what_sound_start"] = json(u.what_sound_start());
    j["what_sound_end"] = json(u.what_sound_end());
    j["what_sound_obj"] = json(u.what_sound_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["piss_sound_start"] = json(u.piss_sound_start());
    j["piss_sound_end"] = json(u.piss_sound_end());
    j["piss_sound_obj"] = json(u.piss_sound_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["what_sound_start"] = json(u.what_sound_start());
    j["what_sound_end"] = json(u.what_sound_end());
    j["what_sound_obj"] = json(u.what_sound_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["yes_sound_start"] = json(u.yes_sound_start());
    j["yes_sound_end"] = json(u.yes_sound_end());
    j["yes_sound_obj"] = json(u.yes_sound_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["staredit_placement_box"] = json(u.staredit_placement_box());

  try
  {
    j["addon_position"] = json(u.addon_position());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["unit_dimension"] = json(u.unit_dimension());
  j["portrait"] = json(u.portrait());

  try
  {
    j["portrait_obj"] = json(u.portrait_obj());
  }
  catch(PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["mineral_cost"] = json(u.mineral_cost());
  j["vespene_cost"] = json(u.vespene_cost());
  j["build_time"] = json(u.build_time());
  j["requirements"] = json(u.requirements());
  j["staredit_group_flags"] = json(u.staredit_group_flags());
  j["supply_required"] = json(u.supply_required());
  j["space_provided"] = json(u.space_provided());
  j["build_score"] = json(u.build_score());
  j["destroy_score"] = json(u.destroy_score());
  j["unit_map_string"] = json(u.unit_map_string());

  if(u.is_format_bw())
  {
    j["broodwar_flag"] = json(u.broodwar_flag());
  }

  j["is_format_bw"] = json(u.is_format_bw());
}

} /* namespace dat */
