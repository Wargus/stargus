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

  Sprite sprite();

private:

};

} /* namespace dat */

#endif /* FLINGY_H */
