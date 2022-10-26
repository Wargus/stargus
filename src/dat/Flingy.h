/*
 * Flingy.h
 *
 *      Author: andreas
 */

#ifndef FLINGY_H
#define FLINGY_H

// project
#include "ObjectAccess.h"
#include "Sprite.h"

namespace dat
{

class Flingy : public ObjectAccess
{
public:
  Flingy(DataHub &datahub, unsigned int id);
  virtual ~Flingy();

  uint16_t sprite();
  Sprite sprite_obj();

  uint32_t speed();

  uint16_t acceleration();

  uint32_t halt_distance();

  uint8_t turn_radius();

  uint8_t unused();

  uint8_t movement_control();

private:

};

} /* namespace dat */

#endif /* FLINGY_H */
