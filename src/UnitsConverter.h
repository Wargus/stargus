/*
 * UnitsExporter.h
 *
 *      Author: Andreas Volz
 */

#ifndef UNITSEXPORTER_H
#define UNITSEXPORTER_H

// project
#include "dat/DataHub.h"
#include "Storage.h"
#include "dat/Unit.h"

// system

namespace dat
{

/**
 * Walk through the tree of Units in the dat architecture and convert what is referenced
 */
class UnitsConverter : public Converter
{
public:
  UnitsConverter(std::shared_ptr<Hurricane> hurricane, DataHub &datahub);
  virtual ~UnitsConverter();

  bool convert(json &unitsJson);

private:
  std::string makeReadySounds(Unit &unit);
  std::string makeWhatSounds(Unit &unit);
  std::string makeYesSounds(Unit &unit);
  std::string makePissSounds(Unit &unit);
  std::string makeHelpSounds(Unit &unit);

  DataHub &mDatahub;
};

} /* namespace dat */

#endif /* UNITSEXPORTER_H */
