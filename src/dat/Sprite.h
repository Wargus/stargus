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

namespace dat
{

class Sprite
{
public:
  Sprite(DataHub &datahub, uint16_t id);
  virtual ~Sprite();

  Image image();

private:
  DataHub &mDatahub;
  uint16_t mId;
};

} /* namespace dat */

#endif /* SPRITE_H */
