#ifndef LUAGEN_TEST_H
#define LUAGEN_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// system
#include <string.h>
#include <cstdio>

// project

class luagenTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE(luagenTest);

  CPPUNIT_TEST(test_function);
  CPPUNIT_TEST(test_table);
  CPPUNIT_TEST(test_assign);
  CPPUNIT_TEST(test_quote);
  CPPUNIT_TEST(test_singleQuote);
  CPPUNIT_TEST(test_params);
  CPPUNIT_TEST(test_paramsQuote);
  CPPUNIT_TEST(test_line);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:
  /**
   * Test the LUA function generators: name()
   */
  void test_function();

  /**
   * Test the LUA table generators: {name}
   */
  void test_table();

  /**
   * Test the LUA assign generators: a = b
   */
  void test_assign();

  /**
   * Test the LUA quoting generators to surround a string with ""
   */
  void test_quote();

  /**
   * Test the LUA quoting generators to surround a string with ''
   */
  void test_singleQuote();

  /**
   * Test the LUA parameters (in functions, tables,... generators: a, b, c
   */
  void test_params();

  /**
   * Test the LUA parameters (in functions, tables,... generators: "a", "b", "c"
   */
  void test_paramsQuote();

  /**
   * The a simple newline generator: line\n
   */
  void test_line();

private:

};

#endif // LUAGEN_TEST_H
