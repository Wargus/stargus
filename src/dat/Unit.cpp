/*
 * Unit.cpp
 *
 *      Author: Andreas Volz
 */

#include "Unit.h"

using namespace std;

namespace dat
{

Unit::Unit(DataHub &datahub, uint8_t id) :
  mLogger("startool.dat.Unit"),
  mDatahub(datahub),
  mId(id)
{

}

Unit::~Unit()
{

}

Flingy Unit::flingy()
{
  uint8_t flingy_id = mDatahub.units->flingy()->at(mId);
  LOG4CXX_TRACE(mLogger, string("flingy(") + to_string(flingy_id) + ")");

  Flingy flingy(mDatahub, flingy_id);

  return flingy;
}

} /* namespace dat */
