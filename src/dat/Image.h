/*
 * Image.h
 *
 *      Author: Andreas Volz
 */

#ifndef IMAGE_H
#define IMAGE_H

// project
#include "ObjectAccess.h"

namespace dat
{

/**
 * Wrapper interface for Kaitai parser images_dat.ksy, but with easier access in the game logic.
 * New functions are added on need as wrapper functions. The function names should stay the same
 * and documentation in only mandatory if needed to understand the difference.
 *
 */
class Image : public ObjectAccess
{
public:
  Image(DataHub &datahub, unsigned int id);
  virtual ~Image();

  uint32_t grp();

  TblEntry grp_tbl();

  uint8_t draw_function();

  uint8_t remapping();

  bool gfx_turns();

  /***/
  std::string getIDString();

private:

};

} /* namespace dat */

#endif /* IMAGE_H */
