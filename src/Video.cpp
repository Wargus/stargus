/*
 * Video.cpp
 *
 *      Author: Andreas Volz
 */

/**
 **		Path the video files. (default=$DIR/video)
 */
#define VIDEO_PATH		"videos"

// Local
#include "Video.h"
#include "Preferences.h"
#include "Hurricane.h"

// System
#include <string>

using namespace std;

Video::Video(std::shared_ptr<Hurricane> hurricane) :
  mHurricane(hurricane)
{

}

Video::~Video()
{

}

bool Video::ConvertVideo(const std::string &arcfile, const std::string &file)
{
  char buf[8192] =
  { '\0' };
  bool result = true;

  Preferences &preferences = Preferences::getInstance();
  snprintf(buf, sizeof(buf), "%s/%s/%s.smk", preferences.getDestDir().c_str(),
           VIDEO_PATH, file.c_str());

  result = mHurricane->extractFile(arcfile, buf, false);

  string ffmpeg_str =
    string("ffmpeg -y -i ") + buf
    + " -codec:v libtheora -qscale:v 31 -codec:a libvorbis -qscale:a 15 -pix_fmt yuv420p "
    + preferences.getDestDir() + "/" + VIDEO_PATH + "/" + file;

  //cout << "video: " << ffmpeg_str << endl;

  // TODO: call it in a way we suppress the output to stdout
  int sys_call = system(ffmpeg_str.c_str());
  if (sys_call != 0)
  {
    result = false;
  }

  remove(buf);

  return result;
}
