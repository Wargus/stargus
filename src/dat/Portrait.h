/*
 * Portrait.h
 *
 *      Author: Andreas Volz
 */

#ifndef PORTRAIT_H
#define PORTRAIT_H

#include "DataHub.h"

namespace dat
{

class Portrait
{
public:
  Portrait(DataHub &datahub,  uint16_t id);
  virtual ~Portrait();

  uint32_t video_idle();
  uint32_t video_talking();

  TblEntry tbl_idle();
  TblEntry tbl_talking();

  static std::string PathToID(const std::string &portrait);

private:


  DataHub &mDatahub;
  uint16_t mId;
};

} /* namespace dat */

#endif /* PORTRAIT_H */
