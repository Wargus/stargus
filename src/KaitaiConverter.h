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

class KaitaiConverter: public Converter
{
public:
  KaitaiConverter(std::shared_ptr<Hurricane> hurricane);
  virtual ~KaitaiConverter();

protected:
  std::shared_ptr<kaitai::kstream> getKaitaiStream(const std::string &file);
};

#endif /* KAITAICONVERTER_H */
