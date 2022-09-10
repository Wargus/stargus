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
  uint32_t video_talking();

  TblEntry video_idle_tbl();
  TblEntry video_talking_tbl();

  static std::string createID(const std::string &portrait);

private:

};

} /* namespace dat */

#endif /* PORTRAIT_H */
