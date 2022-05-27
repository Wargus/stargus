/*
 * Unit.h
 *
 *      Author: Andreas Volz
 */

#ifndef UNIT_H
#define UNIT_H

// project
#include "Flingy.h"
#include "DataHub.h"

namespace dat
{

class Unit
{
public:
  Unit(DataHub &datahub, uint8_t id);
  virtual ~Unit();

  Flingy flingy();

  TblEntry name();

  uint32_t hitpoints();

private:
  DataHub &mDatahub;
  uint8_t mId;
};

} /* namespace dat */

#endif /* UNIT_H */
