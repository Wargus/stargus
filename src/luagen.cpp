/*
 * luagen.cpp
 *
 *      Author: Andreas Volz
 */

#include <luagen.h>

using namespace std;

namespace lg {

std::string function(const std::string &name, const std::initializer_list<std::string> &functionParams)
{
  return function(name, params(functionParams));
}

std::string function(const std::string &name, const std::string &functionParams)
{
  string func_str(name + "(");
  func_str += functionParams;
  func_str += ")";

  return func_str;
}

std::string table(const std::initializer_list<std::string> &tableElements)
{
  return table(params(tableElements));
}

std::string table(const std::string &content)
{
  string table_str("{");
  table_str += content;
  table_str += "}";

  return table_str;
}

std::string assign(const std::string &left, const std::string &right)
{
  string assign_str(left + " = " + right);

  return assign_str;
}

std::string quote(const std::string &text)
{
  string quote_str("\"");
  quote_str += text;
  quote_str += "\"";

  return quote_str;
}

std::string params(const std::initializer_list<std::string> &params_init_list)
{
  return params(params_init_list.begin(), params_init_list.end());
}

std::string params(const std::vector<std::string> &param_vector)
{
  return params(param_vector.begin(), param_vector.end());
}

std::string paramsQuote(const std::initializer_list<std::string> &params)
{
  string param_str;

  unsigned int i = 1;
  for(auto func_it = params.begin(); func_it != params.end(); func_it++)
  {
    const std::string &param = *func_it;
    param_str += "\"" + param + "\"";

    if(i < params.size())
    {
      param_str += ", ";
    }

    i++;
  }

  return param_str;
}

std::string line(const std::string &str)
{
  return string(str + '\n');
}

std::string sizeTable(const Size &s)
{
  return table({to_string(s.getWidth()), to_string(s.getHeight())});
}

std::string posTable(const Pos &p)
{
  return table({to_string(p.getX()), to_string(p.getY())});
}

std::string DefineUnitType(const std::string &id, const std::string &unitTable)
{
  return function("DefineUnitType", {quote(id), unitTable});
}

std::string DefineUnitType(const std::string &id, const std::initializer_list<std::string> &tableElements)
{
  return DefineUnitType(id, table(tableElements));
}

std::string CreateUnit(const std::string &id, int playerID, const Pos &pos)
{
  return function("CreateUnit", {quote(id), to_string(playerID), posTable(pos)});
}

std::string DefineTileset(const std::string &name, const std::string &image, const std::initializer_list<std::string> &slotsTable)
{
  return function("DefineTileset", {quote("name"), quote(name), quote("image"), quote(image), quote("slots"), table(slotsTable)});
}

std::string tilesetSlotEntry(const std::string &type, const std::initializer_list<std::string> &propertiesQuotedParams, const std::initializer_list<std::string> &tilesTable)
{
  return params({quote(type), table({paramsQuote(propertiesQuotedParams), table(tilesTable)})});
}

std::string tilesetSlotEntryNonMix(const std::string &type, const std::initializer_list<std::string> &propertiesQuotedParams, const std::initializer_list<std::string> &tilesTable)
{
  return params({quote(type), table({paramsQuote(propertiesQuotedParams), table(tilesTable)})});
}

} /* namespace lg */
