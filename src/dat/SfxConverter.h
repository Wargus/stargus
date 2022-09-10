/*
 * SfxConverter.h
 *
 *      Author: Andreas Volz
 */

#ifndef SFXCONVERTER_H
#define SFXCONVERTER_H

// project
#include "DataHub.h"

namespace dat
{

class SfxConverter : public Converter
{
public:
  SfxConverter(std::shared_ptr<Hurricane> hurricane, DataHub &datahub);
  virtual ~SfxConverter();

  bool convert();

private:
  DataHub &mDatahub;
};

} /* namespace dat */

#endif /* SFXCONVERTER_H */
