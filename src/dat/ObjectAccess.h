/*
 * ObjectAccess.h
 *
 *      Author: Andreas Volz
 */

#ifndef OBJECTACCESS_H
#define OBJECTACCESS_H

// project
#include "DataHub.h"

namespace dat
{

class ObjectAccess
{
public:
  ObjectAccess(DataHub &datahub, unsigned int id) : mDatahub(datahub), mId(id) {}
  virtual ~ObjectAccess() {}

protected:
  DataHub &mDatahub;
  unsigned int mId;
};

} /* namespace dat */

#endif /* OBJECTACCESS_H */
