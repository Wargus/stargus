/*
 * LuaTest.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "CreateUnitLuaTest.h"

// system
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  // read in the json file
  std::ifstream json_file("dataset/units.json");
  json units_json;
  json_file >> units_json;

  cout << "Run CreateUnitLuaTest..." << endl;
  CreateUnitLuaTest createUnitLuaTest(units_json);


  return 0;
}

