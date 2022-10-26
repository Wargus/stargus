/*
 * Widget.h
 *
 *      Author: Andreas Volz
 */

#ifndef WIDGETS_H_
#define WIDGETS_H_

#include "Grp.h"
#include "Palette.h"

// system
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Widgets: public Grp
{
public:
  Widgets(std::shared_ptr<Hurricane> hurricane);
  virtual ~Widgets();

  /**
   * Convert a widget from data container as several PNG files
   */
  bool convert(const std::string &arcfile, Storage filename, json &frameExtractJson);

private:

};

#endif /* WIDGETS_H_ */
