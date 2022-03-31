#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "StormTest.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION (StormTest);

void StormTest::setUp ()
{
  
}

void StormTest::tearDown ()
{
  
}

void StormTest::testFunc1 ()
{
  // test here
  int result1 = 5;
  int result2 = 5;

  CPPUNIT_ASSERT_EQUAL (result1, result2);
}

