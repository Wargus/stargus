/*
 * Image.h
 *
 *      Author: Andreas Volz
 */

#ifndef IMAGE_H
#define IMAGE_H

// project
#include "DataHub.h"

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

  static std::string createID(const std::string &image);

private:
  DataHub &mDatahub;
  uint16_t mId;
};

} /* namespace dat */

#endif /* IMAGE_H */
