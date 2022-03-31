#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TextTestRunner.h>

/* log4cxx */
#ifdef HAVE_LOG4CXX
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
#endif // HAVE_LOG4CXX

#ifdef HAVE_LOG4CXX
using namespace log4cxx;
using namespace log4cxx::helpers;
#endif // HAVE_LOG4CXX

using namespace std;

int main (int argc, char **argv)
{
  #ifdef HAVE_LOG4CXX
    PropertyConfigurator::configure ("logging.prop");
  #endif // HAVE_LOG4CXX

  // informs test-listener about testresults
  CPPUNIT_NS::TestResult testresult;
  
  // register listener for collecting the test-results
  CPPUNIT_NS::TestResultCollector collectedresults;
  testresult.addListener (&collectedresults);

  CPPUNIT_NS::BriefTestProgressListener progress;
  testresult.addListener (&progress);

  // insert test-suite at test-runner by registry
  CPPUNIT_NS::TextTestRunner testrunner;
  testrunner.setOutputter (CppUnit::CompilerOutputter::defaultOutputter(
                           &testrunner.result(), std::cerr));

  testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
  testrunner.run (testresult);

  // output results in compiler-format
  CPPUNIT_NS::CompilerOutputter compileroutputter (&collectedresults, std::cerr);

  compileroutputter.write ();
    
  // return 0 if tests were successful
  return collectedresults.wasSuccessful () ? 0 : 1;
}
