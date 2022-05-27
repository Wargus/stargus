#ifndef TILEDPALETTEIMAGE_TEST_H
#define TILEDPALETTEIMAGE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// system
#include <string.h>
#include <cstdio>

// project
#include "Palette.h"

class TiledPaletteImageTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(TiledPaletteImageTest);

  CPPUNIT_TEST(test1_tileStrategyCompare);
  CPPUNIT_TEST(test2_tileHorizontalFlipping);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:
  /**
   * Generate 8x8 image in red, green, blue, yellow and order them in a 2x2 tile.
   * Compare both results by comparing both images vector data. This test doesn't
   * check if the image itself was created as specified or if both are wrong.
   */
  void test1_tileStrategyCompare();

  void test2_tileHorizontalFlipping();


private:
  Palette generateTestPalette();

  const unsigned char ColorBlack  = 0;
  const unsigned char ColorRed    = 1;
  const unsigned char ColorGreen  = 2;
  const unsigned char ColorBlue   = 3;
  const unsigned char ColorYellow = 4;

};

#endif // TILEDPALETTEIMAGE_TEST_H
