/*
 * ImagesConverter.h
 *
 *      Author: Andreas Volz
 */

#ifndef IMAGESCONVERTER_H
#define IMAGESCONVERTER_H

#include "Converter.h"
#include "DataHub.h"

namespace dat
{

class ImagesConverter: public Converter
{
public:
  ImagesConverter(std::shared_ptr<Hurricane> hurricane, DataHub &datahub);
  virtual ~ImagesConverter();

  bool convert(std::map<std::string, std::shared_ptr<Palette>> &paletteMap,
               std::map<std::string, std::shared_ptr<Palette2D>> palette2DMap);

private:
  DataHub &mDatahub;
};

} /* namespace dat */

#endif /* IMAGESCONVERTER_H */
