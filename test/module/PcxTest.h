#ifndef PCX_TEST_H
#define PCX_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// system
#include <string.h>
#include <cstdio>
#include <cstring>

// project
#include "Pcx.h"
#include "Breeze.h"
#include "TestHelpers.h"

class PcxTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(PcxTest);

  CPPUNIT_TEST(test1_SaveIndexedPalettePNG);
  CPPUNIT_TEST(test2_copyIndexPaletteIconColor);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:

  /**
   * Idea for test cases: (always compare with result test data for sure)
   * -
   * - Load a PCX, use only the Palette information,  exchange palette position with image position -> copyIndexPalette()
   *   - use case: Player coloring
   *   - use case: Icon coloring
   *   - use case: terrain coloring
   *   - use case: fire coloring
   *   - use case: ???
   */


  /**
   * Load a PCX, save as PNG with Palette indexing, file compare PNG image and also the palette data
   */
  void test1_SaveIndexedPalettePNG();


  /**
   *
   */
  void test2_copyIndexPaletteIconColor();

private:

};

#endif // PCX_TEST_H
