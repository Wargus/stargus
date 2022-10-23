#ifndef DATACHUNK_TEST_H
#define DATACHUNK_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// system
#include <string.h>
#include <cstdio>

// project
#include "DataChunk.h"

class DataChunkTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(DataChunkTest);

  CPPUNIT_TEST(test1_addData);
  CPPUNIT_TEST(test2_createFromExistingHeap);
  CPPUNIT_TEST(test3_vectorReturn);
  CPPUNIT_TEST(test4_write_compare);
  CPPUNIT_TEST(test5_read_write_compare);


  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:
  /**
   * Create an empty DataCkunk add some data, read it back with the at() function and compare with input data
   */
  void test1_addData();

  /**
   * Create an DataCkunk from heap memory, add some data, read it back with the getDataPointer() function and compare content
   */
  void test2_createFromExistingHeap();

  /**
   * Create an empty DataCkunk add some data, read it back with the getUCharVector() function and compare input data with vector content
   */
  void test3_vectorReturn();

  /**
   * Create an empty DataCkunk add some data, write it into a file, read it back from file and compare with input data
   */
  void test4_write_compare();

  /**
   * Similar to test4_write_compare() but with the DataChunk::read() function
   */
  void test5_read_write_compare();

private:

};

#endif // DATACHUNK_TEST_H
