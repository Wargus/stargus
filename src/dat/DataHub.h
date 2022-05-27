/*
 * DataHub.h
 *
 *      Author: Andreas Volz
 */

#ifndef DATAHUB_H
#define DATAHUB_H

// project
#include "KaitaiConverter.h"
#include "Palette.h"
#include "Palette2D.h"
#include "Tbl.h"

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
#include <nlohmann/json.hpp>
#include <map>

using json = nlohmann::json;

namespace dat
{

/**
 * The DataHub parses the complete data structures inside those files:
 * - arr\\units.dat
 * - arr\\orders.dat
 * - arr\\weapons.dat
 * - arr\\flingy.dat
 * - arr\\sprites.dat
 * - arr\\images.dat
 * - arr\\sfxdata.dat
 * - arr\\portdata.dat
 * - arr\\upgrades.dat
 * - arr\\techdata.dat
 * - arr\\mapdata.dat
 * - rez\\stat_txt.tbl
 * - arr\\images.tbl
 * - arr\\sfxdata.tbl
 * - arr\\portdata.tbl
 * - arr\\mapdata.tbl
 *
 * As those data has have depends on each other they're all parsed together in one run. After being parsed
 * to Kaitai data structures they could be accessed from outside.
 *
 * The Kaitai parsed objects in this class are by intension public. There's no benefit in putting dozen silly
 * getter around them. The alternative to put them private means to implement every parser logic
 * inside this class or friend them all.
 *
 * So the design decision is just to let them public and the outside accessing function should only read them!
 * If I ever put this stuff to a general purpose library this design might change.
 *
 *  "with great power comes great responsibility" - (Spiderman)
 */
class DataHub : public KaitaiConverter
{
public:
  DataHub(std::shared_ptr<Hurricane> hurricane);
  virtual ~DataHub();

  bool convert();

  bool convertUnits(json &unitsJson,
                         std::map<std::string, std::shared_ptr<Palette>> &paletteMap,
                         std::map<std::string, std::shared_ptr<Palette2D>> palette2DMap);

  // Kaitai parsed objects
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

  // kaitai parsed Tbl vectors
  std::vector<TblEntry> stat_txt_vec;
  std::vector<TblEntry> images_tbl_vec;
  std::vector<TblEntry> sfxdata_tbl_vec;
  std::vector<TblEntry> portdata_tbl_vec;
  std::vector<TblEntry> mapdata_tbl_vec;

  static const int units_portrait_none = 65535;
  static const int units_units_ready_sound_end = 106;

private:
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

};

} /* namespace dat */

#endif /* DATAHUB_H */
