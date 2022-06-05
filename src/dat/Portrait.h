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

  TblEntry idle();
  TblEntry talking();

  static std::string PathToID(const std::string &portrait);

private:
  uint32_t file();

  DataHub &mDatahub;
  uint16_t mId;
};

} /* namespace dat */

#endif /* PORTRAIT_H */
