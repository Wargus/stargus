/*
 * CSVExporter.h
 *
 *      Author: Andreas Volz
 */

#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include "dat/DataHub.h"

/**
 * Just some experiments for development to print the dat files into a csv compatible format
 */
class CSVExporter
{
public:
  CSVExporter(dat::DataHub &datahub);
  virtual ~CSVExporter();

  void print();

private:
  dat::DataHub &mDatahub;
};

#endif /* CSVEXPORTER_H */
