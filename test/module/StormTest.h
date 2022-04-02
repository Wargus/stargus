#ifndef STORM_TEST_H
#define STORM_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// system
#include <string.h>
#include <cstdio>


// project
#include "Storm.h"
#include "StringUtil.h"

class StormTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(StormTest);

  CPPUNIT_TEST(test1_mpq_txt_extractMemory);
  CPPUNIT_TEST(test2_mpq_txt_extractFile);
  CPPUNIT_TEST(test3_mpq_txt_extractFileCompressed);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:
  /**
   * Test the extractMemory() function by reading a string from a example .mpq file and compare the content
   */
  void test1_mpq_txt_extractMemory();

  /**
   * Test extractFile() function by expanding the file on drive and then read in again and compare the content
   */
  void test2_mpq_txt_extractFile();

  /**
   * Test extractFile() function by expanding the file (gzip compressed) on drive and then read in again and compare the content
   */
  void test3_mpq_txt_extractFileCompressed();

private:

};

#endif // STORM_TEST_H
