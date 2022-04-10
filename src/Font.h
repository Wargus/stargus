/*
 * Font.h
 *
 *      Author: Andreas Volz
 */

#ifndef FONT_H_
#define FONT_H_

// Local
#include "Logger.h"

// System
#include <memory>

// Forward declarations
class Hurricane;

class Font
{
public:
  Font(std::shared_ptr<Hurricane> hurricane);
  virtual ~Font();

  bool convert(const std::string &arcfile, const std::string &file);

  void setPalette(std::shared_ptr<Palette> pal);

private:
  /**
   **  Convert font into raw image data
   */
  unsigned char* convertImage(unsigned char *start, int *wp, int *hp);

  Logger mLogger;
  std::shared_ptr<Hurricane> mHurricane;
  std::shared_ptr<Palette> mPalette;
};

#endif /* FONT_H_ */
