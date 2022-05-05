/*
 * Flingy.cpp
 *
 *      Author: Andreas
 */

#include "Flingy.h"

using namespace std;

namespace dat
{

Flingy::Flingy(DataHub &datahub, uint8_t id) :
  mLogger("startool.dat.Flingy"),
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
  LOG4CXX_TRACE(mLogger, string("sprite(") + to_string(sprite_id) + ")");

  Sprite sprite(mDatahub, sprite_id);

  return sprite;
}

} /* namespace dat */
