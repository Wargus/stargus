/*
 * Video.h
 *
 *      Author: Andreas Volz
 */

#ifndef VIDEO_H
#define VIDEO_H

// System
#include <memory>

// project
#include "Storage.h"

// Forward declarations
class Hurricane;

class Smacker
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

  std::shared_ptr<Hurricane> mHurricane;
};

#endif /* VIDEO_H */
