/*
 * Image.h
 *
 *      Author: Andreas Volz
 */

#ifndef IMAGE_H
#define IMAGE_H

// project
#include "ObjectAccess.h"
#include "PropertyNotAvailableException.h"

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

  bool gfx_turns();

  bool clickable();

  bool use_full_iscript();

  bool draw_if_cloaked();

  images_dat_t::draw_function_enum_t draw_function();

  images_dat_t::remapping_enum_t remapping();

  // TODO: Iscript Object
  uint32_t iscript_id();

  uint32_t shield_overlay();
  TblEntry shield_overlay_tbl();

  uint32_t attack_overlay();
  TblEntry attack_overlay_tbl();

  uint32_t damage_overlay();
  TblEntry damage_overlay_tbl();

  uint32_t special_overlay();
  TblEntry special_overlay_tbl();

  uint32_t landing_dust_overlay();
  TblEntry landing_dust_overlay_tbl();

  uint32_t lift_off_dust_overlay();
  TblEntry lift_off_dust_overlay_tbl();

  /***/
  std::string getIDString();

  static const int overlay_none = 0;

private:

};

} /* namespace dat */

#endif /* IMAGE_H */
