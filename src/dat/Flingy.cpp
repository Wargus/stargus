/*
 * Flingy.cpp
 *
 *      Author: Andreas
 */

#include "Flingy.h"
#include "Logger.h"

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.Flingy");

Flingy::Flingy(DataHub &datahub, uint8_t id) :
  mDatahub(datahub),
  mId(id)
{


}

Flingy::~Flingy()
{

}


Sprite Flingy::sprite()
{
  uint16_t sprite_id = mDatahub.flingy->sprite()->at(mId);
  LOG4CXX_TRACE(logger, string("sprite(") + to_string(sprite_id) + ")");

  Sprite sprite(mDatahub, sprite_id);

  return sprite;
}

} /* namespace dat */
