/*
 * Sprite.h
 *
 *      Author: Andreas
 */

#ifndef SPRITE_H
#define SPRITE_H

// project
#include "DataHub.h"
#include "Image.h"
#include "Logger.h"

namespace dat
{

class Sprite
{
public:
  Sprite(DataHub &datahub, uint16_t id);
  virtual ~Sprite();

  Image image();

private:
  Logger mLogger;
  DataHub &mDatahub;
  uint16_t mId;
};

} /* namespace dat */

#endif /* SPRITE_H */
