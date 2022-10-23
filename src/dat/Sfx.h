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

  uint32_t sound_file();

  TblEntry sound_file_tbl();

  uint8_t unknown1();

  uint8_t unknown2();

  uint8_t unknown3();

  uint8_t unknown4();

private:

};

} /* namespace dat */

#endif /* SFX_H */
