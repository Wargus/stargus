/*
 * Video.h
 *
 *      Author: Andreas Volz
 */

#ifndef VIDEO_H
#define VIDEO_H

// project
#include "Storage.h"
#include "Converter.h"

// System
#include <memory>

class Smacker : public Converter
{
public:
  Smacker(std::shared_ptr<Hurricane> hurricane);
  virtual ~Smacker();

  /**
   *  Convert SMK video to OGV
   */
  bool convertOGV(const std::string &arcfile, Storage storage);

  bool convertMNG(const std::string &arcfile,  Storage storage);

private:
  bool callConvert(const std::string &cmd);
};

#endif /* VIDEO_H */
