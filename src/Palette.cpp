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


Palette::Palette(std::shared_ptr<DataChunk> rawPalette) :
  mLogger("startool.Palette")
{
  load(rawPalette);
}

Palette::~Palette()
{
}

void Palette::load(std::shared_ptr<DataChunk> rawPalette)
{
  if(rawPalette->getSize() == 256 * 4) // RGBx/WPE size type
    {
      for(unsigned int i = 0; i < rawPalette->getSize(); i += 4)
      {
        unsigned char red = rawPalette->at(i);
        unsigned char green = rawPalette->at(i+1);
        unsigned char blue = rawPalette->at(i+2);
        // ignore the 4th component, as it is not used as alpha

        Color rgb(red, green, blue);
        addColor(rgb);
      }
    }
    else if(rawPalette->getSize() == 256 * 3) // RGB size type
    {
      for(unsigned int i = 0; i < rawPalette->getSize(); i += 3)
      {
        unsigned char red = rawPalette->at(i);
        unsigned char green = rawPalette->at(i+1);
        unsigned char blue = rawPalette->at(i+2);

        Color rgb(red, green, blue);
        addColor(rgb);
      }
    }
    else
    {
      LOG4CXX_ERROR(mLogger, string("Palette size doesn't fit to RGB (256*3 bytes) or RGBx/WPE (256*4 bytes): ") + to_string(rawPalette->getSize()) + " bytes");
    }
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

void Palette::replaceIndexColor(unsigned int index, const Color &rgb)
{
  if(index <= mColorPalette.size())
  {
    mColorPalette[index] = rgb;
  }
}

void Palette::replaceIndexColorRange(const Palette &pal, unsigned int startIndex, unsigned int endIndex)
{
  for(unsigned int index = startIndex; index <= endIndex; index++)
  {
    replaceIndexColor(index, pal.at(index));
  }
}

bool Palette::write(const std::string filename)
{
  bool result = true;

  ofstream wf(filename, ios::out | ios::binary);

  if (wf)
  {
    for(vector<Color>::iterator col_vec_it = mColorPalette.begin(); col_vec_it != mColorPalette.end(); col_vec_it++)
    {
      Color &color = *col_vec_it;
      char red = color.red();
      char green = color.green();
      char blue = color.blue();


      wf.write((char *) &red, sizeof(unsigned char));
      wf.write((char *) &green, sizeof(unsigned char));
      wf.write((char *) &blue, sizeof(unsigned char));
    }
    wf.close();
  }
  else
  {
    LOG4CXX_DEBUG(mLogger, string("Couldn't write in: ") + filename);
    result = false;
  }

  return result;
}
