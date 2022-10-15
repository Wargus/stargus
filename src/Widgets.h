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
  bool convert(const char *arcfile, const char *file);

  bool convert2(const std::string &arcfile, Storage filename, json &frameExtractJson);

private:
  /**
   * Save Image part of a Widget as PNG file
   */
  void SaveImage(char *name, unsigned char *image, int id,
      int w, int h);

  /**
   * Save Button part of a Widget as PNG
   */
  void SaveButton(char *name, unsigned char *image,
      int size, int id);

};

#endif /* WIDGETS_H_ */
