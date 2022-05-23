#ifndef SIZE_H
#define SIZE_H

#include <stdint.h>

/*!
 * Trivial class which stores a size in integer notation. 
 */

class Size
{
public:
  Size ();
  Size (int inWidth, int inHeight);
  Size (const Size& inSize);

  ~Size () {}

  bool isEmpty() const { return ((mWidth == 0) && (mHeight == 0));}

  int getWidth()  const {return mWidth;}

  int getHeight() const {return mHeight;}

  Size& operator= (const Size& inRHS);

  Size& operator *= (const Size& inSize);

  bool operator== (const Size& inSize) const;

  bool operator!= (const Size& inSize) const;

private:
  int mWidth, mHeight;


};

inline Size::Size ()
    : mWidth (0), mHeight (0)
{
}

inline Size::Size(int inWidth, int inHeight)
    : mWidth (inWidth), mHeight(inHeight)
{
}

inline Size::Size(const Size& inSize)
    : mWidth (inSize.mWidth), mHeight(inSize.mHeight)
{
}

inline Size& Size::operator= (const Size& inRHS)
{
  mWidth  = inRHS.mWidth;
  mHeight = inRHS.mHeight;
  return *this;
}

inline bool Size::operator== (const Size& inSize) const
{
  // if the same object
  if (this == &inSize)
  {
    return true;
  }

  return (mWidth  == inSize.mWidth &&
          mHeight == inSize.mHeight);
}

inline bool Size::operator!= (const Size& inSize) const
{
  return !(inSize == *this);
}

inline Size& Size::operator*= (const Size& inSize)
{
  mWidth *= inSize.mWidth;
  mHeight *= inSize.mHeight;

  return *this;
}

inline Size& operator* (const Size& s1, const Size& s2)
{
  Size s3 (s1);

  return s3 *= s2;
}

#endif // SIZE_H
