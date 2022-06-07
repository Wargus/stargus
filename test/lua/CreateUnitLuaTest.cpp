/*
 * CreateUnitLuaTest.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "CreateUnitLuaTest.h"
#include "luagen.h"
#include "Storage.h"
#include "FileUtil.h"

// system
#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

CreateUnitLuaTest::CreateUnitLuaTest(json &unitsJson)
{
  Storage luagen;
  luagen.setDataPath("data"); // FIXME for now need to copy this manually into your data directory
  luagen.setDataType("luagen/tests");
  CheckPath(luagen.getFullPath());

  Storage lua_file_store(luagen("CreateUnitLuaTest.lua"));

  ofstream lua_file;
  lua_file.open (lua_file_store.getFullPath());

  lua_file << lg::line("function CreateUnitLuaTest()");

  unsigned int end = 0;
  for(auto &array : unitsJson)
  {
    string unit_name = array.at("name");

    // intermediate solution to jump over (currently/not yet) known not working units
    vector<string> brokenUnits({

    });

    if(std::find(brokenUnits.begin(), brokenUnits.end(), unit_name) == brokenUnits.end())
    {
      string create_unit = lg::CreateUnit(unit_name, 0, Pos(0,0));
      string print_create_unit = lg::function("print", lg::singleQuote(create_unit));

      lua_file << print_create_unit << endl;
      lua_file << create_unit << endl;
    }

    end++;
  }

  lua_file << lg::line("end");

  lua_file.close();

}

CreateUnitLuaTest::~CreateUnitLuaTest()
{

}

