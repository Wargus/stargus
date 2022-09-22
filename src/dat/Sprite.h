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
#include "PropertyNotAvailableException.h"

namespace dat
{

class Sprite : public ObjectAccess
{
public:
  Sprite(DataHub &datahub, unsigned int id);
  virtual ~Sprite();

  uint16_t image();
  Image image_obj();

  uint8_t health_bar();

  uint8_t unknown2();

  uint8_t is_visible();

  uint8_t select_circle_image_size();

  uint8_t select_circle_vertical_pos();

private:

};

} /* namespace dat */

#endif /* SPRITE_H */
