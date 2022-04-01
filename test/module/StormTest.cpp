#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "StormTest.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(StormTest);

void StormTest::setUp()
{

}

void StormTest::tearDown()
{

}

void StormTest::StormTest_test1_mpq_txt_extractMemory()
{
  unsigned char *text_str = NULL;
  size_t bufLen = 0;
  string test_data_dir = "test/module/data/";

  shared_ptr<Storm> storm = make_shared<Storm>(test_data_dir + "StormTest_test1_mpq_txt.mpq");

  bool result = storm->extractMemory("test.txt", &text_str, &bufLen);

  CPPUNIT_ASSERT(result == true);
  CPPUNIT_ASSERT((int)bufLen == 10);
  CPPUNIT_ASSERT(string((char *) text_str) != string("stormtest"));
}

