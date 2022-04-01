#ifndef STORM_TEST_H
#define STORM_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// system
#include <string.h>

// project
#include "Storm.h"

class StormTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(StormTest);

  CPPUNIT_TEST(StormTest_test1_mpq_txt_extractMemory);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:
  /**
   * Test the extractMemory() function by reading a string from a example .mpq file and compare the content
   */
  void StormTest_test1_mpq_txt_extractMemory();

private:

};

#endif // STORM_TEST_H
