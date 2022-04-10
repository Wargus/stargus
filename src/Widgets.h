/*
 * Widget.h
 *
 *      Author: Andreas Volz
 */

#ifndef WIDGETS_H_
#define WIDGETS_H_

#include "Grp.h"

class Widgets: public Grp
{
public:
  Widgets(std::shared_ptr<Hurricane> hurricane);
  virtual ~Widgets();

  /**
   * Convert a widget from data container as several PNG files
   */
  bool convert(const char *mpqfile, const char *arcfile, const char *file);

  void setPalette(std::shared_ptr<Palette> pal);

private:
  /**
   * Save Image part of a Widget as PNG file
   */
  void SaveImage(char *name, unsigned char *image, unsigned char *palp, int id,
      int w, int h);

  /**
   * Save Button part of a Widget as PNG
   */
  void SaveButton(char *name, unsigned char *image, unsigned char *palp,
      int size, int id);

  std::shared_ptr<Palette> mPalette;
};

#endif /* WIDGETS_H_ */
