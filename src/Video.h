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

class Video
{
public:
  Video(std::shared_ptr<Hurricane> hurricane);
  virtual ~Video();

  /**
   *  Convert SMK video to OGV
   */
  bool ConvertVideo(const std::string &arcfile, Storage storage);

  bool ConvertPortrait(const std::string &arcfile,  Storage storage);

private:
  std::shared_ptr<Hurricane> mHurricane;
};

#endif /* VIDEO_H */
