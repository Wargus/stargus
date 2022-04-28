/*
 * Color.cpp
 *
  *      Author: Andreas Volz
 */

// project
#include <Color.h>

// system
#include <algorithm>

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
  mRed(red),
  mGreen(green),
  mBlue(blue)
{

}

Color::~Color()
{

}

void Color::setRed(unsigned char color)
{
  mRed = color;
}

void Color::setGreen(unsigned char color)
{
  mGreen = color;
}

void Color::setBlue(unsigned char color)
{
  mBlue = color;
}

unsigned char Color::getRed() const
{
  return mRed;
}

unsigned char Color::getGreen() const
{
  return mGreen;
}

unsigned char Color::getBlue() const
{
  return mBlue;
}

unsigned char Color::getBiggestColor() const
{
  return std::max(std::max(mRed, mGreen), mBlue);
}

Color Color::getBrighened() const
{
  double color_factor = getBiggestColor() / 255.0;

  unsigned char bright_red = mRed / color_factor;
  unsigned char bright_green = mGreen / color_factor;
  unsigned char bright_blue = mBlue / color_factor;

  Color bright_color(bright_red, bright_green, bright_blue);

  return bright_color;
}

Color& Color::operator=(const Color& color)
{
  mRed = color.mRed;
  mGreen = color.mGreen;
  mBlue = color.mBlue;

  return *this;
}



