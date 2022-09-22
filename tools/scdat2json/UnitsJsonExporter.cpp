/*
 * UnitsJsonExporter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "UnitsJsonExporter.h"
#include "to_json.h"

// system
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace dat;

UnitsJsonExporter::UnitsJsonExporter(dat::DataHub &datahub)  :
  mDatahub(datahub)
{

}

UnitsJsonExporter::~UnitsJsonExporter()
{

}




void UnitsJsonExporter::exportUnit(unsigned int id, const std::string &idString)
{
  Unit unit(mDatahub, id, idString);

  json j;

  json j_unit(unit);
  j["unit"] = j_unit;

  //cout << j_unit << endl;
  cout << std::setw(4) << j;

}

