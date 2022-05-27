/*
 * CSVExporter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "CSVExporter.h"

// system
#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace dat
{

CSVExporter::CSVExporter(DataHub &datahub) :
  mDatahub(datahub)
{

}

CSVExporter::~CSVExporter()
{

}

void CSVExporter::print()
{
  string csv_dat;
  char buf[1024];
  const string CSV_ENDLINE = "\n";
  const string CSV_SEPARATOR = ";";

  std::vector<uint32_t> *sfxdata_sound_file_vec;
  std::vector<uint32_t> *mapdata_mission_dir_vec;

  // units.dat
  std::vector<uint8_t> *units_graphics_vec = mDatahub.units->flingy();
  std::vector<uint8_t> *units_ground_weapon_vec = mDatahub.units->ground_weapon();
  std::vector<units_dat_t::staredit_group_flags_type_t *> *se_group_flags_vec =
      mDatahub.units->staredit_group_flags();
  std::vector<uint16_t> *units_ready_sound_vec = mDatahub.units->ready_sound();
  std::vector<uint16_t> *units_portrait_vec = mDatahub.units->portrait();
  std::vector<uint8_t> *units_armor_upgrade_vec = mDatahub.units->armor_upgrade();

  // orders.dat
  std::vector<uint16_t> *orders_label_vec = mDatahub.orders->label();
  std::vector<uint8_t> *orders_energy_vec = mDatahub.orders->energy();

  // weapons.dat
  std::vector<uint16_t> *weapon_label_vec = mDatahub.weapons->label();
  std::vector<uint32_t> *weapon_graphics_vec = mDatahub.weapons->graphics();
  std::vector<uint16_t> *weapon_error_message_vec = mDatahub.weapons->error_message();
  std::vector<uint16_t> *flingy_sprites_vec = mDatahub.flingy->sprite();

  // sprites.dat
  std::vector<uint16_t> *sprites_images_vec = mDatahub.sprites->image();

  std::vector<uint32_t> *images_grp_vec = mDatahub.images->grp();

  sfxdata_sound_file_vec = mDatahub.sfxdata->sound_file();

  std::vector<uint32_t> *portdata_portrait_file_vec = mDatahub.portrait->portrait_file();

  // upgrades.dat
  std::vector<uint16_t> *upgrades_label_vec = mDatahub.upgrades->label();

  // techdata.dat
  uint8_t orders_energy_max = *max_element(orders_energy_vec->begin(),
                              orders_energy_vec->end());

  printf("orders_energy_max=%d\n", orders_energy_max);
  std::vector<uint16_t> *techdata_label_vec = mDatahub.techdata->label();

  // mapdata.dat
  mapdata_mission_dir_vec = mDatahub.mapdata->mission_dir();

  // images.dat
  std::vector<uint8_t> *images_draw_function = mDatahub.images->draw_function();
  std::vector<uint8_t> *images_remapping_function = mDatahub.images->remapping();

  // units.dat
  for (unsigned int i = 0; i < units_graphics_vec->size(); i++)
  {
    csv_dat += "units.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + to_string(i);

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

    TblEntry tblEntry = mDatahub.stat_txt_vec.at(i);
    csv_dat += "ref:name=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    uint16_t sprite_id = flingy_sprites_vec->at(graphic_id);
    sprintf(buf, "ref:sprite=%d", sprite_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    uint16_t weapon_id = units_ground_weapon_vec->at(i);
    sprintf(buf, "weapon=%d", weapon_id);
    csv_dat += buf;

    if (i < DataHub::units_units_ready_sound_end)
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

    if (units_portrait_file != DataHub::units_portrait_none)
    {
      uint32_t portrait_file = portdata_portrait_file_vec->at(
                                 units_portrait_file);
      sprintf(buf, "ref:portrait_idle_file=%d", portrait_file - 1);
      csv_dat += buf;

      csv_dat += CSV_SEPARATOR;

      TblEntry tblEntry_portrait = mDatahub.portdata_tbl_vec.at(portrait_file - 1);
      csv_dat += "ref:portrait_idle=" + tblEntry_portrait.name1;

      csv_dat += CSV_SEPARATOR;
    }

    if (units_portrait_file != DataHub::units_portrait_none)
    {
      uint32_t portrait_file = portdata_portrait_file_vec->at(
                                 units_portrait_file);
      sprintf(buf, "ref:portrait_talking_file=%d", portrait_file);
      csv_dat += buf;

      csv_dat += CSV_SEPARATOR;

      TblEntry tblEntry_portrait = mDatahub.portdata_tbl_vec.at(portrait_file);
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

    csv_dat += "id=" + to_string(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t label_id = weapon_label_vec->at(i);
    sprintf(buf, "label=%d", label_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry_label = mDatahub.stat_txt_vec.at(label_id);
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

    TblEntry tblEntry_error = mDatahub.stat_txt_vec.at(error_id);
    csv_dat += " ref:error_text=" + tblEntry_error.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // flingy.dat
  for (unsigned int i = 0; i < flingy_sprites_vec->size(); i++)
  {
    csv_dat += "flingy.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + to_string(i);

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

    csv_dat += "id=" + to_string(i);

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

    csv_dat += "id=" + to_string(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t grp_id = images_grp_vec->at(i);
    sprintf(buf, "grp_file=%d", grp_id);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = mDatahub.images_tbl_vec.at(grp_id - 1); // spec says first index is -1
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

    csv_dat += "id=" + to_string(i);

    csv_dat += CSV_SEPARATOR;

    uint32_t sound_file = sfxdata_sound_file_vec->at(i);
    sprintf(buf, "sound_file=%d", sound_file);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = mDatahub.sfxdata_tbl_vec.at(sound_file);
    csv_dat += "ref:name=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // portrait.dat
  for (unsigned int i = 0; i < portdata_portrait_file_vec->size(); i++)
  {
    csv_dat += "portrait.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + to_string(i);

    csv_dat += CSV_SEPARATOR;

    uint32_t portrait_file = portdata_portrait_file_vec->at(i);
    sprintf(buf, "portrait_file=%d", portrait_file);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = mDatahub.portdata_tbl_vec.at(portrait_file);
    csv_dat += "ref:file=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // upgrades.dat
  for (unsigned int i = 0; i < upgrades_label_vec->size(); i++)
  {
    csv_dat += "upgrades.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + to_string(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t upgrades_label = upgrades_label_vec->at(i);
    sprintf(buf, "upgrades_label=%d", upgrades_label);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = mDatahub.stat_txt_vec.at(upgrades_label);
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

    csv_dat += "id=" + to_string(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t orders_label = orders_label_vec->at(i);
    sprintf(buf, "orders_label=%d", orders_label);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = mDatahub.stat_txt_vec.at(orders_label);
    csv_dat += "ref:label=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // techdata.dat
  for (unsigned int i = 0; i < techdata_label_vec->size(); i++)
  {
    csv_dat += "techdata.dat";

    csv_dat += CSV_SEPARATOR;

    csv_dat += "id=" + to_string(i);

    csv_dat += CSV_SEPARATOR;

    uint16_t techdata_label = techdata_label_vec->at(i);
    sprintf(buf, "techdata_label=%d", techdata_label);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = mDatahub.stat_txt_vec.at(techdata_label);
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

    csv_dat += "id=" + to_string(i);

    csv_dat += CSV_SEPARATOR;

    uint32_t mapdata_label = mapdata_mission_dir_vec->at(i);
    sprintf(buf, "mapdata_label=%d", mapdata_label);
    csv_dat += buf;

    csv_dat += CSV_SEPARATOR;

    TblEntry tblEntry = mDatahub.mapdata_tbl_vec.at(mapdata_label - 1);
    csv_dat += "ref:dir=" + tblEntry.name1;

    csv_dat += CSV_SEPARATOR;

    csv_dat += CSV_ENDLINE;
  }

  // stdout
  cout << csv_dat;
}


} /* namespace dat */
