#ifndef LOGGER_H
#define LOGGER_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_LOG4CXX
/* log4cxx */
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"

class Logger
{
public:
  Logger(const std::string &name) :
    mLogger(log4cxx::Logger::getLogger(name)) {}

  Logger(const std::wstring &name) :
    mLogger(log4cxx::Logger::getLogger(name)) {}

  /**
   * Deactivate all logging in the application complete
   */
  void off()
  {
	log4cxx::BasicConfigurator::configure();
    mLogger->setLevel(log4cxx::Level::getOff());
  }

  log4cxx::LoggerPtr operator = (const Logger &logger)
  {
    return mLogger;
  }

  log4cxx::LoggerPtr operator -> (void)
  {
    return mLogger;
  }

private:
  log4cxx::LoggerPtr mLogger;
};

#else // no LOG4CXX available...

#include <iostream>

#ifdef HAVE_LOGGING
// macros to log all and everything to stderr...
#define LOGSTR "[Logging] - "
#define LOG4CXX_TRACE(logger, expression) std::cerr << LOGSTR << "TRACE " << expression << std::endl;
#define LOG4CXX_DEBUG(logger, expression) std::cerr << LOGSTR << "DEBUG " << expression << std::endl;
#define LOG4CXX_INFO(logger, expression)  std::cerr << LOGSTR << "INFO "  << expression << std::endl;
#define LOG4CXX_WARN(logger, expression)  std::cerr << LOGSTR << "WARN "  << expression << std::endl;
#define LOG4CXX_ERROR(logger, expression) std::cerr << LOGSTR << "ERROR " << expression << std::endl;
#define LOG4CXX_FATAL(logger, expression) std::cerr << LOGSTR << "FATAL " << expression << std::endl;
#else
// macros to log nothing...
#define LOG4CXX_TRACE(logger, expression)
#define LOG4CXX_DEBUG(logger, expression)
#define LOG4CXX_INFO(logger, expression)
#define LOG4CXX_WARN(logger, expression)
#define LOG4CXX_ERROR(logger, expression)
#define LOG4CXX_FATAL(logger, expression)
#endif // LOG2NIX_ACTIVE

class Logger
{
public:
  Logger(const std::string &name)
  {
  }
  Logger(const std::wstring &name)
  {
  }
};

#endif // HAVE_LOG4CXX

#endif // LOGGER_H
