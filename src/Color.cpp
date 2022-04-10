/*
 * RGBColor.cpp
 *
  *      Author: Andreas Volz
 */

#include <Color.h>

Color::Color() :
  mRed(0),
  mGreen(0),
  mBlue(0)
{

}

Color::Color(const Color &color) :
  mRed(color.mRed),
  mGreen(color.mGreen),
  mBlue(color.mBlue)
{

}

Color::Color(unsigned char red, unsigned char green, unsigned char blue) :
  mRed(red), mGreen(green), mBlue(blue)
{

}

Color::~Color()
{

}

void Color::red(unsigned char color)
{
  mRed = color;
}

void Color::green(unsigned char color)
{
  mGreen = color;
}

void Color::blue(unsigned char color)
{
  mBlue = color;
}

unsigned char Color::red() const
{
  return mRed;
}

unsigned char Color::green() const
{
  return mGreen;
}

unsigned char Color::blue() const
{
  return mBlue;
}


Color& Color::operator=(const Color& color)
{
  mRed = color.mRed;
  mGreen = color.mGreen;
  mBlue = color.mBlue;

  return *this;
}



