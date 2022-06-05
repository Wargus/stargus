#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// system
#include <string>

// project
#include "luagenTest.h"
#include "luagen.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(luagenTest);

void luagenTest::setUp()
{

}

void luagenTest::tearDown()
{

}


void luagenTest::test_function()
{
  string string_function = lg::function("name", "one, two, three");
  string initializer_list_function = lg::function("name", {"one", "two", "three"});

  string lua_result_spec("name(one, two, three)");

  CPPUNIT_ASSERT(initializer_list_function == lua_result_spec);
  CPPUNIT_ASSERT(initializer_list_function == string_function);
}

void luagenTest::test_table()
{
  string string_table = lg::table("one, two, three");
  string initializer_list_table = lg::table({"one", "two", "three"});

  string lua_result_spec("{one, two, three}");

  CPPUNIT_ASSERT(string_table == lua_result_spec);
  CPPUNIT_ASSERT(initializer_list_table == lua_result_spec);
}

void luagenTest::test_assign()
{
  string result = lg::assign("a", "b");

  CPPUNIT_ASSERT(result == "a = b");
}

void luagenTest::test_quote()
{
  string result = lg::quote("example");

  CPPUNIT_ASSERT(result == "\"example\"");
}


void luagenTest::test_params()
{
  vector<string> vector_params_input;
  vector_params_input.push_back("one");
  vector_params_input.push_back("two");
  vector_params_input.push_back("three");

  string intitializer_list_params = lg::params({"one", "two", "three"});
  string vector_params = lg::params(vector_params_input);

  string lua_result_spec("one, two, three");

  CPPUNIT_ASSERT(intitializer_list_params == lua_result_spec);
  CPPUNIT_ASSERT(vector_params == lua_result_spec);
}

void luagenTest::test_paramsQuote()
{
  vector<string> vector_params_input;
  vector_params_input.push_back("one");
  vector_params_input.push_back("two");
  vector_params_input.push_back("three");

  string intitializer_list_params = lg::paramsQuote({"one", "two", "three"});
  string vector_params = lg::paramsQuote(vector_params_input);

  string lua_result_spec("\"one\", \"two\", \"three\"");

  CPPUNIT_ASSERT(intitializer_list_params == lua_result_spec);
  CPPUNIT_ASSERT(vector_params == lua_result_spec);
}

void luagenTest::test_line()
{
  string result = lg::line("example");

  CPPUNIT_ASSERT(result == "example\n");
}
