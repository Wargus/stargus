#ifndef BREEZE_TEST_H
#define BREEZE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// system
#include <string.h>
#include <cstdio>

// project
#include "Breeze.h"

class BreezeTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(BreezeTest);

  CPPUNIT_TEST(test1_txt_extractMemory);
  CPPUNIT_TEST(test2_txt_extractFile);
  CPPUNIT_TEST(test3_txt_extractFileCompressed);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:
  /**
   * Extract file from a file from that "archive" into memory and compare the content
   */
  void test1_txt_extractMemory();

  /**
   * Extract file from a file from that "archive" into a file, read it back and compare the content
   */
  void test2_txt_extractFile();

  /**
   * Extract file from a file from that "archive" into a file (gzip compressed), read it back and compare the content
   */
  void test3_txt_extractFileCompressed();


private:

};

#endif // BREEZE_TEST_H
