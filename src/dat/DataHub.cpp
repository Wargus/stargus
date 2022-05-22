/*
 * DataHub.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "DataHub.h"
#include "StringUtil.h"
#include "Grp.h"
#include "Unit.h"
#include "LuaGen.h"
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

DataHub::DataHub(std::shared_ptr<Hurricane> hurricane) :
  KaitaiConverter(hurricane), mLogger("startool.DataHub")
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
  mUnits_ks = getKaitaiStream(sc_arr_units_dat);

  std::shared_ptr<units_dat_t> units_loc(
    new units_dat_t(has_broodwar_flag, has_max_air_hits, has_max_ground_hits,
                    mUnits_ks.get()));
  units = units_loc;
}

void DataHub::init_orders_dat(int num_lines)
{
  string sc_arr_orders_dat = "arr\\orders.dat";
  orders_ks = getKaitaiStream(sc_arr_orders_dat);

  std::shared_ptr<orders_dat_t> orders_loc(
    new orders_dat_t(num_lines, orders_ks.get()));
  orders = orders_loc;
  printf("units_ai_max=%d\n", get_dat_ai_max() + 1);
}

void DataHub::init_weapons_dat(int num_lines)
{
  string sc_arr_weapons_dat = "arr\\weapons.dat";
  weapons_ks = getKaitaiStream(sc_arr_weapons_dat);

  std::shared_ptr<weapons_dat_t> weapons_loc(
    new weapons_dat_t(num_lines, weapons_ks.get()));
  weapons = weapons_loc;
}

void DataHub::init_flingy_dat(int num_lines)
{
  string sc_arr_flingy_dat = "arr\\flingy.dat";
  flingy_ks = getKaitaiStream(sc_arr_flingy_dat);

  std::shared_ptr<flingy_dat_t> flingy_loc(
    new flingy_dat_t(num_lines, flingy_ks.get()));
  flingy = flingy_loc;
}

void DataHub::init_sprites_dat(int num_lines, int num_decorations)
{
  string sc_arr_sprites_dat = "arr\\sprites.dat";
  sprites_ks = getKaitaiStream(sc_arr_sprites_dat);

  std::shared_ptr<sprites_dat_t> sprites_loc(
    new sprites_dat_t(num_lines, num_decorations, sprites_ks.get()));
  sprites = sprites_loc;
}

void DataHub::init_images_dat(int num_lines)
{
  string sc_arr_images_dat = "arr\\images.dat";
  images_ks = getKaitaiStream(sc_arr_images_dat);

  std::shared_ptr<images_dat_t> images_loc(
    new images_dat_t(num_lines, images_ks.get()));
  images = images_loc;
}

void DataHub::init_sfxdata_dat(int num_lines)
{
  string sc_arr_sfxdata_dat = "arr\\sfxdata.dat";
  sfxdata_ks = getKaitaiStream(sc_arr_sfxdata_dat);

  // 0 means "no sound"
  // TODO: find out if unit_sound_max+1 is needed or not! In some case data seams ok, in others it crash
  std::shared_ptr<sfxdata_dat_t> sfxdata_loc(
    new sfxdata_dat_t(num_lines, sfxdata_ks.get()));
  sfxdata = sfxdata_loc;
}

void DataHub::init_portdata_dat(int num_lines)
{
  string sc_arr_portdata_dat = "arr\\portdata.dat";
  portrait_ks = getKaitaiStream(sc_arr_portdata_dat);

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
  upgrades_ks = getKaitaiStream(sc_arr_upgrades_dat);

  std::shared_ptr<upgrades_dat_t> upgrades_loc(
    new upgrades_dat_t(has_broodwar_flag, num_lines, upgrades_ks.get()));
  upgrades = upgrades_loc;
}

void DataHub::init_techdata_dat(int num_lines, bool has_broodwar_flag)
{
  string sc_arr_techdata_dat = "arr\\techdata.dat";
  techdata_ks = getKaitaiStream(sc_arr_techdata_dat);

  std::shared_ptr<techdata_dat_t> techdata_loc(
    new techdata_dat_t(has_broodwar_flag, num_lines, techdata_ks.get()));
  techdata = techdata_loc;
}

void DataHub::init_mapdata_dat()
{
  string sc_arr_mapdata_dat = "arr\\mapdata.dat";
  mapdata_ks = getKaitaiStream(sc_arr_mapdata_dat);

  std::shared_ptr<mapdata_dat_t> mapdata_loc(
    new mapdata_dat_t(mapdata_ks.get()));
  mapdata = mapdata_loc;
}

void DataHub::init_stat_txt_tbl()
{
  string sc_rez_stat_txt_tbl = "rez\\stat_txt.tbl";
  stat_txt_ks = getKaitaiStream(sc_rez_stat_txt_tbl);

  Tbl stat_txt;
  stat_txt_vec = stat_txt.convertFromStream(stat_txt_ks);
}

void DataHub::init_images_tbl()
{
  string sc_arr_images_tbl = "arr\\images.tbl";
  images_tbl_ks = getKaitaiStream(sc_arr_images_tbl);

  Tbl images_tbl;
  images_tbl_vec = images_tbl.convertFromStream(images_tbl_ks);
}

void DataHub::init_sfxdata_tbl()
{
  string sc_arr_sfxdata_tbl = "arr\\sfxdata.tbl";
  sfxdata_tbl_ks = getKaitaiStream(sc_arr_sfxdata_tbl);

  Tbl sfxdata_tbl;
  sfxdata_tbl_vec = sfxdata_tbl.convertFromStream(sfxdata_tbl_ks);
}

void DataHub::init_portdata_tbl()
{
  string sc_arr_portdata_tbl = "arr\\portdata.tbl";
  portdata_tbl_ks = getKaitaiStream(sc_arr_portdata_tbl);

  Tbl portdata_tbl;
  portdata_tbl_vec = portdata_tbl.convertFromStream(portdata_tbl_ks);
}

void DataHub::init_mapdata_tbl()
{
  string sc_arr_mapdata_tbl = "arr\\mapdata.tbl";
  mapdata_tbl_ks = getKaitaiStream(sc_arr_mapdata_tbl);

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
  printf("weapon_max=%d\n", weapon_max);

  return weapon_max;
}

int DataHub::get_dat_graphics_max() const
{
  std::vector<uint8_t> *units_graphics_vec = units->flingy();
  std::vector<uint32_t> *weapon_graphics_vec = weapons->graphics();

  int unit_graphics_max = *max_element(units_graphics_vec->begin(),
                                       units_graphics_vec->end());
  printf("unit_graphics_max=%d\n", unit_graphics_max);
  int weapon_graphics_max = *max_element(weapon_graphics_vec->begin(),
                                         weapon_graphics_vec->end());
  printf("weapon_graphics_max=%d\n", weapon_graphics_max);
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
  printf("flingy_sprites_max=%d\n", flingy_sprites_max);

  return flingy_sprites_max + 1;
}

int DataHub::get_dat_images_max() const
{
  std::vector<uint16_t> *sprites_images_vec = sprites->image();

  int sprites_image_file_max = *max_element(sprites_images_vec->begin(),
                               sprites_images_vec->end());
  printf("sprites_image_file_max=%d\n", sprites_image_file_max);

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
  printf("unit_sound_max=%d\n", unit_sound_max);

  return unit_sound_max;
}

int DataHub::get_dat_portraits_max() const
{
  std::vector<uint16_t> *units_portrait_vec = units->portrait();

  int units_portrait_max = *max_element(units_portrait_vec->begin(),
                                        units_portrait_vec->end(), portdataCompare);
  printf("units_portrait_max=%d\n", units_portrait_max);

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

  printf("units_upgrade_max=%d\n", units_upgrade_max);

  return units_upgrade_max + 1;
}

int DataHub::get_dat_energy_max() const
{
  std::vector<uint8_t> *orders_energy_vec = orders->energy();
  uint8_t orders_energy_max = *max_element(orders_energy_vec->begin(),
                              orders_energy_vec->end());

  return orders_energy_max;
}

bool DataHub::convert()
{
  //printCSV();

  //convertImages();

  return true;
}

bool DataHub::convertUnits(json &unitsJson,
                                std::map<std::string, std::shared_ptr<Palette>> &paletteMap,
                                std::map<std::string, std::shared_ptr<Palette2D>> palette2DMap)
{
  bool result = true;

  Preferences &preferences = Preferences::getInstance();

  Storage graphics;
  graphics.setDataPath(preferences.getDestDir());
  graphics.setDataType("graphics");

  Storage luagen;
  luagen.setDataPath(preferences.getDestDir());
  luagen.setDataType("luagen");
  CheckPath(luagen.getFullPath());

  ofstream lua_include;
  lua_include.open (luagen("luagen-units.lua").getFullPath());
  string lua_include_str;


  // units.dat
  for(auto &array : unitsJson)
  {
    string unit_name = array.at("name");
    int unit_id = array.at("id");
    bool extractor = true;
    bool save_result = true;

    LOG4CXX_TRACE(mLogger, string("Unit(") + to_string(unit_id) + ")");
    dat::Unit unit(*this, unit_id);

    try
    {
      extractor = array.at("extractor");
    }
    catch (const nlohmann::detail::out_of_range &json_range)
    {
      extractor = true; // default behaviour TODO: maybe better write into JSON file and skip default
    }

    if(extractor)
    {
      uint8_t draw_function = unit.flingy().sprite().image().draw_function();
      uint8_t remapping_function = unit.flingy().sprite().image().remapping();

      string arcfile =  "unit\\" + unit.flingy().sprite().image().grp().name1;

      string grp_storage_file(arcfile);
      replaceString("\\", "/", grp_storage_file);

      // cut the file ending and lower case it
      string grp_storage_file_base = to_lower(cutFileEnding(grp_storage_file, ".grp"));

      cout << unit_name << " : " << arcfile << " => " << grp_storage_file_base << endl;

      Grp grp(mHurricane, arcfile);
      std::shared_ptr<Palette> pal;
      std::shared_ptr<Palette2D> pal2D;

      if(draw_function == 9) // remapping
      {
        if(remapping_function == 1) // ofire
        {
          pal2D = palette2DMap.at("ofire");
          grp.setPalette2D(pal2D);
        }
        else if(remapping_function == 2) // gfire
        {
          pal2D = palette2DMap.at("gfire");
          grp.setPalette2D(pal2D);
        }
        else if(remapping_function == 3) // bfire
        {
          pal2D = palette2DMap.at("bfire");
          grp.setPalette2D(pal2D);
        }
        else if(remapping_function == 4) // bexpl
        {
          pal2D = palette2DMap.at("bexpl");
          grp.setPalette2D(pal2D);
        }
        else // TODO: as default use ofire until I've a better idea....
        {
          pal2D = palette2DMap.at("ofire");
          grp.setPalette2D(pal2D);
        }

        grp.setRGBA(true);
      }
      else // default
      {
        pal = paletteMap.at("install");
        grp.setPalette(pal);
      }

      // TODO: possible optimization possible as some units point toward the same grp
      // could be checked before if the png is yet extracted in the same run
      Storage png_file = graphics(grp_storage_file_base + ".png");
      save_result = grp.save(png_file);

      Storage lua_file_store(luagen(unit_name + ".lua"));
      cout << "lua: " << lua_file_store.getFullPath() << endl;

      ofstream lua_file;
      lua_file.open (lua_file_store.getFullPath());

      Size tilesize = grp.getTileSize();

      string unit_image(lg::assign(
          "Image",
          lg::table({lg::quote("file"), lg::quote(png_file.getRelativePath()), lg::quote("size") , lg::sizeTable(tilesize)}))
          );

      string unit_hitpoints = lg::assign("HitPoints", to_string(unit.hitpoints()));
      string unit_name_translated = lg::assign("Name", lg::quote(unit.name().name1));

      string unit_defintion = lg::DefineUnitType(unit_name,
                                                {unit_name_translated, unit_image, unit_hitpoints});

      lua_include_str += lg::line(lg::function("Load", lg::quote(lua_file_store.getRelativePath())));

      cout << unit_defintion << endl;

      lua_file << unit_defintion;
      lua_file.close();
    }

    printf("...%s\n", save_result ? "ok" : "nok");
  }

  lua_include << lua_include_str;
  lua_include.close();

  return result;
}

void DataHub::printCSV()
{
  string csv_dat;
  char buf[1024];
  const string CSV_ENDLINE = "\n";
  const string CSV_SEPARATOR = ";";

  std::vector<uint32_t> *sfxdata_sound_file_vec;
  std::vector<uint32_t> *mapdata_mission_dir_vec;

  // units.dat
  std::vector<uint8_t> *units_graphics_vec = units->flingy();
  std::vector<uint8_t> *units_ground_weapon_vec = units->ground_weapon();
  std::vector<units_dat_t::staredit_group_flags_type_t *> *se_group_flags_vec =
    units->staredit_group_flags();
  std::vector<uint16_t> *units_ready_sound_vec = units->ready_sound();
  std::vector<uint16_t> *units_portrait_vec = units->portrait();
  std::vector<uint8_t> *units_armor_upgrade_vec = units->armor_upgrade();

  // orders.dat
  std::vector<uint16_t> *orders_label_vec = orders->label();
  std::vector<uint8_t> *orders_energy_vec = orders->energy();

  // weapons.dat
  std::vector<uint16_t> *weapon_label_vec = weapons->label();
  std::vector<uint32_t> *weapon_graphics_vec = weapons->graphics();
  std::vector<uint16_t> *weapon_error_message_vec = weapons->error_message();
  std::vector<uint16_t> *flingy_sprites_vec = flingy->sprite();

  // sprites.dat
  std::vector<uint16_t> *sprites_images_vec = sprites->image();

  std::vector<uint32_t> *images_grp_vec = images->grp();

  sfxdata_sound_file_vec = sfxdata->sound_file();

  std::vector<uint32_t> *portdata_portrait_file_vec = portrait->portrait_file();

  // upgrades.dat
  std::vector<uint16_t> *upgrades_label_vec = upgrades->label();

  // techdata.dat
  uint8_t orders_energy_max = *max_element(orders_energy_vec->begin(),
                              orders_energy_vec->end());

  printf("orders_energy_max=%d\n", orders_energy_max);
  std::vector<uint16_t> *techdata_label_vec = techdata->label();

  // mapdata.dat
  mapdata_mission_dir_vec = mapdata->mission_dir();

  // images.dat
  std::vector<uint8_t> *images_draw_function = images->draw_function();
  std::vector<uint8_t> *images_remapping_function = images->remapping();

  // units.dat
  for (unsigned int i = 0; i < units_graphics_vec->size(); i++)
  {
    csv_dat += "units.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint8_t graphic_id = units_graphics_vec->at(i);
    sprintf(buf, "graphics=%d", graphic_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    units_dat_t::staredit_group_flags_type_t *se_group_flags =
      se_group_flags_vec->at(i);
    bool zerg = se_group_flags->zerg();
    bool terran = se_group_flags->terran();
    bool protoss = se_group_flags->protoss();

    if (zerg)
    {
      csv_dat += "race=zerg";
    }
    else if (terran)
    {
      csv_dat += "race=terran";
    }
    else if (protoss)
    {
      csv_dat += "race=protoss";
    }

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = stat_txt_vec.at(i);
    csv_dat += "ref:name=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    uint16_t sprite_id = flingy_sprites_vec->at(graphic_id);
    sprintf(buf, "ref:sprite=%d", sprite_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    uint16_t weapon_id = units_ground_weapon_vec->at(i);
    sprintf(buf, "weapon=%d", weapon_id);
    csv_dat += buf;

    if (i < units_units_ready_sound_end)
    {
      csv_dat += CSV_SEPARATOR;
      uint16_t ready_sound_id = units_ready_sound_vec->at(i);
      sprintf(buf, "ready_sound=%d", ready_sound_id);
      csv_dat += buf;
    }

    csv_dat += CSV_SEPARATOR;

    uint32_t units_portrait_file = units_portrait_vec->at(i);
    sprintf(buf, "portrait=%d", units_portrait_file);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    if (units_portrait_file != units_portrait_none)
    {
      uint32_t portrait_file = portdata_portrait_file_vec->at(
                                 units_portrait_file);
      sprintf(buf, "ref:portrait_idle_file=%d", portrait_file - 1);
      csv_dat += buf;

      csv_dat += CSV_SEPARATOR;

      TblEntry tblEntry_portrait = portdata_tbl_vec.at(portrait_file - 1);
      csv_dat += "ref:portrait_idle=" + tblEntry_portrait.name1;

      csv_dat += CSV_SEPARATOR;
    }

    if (units_portrait_file != units_portrait_none)
    {
      uint32_t portrait_file = portdata_portrait_file_vec->at(
                                 units_portrait_file);
      sprintf(buf, "ref:portrait_talking_file=%d", portrait_file);
      csv_dat += buf;

      csv_dat += CSV_SEPARATOR;

      TblEntry tblEntry_portrait = portdata_tbl_vec.at(portrait_file);
      csv_dat += "ref:portrait_talking=" + tblEntry_portrait.name1;

      csv_dat += CSV_SEPARATOR;
    }

    csv_dat += CSV_SEPARATOR;

    uint8_t units_armor_upgrade = units_armor_upgrade_vec->at(i);
    sprintf(buf, "units_armor_upgrade=%d", units_armor_upgrade);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // weapons.dat
  for (unsigned int i = 0; i < weapon_label_vec->size(); i++)
  {
    csv_dat += "weapons.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t label_id = weapon_label_vec->at(i);
    sprintf(buf, "label=%d", label_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry_label = stat_txt_vec.at(label_id);
    csv_dat += "ref:name=" + tblEntry_label.name1;

    csv_dat += CSV_SEPARATOR;

    uint32_t graphic = weapon_graphics_vec->at(i);
    sprintf(buf, "graphics=%d", graphic);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    uint16_t error_id = weapon_error_message_vec->at(i);
    sprintf(buf, "error_id=%d", error_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry_error = stat_txt_vec.at(error_id);
    csv_dat += " ref:error_text=" + tblEntry_error.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // flingy.dat
  for (unsigned int i = 0; i < flingy_sprites_vec->size(); i++)
  {
    csv_dat += "flingy.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t flingy_id = flingy_sprites_vec->at(i);
    sprintf(buf, "sprite=%d", flingy_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // sprites.dat
  for (unsigned int i = 0; i < sprites_images_vec->size(); i++)
  {
    csv_dat += "sprites.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t image_id = sprites_images_vec->at(i);
    sprintf(buf, "images_file=%d", image_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // images.dat
  for (unsigned int i = 0; i < images_grp_vec->size(); i++)
  {
    csv_dat += "images.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t grp_id = images_grp_vec->at(i);
    sprintf(buf, "grp_file=%d", grp_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = images_tbl_vec.at(grp_id - 1); // spec says first index is -1
    csv_dat += "ref:name=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += "ref:draw_function=" + to_string(images_draw_function->at(i));

    csv_dat += CSV_SEPARATOR;

    csv_dat += "ref:remapping_function=" + to_string(images_remapping_function->at(i));

    csv_dat += CSV_ENDLINE;
  }

  // sfxdata.dat
  for (unsigned int i = 0; i < sfxdata_sound_file_vec->size(); i++)
  {
    csv_dat += "sfxdata.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint32_t sound_file = sfxdata_sound_file_vec->at(i);
    sprintf(buf, "sound_file=%d", sound_file);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = sfxdata_tbl_vec.at(sound_file);
    csv_dat += "ref:name=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // portrait.dat
  for (unsigned int i = 0; i < portdata_portrait_file_vec->size(); i++)
  {
    csv_dat += "portrait.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint32_t portrait_file = portdata_portrait_file_vec->at(i);
    sprintf(buf, "portrait_file=%d", portrait_file);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = portdata_tbl_vec.at(portrait_file);
    csv_dat += "ref:file=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // upgrades.dat
  for (unsigned int i = 0; i < upgrades_label_vec->size(); i++)
  {
    csv_dat += "upgrades.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t upgrades_label = upgrades_label_vec->at(i);
    sprintf(buf, "upgrades_label=%d", upgrades_label);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = stat_txt_vec.at(upgrades_label);
    csv_dat += "ref:label=" + tblEntry.name1;
    sprintf(buf, "ref:shortcut=%s", tblEntry.shortcut.c_str());
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // orders.dat
  for (unsigned int i = 0; i < orders_label_vec->size(); i++)
  {
    csv_dat += "orders.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t orders_label = orders_label_vec->at(i);
    sprintf(buf, "orders_label=%d", orders_label);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = stat_txt_vec.at(orders_label);
    csv_dat += "ref:label=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // techdata.dat
  for (unsigned int i = 0; i < techdata_label_vec->size(); i++)
  {
    csv_dat += "techdata.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t techdata_label = techdata_label_vec->at(i);
    sprintf(buf, "techdata_label=%d", techdata_label);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = stat_txt_vec.at(techdata_label);
    csv_dat += "ref:label=" + tblEntry.name1;
    csv_dat += CSV_SEPARATOR;
    sprintf(buf, "ref:shortcut=%s", tblEntry.shortcut.c_str());
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;
    sprintf(buf, "ref:shortcut_pos=%d", tblEntry.shortcut_pos);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // mapdata.dat
  for (unsigned int i = 0; i < mapdata_mission_dir_vec->size(); i++)
  {
    csv_dat += "mapdata.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + toString(i);

    csv_dat += CSV_SEPARATOR;

    uint32_t mapdata_label = mapdata_mission_dir_vec->at(i);
    sprintf(buf, "mapdata_label=%d", mapdata_label);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = mapdata_tbl_vec.at(mapdata_label - 1);
    csv_dat += "ref:dir=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // stdout
  cout << csv_dat;
}

bool DataHub::portdataCompare(int val1, int val2)
{
  bool result = false;

  if (val2 != units_portrait_none)
  {
    result = val1 < val2;
  }

  return result;
}

} /* namespace dat */
