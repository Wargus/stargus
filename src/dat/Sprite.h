/*
 * Sprite.h
 *
 *      Author: Andreas
 */

#ifndef SPRITE_H
#define SPRITE_H

// project
#include "ObjectAccess.h"
#include "Image.h"

namespace dat
{

class Sprite : public ObjectAccess
{
public:
  Sprite(DataHub &datahub, unsigned int id);
  virtual ~Sprite();

  Image image();

private:

};

} /* namespace dat */

#endif /* SPRITE_H */
