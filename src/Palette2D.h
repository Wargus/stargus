/*
 * Palette2D.h
 *
 *      Author: Andreas Volz
 */

#ifndef PALETTE2D_H
#define PALETTE2D_H

// local
#include "Color.h"

// system
#include <array>

class Palette2D
{
public:
  Palette2D();
  virtual ~Palette2D();

  const Color &at(int x, int y) const;

  Color &at(int x, int y);

private:
  std::array<std::array<Color, 256>, 63> mColorPalette2D;
};

#endif /* PALETTE2D_H */
