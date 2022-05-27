/*
 * CSVExporter.h
 *
 *      Author: Andreas Volz
 */

#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include "DataHub.h"

namespace dat
{

/**
 * Just some experiments for development to print the dat files into a csv compatible format
 */
class CSVExporter
{
public:
  CSVExporter(DataHub &datahub);
  virtual ~CSVExporter();

  void print();

private:
  DataHub &mDatahub;
};

} /* namespace dat */

#endif /* CSVEXPORTER_H */
