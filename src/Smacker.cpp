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

bool Smacker::convertAnimation(const std::string &arcfile,  Storage storage)
{
  bool result = true;

  string smk_file = storage.getFullPath() + ".smk";
  string png_path = storage.getFullPath() + "_png/";
  string gif_file = storage.getFullPath() + ".gif";

  result = mHurricane->extractFile(arcfile, smk_file, false);
  if(result)
  {
    CheckPath(png_path);

    string ffmpeg_str =
      string("ffmpeg -y -i \"") + smk_file + "\" -codec:v png -qscale:v 31 -pix_fmt yuv420p \"" + png_path + "\"image%05d.png";
      LOG4CXX_DEBUG(logger, ffmpeg_str);

    // TODO: call it in a way we suppress the output to stdout
    int sys_call = system(ffmpeg_str.c_str());
    if (sys_call == 0)
    {
      if(result)
      {
        // -delay is in 1/100s and -loop 0 keeps the animation running forever.
        // Both only apply to the images that follow them, so they have to come
        // before the frames, otherwise the GIF ends up with a delay of zero.
        string gif_cmd = "convert -delay 4 -loop 0 \"" + png_path + "image*.png\" \"" + gif_file + "\"";
        LOG4CXX_DEBUG(logger, gif_cmd);

        result = callConvert(gif_cmd);
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
