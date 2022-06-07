/*
 * CreateUnitLuaTest.h
 *
 *      Author: Andreas Volz
 */

#ifndef CREATEUNITLUATEST_H
#define CREATEUNITLUATEST_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CreateUnitLuaTest
{
public:
  CreateUnitLuaTest(json &unitsJson);
  virtual ~CreateUnitLuaTest();

private:

};

#endif /* CREATEUNITLUATEST_H */
