/*
 * Dds.h
 *
 *      Author: Andreas Volz
 */

#ifdef HAVE_IMAGEMAGICKPP

#ifndef DDS_H_
#define DDS_H_

// Local
#include "Converter.h"

// System
#include <memory>

// Forward declarations
class Hurricane;

class Dds: public Converter
{
public:
  Dds(std::shared_ptr<Hurricane> hurricane);
  virtual ~Dds();

  bool convert(const std::string &arcfile, const std::string &file);

private:

};

#endif /* DDS_H_ */

#endif /* HAVE_IMAGEMAGICKPP */
