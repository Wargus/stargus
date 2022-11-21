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

  init_iscript_bin();
}

DataHub::~DataHub()
{
}

void DataHub::init_units_dat()
{
  string sc_arr_units_dat = "arr\\units.dat";

  m_units_stream = mHurricane->extractStream(sc_arr_units_dat);
  m_units_ks = make_shared<kaitai::kstream>(&*m_units_stream);

  units = make_shared<units_dat_t>(m_units_ks.get());
}

void DataHub::init_orders_dat()
{
  string sc_arr_orders_dat = "arr\\orders.dat";

  m_orders_stream = mHurricane->extractStream(sc_arr_orders_dat);

  m_orders_ks = make_shared<kaitai::kstream>(&*m_orders_stream);

  orders = make_shared<orders_dat_t>(m_orders_ks.get());
}

void DataHub::init_weapons_dat()
{
  string sc_arr_weapons_dat = "arr\\weapons.dat";

  m_weapons_stream = mHurricane->extractStream(sc_arr_weapons_dat);
  m_weapons_ks = make_shared<kaitai::kstream>(&*m_weapons_stream);

  weapons = make_shared<weapons_dat_t>(m_weapons_ks.get());
}

void DataHub::init_flingy_dat()
{
  string sc_arr_flingy_dat = "arr\\flingy.dat";

  m_flingy_stream = mHurricane->extractStream(sc_arr_flingy_dat);
  m_flingy_ks = make_shared<kaitai::kstream>(&*m_flingy_stream);

  flingy = make_shared<flingy_dat_t>(m_flingy_ks.get());
}

void DataHub::init_sprites_dat()
{
  string sc_arr_sprites_dat = "arr\\sprites.dat";

  m_sprites_stream = mHurricane->extractStream(sc_arr_sprites_dat);
  m_sprites_ks = make_shared<kaitai::kstream>(&*m_sprites_stream);

  sprites = make_shared<sprites_dat_t>(m_sprites_ks.get());
}

void DataHub::init_images_dat()
{
  string sc_arr_images_dat = "arr\\images.dat";

  m_images_stream = mHurricane->extractStream(sc_arr_images_dat);
  m_images_ks = make_shared<kaitai::kstream>(&*m_images_stream);

  images = make_shared<images_dat_t>(m_images_ks.get());
}

void DataHub::init_sfxdata_dat()
{
  string sc_arr_sfxdata_dat = "arr\\sfxdata.dat";

  m_sfxdata_stream = mHurricane->extractStream(sc_arr_sfxdata_dat);
  m_sfxdata_ks = make_shared<kaitai::kstream>(&*m_sfxdata_stream);

  sfxdata = make_shared<sfxdata_dat_t>(m_sfxdata_ks.get());
}

void DataHub::init_portdata_dat()
{
  string sc_arr_portdata_dat = "arr\\portdata.dat";

  m_portdata_stream = mHurricane->extractStream(sc_arr_portdata_dat);
  m_portdata_ks = make_shared<kaitai::kstream>(&*m_portdata_stream);

  portdata = make_shared<portdata_dat_t>(m_portdata_ks.get());
}

void DataHub::init_upgrades_dat()
{
  string sc_arr_upgrades_dat = "arr\\upgrades.dat";

  m_upgrades_stream = mHurricane->extractStream(sc_arr_upgrades_dat);
  m_upgrades_ks = make_shared<kaitai::kstream>(&*m_upgrades_stream);

  upgrades = make_shared<upgrades_dat_t>(m_upgrades_ks.get());
}

void DataHub::init_techdata_dat()
{
  string sc_arr_techdata_dat = "arr\\techdata.dat";

  m_techdata_stream = mHurricane->extractStream(sc_arr_techdata_dat);
  m_techdata_ks = make_shared<kaitai::kstream>(&*m_techdata_stream);

  techdata = make_shared<techdata_dat_t>(m_techdata_ks.get());
}

void DataHub::init_mapdata_dat()
{
  string sc_arr_mapdata_dat = "arr\\mapdata.dat";

  m_mapdata_stream = mHurricane->extractStream(sc_arr_mapdata_dat);
  m_mapdata_ks = make_shared<kaitai::kstream>(&*m_mapdata_stream);

  mapdata = make_shared<mapdata_dat_t>(m_mapdata_ks.get());
}

void DataHub::init_stat_txt_tbl()
{
  string sc_rez_stat_txt_tbl = "rez\\stat_txt.tbl";

  std::shared_ptr<std::istream> tbl_stream = mHurricane->extractStream(sc_rez_stat_txt_tbl);
  std::shared_ptr<kaitai::kstream> stat_txt_ks = make_shared<kaitai::kstream>(&*tbl_stream);

  Tbl stat_txt;
  /*std::vector<TblEntry>*/
  stat_txt_tbl_vec = stat_txt.convertFromStream(stat_txt_ks);

  /*int vec_pos = 0;

  // This below splits the big string vector to smaller ones per type. I found later that regarding the data index one
  // big file is easier to handle. But maybe I change my mind later to enable this again...

  stat_txt_units_tbl_vec.resize(units->flingy()->size());
  std::copy(stat_txt_tbl_vec.begin() + vec_pos, stat_txt_tbl_vec.begin() + units->flingy()->size(), stat_txt_units_tbl_vec.begin());
  vec_pos += units->flingy()->size();

  stat_txt_weapons_tbl_vec.resize(weapons->label()->size());
  std::copy(stat_txt_tbl_vec.begin() + vec_pos, stat_txt_tbl_vec.begin() + vec_pos + weapons->label()->size(), stat_txt_weapons_tbl_vec.begin());
  vec_pos += weapons->label()->size();

  stat_txt_error_messages_tbl_vec.resize(weapons->error_message()->size());
  std::copy(stat_txt_tbl_vec.begin() + vec_pos, stat_txt_tbl_vec.begin() + vec_pos + weapons->error_message()->size(), stat_txt_error_messages_tbl_vec.begin());
  vec_pos += weapons->error_message()->size();

  stat_txt_upgrades_tbl_vec.resize(upgrades->label()->size());
  std::copy(stat_txt_tbl_vec.begin() + vec_pos, stat_txt_tbl_vec.begin() + vec_pos + upgrades->label()->size(), stat_txt_upgrades_tbl_vec.begin());
  vec_pos += upgrades->label()->size();

  stat_txt_orders_tbl_vec.resize(orders->label()->size());
  std::copy(stat_txt_tbl_vec.begin() + vec_pos, stat_txt_tbl_vec.begin() + vec_pos + orders->label()->size(), stat_txt_orders_tbl_vec.begin());
  vec_pos += orders->label()->size();

  stat_txt_techdata_tbl_vec.resize(techdata->label()->size());
  std::copy(stat_txt_tbl_vec.begin() + vec_pos, stat_txt_tbl_vec.begin() + vec_pos + techdata->label()->size(), stat_txt_techdata_tbl_vec.begin());
  vec_pos += techdata->label()->size();*/
}

void DataHub::init_images_tbl()
{
  string sc_arr_images_tbl = "arr\\images.tbl";

  std::shared_ptr<std::istream> tbl_stream = mHurricane->extractStream(sc_arr_images_tbl);
  std::shared_ptr<kaitai::kstream> images_tbl_ks = make_shared<kaitai::kstream>(&*tbl_stream);

  Tbl images_tbl;
  images_tbl_vec = images_tbl.convertFromStream(images_tbl_ks);
}

void DataHub::init_sfxdata_tbl()
{
  string sc_arr_sfxdata_tbl = "arr\\sfxdata.tbl";

  std::shared_ptr<std::istream> tbl_stream = mHurricane->extractStream(sc_arr_sfxdata_tbl);
  std::shared_ptr<kaitai::kstream> sfxdata_tbl_ks = make_shared<kaitai::kstream>(&*tbl_stream);

  Tbl sfxdata_tbl;
  sfxdata_tbl_vec = sfxdata_tbl.convertFromStream(sfxdata_tbl_ks);
}

void DataHub::init_portdata_tbl()
{
  string sc_arr_portdata_tbl = "arr\\portdata.tbl";

  std::shared_ptr<std::istream> tbl_stream = mHurricane->extractStream(sc_arr_portdata_tbl);
  std::shared_ptr<kaitai::kstream> portdata_tbl_ks = make_shared<kaitai::kstream>(&*tbl_stream);

  Tbl portdata_tbl;
  portdata_tbl_vec = portdata_tbl.convertFromStream(portdata_tbl_ks);
}

void DataHub::init_mapdata_tbl()
{
  string sc_arr_mapdata_tbl = "arr\\mapdata.tbl";

  std::shared_ptr<std::istream> tbl_stream = mHurricane->extractStream(sc_arr_mapdata_tbl);
  std::shared_ptr<kaitai::kstream> mapdata_tbl_ks = make_shared<kaitai::kstream>(&*tbl_stream);

  Tbl mapdata_tbl;
  mapdata_tbl_vec = mapdata_tbl.convertFromStream(mapdata_tbl_ks);
}

void DataHub::init_iscript_bin()
{
  string sc_iscript_bin = "scripts\\iscript.bin";

  m_iscript_stream = mHurricane->extractStream(sc_iscript_bin);
  m_iscript_ks = make_shared<kaitai::kstream>(&*m_iscript_stream);

  iscript = make_shared<iscript_bin_t>(m_iscript_ks.get());
}

} /* namespace dat */
