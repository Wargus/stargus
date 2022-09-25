/*
 * Order.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "Order.h"
#include "Logger.h"

static Logger logger = Logger("startool.dat.Order");

using namespace std;

namespace dat
{

Order::Order(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

Order::~Order()
{

}

uint16_t Order::label()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->label()->at(mId);
}

TblEntry Order::label_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.stat_txt_tbl_vec.at(label());
}

bool Order::use_weapon_targeting()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->use_weapon_targeting()->at(mId);
}

uint8_t Order::unknown2()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown2()->at(mId);
}

uint8_t Order::unknown3()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown3()->at(mId);
}

uint8_t Order::unknown4()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown4()->at(mId);
}

uint8_t Order::unknown5()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown5()->at(mId);
}

uint8_t Order::interruptible()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->interruptible()->at(mId);
}

uint8_t Order::unknown7()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown7()->at(mId);
}

uint8_t Order::queueable()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->queueable()->at(mId);
}

uint8_t Order::unknown9()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown9()->at(mId);
}

uint8_t Order::unknown10()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown10()->at(mId);
}

uint8_t Order::unknown11()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown11()->at(mId);
}

uint8_t Order::unknown12()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown12()->at(mId);
}

uint8_t Order::targeting()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  uint8_t targeting = mDatahub.orders->targeting()->at(mId);

  // strange logic in the data. If the weapon links to a index bigger than weapon then it's 'none'
  if(targeting >= mDatahub.weapons->label()->size())
  {
    LOG4CXX_ERROR(logger, string("Exception: targeting > size"));
    throw PropertyNotAvailableException(mId, "targeting");
  }

  return mDatahub.orders->targeting()->at(mId);
}

Weapon Order::targeting_obj()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return Weapon(mDatahub, targeting());
}

uint8_t Order::energy()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->energy()->at(mId);
}

uint8_t Order::animation()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->animation()->at(mId);
}

uint8_t Order::highlight()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->highlight()->at(mId);
}

uint8_t Order::unknown17()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->unknown17()->at(mId);
}

uint8_t Order::obscured_order()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.orders->obscured_order()->at(mId);
}

} /* namespace dat */
