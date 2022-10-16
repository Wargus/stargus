/*
 * Widget.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include <Palette.h>
#include <PngExporter.h>
#include "Widgets.h"
#include "Storm.h"
#include "Preferences.h"
#include "FileUtil.h"
#include "pacman.h"

// system
#include <fstream>
#include <iostream>

using namespace std;

Widgets::Widgets(std::shared_ptr<Hurricane> hurricane) :
  Grp(hurricane)
{

}

Widgets::~Widgets()
{

}

bool Widgets::convert(const std::string &arcfile, Storage filename, json &frameExtractJson)
{
  bool result = true;

  std::shared_ptr<DataChunk> dcGrp = mHurricane->extractDataChunk(arcfile);

  std::vector<char> GrpVec = dcGrp->getCharVector();

  mGRPImage.LoadImage(&GrpVec, true); // true: no duplicate widgets needed

  CheckPath(filename.getFullPath());

  if(dcGrp)
  {
    //cout << frameExtractJson << endl; // prints json object to screen

    //vector<string> frameSingleNames;

    for(auto &array : frameExtractJson)
    {
      //int frame_id = array.at("frame");
      string name = array.at("name");
      nlohmann::json frameArray = array.at("frame");

      int frameStitching = 0;
      vector<int> stitchedFrames;
      for(auto frame : frameArray)
      {
        //cout << "frame: " << frame << endl;
        stitchedFrames.push_back(frame);
        frameStitching++;
      }

      if(frameStitching == 1)
      {
        //frameSingleNames.push_back(name);
        mGRPImage.SaveSinglePNG(filename.getFullPath() + "/" + name, *stitchedFrames.begin(), *stitchedFrames.begin()+1, true);
      }
      else if(frameStitching > 1)
      {
        mGRPImage.SaveStitchedPNG(filename.getFullPath() + "/" + name, stitchedFrames, 0, true);
      }
      else
      {
        cerr << "something wrong with frame array!" << endl;
      }
    }

    //mGRPImage.SaveSinglePNG(filename.getFullPath(), frameSingleNames, 0, mGRPImage.getNumberOfFrames(), true);
  }

  return result;
}



