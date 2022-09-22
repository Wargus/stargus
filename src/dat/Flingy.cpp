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
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.flingy->sprite()->at(mId);
}

Sprite Flingy::sprite_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Sprite(mDatahub, sprite());
}

uint32_t Flingy::speed()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.flingy->speed()->at(mId);
}

uint16_t Flingy::acceleration()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.flingy->acceleration()->at(mId);
}

uint32_t Flingy::halt_distance()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.flingy->halt_distance()->at(mId);
}

uint8_t Flingy::turn_radius()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.flingy->turn_radius()->at(mId);
}

uint8_t Flingy::unused()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.flingy->unused()->at(mId);
}

uint8_t Flingy::movement_control()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.flingy->movement_control()->at(mId);
}

} /* namespace dat */
