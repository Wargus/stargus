/*
 * KaitaiConverter.h
 *
 *      Author: Andreas
 */

#ifndef KAITAICONVERTER_H
#define KAITAICONVERTER_H

// project
#include "Converter.h"
#include "kaitai/kaitaistream.h"

//system
#include <memory>

/**
 * TODO: meaybe remove complete KaitaiConverter class layer...
 */
class KaitaiConverter: public Converter
{
public:
  KaitaiConverter(std::shared_ptr<Hurricane> hurricane);
  virtual ~KaitaiConverter();

protected:
  /**
   * WARNING DEPRECATED!
   * remove getKaitaiStream() complete and replace by logic in DataHub
   */
  //std::shared_ptr<kaitai::kstream> getKaitaiStream(const std::string &file);
};

#endif /* KAITAICONVERTER_H */
