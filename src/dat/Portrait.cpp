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

Portrait::Portrait(DataHub &datahub,  uint16_t id) :
  mDatahub(datahub),
  mId(id)
{

}

Portrait::~Portrait()
{

}

uint32_t Portrait::video_idle()
{
  uint32_t portrait_id = mDatahub.portrait->video_idle()->at(mId);
  LOG4CXX_TRACE(logger, string("video_idle(") + to_string(portrait_id) + ")");

  return portrait_id;
}

uint32_t Portrait::video_talking()
{
  uint32_t portrait_id = mDatahub.portrait->video_talking()->at(mId);
  LOG4CXX_TRACE(logger, string("video_talking(") + to_string(portrait_id) + ")");

  return portrait_id;
}

TblEntry Portrait::tbl_idle()
{
  TblEntry tbl_entry = mDatahub.portdata_tbl_vec.at(video_idle() - 1);
  LOG4CXX_TRACE(logger, string("tbl_idle(") + tbl_entry.name1 + ")");

  return tbl_entry;
}

TblEntry Portrait::tbl_talking()
{
  TblEntry tbl_entry = mDatahub.portdata_tbl_vec.at(video_talking() - 1);
  LOG4CXX_TRACE(logger, string("tbl_talking(") + tbl_entry.name1 + ")");

  return tbl_entry;
}

std::string Portrait::PathToID(const std::string &portrait)
{
  string portrait_name(portrait);
  replaceString("\\", "/", portrait_name);
  fs::path p(portrait_name);

  portrait_name = to_lower(p.parent_path().string());
  //cout << "portrait_name: " << portrait_name << endl;

  return portrait_name;
}

} /* namespace dat */
