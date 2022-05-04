/*
 * Palette2D.cpp
 *
 *      Author: Andreas Volz
 */

#include "Palette2D.h"

using namespace std;

Palette2D::Palette2D(int size) :
  mColorPalette2D(size),
  mSize(size)
{

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
