/*
 * Palettes.cpp
 *
 *      Author: Andreas Volz
 */

#include <Palette.h>

// C++
#include <iostream>
#include <fstream>

using namespace std;

Palette::Palette() :
  mLogger("startool.Palette")
{

}

Palette::Palette(std::shared_ptr<DataChunk> wpePalette) :
  mLogger("startool.Palette")
{
  if(wpePalette->getSize() == 256 * 4) // RGBx/WPE size type
  {
    for(unsigned int i = 0; i < wpePalette->getSize(); i += 4)
    {
      unsigned char red = wpePalette->at(i);
      unsigned char green = wpePalette->at(i+1);
      unsigned char blue = wpePalette->at(i+2);
      // ignore the 4th component, as it is not used as alpha

      Color rgb(red, green, blue);
      addColor(rgb);
    }
  }
  else if(wpePalette->getSize() == 256 * 3) // RGB size type
  {
    for(unsigned int i = 0; i < wpePalette->getSize(); i += 3)
    {
      unsigned char red = wpePalette->at(i);
      unsigned char green = wpePalette->at(i+1);
      unsigned char blue = wpePalette->at(i+2);

      Color rgb(red, green, blue);
      addColor(rgb);
    }
  }
  else
  {
    LOG4CXX_ERROR(mLogger, string("Palette size doesn't fit to RGB (256*3 bytes) or RGBx/WPE (256*4 bytes): ") + to_string(wpePalette->getSize()) + " bytes");
  }
}

Palette::~Palette()
{
}

std::shared_ptr<DataChunk> Palette::createDataChunk()
{
  std::shared_ptr<DataChunk> datachunk = make_shared<DataChunk>();

  for(vector<Color>::iterator color_it = mColorPalette.begin(); color_it < mColorPalette.end(); color_it++)
  {
    Color &rgb = *color_it;
    unsigned char red = rgb.red();
    unsigned char green = rgb.green();
    unsigned char blue = rgb.blue();

    datachunk->addData(&red, 1);
    datachunk->addData(&green, 1);
    datachunk->addData(&blue, 1);
  }

  return datachunk;
}

void Palette::addColor(const Color &rgb)
{
  mColorPalette.push_back(rgb);
}

const Color &Palette::at(int index) const
{
  return mColorPalette.at(index);
}

Color &Palette::at(int index)
{
  return mColorPalette.at(index);
}

void Palette::replaceIndexColor(int index, const Color &rgb)
{
  mColorPalette[index] = rgb;
}
