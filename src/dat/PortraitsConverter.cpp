/*
 * PortraitsConverter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "PortraitsConverter.h"
#include "Portrait.h"
#include "Smacker.h"
#include "StringUtil.h"
#include "Preferences.h"
#include "FileUtil.h"
#include "platform.h"
#include "luagen.h"
#include "Logger.h"

// system
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

namespace dat
{

static Logger mLogger = Logger("startool.dat.PortraitsConverter");

PortraitsConverter::PortraitsConverter(std::shared_ptr<Hurricane> hurricane, DataHub &datahub) :
    Converter(hurricane),
    mDatahub(datahub)
{

}

PortraitsConverter::~PortraitsConverter()
{

}

bool PortraitsConverter::convert()
{
  bool result = true;

  Preferences &preferences = Preferences::getInstance();

  Storage videos;
  videos.setDataPath(preferences.getDestDir());
  videos.setDataType("videos/portrait");

  Storage luagen;
  luagen.setDataPath(preferences.getDestDir());
  luagen.setDataType("luagen/portrait");
  CheckPath(luagen.getFullPath());

  ofstream lua_include;
  lua_include.open (luagen("luagen-portrait.lua").getFullPath());
  string lua_include_str;

  for(unsigned int i = 0; i < mDatahub.portrait->video_idle()->size(); i++)
  {
    Portrait portrait(mDatahub, i);

    string portrait_arcfile_idle(portrait.tbl_idle()->name1);
    string portrait_arcfile_talking(portrait.tbl_talking()->name1);

    string portrait_idle_id(Portrait::createID(portrait_arcfile_idle));
    string portrait_talking_id(Portrait::createID(portrait_arcfile_talking));

    // just to ensure the idle / talking consistency in the database
    // this should also be the case otherwise something is broken
    if(portrait_idle_id == portrait_talking_id)
    {
      Storage lua_file_store(luagen("portrait-" + portrait_idle_id + ".lua"));
      ofstream lua_file;
      lua_file.open (lua_file_store.getFullPath());

      vector<string> portrait_list;

      convertMngPortraits(portrait_arcfile_idle, portrait_list);
      portrait_list.push_back("talking"); // the stratagus API needs this as separator
      convertMngPortraits(portrait_arcfile_talking, portrait_list);

      string portraits_table = lg::assign("portrait_" + portrait_idle_id ,lg::table(lg::paramsQuote(portrait_list)));

      lua_include_str += lg::line(lg::function("Load", lg::quote(lua_file_store.getRelativePath())));

      lua_file << portraits_table;
      lua_file.close();
    }
    else
    {
      LOG4CXX_FATAL(mLogger, "portrait_idle_id != portrait_talking_id");
    }
  }


  lua_include << lua_include_str;
  lua_include.close();

  return result;
}

bool PortraitsConverter::convertMngPortraits(const std::string &arcfile, std::vector<std::string> &portrait_list)
{
  bool smk_available = true;
  unsigned int smk_num = 0;

  Preferences &preferences = Preferences::getInstance();

  Storage videos;
  videos.setDataPath(preferences.getDestDir());
  videos.setDataType("videos/portrait");

  while(smk_available && smk_num <= 3)
  {
    Smacker video(mHurricane);

    // build the name of the specific #smk file
    string smk_arcfile("portrait\\" + arcfile + to_string(smk_num) + ".smk");

    // target place where to store the file
    string target_basename(arcfile + to_string(smk_num));
    replaceString("\\", "/", target_basename);
    target_basename = to_lower(target_basename);

    cout << "Try export (last one may fail if less then three) " << smk_arcfile << " to " << target_basename;

    smk_available = video.convertMNG(smk_arcfile, videos(target_basename));

    if(smk_available)
    {
      portrait_list.push_back(videos.getDataType() + "/" + target_basename + ".mng");
    }

    printf("...%s\n", smk_available ? "ok" : "nok");
    smk_num++;
  }

  return true;
}

} /* namespace dat */
