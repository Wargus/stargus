/*
 * Image.cpp
 *
 *      Author: Andreas Volz
 */

#include "Image.h"
#include "Logger.h"

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.Image");

Image::Image(DataHub &datahub, uint16_t id) :
  mDatahub(datahub),
  mId(id)
{

}

Image::~Image()
{

}

TblEntry Image::grp()
{
  uint32_t grp_id = mDatahub.images->grp()->at(mId);
  LOG4CXX_TRACE(logger, string("grp(") + to_string(grp_id) + ")");

  TblEntry tbl_entry = mDatahub.images_tbl_vec.at(grp_id-1);

  return tbl_entry;
}

uint8_t Image::draw_function()
{
  uint8_t draw_function_id = mDatahub.images->draw_function()->at(mId);
  LOG4CXX_TRACE(logger, string("draw_function(") + to_string(draw_function_id) + ")");

  return draw_function_id;
}

uint8_t Image::remapping()
{
  uint8_t remapping_id = mDatahub.images->draw_function()->at(mId);
  LOG4CXX_TRACE(logger, string("remapping(") + to_string(remapping_id) + ")");

  return remapping_id;
}

} /* namespace dat */
