/*
 * Techdata.cpp
 *
 *      Author: Andreas Volz
 */

#include "Techdata.h"
#include "Logger.h"
#include "PropertyNotAvailableException.h"

static Logger logger = Logger("startool.dat.Techdata");

using namespace std;

namespace dat
{

Techdata::Techdata(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

Techdata::~Techdata()
{

}

uint16_t Techdata::mineral_cost()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->mineral_cost()->at(mId);
}

uint16_t Techdata::vespene_cost()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->vespene_cost()->at(mId);
}

uint16_t Techdata::research_time()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->research_time()->at(mId);
}

uint16_t Techdata::energy_required()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->energy_required()->at(mId);
}

uint32_t Techdata::unknown4()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->unknown4()->at(mId);
}

uint16_t Techdata::icon()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->icon()->at(mId);
}

uint16_t Techdata::label()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->label()->at(mId);
}

TblEntry Techdata::label_tbl()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  if(label() == Techdata::label_none)
  {
    throw PropertyNotAvailableException(mId, "label_tbl");
  }

  return mDatahub.stat_txt_tbl_vec.at(label()-1);
}

uint8_t Techdata::race()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->race()->at(mId);
}

uint8_t Techdata::unused()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->unused()->at(mId);
}

bool Techdata::broodwar_flag()
{
  LOG4CXX_TRACE(logger, to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.techdata->broodwar_flag()->at(mId);
}

bool Techdata::has_broodwar_flag()
{
  return mDatahub.techdata->has_broodwar_flag();
}

} /* namespace dat */
