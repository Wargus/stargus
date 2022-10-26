/*
 * Upgrade.cpp
 *
 *      Author: Andreas Volz
 */

#include "Upgrade.h"
#include "Logger.h"
#include "PropertyNotAvailableException.h"

static Logger logger = Logger("startool.dat.Upgrade");

using namespace std;

namespace dat
{

Upgrade::Upgrade(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

Upgrade::~Upgrade()
{

}

uint16_t Upgrade::mineral_cost_base()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->mineral_cost_base()->at(mId);
}

uint16_t Upgrade::mineral_cost_factor()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->mineral_cost_factor()->at(mId);
}

uint16_t Upgrade::vespene_cost_base()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->vespene_cost_base()->at(mId);
}

uint16_t Upgrade::vespene_cost_factor()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->vespene_cost_factor()->at(mId);
}

uint16_t Upgrade::research_time_base()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->research_time_base()->at(mId);
}

uint16_t Upgrade::research_time_factor()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->research_time_factor()->at(mId);
}

uint16_t Upgrade::unknown6()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->unknown6()->at(mId);
}

uint16_t Upgrade::icon()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->icon()->at(mId);
}

uint16_t Upgrade::label()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->label()->at(mId);
}

TblEntry Upgrade::label_tbl()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  if(label() == Upgrade::label_none)
  {
    throw PropertyNotAvailableException(mId, "label_tbl");
  }

  return mDatahub.stat_txt_tbl_vec.at(label()-1);
}

uint8_t Upgrade::race()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->race()->at(mId);
}

uint8_t Upgrade::max_repeats()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->max_repeats()->at(mId);
}

bool Upgrade::broodwar_flags()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.upgrades->broodwar_flags()->at(mId);
}

bool Upgrade::has_broodwar_flag()
{
  return mDatahub.upgrades->has_broodwar_flag();
}

} /* namespace dat */
