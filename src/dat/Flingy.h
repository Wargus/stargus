/*
 * Flingy.h
 *
 *      Author: andreas
 */

#ifndef FLINGY_H
#define FLINGY_H

// project
#include "DataHub.h"
#include "Sprite.h"
#include "Logger.h"

namespace dat
{

class Flingy
{
public:
  Flingy(DataHub &datahub, uint8_t id);
  virtual ~Flingy();

  Sprite sprite();

private:
  Logger mLogger;
  DataHub &mDatahub;
  uint8_t mId;
};

} /* namespace dat */

#endif /* FLINGY_H */
