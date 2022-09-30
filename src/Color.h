/*
 * Color.h
 *
 *      Author: Andreas Volz
 */

#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
  Color();
  Color(const Color &color);
  Color(unsigned char red, unsigned char green, unsigned char blue);
  Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
  virtual ~Color();

  void setRed(unsigned char color);
  void setGreen(unsigned char color);
  void setBlue(unsigned char color);
  void setAlpha(unsigned char color);

  unsigned char getRed() const;
  unsigned char getGreen() const;
  unsigned char getBlue() const;
  unsigned char getAlpha() const;

  /**
   * @return The same color but 100% brightened
   */
  Color getBrighened() const;

  /**
   * Blend the current color against a reference color (don't modify current color)
   *
   * @return The new blended color
   */
  Color blendAgainstReference(const Color &reference) const;

  Color& operator=(const Color& color);

private:
  unsigned char getBiggestColor() const;

  unsigned char mRed;
  unsigned char mGreen;
  unsigned char mBlue;
  unsigned char mAlpha;
};

#endif /* COLOR_H */
