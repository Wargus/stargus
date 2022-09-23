/*
 * Image.cpp
 *
 *      Author: Andreas Volz
 */

#include "Image.h"
#include "Logger.h"
#include "platform.h"
#include "StringUtil.h"

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.Image");

Image::Image(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

Image::~Image()
{

}

uint32_t Image::grp()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint32_t grp_id = mDatahub.images->grp()->at(mId);

  return grp_id;
}

TblEntry Image::grp_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images_tbl_vec.at(grp()-1);
}

bool Image::gfx_turns()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->gfx_turns()->at(mId);
}

bool Image::clickable()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->clickable()->at(mId);
}

bool Image::use_full_iscript()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->use_full_iscript()->at(mId);
}

bool Image::draw_if_cloaked()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->draw_if_cloaked()->at(mId);
}

images_dat_t::draw_function_enum_t Image::draw_function()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->draw_function()->at(mId);
}

images_dat_t::remapping_enum_t Image::remapping()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->remapping()->at(mId);
}

uint32_t Image::iscript_id()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->iscript_id()->at(mId);
}

uint32_t Image::shield_overlay()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->shield_overlay()->at(mId);
}

TblEntry Image::shield_overlay_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint32_t overlay = shield_overlay();

  if(overlay == Image::overlay_none)
    {
      throw PropertyNotAvailableException(mId, "shield_overlay_tbl");
    }

  return  mDatahub.images_tbl_vec.at(overlay);
}

uint32_t Image::attack_overlay()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->attack_overlay()->at(mId);
}

TblEntry Image::attack_overlay_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint32_t overlay = attack_overlay();

  if(overlay == Image::overlay_none)
    {
      throw PropertyNotAvailableException(mId, "attack_overlay_tbl");
    }

  return  mDatahub.images_tbl_vec.at(overlay);
}

uint32_t Image::damage_overlay()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->damage_overlay()->at(mId);
}

TblEntry Image::damage_overlay_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint32_t overlay = damage_overlay();

  if(overlay == Image::overlay_none)
    {
      throw PropertyNotAvailableException(mId, "damage_overlay_tbl");
    }

  return  mDatahub.images_tbl_vec.at(overlay);
}

uint32_t Image::special_overlay()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->special_overlay()->at(mId);
}

TblEntry Image::special_overlay_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint32_t overlay = special_overlay();

  if(overlay == Image::overlay_none)
    {
      throw PropertyNotAvailableException(mId, "special_overlay_tbl");
    }

  return  mDatahub.images_tbl_vec.at(overlay);
}

uint32_t Image::landing_dust_overlay()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->landing_dust_overlay()->at(mId);
}

TblEntry Image::landing_dust_overlay_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint32_t overlay = landing_dust_overlay();

  if(overlay == Image::overlay_none)
    {
      throw PropertyNotAvailableException(mId, "landing_dust_overlay_tbl");
    }

  return  mDatahub.images_tbl_vec.at(overlay);
}

uint32_t Image::lift_off_dust_overlay()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.images->lift_off_dust_overlay()->at(mId);
}

TblEntry Image::lift_off_dust_overlay_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint32_t overlay = lift_off_dust_overlay();

  if(overlay == Image::overlay_none)
    {
      throw PropertyNotAvailableException(mId, "lift_off_dust_overlay_tbl");
    }

  return  mDatahub.images_tbl_vec.at(overlay);
}

std::string Image::getIDString()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  string image_name("image_" + to_string(mId) + "_" + grp_tbl().name1);
  replaceString("\\", "_", image_name);
  //fs::path p(image_name);

  image_name = to_lower(cutFileEnding(image_name));
  //cout << "image_name: " << image_name << endl;

  return image_name;
}

} /* namespace dat */
