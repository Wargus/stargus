/*
 * Portrait.h
 *
 *      Author: Andreas Volz
 */

#ifndef PORTRAIT_H
#define PORTRAIT_H

#include "ObjectAccess.h"

namespace dat
{

class Portrait : public ObjectAccess
{
public:
  Portrait(DataHub &datahub, unsigned int id);
  virtual ~Portrait();

  uint32_t video_idle();
  TblEntry video_idle_tbl();

  uint32_t video_talking();
  TblEntry video_talking_tbl();

  uint8_t change_idle();

  uint8_t change_talking();

  uint8_t unknown1_idle();

  uint8_t unknown1_talking();

  std::string getIDString(const std::string &portrait);

private:

};

} /* namespace dat */

#endif /* PORTRAIT_H */
