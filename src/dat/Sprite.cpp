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

Image Sprite::image()
{
  uint16_t image_id = 0;

  if (mId < mDatahub.sprites->image()->size())
  {
    image_id = mDatahub.sprites->image()->at(mId);
    LOG4CXX_TRACE(logger, string("image(") + to_string(image_id) + ")");
  }
  else
  {
    LOG4CXX_WARN(logger, string("not found image->at(") + to_string(mId) + ") mapped to 0");
  }

  Image image(mDatahub, image_id);

  return image;
}

} /* namespace dat */
