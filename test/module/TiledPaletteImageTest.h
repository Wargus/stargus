#ifndef TILEDPALETTEIMAGE_TEST_H
#define TILEDPALETTEIMAGE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// system
#include <string.h>
#include <cstdio>

// project

class TiledPaletteImageTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(TiledPaletteImageTest);

  CPPUNIT_TEST(test1_tileStrategyCompare);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:
  /**
   * Tbd
   */
  void test1_tileStrategyCompare();


private:

};

#endif // TILEDPALETTEIMAGE_TEST_H
