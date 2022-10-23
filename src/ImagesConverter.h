/*
 * ImagesConverter.h
 *
 *      Author: Andreas Volz
 */

#ifndef IMAGESCONVERTER_H
#define IMAGESCONVERTER_H

#include "Converter.h"
#include "dat/DataHub.h"

class ImagesConverter: public Converter
{
public:
  ImagesConverter(std::shared_ptr<Hurricane> hurricane, dat::DataHub &datahub);
  virtual ~ImagesConverter();

  bool convert(std::map<std::string, std::shared_ptr<AbstractPalette>> &paletteMap);

private:
  dat::DataHub &mDatahub;
};

#endif /* IMAGESCONVERTER_H */
