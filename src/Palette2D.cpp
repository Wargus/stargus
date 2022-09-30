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

using namespace std;

static Logger logger = Logger("startool.Palette2D");

Palette2D::Palette2D(unsigned int size) :
  mColorPalette2D(size),
  mSize(size)
{

}

Palette2D::Palette2D(std::shared_ptr<DataChunk> rawPalette) :
  mColorPalette2D(rawPalette->getSize()/256),
  mSize(rawPalette->getSize()/256)
{
  /**
   * For initial construction just check that the DataChunk is a multiple of 256 bytes
   * which is an hint for a valid 2D palette.
   */
  if((rawPalette->getSize() % 256) != 0)
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

  for(unsigned int i = 0; i < mSize; i++)
  {
    shared_ptr<DataChunk> dc;
    dc->addData(rawPalette->getDataPointer(), 256);

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

      i++;
    }
  }

  return datachunk;
}

Color &Palette2D::at(unsigned int column, unsigned int row)
{
  /*if(row <= mSize)
  {
    // dynamic grow the palette if one try to access a not available row
    mColorPalette2D.resize(row);
  }*/

  auto &color_array = mColorPalette2D.at(row);
  Color &color = color_array.at(column);

  return color;
}

unsigned int Palette2D::getSize()
{
  return mSize;
}

bool Palette2D::write(const std::string &filename)
{
  bool result = true;

  std::shared_ptr<DataChunk> dc_pal = createDataChunk();
  result = dc_pal->write(filename);

  return result;
}

bool Palette2D::read(const std::string &filename)
{
  bool result = true;

  std::shared_ptr<DataChunk> dc_pal = make_shared<DataChunk>();
  result = dc_pal->read(filename);
  if(result)
  {
    load(dc_pal);
  }

  return result;
}
