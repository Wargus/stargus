/*
 * Palette2D.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "Palette2D.h"
#include "Logger.h"
#include "NoValidPaletteException.h"

// system
#include <fstream>
#include <iostream>

using namespace std;

static Logger logger = Logger("startool.Palette2D");

Palette2D::Palette2D(unsigned int size) :
  mColorPalette2D(size)
{

}

Palette2D::Palette2D(std::shared_ptr<DataChunk> rawPalette) :
  mColorPalette2D(rawPalette->getSize()/256)
{
  /**
   * For initial construction just check that the DataChunk is a multiple of 256*3 bytes
   * which is an hint for a valid 2D palette.
   */
  if((rawPalette->getSize() % (256 * 3)))
  {
    throw NoValidPaletteException(rawPalette->getSize());
  }

  load(rawPalette);
}

Palette2D::~Palette2D()
{

}

void Palette2D::load(std::shared_ptr<DataChunk> rawPalette)
{
  mColorPalette2D.clear();

  unsigned int paletteSize = rawPalette->getSize() / (256*3);

  for(unsigned int i = 0; i < paletteSize; i++)
  {
    shared_ptr<DataChunk> dc = make_shared<DataChunk>();

    int start_read_pos = i * 256 *3;
    int read_size = 256*3;
    dc->addData(rawPalette->getDataPointer() + start_read_pos, read_size);

    Palette pal(dc);

    mColorPalette2D.push_back(pal);
  }
}

std::shared_ptr<DataChunk> Palette2D::createDataChunk()
{
  std::shared_ptr<DataChunk> datachunk = make_shared<DataChunk>();

  for(Palette &pal : mColorPalette2D)
  {
    for(unsigned int i = 0; i < 256; i++)
    {
      unsigned char red = pal.at(i).getRed();
      unsigned char green = pal.at(i).getGreen();
      unsigned char blue = pal.at(i).getBlue();

      datachunk->addData(&red, 1);
      datachunk->addData(&green, 1);
      datachunk->addData(&blue, 1);
    }

  }

  return datachunk;
}

Color &Palette2D::at(unsigned int column, unsigned int row)
{
  auto &color_array = mColorPalette2D.at(row);
  Color &color = color_array.at(column);

  return color;
}

unsigned int Palette2D::getSize()
{
  return mColorPalette2D.size();
}


