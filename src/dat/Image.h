/*
 * Image.h
 *
 *      Author: Andreas Volz
 */

#ifndef IMAGE_H
#define IMAGE_H

// project
#include "DataHub.h"
#include "Logger.h"

namespace dat
{

class Image
{
public:
  Image(DataHub &datahub, uint16_t id);
  virtual ~Image();

  TblEntry grp();

  uint8_t draw_function();

  uint8_t remapping();

private:
  Logger mLogger;
  DataHub &mDatahub;
  uint16_t mId;
};

} /* namespace dat */

#endif /* IMAGE_H */
