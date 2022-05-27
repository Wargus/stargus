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

Sprite::Sprite(DataHub &datahub, uint16_t id) :
  mDatahub(datahub),
  mId(id)
{

}

Sprite::~Sprite()
{

}

Image Sprite::image()
{
  uint16_t image_id = mDatahub.sprites->image()->at(mId);
  LOG4CXX_TRACE(logger, string("image(") + to_string(image_id) + ")");

  Image image(mDatahub, image_id);

  return image;
}

} /* namespace dat */
