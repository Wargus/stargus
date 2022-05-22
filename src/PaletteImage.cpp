/*
 * PaletteImage.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "PaletteImage.h"

// system
#include <iostream>
#include <math.h>

using namespace std;

PaletteImage::PaletteImage(const DataChunk &datachunk, const Size &size) :
  mData(datachunk.getDataPointer(), datachunk.getDataPointer()+datachunk.getSize()),
  mSize(size)
{

}

PaletteImage::PaletteImage(const Size &size) :
  mData(size.getWidth() * size.getHeight(), 0),
  mSize(size)
{

}

PaletteImage::~PaletteImage()
{

}

const unsigned char* PaletteImage::getRawDataPointer() const
{
  return mData.data();
}

size_t PaletteImage::positionToIndex(const Pos &pos) const
{
  size_t data_pos = 0;

  // if pos is outside image return just 0 as fail safe
  if((pos.getX() < mSize.getWidth()) || (pos.getY() < mSize.getHeight()) || (pos.getX() > 0) || (pos.getY() > 0))
  {
    data_pos = (pos.getY() * mSize.getWidth()) + pos.getX();
  }

  return data_pos;
}

const Pos PaletteImage::indexToPosition(size_t index) const
{
  int y = 0;
  int x = 0;

  // if index is out of data size that return Pos(0, 0) as fail safe
  if(index < mData.size())
  {
    y = index / mSize.getWidth();
    x = index % mSize.getWidth();
  }

  return Pos(x, y);
}

const Size PaletteImage::getSize() const
{
  return mSize;
}

unsigned char &PaletteImage::at(const Pos &pos)
{
  return at(positionToIndex(pos));
}

const unsigned char &PaletteImage::at(const Pos &pos) const
{
  return at(positionToIndex(pos));
}

unsigned char &PaletteImage::at(size_t pos)
{
  return mData.at(pos);
}

const unsigned char &PaletteImage::at(size_t pos) const
{
  return mData.at(pos);
}
