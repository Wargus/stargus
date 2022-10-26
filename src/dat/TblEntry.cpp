/*
 * TblEntry.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "TblEntry.h"
#include "Logger.h"

// system
#include <string>

using namespace std;

static Logger logger = Logger("startool.dat.TblEntry");

namespace dat
{

TblEntry::TblEntry()
{
  m_shortcut_pos = -1;
  m_shortcut = ' ';
}

TblEntry::~TblEntry()
{

}

std::string TblEntry::name1()
{
  LOG4CXX_TRACE(logger, LOG_CUR_FUNC + "()=" + m_name1);
  return m_name1;
}

std::string TblEntry::name2()
{
  LOG4CXX_TRACE(logger, LOG_CUR_FUNC + "()=" + m_name2);
  return m_name2;
}

std::string TblEntry::name3()
{
  LOG4CXX_TRACE(logger, LOG_CUR_FUNC + "()=" + m_name3);
  return m_name3;
}

int TblEntry::shortcut_pos()
{
  LOG4CXX_TRACE(logger, LOG_CUR_FUNC + "()=" + to_string(m_shortcut_pos));
  return m_shortcut_pos;
}

std::string TblEntry::shortcut()
{
  LOG4CXX_TRACE(logger, LOG_CUR_FUNC + "()=" + m_shortcut);
  return m_shortcut;
}

} /* namespace dat */
