/*
 * Palette2D.cpp
 *
 *      Author: Andreas Volz
 */

#include "Palette2D.h"
#include "Logger.h"

#include <fstream>

using namespace std;

static Logger logger = Logger("startool.Palette2D");

Palette2D::Palette2D(int size) :
  mColorPalette2D(size),
  mSize(size)
{

}

Palette2D::Palette2D(std::shared_ptr<DataChunk> rawPalette) :
  mColorPalette2D(rawPalette->getSize()/256),
  mSize(rawPalette->getSize()/256)
{
  // TODO check if size match and if not throw Exception/assert

  for(int i = 0; i < mSize; i++)
  {
    shared_ptr<DataChunk> dc;
    dc->addData(rawPalette->getDataPointer(), 256);

    Palette pal(dc);

    mColorPalette2D.push_back(pal);
  }
}

Palette2D::~Palette2D()
{

}

const Color &Palette2D::at(int x, int y) const
{
  const auto &color_array = mColorPalette2D.at(y);
  const Color &color = color_array.at(x);

  return color;
}

Color &Palette2D::at(int x, int y)
{
  auto &color_array = mColorPalette2D.at(y);
  Color &color = color_array.at(x);

  return color;
}

int Palette2D::getSize()
{
  return mSize;
}

bool Palette2D::write(const std::string &filename)
{
  bool result = true;

  ofstream wf(filename, ios::out | ios::binary);

  if (wf)
  {
    for(Palette &pal : mColorPalette2D)
    {
      for(unsigned int i = 0; i < 256; i++)
      {
        char red = pal.at(i).getRed();
        char green = pal.at(i).getGreen();
        char blue = pal.at(i).getBlue();


        wf.write((char *) &red, sizeof(unsigned char));
        wf.write((char *) &green, sizeof(unsigned char));
        wf.write((char *) &blue, sizeof(unsigned char));

        i++;
      }
    }
    wf.close();
  }
  else
  {
    LOG4CXX_DEBUG(logger, string("Couldn't write in: ") + filename);
    result = false;
  }

  return result;
}
