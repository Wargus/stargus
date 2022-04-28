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
#include <vector>
#include <array>

class Palette2D
{
public:
  Palette2D(size_t size);
  virtual ~Palette2D();

  const Color &at(int x, int y) const;

  Color &at(int x, int y);

private:
  std::vector<std::array<Color, 256>> mColorPalette2D;
};

#endif /* PALETTE2D_H */
