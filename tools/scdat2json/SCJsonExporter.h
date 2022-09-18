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

  bool export_unit_dat();

private:
  dat::DataHub &mDatahub;
};

#endif /* SCJSONEXPORTER_H */
