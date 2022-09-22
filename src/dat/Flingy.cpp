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

Flingy::Flingy(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{


}

Flingy::~Flingy()
{

}

uint16_t Flingy::sprite()
{
  return mDatahub.flingy->sprite()->at(mId);
}

Sprite Flingy::sprite_obj()
{
  return Sprite(mDatahub, sprite());
}

uint32_t Flingy::speed()
{
  return mDatahub.flingy->speed()->at(mId);
}

uint16_t Flingy::acceleration()
{
  return mDatahub.flingy->acceleration()->at(mId);
}

uint32_t Flingy::halt_distance()
{
  return mDatahub.flingy->halt_distance()->at(mId);
}

uint8_t Flingy::turn_radius()
{
  return mDatahub.flingy->turn_radius()->at(mId);
}

uint8_t Flingy::unused()
{
  return mDatahub.flingy->unused()->at(mId);
}

uint8_t Flingy::movement_control()
{
  return mDatahub.flingy->movement_control()->at(mId);
}

} /* namespace dat */
