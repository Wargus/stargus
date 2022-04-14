/*
 * PaletteImage.cpp
 *
 *      Author: Andreas Volz
 */

#include "PaletteImage.h"

using namespace std;

PaletteImage::PaletteImage(const DataChunk &datachunk, int width, int height) :
    mImageData(datachunk), mWidth(width), mHeight(height)
{

}

PaletteImage::PaletteImage(int width, int height) :
  mWidth(width), mHeight(height)
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

  if((x < getWidth()) || (y < getHeight()) || (x > 0) || (y > 0))
  {
    if(y == 0)
    {
      pos = x;
    }
    else
    {
      pos = ((y - 1) * getWidth()) + x;
      palette = mImageData.at(pos);
    }
  }
  else
  {
    printf("getPaletteIndex(int x, int y) error");
  }

  return palette;
}

int PaletteImage::getHeight() const
{
  return mHeight;
}

int PaletteImage::getWidth() const
{
  return mWidth;
}

unsigned char PaletteImage::at(size_t pos)
{
  return mImageData.at(pos);
}
