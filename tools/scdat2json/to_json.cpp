#include "to_json.h"
#include "StringUtil.h"

#include <iostream>

using namespace std;
using namespace dat;



void to_json(json &j, units_dat_t::hit_points_type_t *t)
{
  j = json{ {"hitpoints", t->hitpoints()} };
}

void to_json(json &j, units_dat_t::special_ability_flags_type_t *t)
{
  j = json
  {
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

void to_json(json &j, units_dat_t::staredit_placement_box_type_t *t)
{
  j = json{ {"width", t->width()}, {"height", t->height()} };
}

void to_json(json &j, units_dat_t::addon_position_type_t *t)
{
  j = json{ {"horizontal", t->horizontal()}, {"vertical", t->vertical()} };
}

void to_json(json &j, units_dat_t::unit_dimension_type_t *t)
{
  j = json{ {"left", t->left()}, {"up", t->up()}, {"right", t->right()}, {"down", t->down()} };
}

void to_json(json &j, units_dat_t::staredit_group_flags_type_t *t)
{
  j = json
  {
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

void to_json(json &j, units_dat_t::staredit_availability_flags_type_t *t)
{
  j = json
  {
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

NLOHMANN_JSON_SERIALIZE_ENUM(iscript_bin_t::opcode_t,
{
  {iscript_bin_t::opcode_t::OPCODE_PLAYFRAM, "playfram"},
  {iscript_bin_t::opcode_t::OPCODE_PLAYFRAMTILE, "playframtile"},
  {iscript_bin_t::opcode_t::OPCODE_SETHORPOS, "sethorpos"},
  {iscript_bin_t::opcode_t::OPCODE_SETVERTPOS, "setvertpos"},
  {iscript_bin_t::opcode_t::OPCODE_SETPOS, "setpos"},
  {iscript_bin_t::opcode_t::OPCODE_WAIT, "wait"},
  {iscript_bin_t::opcode_t::OPCODE_WAITRAND, "waitrand"},
  {iscript_bin_t::opcode_t::OPCODE_GOTO, "goto"},
  {iscript_bin_t::opcode_t::OPCODE_IMGOL, "imgol"},
  {iscript_bin_t::opcode_t::OPCODE_IMGUL, "imgul"},
  {iscript_bin_t::opcode_t::OPCODE_IMGOLORIG, "imgolorig"},
  {iscript_bin_t::opcode_t::OPCODE_SWITCHUL, "switchul"},
  {iscript_bin_t::opcode_t::OPCODE_UNKNOWN_0C, "unknown_0c"},
  {iscript_bin_t::opcode_t::OPCODE_IMGOLUSELO, "imgoluselo"},
  {iscript_bin_t::opcode_t::OPCODE_IMGULUSELO, "imguluselo"},
  {iscript_bin_t::opcode_t::OPCODE_SPROL, "sprol"},
  {iscript_bin_t::opcode_t::OPCODE_HIGHSPROL, "highsprol"},
  {iscript_bin_t::opcode_t::OPCODE_LOWSPRUL, "lowsprul"},
  {iscript_bin_t::opcode_t::OPCODE_UFLUNSTABLE, "uflunstable"},
  {iscript_bin_t::opcode_t::OPCODE_SPRULUSELO, "spruluselo"},
  {iscript_bin_t::opcode_t::OPCODE_SPRUL, "sprul"},
  {iscript_bin_t::opcode_t::OPCODE_SPROLUSELO, "sproluselo"},
  {iscript_bin_t::opcode_t::OPCODE_END, "end"},
  {iscript_bin_t::opcode_t::OPCODE_SETFLIPSTATE, "setflipstate"},
  {iscript_bin_t::opcode_t::OPCODE_PLAYSND, "playsnd"},
  {iscript_bin_t::opcode_t::OPCODE_PLAYSNDRAND, "playsndrand"},
  {iscript_bin_t::opcode_t::OPCODE_PLAYSNDBTWN, "playsndbtwn"},
  {iscript_bin_t::opcode_t::OPCODE_DOMISSILEDMG, "domissiledmg"},
  {iscript_bin_t::opcode_t::OPCODE_ATTACKMELEE, "attackmelee"},
  {iscript_bin_t::opcode_t::OPCODE_FOLLOWMAINGRAPHIC, "followmaingraphic"},
  {iscript_bin_t::opcode_t::OPCODE_RANDCONDJMP, "randcondjmp"},
  {iscript_bin_t::opcode_t::OPCODE_TURNCCWISE, "turnccwise"},
  {iscript_bin_t::opcode_t::OPCODE_TURNCWISE, "turncwise"},
  {iscript_bin_t::opcode_t::OPCODE_TURN1CWISE, "turn1cwise"},
  {iscript_bin_t::opcode_t::OPCODE_TURNRAND, "turnrand"},
  {iscript_bin_t::opcode_t::OPCODE_SETSPAWNFRAME, "setspawnframe"},
  {iscript_bin_t::opcode_t::OPCODE_SIGORDER, "sigorder"},
  {iscript_bin_t::opcode_t::OPCODE_ATTACKWITH, "attackwith"},
  {iscript_bin_t::opcode_t::OPCODE_ATTACK, "attack"},
  {iscript_bin_t::opcode_t::OPCODE_CASTSPELL, "castspell"},
  {iscript_bin_t::opcode_t::OPCODE_USEWEAPON, "useweapon"},
  {iscript_bin_t::opcode_t::OPCODE_MOVE, "move"},
  {iscript_bin_t::opcode_t::OPCODE_GOTOREPEATATTK, "gotorepeatattk"},
  {iscript_bin_t::opcode_t::OPCODE_ENGFRAME, "engframe"},
  {iscript_bin_t::opcode_t::OPCODE_ENGSET, "engset"},
  {iscript_bin_t::opcode_t::OPCODE_UNKNOWN_2D, "unknown_2d"},
  {iscript_bin_t::opcode_t::OPCODE_NOBRKCODESTART, "nobrkcodestart"},
  {iscript_bin_t::opcode_t::OPCODE_NOBRKCODEEND, "nobrkcodeend"},
  {iscript_bin_t::opcode_t::OPCODE_IGNOREREST, "ignorerest"},
  {iscript_bin_t::opcode_t::OPCODE_ATTKSHIFTPROJ, "attkshiftproj"},
  {iscript_bin_t::opcode_t::OPCODE_TMPRMGRAPHICSTART, "tmprmgraphicstart"},
  {iscript_bin_t::opcode_t::OPCODE_TMPRMGRAPHICEND, "tmprmgraphicend"},
  {iscript_bin_t::opcode_t::OPCODE_SETFLDIRECT, "setfldirect"},
  {iscript_bin_t::opcode_t::OPCODE_CALL, "call"},
  {iscript_bin_t::opcode_t::OPCODE_RETURN, "return"},
  {iscript_bin_t::opcode_t::OPCODE_SETFLSPEED, "setflspeed"},
  {iscript_bin_t::opcode_t::OPCODE_CREATEGASOVERLAYS, "creategasoverlays"},
  {iscript_bin_t::opcode_t::OPCODE_PWRUPCONDJMP, "pwrupcondjmp"},
  {iscript_bin_t::opcode_t::OPCODE_TRGTRANGECONDJMP, "trgtrangecondjmp"},
  {iscript_bin_t::opcode_t::OPCODE_TRGTARCCONDJMP, "trgtarccondjmp"},
  {iscript_bin_t::opcode_t::OPCODE_CURDIRECTCONDJMP, "curdirectcondjmp"},
  {iscript_bin_t::opcode_t::OPCODE_IMGULNEXTID, "imgulnextid"},
  {iscript_bin_t::opcode_t::OPCODE_UNKNOWN_3E, "unknown_3e"},
  {iscript_bin_t::opcode_t::OPCODE_LIFTOFFCONDJMP, "liftoffcondjmp"},
  {iscript_bin_t::opcode_t::OPCODE_WARPOVERLAY, "warpoverlay"},
  {iscript_bin_t::opcode_t::OPCODE_ORDERDONE, "orderdone"},
  {iscript_bin_t::opcode_t::OPCODE_GRDSPROL, "grdsprol"},
  {iscript_bin_t::opcode_t::OPCODE_UNKNOWN_43, "unknown_43"},
  {iscript_bin_t::opcode_t::OPCODE_DOGRDDAMAGE, "dogrddamage"},
})

void to_json(json &j, iscript_bin_t::u2_type_t *u2)
{
  j = json(to_string(u2->value()));
}

void to_json(json &j, iscript_bin_t::u1_type_t *u1)
{
  j = json(to_string(u1->value()));
}

void to_json(json &j, iscript_bin_t::pos_type_t *pos)
{
  j["x"] = json(to_string(pos->x()));
  j["y"] = json(to_string(pos->y()));
}

void to_json(json &j, iscript_bin_t::playsndbtwn_type_t *snd)
{
  j["firstsound"] = json(to_string(snd->firstsound()));
  j["lastsound"] = json(to_string(snd->lastsound()));
}

void to_json(json &j, iscript_bin_t::trgcondjmp_type_t *trgcondjmp)
{
  j["angle1"] = json(to_string(trgcondjmp->angle1()));
  j["angle2"] = json(to_string(trgcondjmp->angle2()));
  j["labelname"] = json(to_string(trgcondjmp->labelname()));
}

void to_json(json &j, iscript_bin_t::imgl_type_t *imgl)
{
  j["image"] = json(to_string(imgl->image()));
  j["pos"] = json(imgl->pos());
}

void to_json(json &j, iscript_bin_t::sprl_type_t *sprl)
{
  j["sprite"] = json(to_string(sprl->sprite()));
  j["pos"] = json(sprl->pos());
}

void to_json(json &j, iscript_bin_t::trgtrangecondjmp_type_t *ttcj)
{
  j["distance"] = json(to_string(ttcj->distance()));
  j["labelname"] = json(ttcj->labelname());
}

void to_json(json &j, iscript_bin_t::randcondjmp_type_t *rcj)
{
  j["randchance"] = json(to_string(rcj->randchance()));
  j["labelname"] = json(rcj->labelname());
}

void to_json(json &j, iscript_bin_t::playsounds_type_t *ps)
{
  j = json::array();

  for(auto sound : *(ps->sound()))
  {
    j.push_back(to_string(sound));
  }
}

void to_json(json &j, iscript_bin_t::sprov_type_t *sprov)
{
  j["sprite"] = json(to_string(sprov->sprite()));
  j["overlay"] = json(to_string(sprov->overlay()));
}

void to_json(json &j, iscript_bin_t::waitrand_type_t *wr)
{
  j["ticks1"] = json(to_string(wr->ticks1()));
  j["ticks2"] = json(to_string(wr->ticks2()));
}


void to_json(json &j, iscript_bin_t::opcode_type_t *opcode)
{
  iscript_bin_t::opcode_t opcode_code_enum = opcode->code();
  string opcode_code_name = json(opcode_code_enum);

  switch (opcode_code_enum)
  {
  case iscript_bin_t::OPCODE_TURN1CWISE:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_IMGOLORIG:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_UNKNOWN_3E:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_SIGORDER:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_ENGFRAME:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_TURNCCWISE:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_UNKNOWN_2D:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_END:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_PLAYFRAM:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_TMPRMGRAPHICSTART:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_IMGULNEXTID:
  {
    iscript_bin_t::pos_type_t *casted_args = static_cast<iscript_bin_t::pos_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_PLAYSNDBTWN:
  {
    iscript_bin_t::playsndbtwn_type_t *casted_args = static_cast<iscript_bin_t::playsndbtwn_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_UNKNOWN_0C:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_ENGSET:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SWITCHUL:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_TRGTARCCONDJMP:
  {
    iscript_bin_t::trgcondjmp_type_t *casted_args = static_cast<iscript_bin_t::trgcondjmp_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SETFLIPSTATE:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SETPOS:
  {
    iscript_bin_t::pos_type_t *casted_args = static_cast<iscript_bin_t::pos_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_IMGOLUSELO:
  {
    iscript_bin_t::imgl_type_t *casted_args = static_cast<iscript_bin_t::imgl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_LOWSPRUL:
  {
    iscript_bin_t::sprl_type_t *casted_args = static_cast<iscript_bin_t::sprl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_TURNRAND:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_DOMISSILEDMG:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_HIGHSPROL:
  {
    iscript_bin_t::sprl_type_t *casted_args = static_cast<iscript_bin_t::sprl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SETFLSPEED:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_USEWEAPON:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_WARPOVERLAY:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_GOTOREPEATATTK:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_UFLUNSTABLE:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_ORDERDONE:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_TRGTRANGECONDJMP:
  {
    iscript_bin_t::trgtrangecondjmp_type_t *casted_args = static_cast<iscript_bin_t::trgtrangecondjmp_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_RETURN:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_CASTSPELL:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_FOLLOWMAINGRAPHIC:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_RANDCONDJMP:
  {
    iscript_bin_t::randcondjmp_type_t *casted_args = static_cast<iscript_bin_t::randcondjmp_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_NOBRKCODEEND:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_CALL:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_NOBRKCODESTART:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_WAIT:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SPROL:
  {
    iscript_bin_t::sprl_type_t *casted_args = static_cast<iscript_bin_t::sprl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_TMPRMGRAPHICEND:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_CREATEGASOVERLAYS:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SETFLDIRECT:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_PWRUPCONDJMP:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SETHORPOS:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SPRULUSELO:
  {
    iscript_bin_t::sprl_type_t *casted_args = static_cast<iscript_bin_t::sprl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SPRUL:
  {
    iscript_bin_t::sprl_type_t *casted_args = static_cast<iscript_bin_t::sprl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_GRDSPROL:
  {
    iscript_bin_t::sprl_type_t *casted_args = static_cast<iscript_bin_t::sprl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_MOVE:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_GOTO:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_IMGUL:
  {
    iscript_bin_t::imgl_type_t *casted_args = static_cast<iscript_bin_t::imgl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_PLAYFRAMTILE:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_ATTKSHIFTPROJ:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_LIFTOFFCONDJMP:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_IMGOL:
  {
    iscript_bin_t::imgl_type_t *casted_args = static_cast<iscript_bin_t::imgl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_IMGULUSELO:
  {
    iscript_bin_t::imgl_type_t *casted_args = static_cast<iscript_bin_t::imgl_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_ATTACK:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_ATTACKMELEE:
  {
    iscript_bin_t::playsounds_type_t *casted_args = static_cast<iscript_bin_t::playsounds_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SPROLUSELO:
  {
    iscript_bin_t::sprov_type_t *casted_args = static_cast<iscript_bin_t::sprov_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_PLAYSNDRAND:
  {
    iscript_bin_t::playsounds_type_t *casted_args = static_cast<iscript_bin_t::playsounds_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_IGNOREREST:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_PLAYSND:
  {
    iscript_bin_t::u2_type_t *casted_args = static_cast<iscript_bin_t::u2_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_UNKNOWN_43:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_SETVERTPOS:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_DOGRDDAMAGE:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  case iscript_bin_t::OPCODE_WAITRAND:
  {
    iscript_bin_t::waitrand_type_t *casted_args = static_cast<iscript_bin_t::waitrand_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_TURNCWISE:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_CURDIRECTCONDJMP:
  {
    iscript_bin_t::trgcondjmp_type_t *casted_args = static_cast<iscript_bin_t::trgcondjmp_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_SETSPAWNFRAME:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  case iscript_bin_t::OPCODE_ATTACKWITH:
  {
    iscript_bin_t::u1_type_t *casted_args = static_cast<iscript_bin_t::u1_type_t *>(opcode->args());
    j[opcode_code_name] = json(casted_args);
    break;
  }
  default:
  {
    j[opcode_code_name] = nullptr;
    break;
  }
  }

}

void to_json(json &j, std::vector<iscript_bin_t::opcode_type_t *> opcode_vec)
{
  j = json::array();

  for (auto opcode : opcode_vec)
  {
    j.push_back(opcode);
  }
}

namespace dat
{

void to_json(json &j, TblEntry t)
{
  j = json
  {
    {"name1", t.name1()},
    {"name2", t.name2()},
    {"name3", t.name3()},
    {"shortcut_pos", t.shortcut_pos()},
    {"shortcut", t.shortcut()}
  };
}

void to_json(json &j, Upgrade u)
{
  j["id"] = json(u.id());
  j["mineral_cost_base"] = json(u.mineral_cost_base());
  j["mineral_cost_factor"] = json(u.mineral_cost_factor());
  j["vespene_cost_base"] = json(u.vespene_cost_base());
  j["vespene_cost_factor"] = json(u.vespene_cost_factor());
  j["research_time_base"] = json(u.research_time_base());
  j["research_time_factor"] = json(u.research_time_factor());
  j["unknown6"] = json(u.unknown6());
  j["icon"] = json(u.icon());
  j["label"] = json(u.label());
  j["label_tbl"] = json(u.label_tbl());
  j["race"] = json(u.race());
  j["max_repeats"] = json(u.max_repeats());

  if (u.has_broodwar_flag())
  {
    j["broodwar_flags"] = json(u.broodwar_flags());
  }
}

void to_json(json &j, Order o)
{
  j["id"] = json(o.id());
  j["label"] = json(o.label());
  j["label_tbl"] = json(o.label_tbl());
  j["use_weapon_targeting"] = json(o.use_weapon_targeting());
  j["unknown2"] = json(o.unknown2());
  j["unknown3"] = json(o.unknown3());
  j["unknown4"] = json(o.unknown4());
  j["unknown5"] = json(o.unknown5());
  j["interruptible"] = json(o.interruptible());
  j["unknown7"] = json(o.unknown7());
  j["queueable"] = json(o.queueable());
  j["unknown9"] = json(o.unknown9());
  j["unknown10"] = json(o.unknown10());
  j["unknown11"] = json(o.unknown11());
  j["unknown12"] = json(o.unknown12());

  j["targeting"] = json(o.targeting());
  try
  {
    j["targeting_obj"] = json(o.targeting_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["energy"] = json(o.energy());
  try
  {
    j["energy_obj"] = json(o.energy_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["animation"] = json(o.animation());
  j["highlight"] = json(o.highlight());
  j["unknown17"] = json(o.unknown17());
  j["obscured_order"] = json(o.obscured_order());
  //j["obscured_order_obj"] = json(o.obscured_order_obj());
}

void to_json(json &j, Techdata t)
{
  j["id"] = json(t.id());
  j["mineral_cost"] = json(t.mineral_cost());
  j["vespene_cost"] = json(t.vespene_cost());
  j["research_time"] = json(t.research_time());
  j["energy_required"] = json(t.energy_required());
  j["unknown4"] = json(t.unknown4());
  j["icon"] = json(t.icon());
  j["label"] = json(t.label());
  j["race"] = json(t.race());
  j["unused"] = json(t.unused());

  if (t.has_broodwar_flag())
  {
    j["broodwar_flag"] = json(t.broodwar_flag());
  }
}

void to_json(json &j, Weapon w)
{
  j["id"] = json(w.id());
  j["label"] = json(w.label());
  j["label_tbl"] = json(w.label_tbl());
  j["graphics"] = json(w.graphics());
  j["graphics_obj"] = json(w.graphics_obj());
  j["explosion"] = json(w.explosion());
  j["target_flags"] = json(w.target_flags());
  j["minimum_range"] = json(w.minimum_range());
  j["maximum_range"] = json(w.maximum_range());
  j["damage_upgrade"] = json(w.damage_upgrade());
  j["damage_upgrade_obj"] = json(w.damage_upgrade_obj());
  j["weapon_type"] = json(w.weapon_type());
  j["weapon_behaviour"] = json(w.weapon_behaviour());
  j["remove_after"] = json(w.remove_after());
  j["explosive_type"] = json(w.explosive_type());
  j["inner_splash_range"] = json(w.inner_splash_range());
  j["medium_splash_range"] = json(w.medium_splash_range());
  j["outer_splash_range"] = json(w.outer_splash_range());
  j["damage_amount"] = json(w.damage_amount());
  j["damage_bonus"] = json(w.damage_bonus());
  j["weapon_cooldown"] = json(w.weapon_cooldown());
  j["damage_factor"] = json(w.damage_factor());
  j["attack_angle"] = json(w.attack_angle());
  j["launch_spin"] = json(w.launch_spin());
  j["x_offset"] = json(w.x_offset());
  j["y_offset"] = json(w.y_offset());
  j["error_message"] = json(w.error_message());
  j["error_message_tbl"] = json(w.error_message_tbl());
  j["icon"] = json(w.icon());

}

void to_json(json &j, Sfx s)
{
  j = json
  {
    {"id", s.id()},
    {"sound_file", s.sound_file()},
    {"sound_file_tbl", s.sound_file_tbl()},
    {"unknown1", s.unknown1()},
    {"unknown2", s.unknown2()},
    {"unknown3", s.unknown3()},
    {"unknown4", s.unknown4()}
  };
}

void to_json(json &j, Portrait p)
{
  j = json
  {
    {"id", p.id()},
    {"video_idle", p.video_idle()},
    {"video_idle_tbl", p.video_idle_tbl()},
    {"video_talking", p.video_talking()},
    {"video_talking_tbl", p.video_talking_tbl()},
    {"change_idle", p.change_idle()},
    {"change_talking", p.change_talking()},
    {"unknown1_idle", p.unknown1_idle()},
    {"unknown1_talking", p.unknown1_talking()}
  };
}

NLOHMANN_JSON_SERIALIZE_ENUM(IScript::AnimationType,
{
  {IScript::AnimationType::Init, "Init"},
  {IScript::AnimationType::Death, "Death"},
  {IScript::AnimationType::GndAttkInit, "GndAttkInit"},
  {IScript::AnimationType::AirAttkInit, "AirAttkInit"},
  {IScript::AnimationType::Unused1, "Unused1"},
  {IScript::AnimationType::GndAttkRpt, "GndAttkRpt"},
  {IScript::AnimationType::AirAttkRpt, "AirAttkRpt"},
  {IScript::AnimationType::CastSpell, "CastSpell"},
  {IScript::AnimationType::GndAttkToIdle, "GndAttkToIdle"},
  {IScript::AnimationType::AirAttkToIdle, "AirAttkToIdle"},
  {IScript::AnimationType::Unused2, "Unused2"},
  {IScript::AnimationType::Walking, "Walking"},
  {IScript::AnimationType::WalkingToIdle, "WalkingToIdle"},
  {IScript::AnimationType::SpecialState1, "SpecialState1"},
  {IScript::AnimationType::SpecialState2, "SpecialState2"},
  {IScript::AnimationType::AlmostBuilt, "AlmostBuilt"},
  {IScript::AnimationType::Built, "Built"},
  {IScript::AnimationType::Landing, "Landing"},
  {IScript::AnimationType::LiftOff, "LiftOff"},
  {IScript::AnimationType::IsWorking, "IsWorking"},
  {IScript::AnimationType::WorkingToIdle, "WorkingToIdle"},
  {IScript::AnimationType::WarpIn, "WarpIn"},
  {IScript::AnimationType::Unused3, "Unused3"},
  {IScript::AnimationType::StarEditInit, "StarEditInit"},
  {IScript::AnimationType::Disable, "Disable"},
  {IScript::AnimationType::Burrow, "Burrow"},
  {IScript::AnimationType::UnBurrow, "UnBurrow"},
  {IScript::AnimationType::Enable, "Enable"},
})

void to_json(json &j, IScript is)
{
  int animation_count = is.getAnimationCount();

  for (int i = 0; i < animation_count; i++)
  {
    IScript::AnimationType anim_t = static_cast<IScript::AnimationType>(i);
    string anim_name = json(anim_t);

    std::vector<iscript_bin_t::opcode_type_t *> opcode_vec = is.getAnimationScript(i);

    j[anim_name] = json(opcode_vec);
  }
}

void to_json(json &j, Image i)
{
  j["id"] = json(i.id());
  j["grp"] = json(i.grp());
  j["grp_tbl"] = json(i.grp_tbl());
  j["gfx_turns"] = json(i.gfx_turns());
  j["clickable"] = json(i.clickable());
  j["use_full_iscript"] = json(i.use_full_iscript());
  j["draw_if_cloaked"] = json(i.draw_if_cloaked());
  j["draw_function"] = json(i.draw_function());
  j["remapping"] = json(i.remapping());
  j["iscript"] = json(i.iscript());
  j["iscript_obj"] = json(i.iscript_obj());

  j["shield_overlay"] = json(i.shield_overlay());
  try
  {
    j["shield_overlay_tbl"] = json(i.shield_overlay_tbl());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["attack_overlay"] = json(i.attack_overlay());
  try
  {
    j["attack_overlay_tbl"] = json(i.attack_overlay_tbl());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["damage_overlay"] = json(i.damage_overlay());
  try
  {
    j["damage_overlay_tbl"] = json(i.damage_overlay_tbl());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["special_overlay"] = json(i.special_overlay());
  try
  {
    j["special_overlay_tbl"] = json(i.special_overlay_tbl());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["landing_dust_overlay"] = json(i.landing_dust_overlay());
  try
  {
    j["landing_dust_overlay_tbl"] = json(i.landing_dust_overlay_tbl());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }
}

void to_json(json &j, Sprite s)
{
  j["id"] = json(s.id());
  j["image"] = json(s.image());
  j["image_obj"] = json(s.image_obj());

  try
  {
    j["health_bar"] = json(s.health_bar());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["unknown2"] = json(s.unknown2());
  j["is_visible"] = json(s.is_visible());

  try
  {
    j["select_circle_image_size"] = json(s.select_circle_image_size());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["select_circle_vertical_pos"] = json(s.select_circle_vertical_pos());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }
}

void to_json(json &j, Flingy f)
{
  j = json
  {
    {"id", f.id()},
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
  j["id"] = json(u.id());
  j["id_string"] = json(u.getIDString());
  j["name_tbl"] = json(u.name_tbl());
  j["flingy"] = json(u.flingy());
  j["flingy_obj"] = json(u.flingy_obj());
  j["subunit1"] = json(u.subunit1());

  try
  {
    j["subunit1_obj"] = json(u.subunit1_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["subunit2"] = json(u.subunit2());

  try
  {
    j["subunit2_obj"] = json(u.subunit2_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["infestation"] = json(u.infestation());
    j["infestation_obj"] = json(u.infestation_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["construction_animation"] = json(u.construction_animation());
    j["construction_animation_obj"] = json(u.construction_animation_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["unit_direction"] = json(u.unit_direction());
  j["shield_enable"] = json(u.shield_enable());
  j["shield_amount"] = json(u.shield_amount());
  j["hitpoints"] = json(u.hitpoints());
  j["elevation_level"] = json(u.elevation_level());
  j["unknown"] = json(u.unknown());
  j["rank"] = json(u.rank());
  j["ai_computer_idle"] = json(u.ai_computer_idle());
  j["ai_computer_idle_obj"] = json(u.ai_computer_idle_obj());
  j["ai_human_idle"] = json(u.ai_human_idle());
  j["ai_human_idle_obj"] = json(u.ai_human_idle_obj());
  j["ai_return_to_idle"] = json(u.ai_return_to_idle());
  j["ai_return_to_idle_obj"] = json(u.ai_return_to_idle_obj());
  j["ai_attack_unit"] = json(u.ai_attack_unit());
  j["ai_attack_unit_obj"] = json(u.ai_attack_unit_obj());
  j["ai_attack_move"] = json(u.ai_attack_move());
  j["ai_attack_move_obj"] = json(u.ai_attack_move_obj());

  try
  {
    j["ground_weapon"] = json(u.ground_weapon());
    j["ground_weapon_obj"] = json(u.ground_weapon_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  if (u.is_format_bw())
  {
    j["max_ground_hits"] = json(u.max_ground_hits());
  }

  try
  {
    j["air_weapon"] = json(u.air_weapon());
    j["air_weapon_obj"] = json(u.air_weapon_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  if (u.is_format_bw())
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
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["what_sound_start"] = json(u.what_sound_start());
    j["what_sound_end"] = json(u.what_sound_end());
    j["what_sound_obj"] = json(u.what_sound_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["piss_sound_start"] = json(u.piss_sound_start());
    j["piss_sound_end"] = json(u.piss_sound_end());
    j["piss_sound_obj"] = json(u.piss_sound_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["what_sound_start"] = json(u.what_sound_start());
    j["what_sound_end"] = json(u.what_sound_end());
    j["what_sound_obj"] = json(u.what_sound_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  try
  {
    j["yes_sound_start"] = json(u.yes_sound_start());
    j["yes_sound_end"] = json(u.yes_sound_end());
    j["yes_sound_obj"] = json(u.yes_sound_obj());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["staredit_placement_box"] = json(u.staredit_placement_box());

  try
  {
    j["addon_position"] = json(u.addon_position());
  }
  catch (PropertyNotAvailableException &ex)
  { /*it's fine, do nothing */ }

  j["unit_dimension"] = json(u.unit_dimension());
  j["portrait"] = json(u.portrait());

  try
  {
    j["portrait_obj"] = json(u.portrait_obj());
  }
  catch (PropertyNotAvailableException &ex)
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

  if (u.is_format_bw())
  {
    j["broodwar_flag"] = json(u.broodwar_flag());
  }

  j["is_format_bw"] = json(u.is_format_bw());
}

} /* namespace dat */
