/*
 * LuaGen.h
 *
 *      Author: Andreas Volz
 */

#ifndef LUAGEN_H
#define LUAGEN_H

// project
#include "Size.h"

// system
#include <iostream>
#include <string>
#include <list>
#include <initializer_list>

/**
 * Design of this LUA code generator is to be most simple and use strings.
 * But saves typing and less errors adding strings while generating code.
 */
namespace lg
{
  // generic LUA language generators
  std::string function(const std::string &name, const std::initializer_list<std::string> &functionParams);
  std::string function(const std::string &name, const std::string &functionParams);

  std::string table(const std::initializer_list<std::string> &tableElements);
  std::string table(const std::string &content);

  std::string assign(const std::string &left, const std::string &right);

  std::string quote(const std::string &text);

  std::string params(const std::initializer_list<std::string> &params);

  std::string line(const std::string &str);

  // specific stratagus LUA functions
  std::string DefineUnitType(const std::string &id, const std::string &unitTable);
  std::string DefineUnitType(const std::string &id, const std::initializer_list<std::string> &tableElements);

  std::string sizeTable(const Size &s);

} /* namespace luagen */

#endif /* LUAGEN_H */
