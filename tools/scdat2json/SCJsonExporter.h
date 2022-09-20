/*
 * SCJsonExporter.h
 *
 *      Author: Andreas Volz
 */

#ifndef SCJSONEXPORTER_H
#define SCJSONEXPORTER_H

#include "dat/DataHub.h"

class SCJsonExporter
{
public:
  SCJsonExporter(dat::DataHub &datahub);
  virtual ~SCJsonExporter();

  void save(json &j, const std::string &file, bool pretty);

  json export_unit_dat();
  json export_orders_dat();
  json export_weapons_dat();
  json export_flingy_dat();
  json export_sprites_dat();
  json export_images_dat();
  json export_sfxdata_dat();
  json export_portdata_dat();
  json export_upgrades_dat();
  json export_techdata_dat();
  json export_mapdata_dat();

  json export_file_tbl(std::vector<dat::TblEntry> &tblentry_vec);

private:
  dat::DataHub &mDatahub;
};

#endif /* SCJSONEXPORTER_H */
