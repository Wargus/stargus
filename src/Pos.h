#ifndef POS_H
#define POS_H

#include <stdint.h>

/*!
 * Trivial class which stores a Position in integer notation.
 */

class Pos
{
public:
  Pos ();
  Pos (int inX, int inY);
  Pos (const Pos& inPos);

  ~Pos () {}

  Pos& operator= (const Pos& inRHS);

  bool operator== (const Pos& inPos) const;

  bool isEmpty() const { return ((mX == 0) && (mY == 0));}

  int getX ()  const {return mX;}
  int getY() const {return mY;}

  void setX(int x) {mX = x;}
  void setY(int y) {mY = y;}

private:
  int mX, mY;
};

inline Pos::Pos ()
    : mX (0), mY (0)
{
}

inline Pos::Pos(int inX, int inY)
    : mX (inX), mY(inY)
{
}

inline Pos::Pos(const Pos& inPos)
    : mX (inPos.mX), mY(inPos.mY)
{
}

inline Pos& Pos::operator= (const Pos& inRHS)
{
  mX  = inRHS.mX;
  mY = inRHS.mY;
  return *this;
}

inline bool Pos::operator== (const Pos& inPos) const
{
  if (this == &inPos)  // The same object?
    return true;

  return (mX  == inPos.mX &&
          mY == inPos.mY);
}

#endif // POS_H
