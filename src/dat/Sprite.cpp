/*
 * Sprite.cpp
 *
 *      Author: Andreas Volz
 */

#include "Sprite.h"
#include "Logger.h"

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.Sprite");

Sprite::Sprite(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

Sprite::~Sprite()
{

}

uint16_t Sprite::image()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t image_id = 0;

  /*
   * The data deep dive shows that there're some unused units which request a sprite/image
   * which is available first in Broodwar for this Sprite. I could only assume that this is an error.
   * Therefore this is just mapped to 0. No problem as such units are never used in the normal game.
   * This is just to draw the unit in test code.
   */
  if (mId < mDatahub.sprites->image()->size())
  {
    image_id = mDatahub.sprites->image()->at(mId);
    LOG4CXX_TRACE(logger, string("image(") + to_string(image_id) + ")");
  }
  else
  {
    LOG4CXX_TRACE(logger, string("not found image->at(") + to_string(mId) + ") mapped to 0");
  }

  return image_id;
}

Image Sprite::image_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Image(mDatahub, image());
}

uint8_t Sprite::health_bar()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t health_bar = 0;

  try
  {
    // This property is only available from unit index 130 to num_lines
    health_bar = mDatahub.sprites->health_bar()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: health_bar(") + to_string(health_bar) + ")");
    throw PropertyNotAvailableException(mId, "health_bar");
  }

  return health_bar;
}

uint8_t Sprite::unknown2()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint8_t unknown2 = 0;

  /*
   * The data deep dive shows that there're some unused units which request a unknown property
   * which is available first in Broodwar for this Sprite. I could only assume that this is an error.
   * Therefore this is just mapped to 0. No problem as such units are never used in the normal game.
   */
  if (mId < mDatahub.sprites->unknown2()->size())
  {
    unknown2 = mDatahub.sprites->unknown2()->at(mId);
    LOG4CXX_TRACE(logger, string("unknown2(") + to_string(unknown2) + ")");
  }
  else
  {
    LOG4CXX_TRACE(logger, string("not found unknown2->at(") + to_string(mId) + ") mapped to 0");
  }

  return unknown2;
}

bool Sprite::is_visible()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint8_t is_visible = 1;

  /*
   * The data deep dive shows that there're some unused units which request a unknown property
   * which is available first in Broodwar for this Sprite. I could only assume that this is an error.
   * Therefore this is just mapped to 0. No problem as such units are never used in the normal game.
   * We map it to 1 to let this units draw for test cases.
   */
  if (mId < mDatahub.sprites->is_visible()->size())
  {
    is_visible = mDatahub.sprites->is_visible()->at(mId);
    LOG4CXX_TRACE(logger, string("is_visible(") + to_string(is_visible) + ")");
  }
  else
  {
    LOG4CXX_TRACE(logger, string("not found is_visible->at(") + to_string(mId) + ") mapped to 1");
  }

  return is_visible;
}

uint8_t Sprite::select_circle_image_size()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t select_circle_image_size = 0;

  try
  {
    // This property is only available from unit index 130 to num_lines
    select_circle_image_size = mDatahub.sprites->select_circle_image_size()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: select_circle_image_size(") + to_string(select_circle_image_size) + ")");
    throw PropertyNotAvailableException(mId, "select_circle_image_size");
  }

  return select_circle_image_size;
}

uint8_t Sprite::select_circle_vertical_pos()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  uint16_t select_circle_vertical_pos = 0;

  try
  {
    // This property is only available from unit index 130 to num_lines
    select_circle_vertical_pos = mDatahub.sprites->select_circle_vertical_pos()->at(mId);
  }
  catch (const std::out_of_range& oor)
  {
    LOG4CXX_TRACE(logger, string("Exception: select_circle_vertical_pos(") + to_string(select_circle_vertical_pos) + ")");
    throw PropertyNotAvailableException(mId, "select_circle_vertical_pos");
  }

  return select_circle_vertical_pos;
}

} /* namespace dat */
