/*
 * Video.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include <Smacker.h>
#include "Hurricane.h"
#include "FileUtil.h"
#include "platform.h"
#include "Logger.h"

// System
#include <iostream>

using namespace std;

static Logger logger = Logger("startool.Smacker");

Smacker::Smacker(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane)
{

}

Smacker::~Smacker()
{

}

bool Smacker::convertOGV(const std::string &arcfile,  Storage storage)
{
  bool result = true;

  string smk_file = storage.getFullPath() + ".smk";
  string ogv_file = storage.getFullPath() + ".ogv";

  result = mHurricane->extractFile(arcfile, smk_file, false);
  if(result)
  {
    string ffmpeg_str =
      string("ffmpeg -y -i \"") + smk_file
      + "\" -codec:v libtheora -qscale:v 31 -codec:a libvorbis -qscale:a 15 -pix_fmt yuv420p \""
      + ogv_file + "\"";

    LOG4CXX_DEBUG(logger, ffmpeg_str);

    // TODO: call it in a way we suppress the output to stdout
    int sys_call = system(ffmpeg_str.c_str());
    if (sys_call != 0)
    {
      result = false;
    }

    fs::remove(smk_file);
  }

  return result;
}

bool Smacker::convertMNG(const std::string &arcfile,  Storage storage)
{
  bool result = true;

  string smk_file = storage.getFullPath() + ".smk";
  string png_path = storage.getFullPath() + "_png/";
  string mng_file = storage.getFullPath() + ".mng";

  result = mHurricane->extractFile(arcfile, smk_file, false);
  if(result)
  {
    CheckPath(png_path);

    /**
     * The framerate of animation SC smk files is 15.15fps (said ffprobe)
     * I tried to calculate the framerate, but it didn't came out as expected, so I just compared it
     * visually and tweeked the value until it fits: -r 117
     */
    string ffmpeg_str =
      string("ffmpeg -y -i \"") + smk_file + "\" -codec:v png -r 117 -qscale:v 31 -pix_fmt yuv420p \"" + png_path + "\"image%05d.png";
      LOG4CXX_DEBUG(logger, ffmpeg_str);

    // TODO: call it in a way we suppress the output to stdout
    int sys_call = system(ffmpeg_str.c_str());
    if (sys_call == 0)
    {
      if(result)
      {
        string mng_cmd = "convert \"" + png_path + "image*.png\" \"" + mng_file + "\"";
        LOG4CXX_DEBUG(logger, mng_cmd);

        result = callConvert(mng_cmd);
      }
    }
    else
    {
      result = false;
    }

    fs::remove(smk_file);
    fs::remove_all(png_path);
  }

  return result;
}

bool Smacker::callConvert(const std::string &cmd)
{
  bool result = true;

  // try convert with ImageMagick 7+
  string magic7_cmd("magick " + cmd);
  int sys_call = system(magic7_cmd.c_str());
  if (sys_call != 0)
  {
    // try convert with ImageMagick <= 6
    string magic6_cmd(cmd);
    sys_call = system(magic6_cmd.c_str());
    if (sys_call != 0)
    {
      // try convert with GraphicsMagick
      string gm_cmd("gm " + cmd);
      sys_call = system(gm_cmd.c_str());
      if (sys_call != 0)
      {
        result = false;
      }
    }
  }

  return result;
}
