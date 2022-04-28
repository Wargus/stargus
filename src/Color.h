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
  virtual ~Color();

  void setRed(unsigned char c);
  void setGreen(unsigned char c);
  void setBlue(unsigned char c);

  unsigned char getRed() const;
  unsigned char getGreen() const;
  unsigned char getBlue() const;

  Color getBrighened() const;

  Color& operator=(const Color& color);

  unsigned char getBiggestColor() const;

private:


  unsigned char mRed;
  unsigned char mGreen;
  unsigned char mBlue;
};

#endif /* COLOR_H */
