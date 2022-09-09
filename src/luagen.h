/*
 * luagen.h
 *
 *      Author: Andreas Volz
 */

#ifndef LUAGEN_H
#define LUAGEN_H

// project
#include "Size.h"
#include "Pos.h"

// system
#include <iostream>
#include <string>
#include <list>
#include <initializer_list>
#include <vector>

/**
 * Design of this LUA code generator is to be most simple and use strings.
 * But saves typing and less errors adding strings while generating code.
 */
namespace lg
{
  // type generators
  std::string boolean(bool b);

  // generic LUA language generators
  std::string function(const std::string &name, const std::initializer_list<std::string> &functionParams);
  std::string function(const std::string &name, const std::string &functionParams);

  /**
   * Create a LUA table from the std::initializer_list. The function calls implicit params().
   *
   * @return example: {one, two, three}
   */
  std::string table(const std::initializer_list<std::string> &tableElements);

  /**
   * Create a LUA table from the input string. So it assumes the input string is yet in a parameterized form.
   *
   * @return example: {example}
   */
  std::string table(const std::string &content);

  /**
   * Create a LUA assignment from left and right side
   *
   * @return example: left = right
   */
  std::string assign(const std::string &left, const std::string &right);

  /**
   * Put surrounding quotes around:
   *
   * @return example: "example"
   */
  std::string quote(const std::string &text);

  /**
   * Put surrounding quotes around:
   *
   * @return example: 'example'
   */
  std::string singleQuote(const std::string &text);

  /**
   * internal template function for implementation of params() outer interfaces
   */
  template<typename T>
  std::string params(T first, T last)
  {
    std::string param_str;

    for(auto func_it = first; func_it != last; func_it++)
    {
      const std::string &param = *func_it;

      if(func_it != first)
      {
        param_str += ", ";
      }

      param_str += param;
    }

    return param_str;
  }

  /**
   * Loop over the parameters and generate a comma separated function parameter list
   *
   * @param params_init_list give input list in form of {...} initializer list
   *
   * @return example: one, two, three
   */
  std::string params(const std::initializer_list<std::string> &params_init_list);

  /**
   * Loop over the parameters and generate a comma separated function parameter list
   *
   * @param param_vector give input list in form of vector initializer list
   *
   * @return example: one, two, three
   */
  std::string params(const std::vector<std::string> &params_vector);

  /**
   * internal template function for implementation of paramsQuote() outer interfaces
   */
  template<typename T>
  std::string paramsQuote(T first, T last)
  {
    std::string param_str;

    for(auto func_it = first; func_it != last; func_it++)
    {
      const std::string &param = *func_it;

      if(func_it != first)
      {
        param_str += ", ";
      }

      param_str += "\"" + param + "\"";
    }

    return param_str;
  }

  /**
   * Convenience function to quote all parameters
   *
   * @return example: "one", "two", "three"
   */
  std::string paramsQuote(const std::initializer_list<std::string> &params_init_list);

  /**
   * Convenience function to quote all parameters
   *
   * @return example: "one", "two", "three"
   */
  std::string paramsQuote(const std::vector<std::string> &params_vector);

  /**
   * No function, just some explicit simple pretty printing by ensure to put a newline at the end.
   *
   * @return example: example\n
   */
  std::string line(const std::string &str);

  /**
   * Convenience function to create a a LUA table that represents a Size object
   *
   * @return example: {width, height}
   */
  std::string sizeTable(const Size &s);

  /**
   * Convenience function to create a a LUA table that represents a Pos object (psoition coordinate)
   * @return example: {x, y}
   */
  std::string posTable(const Pos &p);

  /**
   * Convenience function to define a stratagus unit by calling function() with specific parameters.
   * What ever you give as parameters will be included. For sure you need to set something useful as "name" or "image",
   * but all are optional and the caller has to decide.
   *
   * @return example: DefineUnitType("unit-type", {one, two, three})
   */
  std::string DefineUnitType(const std::string &id, const std::initializer_list<std::string> &elementsTable);

  /**
   * Convenience function to define a stratagus unit but with a pre-generated table string as input.
   */
  std::string DefineUnitType(const std::string &id, const std::string &unitTable);


  /**
   * Create a stratagus unit by referencing before defined units. This is done on the map format.
   */
  std::string CreateUnit(const std::string &id, int playerID, const Pos &pos);

  /**
   * Create a Tileset definition for stratagus.
   *
   * @param slotsTable the slots should be defined by convenience function tilesetSlotEntry() because of complexity
   *
   * @return example: DefineTileset("name", "myname", "image", "myimage.png", "slots", {slotsTable})
 }},
   */
  std::string DefineTileset(const std::string &name, const std::string &image, const std::initializer_list<std::string> &slotsTable);

  /**
   * Create a single tileset slot entry for usage in DefineTileset()
   *
   * @param type "mixed" or "solid", the parameter is quoted by default
   * @param propertiesQuotedParams The parameters are quoted by default
   * @param tilesTable the tiles not quoted by default
   *
   * @return example: "solid", {"property1", "property2", {1, 2, 3}}
 }}
   */
  std::string tilesetSlotEntry(const std::string &type, const std::initializer_list<std::string> &propertiesQuotedParams, const std::initializer_list<std::string> &tilesTable);

} /* namespace luagen */

#endif /* LUAGEN_H */
