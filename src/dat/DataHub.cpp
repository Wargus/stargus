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
#include "Hurricane.h"

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
  init_units_dat();

  init_orders_dat();

  init_weapons_dat();

  init_flingy_dat();

  init_sprites_dat();

  init_images_dat();

  init_sfxdata_dat();

  init_portdata_dat();

  init_upgrades_dat();

  init_techdata_dat();

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

void DataHub::init_units_dat()
{
  string sc_arr_units_dat = "arr\\units.dat";

  std::shared_ptr<kaitai::kstream> units_ks;
  units_ks = getKaitaiStream(sc_arr_units_dat);

  std::shared_ptr<units_dat_t> units_loc(
    new units_dat_t(units_ks.get()));
  units = units_loc;
}

void DataHub::init_orders_dat()
{
  string sc_arr_orders_dat = "arr\\orders.dat";

  std::shared_ptr<kaitai::kstream> orders_ks = getKaitaiStream(sc_arr_orders_dat);

  std::shared_ptr<orders_dat_t> orders_loc(
    new orders_dat_t(orders_ks.get()));
  orders = orders_loc;
}

void DataHub::init_weapons_dat()
{
  string sc_arr_weapons_dat = "arr\\weapons.dat";

  std::shared_ptr<kaitai::kstream> weapons_ks = getKaitaiStream(sc_arr_weapons_dat);

  std::shared_ptr<weapons_dat_t> weapons_loc(
    new weapons_dat_t(weapons_ks.get()));
  weapons = weapons_loc;
}

void DataHub::init_flingy_dat()
{
  string sc_arr_flingy_dat = "arr\\flingy.dat";

  std::shared_ptr<kaitai::kstream> flingy_ks = getKaitaiStream(sc_arr_flingy_dat);

  std::shared_ptr<flingy_dat_t> flingy_loc(
    new flingy_dat_t(flingy_ks.get()));
  flingy = flingy_loc;
}

void DataHub::init_sprites_dat()
{
  string sc_arr_sprites_dat = "arr\\sprites.dat";

  std::shared_ptr<kaitai::kstream> sprites_ks = getKaitaiStream(sc_arr_sprites_dat);

  std::shared_ptr<sprites_dat_t> sprites_loc(
    new sprites_dat_t(sprites_ks.get()));
  sprites = sprites_loc;
}

void DataHub::init_images_dat()
{
  string sc_arr_images_dat = "arr\\images.dat";

  std::shared_ptr<kaitai::kstream> images_ks = getKaitaiStream(sc_arr_images_dat);

  std::shared_ptr<images_dat_t> images_loc(
    new images_dat_t(images_ks.get()));
  images = images_loc;
}

void DataHub::init_sfxdata_dat()
{
  string sc_arr_sfxdata_dat = "arr\\sfxdata.dat";

  std::shared_ptr<kaitai::kstream> sfxdata_ks = getKaitaiStream(sc_arr_sfxdata_dat);

  // 0 means "no sound"
  // TODO: find out if unit_sound_max+1 is needed or not! In some case data seams ok, in others it crash
  std::shared_ptr<sfxdata_dat_t> sfxdata_loc(
    new sfxdata_dat_t(sfxdata_ks.get()));
  sfxdata = sfxdata_loc;
}

void DataHub::init_portdata_dat()
{
  string sc_arr_portdata_dat = "arr\\portdata.dat";

  std::shared_ptr<kaitai::kstream> portrait_ks = getKaitaiStream(sc_arr_portdata_dat);

  // TODO: remove comment if working
  // 1. units_portrait_max => idle portraits
  // 2. 4x flags => idle portraits
  // 3. units_portrait_max => talking portraits
  // 4. 4x flags => talking portraits
  // 5. +2 because index starting at zero
  std::shared_ptr<portdata_dat_t> portrait_loc(
    new portdata_dat_t(portrait_ks.get()));
  portrait = portrait_loc;
}

void DataHub::init_upgrades_dat()
{
  string sc_arr_upgrades_dat = "arr\\upgrades.dat";

  std::shared_ptr<kaitai::kstream> upgrades_ks = getKaitaiStream(sc_arr_upgrades_dat);

  std::shared_ptr<upgrades_dat_t> upgrades_loc(
    new upgrades_dat_t(upgrades_ks.get()));
  upgrades = upgrades_loc;
}

void DataHub::init_techdata_dat()
{
  string sc_arr_techdata_dat = "arr\\techdata.dat";

  std::shared_ptr<kaitai::kstream> techdata_ks = getKaitaiStream(sc_arr_techdata_dat);

  std::shared_ptr<techdata_dat_t> techdata_loc(
    new techdata_dat_t(techdata_ks.get()));
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

} /* namespace dat */
