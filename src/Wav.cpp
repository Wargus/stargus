/*
 * Wav.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "Wav.h"
#include "Hurricane.h"
#include "platform.h"
#include "Logger.h"
#include "FileUtil.h"

// system

using namespace std;

static Logger logger = Logger("startool.Wav");

Wav::Wav(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane)
{
}

Wav::Wav(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
  Converter(hurricane)
{

}

Wav::~Wav()
{

}

bool Wav::convert(const std::string &arcfile,  Storage storage)
{
  bool result = true;

  string wav_file = storage.getFullPath() + ".wav";
  string ogg_file = storage.getFullPath() + ".ogg";

  CheckPath(wav_file);
  result = mHurricane->extractFile(arcfile, wav_file, false);

  string ffmpeg_str =
    string("ffmpeg -y -i \"") + wav_file
    + "\" -acodec libvorbis  \""
    + ogg_file + "\"";

  //cout << "video: " << ffmpeg_str << endl;

  // TODO: call it in a way we suppress the output to stdout
  int sys_call = system(ffmpeg_str.c_str());
  if (sys_call != 0)
  {
    result = false;
  }

  fs::remove(wav_file);

  return result;
}
