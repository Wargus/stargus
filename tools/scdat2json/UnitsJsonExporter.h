/*
 * UnitsJsonExporter.h
 *
  *      Author: Andreas Volz
 */

#ifndef UNITSJSONEXPORTER_H
#define UNITSJSONEXPORTER_H

#include "dat/DataHub.h"

class UnitsJsonExporter
{
public:
  UnitsJsonExporter(dat::DataHub &datahub);
  virtual ~UnitsJsonExporter();

  void exportUnit(unsigned int id);

private:
  dat::DataHub &mDatahub;
};

#endif /* UNITSJSONEXPORTER_H */
