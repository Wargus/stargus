/*
 * Portrait.cpp
 *
 *      Author: Andreas Volz
 */

#include "Portrait.h"
#include "Logger.h"
#include "StringUtil.h"
#include "platform.h"

using namespace std;

namespace dat
{

static Logger logger = Logger("startool.dat.Portrait");

Portrait::Portrait(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

Portrait::~Portrait()
{

}

uint32_t Portrait::video_idle()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.portdata->video_idle()->at(mId);
}

TblEntry Portrait::video_idle_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.portdata_tbl_vec.at(video_idle() - 1);
}

uint32_t Portrait::video_talking()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.portdata->video_talking()->at(mId);
}

TblEntry Portrait::video_talking_tbl()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.portdata_tbl_vec.at(video_talking() - 1);
}

uint8_t Portrait::change_idle()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.portdata->change_idle()->at(mId);
}

uint8_t Portrait::change_talking()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.portdata->change_talking()->at(mId);
}

uint8_t Portrait::unknown1_idle()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.portdata->unknown1_idle()->at(mId);
}

uint8_t Portrait::unknown1_talking()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");
  return mDatahub.portdata->unknown1_talking()->at(mId);
}

std::string Portrait::getIDString(const std::string &portrait)
{
  string portrait_name(portrait);
  replaceString("\\", "/", portrait_name);
  fs::path p(portrait_name);

  portrait_name = to_lower(p.parent_path().string());
  //cout << "portrait_name: " << portrait_name << endl;

  return portrait_name;
}

} /* namespace dat */
