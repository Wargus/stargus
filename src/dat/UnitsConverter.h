/*
 * UnitsExporter.h
 *
 *      Author: Andreas Volz
 */

#ifndef UNITSEXPORTER_H
#define UNITSEXPORTER_H

// project
#include "DataHub.h"
#include "Storage.h"

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

  bool convert(json &unitsJson,
               std::map<std::string, std::shared_ptr<Palette>> &paletteMap,
               std::map<std::string, std::shared_ptr<Palette2D>> palette2DMap);

private:
  void convertGrp(const std::string &arcfile, Storage storage);

  DataHub &mDatahub;
};

} /* namespace dat */

#endif /* UNITSEXPORTER_H */
