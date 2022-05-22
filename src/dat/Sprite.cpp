/*
 * Sprite.cpp
 *
 *      Author: Andreas Volz
 */

#include "Sprite.h"

using namespace std;

namespace dat
{

Sprite::Sprite(DataHub &datahub, uint16_t id) :
  mLogger("startool.dat.Sprite"),
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
  LOG4CXX_TRACE(mLogger, string("image(") + to_string(image_id) + ")");

  Image image(mDatahub, image_id);

  return image;
}

} /* namespace dat */
