/*
 * Video.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Video.h"
#include "Hurricane.h"
#include "FileUtil.h"

// System
#include <string>
#include <iostream>

using namespace std;

Video::Video(std::shared_ptr<Hurricane> hurricane) :
  mHurricane(hurricane)
{

}

Video::~Video()
{

}

bool Video::ConvertVideo(const std::string &arcfile,  Storage storage)
{
  bool result = true;

  string smk_file = storage.getFullPath() + ".smk";
  string ogv_file = storage.getFullPath() + ".ogv";

  result = mHurricane->extractFile(arcfile, smk_file, false);

  string ffmpeg_str =
    string("ffmpeg -y -i ") + smk_file
    + " -codec:v libtheora -qscale:v 31 -codec:a libvorbis -qscale:a 15 -pix_fmt yuv420p "
    + ogv_file;

  //cout << "video: " << ffmpeg_str << endl;

  // TODO: call it in a way we suppress the output to stdout
  int sys_call = system(ffmpeg_str.c_str());
  if (sys_call != 0)
  {
    result = false;
  }

  remove(smk_file.c_str());

  return result;
}

bool Video::ConvertPortrait(const std::string &arcfile,  Storage storage)
{
  bool result = true;

  string smk_file = storage.getFullPath() + ".smk";
  string png_path = storage.getFullPath() + "_png/";
  string mng_file = storage.getFullPath() + ".mng";

  result = mHurricane->extractFile(arcfile, smk_file, false);

  CheckPath(png_path);

  string ffmpeg_str =
    string("ffmpeg -y -i ") + smk_file + " -codec:v png -qscale:v 31 -pix_fmt yuv420p " + png_path + "image%05d.png";

  cout << "ffmpeg: " << ffmpeg_str << endl;

  // TODO: call it in a way we suppress the output to stdout
  int sys_call = system(ffmpeg_str.c_str());
  if (sys_call != 0)
  {
    result = false;
  }

  string gm_str = "gm convert " + png_path + "image*.png -delay 4 " + mng_file; // 60sec / 15fps = 4

  cout << "gm: " << gm_str << endl;

  sys_call = system(gm_str.c_str());
  if (sys_call != 0)
  {
    result = false;
  }

  remove(smk_file.c_str());

  return result;
}
