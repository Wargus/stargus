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
  uint32_t portrait_id = mDatahub.portdata->video_idle()->at(mId);
  LOG4CXX_TRACE(logger, string("video_idle(") + to_string(portrait_id) + ")");

  return portrait_id;
}

uint32_t Portrait::video_talking()
{
  uint32_t portrait_id = mDatahub.portdata->video_talking()->at(mId);
  LOG4CXX_TRACE(logger, string("video_talking(") + to_string(portrait_id) + ")");

  return portrait_id;
}

TblEntry Portrait::video_idle_tbl()
{
  TblEntry tbl_entry = mDatahub.portdata_tbl_vec.at(video_idle() - 1);
  LOG4CXX_TRACE(logger, string("video_idle_tbl(") + tbl_entry.name1 + ")");

  return tbl_entry;
}

TblEntry Portrait::video_talking_tbl()
{
  TblEntry tbl_entry = mDatahub.portdata_tbl_vec.at(video_talking() - 1);
  LOG4CXX_TRACE(logger, string("video_talking_tbl(") + tbl_entry.name1 + ")");

  return tbl_entry;
}

std::string Portrait::createID(const std::string &portrait)
{
  string portrait_name(portrait);
  replaceString("\\", "/", portrait_name);
  fs::path p(portrait_name);

  portrait_name = to_lower(p.parent_path().string());
  //cout << "portrait_name: " << portrait_name << endl;

  return portrait_name;
}

} /* namespace dat */
