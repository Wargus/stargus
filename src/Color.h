/*
 * RGBColor.h
 *
 *      Author: Andreas Volz
 */

#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class Color
{
public:
  Color();
  virtual ~Color();

  void red(unsigned char c);
  void green(unsigned char c);
  void blue(unsigned char c);

  unsigned char red() const;
  unsigned char green() const;
  unsigned char blue() const;

private:
  unsigned char mRed;
  unsigned char mGreen;
  unsigned char mBlue;
};

#endif /* RGBCOLOR_H */
