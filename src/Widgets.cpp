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

bool Widgets::convert2(const std::string &arcfile, Storage filename, json &frameExtractJson)
{
  bool result = true;

  std::shared_ptr<DataChunk> dcGrp = mHurricane->extractDataChunk(arcfile);

  std::vector<char> GrpVec = dcGrp->getCharVector();

  if(dcGrp)
  {
    //cout << frameExtractJson << endl; // prints json object to screen

    vector<string> frameNames;

    for(auto &array : frameExtractJson)
    {
      //int frame_id = array.at("frame");
      string name = array.at("name");

      //cout << "frame: " << to_string(frame_id) << endl;
      //cout << "name: " << name << endl;

      frameNames.push_back(name);
    }

    mGRPImage.LoadImage(&GrpVec, true); // true: no duplicate widgets needed

    CheckPath(filename.getFullPath());
    mGRPImage.SaveSinglePNG(filename.getFullPath(), frameNames, 0, mGRPImage.getNumberOfFrames(), true);

    vector<int> testVec;
    testVec.push_back(88);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(82);
    testVec.push_back(83);

    mGRPImage.SaveStitchedPNG(filename.getFullPath()+"/widget2.png", testVec, 0, true);
  }

  return result;
}

bool Widgets::convert(const char *arcfile,
                      const char *file)
{
  unsigned char *gfup = NULL;
  unsigned char *gfup2 = NULL;
  unsigned char *image = NULL;
  int w;
  int h;
  char buf[1024];
  unsigned char *p;
  unsigned char *end;
  bool result = true;

  result = mHurricane->extractMemory(arcfile, &gfup, NULL);
  if (result)
  {
    image = ConvertGraphic(false, gfup, &w, &h, gfup2);

    // 0 and 255 are transparent
    p = image;
    end = image + w * h;
    while (p < end)
    {
      if (!*p)
      {
        *p = 0xFF;
      }
      ++p;
    }

    free(gfup);

    Preferences &preferences = Preferences::getInstance();

    // TODO: the complete.png is not used in stargus UI, just saved for debug/understanding reason
    sprintf(buf, "%s/graphics/%s/complete.png", preferences.getDestDir().c_str(), file);
    //SaveImage(buf, image, *mPalette, 1, w, h);

    sprintf(buf, "%s/graphics/%s/menu.png", preferences.getDestDir().c_str(),
            file);
    SaveImage(buf, image, 1, 64, 20);

    sprintf(buf, "%s/graphics/%s/menu pressed.png",
            preferences.getDestDir().c_str(), file);
    SaveImage(buf, image, 2, 64, 20);

    sprintf(buf, "%s/graphics/%s/minimap terrain disabled.png",
            preferences.getDestDir().c_str(), file);
    SaveImage(buf, image,3, 64, 20);

    sprintf(buf, "%s/graphics/%s/minimap terrain.png",
            preferences.getDestDir().c_str(), file);
    SaveImage(buf, image, 4, 64, 20);

    sprintf(buf, "%s/graphics/%s/minimap terrain pressed.png",
            preferences.getDestDir().c_str(), file);
    SaveImage(buf, image, 5, 64, 20);

    sprintf(buf, "%s/graphics/%s/diplomacy disabled.png",
            preferences.getDestDir().c_str(), file);
    SaveImage(buf, image, 83, 64, 20);

    sprintf(buf, "%s/graphics/%s/diplomacy.png",
            preferences.getDestDir().c_str(), file);
    SaveImage(buf, image, 84, 64, 20);

    sprintf(buf, "%s/graphics/%s/diplomacy pressed.png",
            preferences.getDestDir().c_str(), file);
    SaveImage(buf, image, 85, 64, 20);

    sprintf(buf, "%s/graphics/%s/button left disabled 224x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 224, 104);

    sprintf(buf, "%s/graphics/%s/button left 224x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 224, 107);

    sprintf(buf, "%s/graphics/%s/button left pressed 224x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 224, 110);

    sprintf(buf, "%s/graphics/%s/button left disabled 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 104);

    sprintf(buf, "%s/graphics/%s/button left 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 107);

    sprintf(buf, "%s/graphics/%s/button left pressed 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 110);

    sprintf(buf, "%s/graphics/%s/button disabled 224x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 224, 113);

    sprintf(buf, "%s/graphics/%s/button 224x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 224, 116);

    sprintf(buf, "%s/graphics/%s/button pressed 224x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 224, 119);

    sprintf(buf, "%s/graphics/%s/button disabled 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 113);

    sprintf(buf, "%s/graphics/%s/button 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 116);

    sprintf(buf, "%s/graphics/%s/button pressed 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 119);

    sprintf(buf, "%s/graphics/%s/button right disabled 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 122);

    sprintf(buf, "%s/graphics/%s/button right 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 125);

    sprintf(buf, "%s/graphics/%s/button right pressed 104x28.png",
            preferences.getDestDir().c_str(), file);
    SaveButton(buf, image, 104, 128);
  }
  else
  {
    result = false;
  }


  free(image);

  return result;
}

void Widgets::SaveImage(char *name, unsigned char *image,
                        int id, int w, int h)
{
  unsigned char *buf = (unsigned char *) malloc(w * h);
  int i;

  for (i = 0; i < h; ++i)
  {
    memcpy(buf + w * i, image + id * 28 * 64 + 64 * i, w);
  }

  DataChunk dc_image(&buf, w * h);
  PaletteImage palImage(dc_image, Size(w, h));

  PngExporter::save(name, palImage, mPal, 255);
}

void Widgets::SaveButton(char *name, unsigned char *image,
                         int size, int id)
{
  unsigned char *button;
  int i, j;

  button = (unsigned char *) malloc(size * 28);

#define copyimage(dst, src) \
	for (j = 0; j < 28; ++j) { \
		memcpy((dst + size*j), (src + 64*j), 8); \
	}

  copyimage(button + 0, image + (id - 1) * 28 * 64);
  for (i = 8; i < size - 8; i += 8)
  {
    copyimage(button + i, image + id * 28 * 64);
  }
  copyimage(button + size - 8, image + (id + 1) * 28 * 64);

  for (i = 0; i < size * 28; ++i)
  {
    if (button[i] == 41)
    {
      button[i] = 255;
    }
  }

  DataChunk dc_image(&button, size * 28);
  PaletteImage palImage(dc_image, Size(size, 28));

  PngExporter::save(name, palImage, mPal, 255);
}

