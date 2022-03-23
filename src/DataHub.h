/*
 * DataHub.h
 *
 *      Author: Andreas Volz
 */

#ifndef DATAHUB_H_
#define DATAHUB_H_

// Local
#include "kaitai/kaitaistream.h"
#include "Logger.h"
#include "Converter.h"
#include "kaitai/units_dat.h"
#include "kaitai/weapons_dat.h"
#include "kaitai/flingy_dat.h"
#include "kaitai/sprites_dat.h"
#include "kaitai/images_dat.h"
#include "kaitai/sfxdata_dat.h"
#include "kaitai/portdata_dat.h"
#include "kaitai/upgrades_dat.h"
#include "kaitai/orders_dat.h"
#include "kaitai/techdata_dat.h"
#include "kaitai/mapdata_dat.h"

// System
#include <memory>

class DataHub: public Converter
{
public:
  DataHub(std::shared_ptr<Hurricane> hurricane);
  virtual ~DataHub();

  virtual bool convert(const std::string &arcfile, const std::string &file);

private:
  Logger mLogger;

  static const int units_portrait_none = 65535;
  static const int units_units_ready_sound_end = 106;

  // Kaitai streams
  std::shared_ptr<kaitai::kstream> stat_txt_ks;
  std::shared_ptr<kaitai::kstream> mUnits_ks;
  std::shared_ptr<kaitai::kstream> orders_ks;
  std::shared_ptr<kaitai::kstream> weapons_ks;
  std::shared_ptr<kaitai::kstream> flingy_ks;
  std::shared_ptr<kaitai::kstream> sprites_ks;
  std::shared_ptr<kaitai::kstream> images_ks;
  std::shared_ptr<kaitai::kstream> images_tbl_ks;
  std::shared_ptr<kaitai::kstream> sfxdata_ks;
  std::shared_ptr<kaitai::kstream> sfxdata_tbl_ks;
  std::shared_ptr<kaitai::kstream> portrait_ks;
  std::shared_ptr<kaitai::kstream> portdata_tbl_ks;
  std::shared_ptr<kaitai::kstream> upgrades_ks;
  std::shared_ptr<kaitai::kstream> techdata_ks;
  std::shared_ptr<kaitai::kstream> mapdata_ks;
  std::shared_ptr<kaitai::kstream> mapdata_tbl_ks;

  // Kaitai parser objects
  std::shared_ptr<units_dat_t> units;
  std::shared_ptr<orders_dat_t> orders;
  std::shared_ptr<weapons_dat_t> weapons;
  std::shared_ptr<flingy_dat_t> flingy;
  std::shared_ptr<sprites_dat_t> sprites;
  std::shared_ptr<images_dat_t> images;
  std::shared_ptr<sfxdata_dat_t> sfxdata;
  std::shared_ptr<portdata_dat_t> portrait;
  std::shared_ptr<upgrades_dat_t> upgrades;
  std::shared_ptr<techdata_dat_t> techdata;
  std::shared_ptr<mapdata_dat_t> mapdata;

  // Tbl vectors
  std::vector<TblEntry> stat_txt_vec;
  std::vector<TblEntry> images_tbl_vec;
  std::vector<uint32_t> *sfxdata_sound_file_vec;
  std::vector<TblEntry> sfxdata_tbl_vec;
  std::vector<TblEntry> portdata_tbl_vec;
  std::vector<uint32_t> *mapdata_mission_dir_vec;
  std::vector<TblEntry> mapdata_tbl_vec;

  void convertImages();

  std::shared_ptr<kaitai::kstream> getKaitaiStream(const std::string &file);

  void initKaitaiStreams();

  // units.dat
  void init_units_dat(bool has_broodwar_flag, bool has_max_air_hits,
      bool has_max_ground_hits);

  // orders.dat
  void init_orders_dat(int num_lines);

  // weapons.dat
  void init_weapons_dat(int num_lines);

  // flingy.dat
  void init_flingy_dat(int num_lines);

  // sprites.dat
  void init_sprites_dat(int num_lines, int num_decorations);

  // images.dat
  void init_images_dat(int num_lines);

  // sfxdata.dat
  void init_sfxdata_dat(int num_lines);

  // portdata.dat
  void init_portdata_dat(int num_lines);

  // upgrades.dat
  void init_upgrades_dat(int num_lines, bool has_broodwar_flag);

  // techdata.dat
  void init_techdata_dat(int num_lines, bool has_broodwar_flag);

  // mapdata.dat
  void init_mapdata_dat();

  // stat_txt.tbl
  void init_stat_txt_tbl();

  // images.tbl
  void init_images_tbl();

  // sfxdata.tbl
  void init_sfxdata_tbl();

  // portdata.tbl
  void init_portdata_tbl();

  // mapdata.tbl
  void init_mapdata_tbl();

  int get_dat_ai_max() const;

  int get_dat_weapons_max() const;

  int get_dat_graphics_max() const;

  int get_dat_sprites_max() const;

  int get_dat_images_max() const;

  int get_dat_sounds_max() const;

  int get_dat_portraits_max() const;

  int get_dat_upgrades_max() const;

  int get_dat_energy_max() const;

  static bool portdataCompare(int val1, int val2);

  void printCSV();
};

#endif /* DATAHUB_H_ */
