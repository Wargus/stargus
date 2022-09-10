/*
 * Sound.h
 *
 *      Author: Andreas Volz
 */

#ifndef SFX_H
#define SFX_H

// project
#include "ObjectAccess.h"

//system
#include <memory>

namespace dat
{

class Sfx : public ObjectAccess
{
public:
  Sfx(DataHub &datahub, unsigned int id);
  virtual ~Sfx();

  std::shared_ptr<TblEntry> sound_file();

private:

};

} /* namespace dat */

#endif /* SFX_H */
