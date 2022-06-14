/*
 * UIConsole.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "UIConsole.h"
#include "Logger.h"
#include "Hurricane.h"
#include "platform.h"

using namespace std;

static Logger logger = Logger("startool.UIConsole");

UIConsole::UIConsole(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane)
{

}

UIConsole::~UIConsole()
{

}

bool UIConsole::convert(Storage pngfile, int left, int right)
{
  bool result = true;

  string complete_file = pngfile.getFullPath() + ".png";
  string left_file = pngfile.getFullPath() + "_left.png";
  string right_file = pngfile.getFullPath() + "_right.png";
  string middle_file = pngfile.getFullPath() + "_middle.png";
  string tmp_file = pngfile.getFullPath() + "_tmp.png";

  // fix resolution for SC1, in case of Remastered this has to be an option
  int width = 640;
  int height = 480;
  string wxh = to_string(width) + "x" + to_string(height);

  int left_abs = width - left;
  //echo $left_abs

  //convert tconsole.png -crop ${width}x${height}-${left_abs}+0 tconsole_left.png
  //convert tconsole.png -crop ${width}x${height}+${right}+0 tconsole_right.png

  string convert_left_cmd = "convert " + complete_file + " -crop " + wxh + "-" + to_string(left_abs) + "+0 " + left_file;
  string convert_right_cmd = "convert " + complete_file + " -crop " + wxh + "+" + to_string(right) + "+0 " + right_file;
  LOG4CXX_DEBUG(logger, convert_left_cmd);
  LOG4CXX_DEBUG(logger, convert_right_cmd);

  if(result)
  {
    result = callConvert(convert_left_cmd);
  }
  if(result)
  {
    result = callConvert(convert_right_cmd);
  }

  int middle = right - left;
  //echo $middle

  int left_tmp = left_abs - middle;
  int middle_abs = right - middle;
  //echo $left_tmp

  //convert tconsole.png -crop ${width}x${height}-${left_tmp}+0 tmp.png
  //convert tmp.png -crop ${width}x${height}+${middle_abs}+0 tconsole_middle.png

  string convert_tmp_cmd = "convert " + complete_file + " -crop " + wxh + "-" + to_string(left_tmp) + "+0 " + tmp_file;
  string convert_middle_cmd = "convert " + tmp_file + " -crop " + wxh + "+" + to_string(middle_abs) + "+0 " + middle_file;
  LOG4CXX_DEBUG(logger, convert_tmp_cmd);
  LOG4CXX_DEBUG(logger, convert_middle_cmd);

  if(result)
  {
    result = callConvert(convert_tmp_cmd);
  }
  if(result)
  {
    result = callConvert(convert_middle_cmd);
  }


  fs::remove(tmp_file);

  return result;
}

bool UIConsole::callConvert(const std::string &cmd)
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
