/*
 * Image.h
 *
 *      Author: Andreas Volz
 */

#ifndef IMAGE_H
#define IMAGE_H

// project
#include "DataHub.h"

namespace dat
{

/**
 * Wrapper interface for Kaitai parser images_dat.ksy, but with easier access in the game logic.
 * New functions are added on need as wrapper functions. The function names should stay the same
 * and documentation in only mandatory if needed to understand the difference.
 *
 */
class Image
{
public:
  Image(DataHub &datahub, uint16_t id);
  virtual ~Image();

  TblEntry grp();

  uint8_t draw_function();

  uint8_t remapping();

  bool gfx_turns();

  /***/
  static std::string createID(const std::string &image);

private:
  DataHub &mDatahub;
  uint16_t mId;
};

} /* namespace dat */

#endif /* IMAGE_H */
