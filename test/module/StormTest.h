#ifndef STORM_TEST_H
#define STORM_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// STD
#include <string.h>

class StormTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE (StormTest);

  CPPUNIT_TEST (testFunc1);

  CPPUNIT_TEST_SUITE_END ();

public:
  void setUp ();
  void tearDown ();

protected:
  /**
   * dummy
   */
  void testFunc1 ();

private:

};

#endif // STORM_TEST_H
