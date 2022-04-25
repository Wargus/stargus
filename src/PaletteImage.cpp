/*
 * PaletteImage.cpp
 *
 *      Author: Andreas Volz
 */

#include "PaletteImage.h"

using namespace std;

PaletteImage::PaletteImage(const DataChunk &datachunk, Size size) :
    mImageData(datachunk), mSize(size)
{

}

PaletteImage::PaletteImage(Size size) :
  mSize(size)
{

}

PaletteImage::~PaletteImage()
{

}

void PaletteImage::addPaletteIndex(unsigned char paletteIndex)
{
  mImageData.addData(&paletteIndex, 1);
}

unsigned char* PaletteImage::getRawData() const
{
  return mImageData.getDataPointer();
}

unsigned char PaletteImage::getPaletteIndex(int x, int y)
{
  int pos = 0;
  unsigned char palette = 0;

  if((x < mSize.getWidth()) || (y < mSize.getHeight()) || (x > 0) || (y > 0))
  {
    if(y == 0)
    {
      pos = x;
    }
    else
    {
      pos = ((y - 1) * mSize.getWidth()) + x;
    }
    palette = mImageData.at(pos);
  }
  else
  {
    printf("getPaletteIndex(int x, int y) error");
  }

  return palette;
}

Size PaletteImage::getSize() const
{
  return mSize;
}

unsigned char PaletteImage::at(size_t pos)
{
  return mImageData.at(pos);
}
