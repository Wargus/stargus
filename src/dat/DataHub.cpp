/*
 * DataHub.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Logger.h"
#include "luagen.h"
#include "DataHub.h"
#include "StringUtil.h"
#include "Grp.h"
#include "Unit.h"
#include "Preferences.h"
#include "FileUtil.h"

// System
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.DataHub");

DataHub::DataHub(std::shared_ptr<Hurricane> hurricane) :
  KaitaiConverter(hurricane)
{
  bool has_broodwar_flag = false;
  bool has_max_air_hits = false;
  bool has_max_ground_hits = false;

  init_units_dat(has_broodwar_flag, has_max_air_hits, has_max_ground_hits);

  init_orders_dat(get_dat_ai_max());

  init_weapons_dat(get_dat_weapons_max());

  init_flingy_dat(get_dat_graphics_max());

  init_sprites_dat(get_dat_sprites_max(), 208); // TODO: why 208? how could I calculate this??

  init_images_dat(get_dat_images_max());

  init_sfxdata_dat(get_dat_sounds_max());

  init_portdata_dat(get_dat_portraits_max());

  init_upgrades_dat(get_dat_upgrades_max(), has_broodwar_flag);

  init_techdata_dat(get_dat_energy_max(), has_broodwar_flag);

  init_mapdata_dat();

  init_stat_txt_tbl();

  init_images_tbl();

  init_sfxdata_tbl();

  init_portdata_tbl();

  init_mapdata_tbl();
}

DataHub::~DataHub()
{
}

void DataHub::init_units_dat(bool has_broodwar_flag, bool has_max_air_hits,
                             bool has_max_ground_hits)
{
  string sc_arr_units_dat = "arr\\units.dat";

  std::shared_ptr<kaitai::kstream> units_ks;
  units_ks = getKaitaiStream(sc_arr_units_dat);

  std::shared_ptr<units_dat_t> units_loc(
    new units_dat_t(has_broodwar_flag, has_max_air_hits, has_max_ground_hits,
                    units_ks.get()));
  units = units_loc;
}

void DataHub::init_orders_dat(int num_lines)
{
  string sc_arr_orders_dat = "arr\\orders.dat";

  std::shared_ptr<kaitai::kstream> orders_ks = getKaitaiStream(sc_arr_orders_dat);

  std::shared_ptr<orders_dat_t> orders_loc(
    new orders_dat_t(num_lines, orders_ks.get()));
  orders = orders_loc;

  LOG4CXX_TRACE(logger, string("units_ai_max=") + to_string(get_dat_ai_max() + 1));
}

void DataHub::init_weapons_dat(int num_lines)
{
  string sc_arr_weapons_dat = "arr\\weapons.dat";

  std::shared_ptr<kaitai::kstream> weapons_ks = getKaitaiStream(sc_arr_weapons_dat);

  std::shared_ptr<weapons_dat_t> weapons_loc(
    new weapons_dat_t(num_lines, weapons_ks.get()));
  weapons = weapons_loc;
}

void DataHub::init_flingy_dat(int num_lines)
{
  string sc_arr_flingy_dat = "arr\\flingy.dat";

  std::shared_ptr<kaitai::kstream> flingy_ks = getKaitaiStream(sc_arr_flingy_dat);

  std::shared_ptr<flingy_dat_t> flingy_loc(
    new flingy_dat_t(num_lines, flingy_ks.get()));
  flingy = flingy_loc;
}

void DataHub::init_sprites_dat(int num_lines, int num_decorations)
{
  string sc_arr_sprites_dat = "arr\\sprites.dat";

  std::shared_ptr<kaitai::kstream> sprites_ks = getKaitaiStream(sc_arr_sprites_dat);

  std::shared_ptr<sprites_dat_t> sprites_loc(
    new sprites_dat_t(num_lines, num_decorations, sprites_ks.get()));
  sprites = sprites_loc;
}

void DataHub::init_images_dat(int num_lines)
{
  string sc_arr_images_dat = "arr\\images.dat";

  std::shared_ptr<kaitai::kstream> images_ks = getKaitaiStream(sc_arr_images_dat);

  std::shared_ptr<images_dat_t> images_loc(
    new images_dat_t(num_lines, images_ks.get()));
  images = images_loc;
}

void DataHub::init_sfxdata_dat(int num_lines)
{
  string sc_arr_sfxdata_dat = "arr\\sfxdata.dat";

  std::shared_ptr<kaitai::kstream> sfxdata_ks = getKaitaiStream(sc_arr_sfxdata_dat);

  // 0 means "no sound"
  // TODO: find out if unit_sound_max+1 is needed or not! In some case data seams ok, in others it crash
  std::shared_ptr<sfxdata_dat_t> sfxdata_loc(
    new sfxdata_dat_t(num_lines, sfxdata_ks.get()));
  sfxdata = sfxdata_loc;
}

void DataHub::init_portdata_dat(int num_lines)
{
  string sc_arr_portdata_dat = "arr\\portdata.dat";

  std::shared_ptr<kaitai::kstream> portrait_ks = getKaitaiStream(sc_arr_portdata_dat);

  // 1. units_portrait_max => idle portraits
  // 2. 4x flags => idle portraits
  // 3. units_portrait_max => talking portraits
  // 4. 4x flags => talking portraits
  // 5. +2 because index starting at zero
  std::shared_ptr<portdata_dat_t> portrait_loc(
    new portdata_dat_t(num_lines, portrait_ks.get()));
  portrait = portrait_loc;
}

void DataHub::init_upgrades_dat(int num_lines, bool has_broodwar_flag)
{
  string sc_arr_upgrades_dat = "arr\\upgrades.dat";

  std::shared_ptr<kaitai::kstream> upgrades_ks = getKaitaiStream(sc_arr_upgrades_dat);

  std::shared_ptr<upgrades_dat_t> upgrades_loc(
    new upgrades_dat_t(has_broodwar_flag, num_lines, upgrades_ks.get()));
  upgrades = upgrades_loc;
}

void DataHub::init_techdata_dat(int num_lines, bool has_broodwar_flag)
{
  string sc_arr_techdata_dat = "arr\\techdata.dat";

  std::shared_ptr<kaitai::kstream> techdata_ks = getKaitaiStream(sc_arr_techdata_dat);

  std::shared_ptr<techdata_dat_t> techdata_loc(
    new techdata_dat_t(has_broodwar_flag, num_lines, techdata_ks.get()));
  techdata = techdata_loc;
}

void DataHub::init_mapdata_dat()
{
  string sc_arr_mapdata_dat = "arr\\mapdata.dat";

  std::shared_ptr<kaitai::kstream> mapdata_ks = getKaitaiStream(sc_arr_mapdata_dat);

  std::shared_ptr<mapdata_dat_t> mapdata_loc(
    new mapdata_dat_t(mapdata_ks.get()));
  mapdata = mapdata_loc;
}

void DataHub::init_stat_txt_tbl()
{
  string sc_rez_stat_txt_tbl = "rez\\stat_txt.tbl";

  std::shared_ptr<kaitai::kstream> stat_txt_ks = getKaitaiStream(sc_rez_stat_txt_tbl);

  Tbl stat_txt;
  stat_txt_vec = stat_txt.convertFromStream(stat_txt_ks);
}

void DataHub::init_images_tbl()
{
  string sc_arr_images_tbl = "arr\\images.tbl";

  std::shared_ptr<kaitai::kstream> images_tbl_ks = getKaitaiStream(sc_arr_images_tbl);

  Tbl images_tbl;
  images_tbl_vec = images_tbl.convertFromStream(images_tbl_ks);
}

void DataHub::init_sfxdata_tbl()
{
  string sc_arr_sfxdata_tbl = "arr\\sfxdata.tbl";

  std::shared_ptr<kaitai::kstream> sfxdata_tbl_ks = getKaitaiStream(sc_arr_sfxdata_tbl);

  Tbl sfxdata_tbl;
  sfxdata_tbl_vec = sfxdata_tbl.convertFromStream(sfxdata_tbl_ks);
}

void DataHub::init_portdata_tbl()
{
  string sc_arr_portdata_tbl = "arr\\portdata.tbl";

  std::shared_ptr<kaitai::kstream> portdata_tbl_ks = getKaitaiStream(sc_arr_portdata_tbl);

  Tbl portdata_tbl;
  portdata_tbl_vec = portdata_tbl.convertFromStream(portdata_tbl_ks);
}

void DataHub::init_mapdata_tbl()
{
  string sc_arr_mapdata_tbl = "arr\\mapdata.tbl";

  std::shared_ptr<kaitai::kstream> mapdata_tbl_ks = getKaitaiStream(sc_arr_mapdata_tbl);

  Tbl mapdata_tbl;
  mapdata_tbl_vec = mapdata_tbl.convertFromStream(mapdata_tbl_ks);
}

int DataHub::get_dat_ai_max() const
{
  std::vector<uint8_t> *units_ai_attack_move_vec = units->ai_attack_move();
  std::vector<uint8_t> *units_ai_attack_unit_vec = units->ai_attack_unit();
  std::vector<uint8_t> *units_ai_computer_idle_vec = units->ai_computer_idle();
  std::vector<uint8_t> *units_ai_human_idle_vec = units->ai_human_idle();
  std::vector<uint8_t> *units_ai_return_to_idle_vec =
    units->ai_return_to_idle();

  vector<uint8_t> units_ai_max_vec;
  units_ai_max_vec.push_back(
    *max_element(units_ai_attack_move_vec->begin(),
                 units_ai_attack_move_vec->end()));
  units_ai_max_vec.push_back(
    *max_element(units_ai_attack_unit_vec->begin(),
                 units_ai_attack_unit_vec->end()));
  units_ai_max_vec.push_back(
    *max_element(units_ai_computer_idle_vec->begin(),
                 units_ai_computer_idle_vec->end()));
  units_ai_max_vec.push_back(
    *max_element(units_ai_human_idle_vec->begin(),
                 units_ai_human_idle_vec->end()));
  units_ai_max_vec.push_back(
    *max_element(units_ai_return_to_idle_vec->begin(),
                 units_ai_return_to_idle_vec->end()));
  uint8_t units_ai_max = *max_element(units_ai_max_vec.begin(),
                                      units_ai_max_vec.end());

  return units_ai_max + 1;
}

int DataHub::get_dat_weapons_max() const
{
  std::vector<uint8_t> *units_ground_weapon_vec = units->ground_weapon();
  std::vector<uint8_t> *units_air_weapon_vec = units->air_weapon();
  std::vector<uint8_t> *orders_targeting_vec = orders->targeting();

  vector<uint8_t> weapons_max_vec;
  weapons_max_vec.push_back(
    *max_element(units_ground_weapon_vec->begin(),
                 units_ground_weapon_vec->end()));
  weapons_max_vec.push_back(
    *max_element(units_air_weapon_vec->begin(), units_air_weapon_vec->end()));
  weapons_max_vec.push_back(
    *max_element(orders_targeting_vec->begin(), orders_targeting_vec->end()));
  uint8_t weapon_max = *max_element(weapons_max_vec.begin(),
                                    weapons_max_vec.end());


  return weapon_max;
}

int DataHub::get_dat_graphics_max() const
{
  std::vector<uint8_t> *units_graphics_vec = units->flingy();
  std::vector<uint32_t> *weapon_graphics_vec = weapons->graphics();

  int unit_graphics_max = *max_element(units_graphics_vec->begin(),
                                       units_graphics_vec->end());

  LOG4CXX_TRACE(logger, string("unit_graphics_max=") + to_string(unit_graphics_max));

  int weapon_graphics_max = *max_element(weapon_graphics_vec->begin(),
                                         weapon_graphics_vec->end());

  LOG4CXX_TRACE(logger, string("weapon_graphics_max=") + to_string(weapon_graphics_max));

  int graphics_max = unit_graphics_max;
  if (weapon_graphics_max > unit_graphics_max)
    graphics_max = weapon_graphics_max;

  return graphics_max + 1;
}

int DataHub::get_dat_sprites_max() const
{
  std::vector<uint16_t> *flingy_sprites_vec = flingy->sprite();

  int flingy_sprites_max = *max_element(flingy_sprites_vec->begin(),
                                        flingy_sprites_vec->end());

  LOG4CXX_TRACE(logger, string("flingy_sprites_max=") + to_string(flingy_sprites_max));

  return flingy_sprites_max + 1;
}

int DataHub::get_dat_images_max() const
{
  std::vector<uint16_t> *sprites_images_vec = sprites->image();

  int sprites_image_file_max = *max_element(sprites_images_vec->begin(),
                               sprites_images_vec->end());

  LOG4CXX_TRACE(logger, string("sprites_image_file_max=") + to_string(sprites_image_file_max));

  return sprites_image_file_max + 1;
}

int DataHub::get_dat_sounds_max() const
{
  std::vector<uint16_t> *units_ready_sound_vec = units->ready_sound();
  std::vector<uint16_t> *units_what_sound_start_vec = units->what_sound_start();
  std::vector<uint16_t> *units_what_sound_end_vec = units->what_sound_end();
  std::vector<uint16_t> *units_piss_sound_start_vec = units->piss_sound_start();
  std::vector<uint16_t> *units_piss_sound_end_vec = units->piss_sound_end();
  std::vector<uint16_t> *units_yes_sound_start_vec = units->yes_sound_start();
  std::vector<uint16_t> *units_yes_sound_end_vec = units->yes_sound_end();

  vector<uint16_t> units_sound_max_vec;
  units_sound_max_vec.push_back(
    *max_element(units_ready_sound_vec->begin(),
                 units_ready_sound_vec->end()));
  units_sound_max_vec.push_back(
    *max_element(units_what_sound_start_vec->begin(),
                 units_what_sound_start_vec->end()));
  units_sound_max_vec.push_back(
    *max_element(units_what_sound_end_vec->begin(),
                 units_what_sound_end_vec->end()));
  units_sound_max_vec.push_back(
    *max_element(units_piss_sound_start_vec->begin(),
                 units_piss_sound_start_vec->end()));
  units_sound_max_vec.push_back(
    *max_element(units_piss_sound_end_vec->begin(),
                 units_piss_sound_end_vec->end()));
  units_sound_max_vec.push_back(
    *max_element(units_yes_sound_start_vec->begin(),
                 units_yes_sound_start_vec->end()));
  units_sound_max_vec.push_back(
    *max_element(units_yes_sound_end_vec->begin(),
                 units_yes_sound_end_vec->end()));
  uint16_t unit_sound_max = *max_element(units_sound_max_vec.begin(),
                                         units_sound_max_vec.end());

  LOG4CXX_TRACE(logger, string("unit_sound_max=") + to_string(unit_sound_max));

  return unit_sound_max;
}

int DataHub::get_dat_portraits_max() const
{
  std::vector<uint16_t> *units_portrait_vec = units->portrait();

  int units_portrait_max = *max_element(units_portrait_vec->begin(),
                                        units_portrait_vec->end(), portdataCompare);

  LOG4CXX_TRACE(logger, string("units_portrait_max=") + to_string(units_portrait_max));

  return units_portrait_max + 2 * 4;
}

int DataHub::get_dat_upgrades_max() const
{
  std::vector<uint8_t> *units_armor_upgrade_vec = units->armor_upgrade();
  std::vector<uint8_t> *weapon_damage_upgrade_vec = weapons->damage_upgrade();

  vector<uint8_t> units_upgrade_vec;
  units_upgrade_vec.push_back(
    *max_element(units_armor_upgrade_vec->begin(),
                 units_armor_upgrade_vec->end()));
  units_upgrade_vec.push_back(
    *max_element(weapon_damage_upgrade_vec->begin(),
                 weapon_damage_upgrade_vec->end()));
  uint16_t units_upgrade_max = *max_element(units_upgrade_vec.begin(),
                               units_upgrade_vec.end());

  LOG4CXX_TRACE(logger, string("units_upgrade_max=") + to_string(units_upgrade_max));

  return units_upgrade_max + 1;
}

int DataHub::get_dat_energy_max() const
{
  std::vector<uint8_t> *orders_energy_vec = orders->energy();
  uint8_t orders_energy_max = *max_element(orders_energy_vec->begin(),
                              orders_energy_vec->end());

  return orders_energy_max;
}

bool DataHub::portdataCompare(int val1, int val2)
{
  bool result = false;

  if (val2 != Unit::portrait_none)
  {
    result = val1 < val2;
  }

  return result;
}

} /* namespace dat */
