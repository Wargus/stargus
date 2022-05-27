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
  mBlue(0),
  mAlpha(0)
{

}

Color::Color(const Color &color) :
  mRed(color.mRed),
  mGreen(color.mGreen),
  mBlue(color.mBlue),
  mAlpha(0)
{

}

Color::Color(unsigned char red, unsigned char green, unsigned char blue) :
  mRed(red),
  mGreen(green),
  mBlue(blue),
  mAlpha(0)
{

}

Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) :
  mRed(red),
  mGreen(green),
  mBlue(blue),
  mAlpha(alpha)
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

void Color::setAlpha(unsigned char color)
{
  mAlpha = color;
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

unsigned char Color::getAlpha() const
{
  return mAlpha;
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

Color Color::blendAgainstReference(const Color &reference) const
{
  Color color_bright = getBrighened();

  double alpha = 0;

  // red biggest
  if((getRed() > getGreen()) &
     (getRed() > getBlue()))
  {
    alpha = (double) (getRed() - reference.getRed()) /
            (double) (color_bright.getRed() - reference.getRed());

  }
  // green is biggest
  else if((getGreen() > getRed()) &
          (getGreen() > getBlue()))
  {
    alpha = (double) (getGreen() - reference.getGreen()) /
            (double) (color_bright.getGreen() - reference.getGreen());
  }
  // blue is biggest
  {
    alpha = (double) (getBlue() - reference.getBlue()) /
            (double) (color_bright.getBlue() - reference.getBlue());
  }

  unsigned char red = alpha * getRed() + (1 - alpha) * reference.getRed();
  unsigned char green = alpha * getGreen() + (1 - alpha) * reference.getGreen();
  unsigned char blue = alpha * getBlue() + (1 - alpha) * reference.getBlue();

  Color color_result (red, green, blue, alpha * 255);

  return color_result;
}

Color& Color::operator=(const Color& color)
{
  mRed = color.mRed;
  mGreen = color.mGreen;
  mBlue = color.mBlue;
  mAlpha = color.mAlpha;

  return *this;
}



