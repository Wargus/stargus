/*
 * PaletteImage.cpp
 *
 *      Author: Andreas Volz
 */

#include "PaletteImage.h"

using namespace std;

PaletteImage::PaletteImage(int width, int height) :
  mWidth(width), mHeight(height)
{

}

PaletteImage::~PaletteImage()
{

}

void PaletteImage::addPixel(unsigned char paletteIndex)
{
  mImageData.addData(&paletteIndex, 1);
}

unsigned char* PaletteImage::getPixelData() const
{
  return mImageData.getDataPointer();
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
