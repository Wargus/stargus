/*
 * Widget.h
 *
 *      Author: Andreas Volz
 */

#ifndef WIDGETS_H_
#define WIDGETS_H_

#include "Grp.h"
#include "Palette.h"

class Widgets: public Grp
{
public:
  Widgets(std::shared_ptr<Hurricane> hurricane);
  virtual ~Widgets();

  /**
   * Convert a widget from data container as several PNG files
   */
  bool convert(const char *arcfile, const char *file);

  void setPalette(std::shared_ptr<AbstractPalette> pal);

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

  std::shared_ptr<AbstractPalette> mPalette;
};

#endif /* WIDGETS_H_ */
