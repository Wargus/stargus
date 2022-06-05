/*
 * Unit.h
 *
 *      Author: Andreas Volz
 */

#ifndef UNIT_H
#define UNIT_H

// project
#include "Flingy.h"
#include "DataHub.h"
#include "Portrait.h"

namespace dat
{

class Unit
{
public:
  Unit(DataHub &datahub, uint8_t id);
  virtual ~Unit();

  Flingy flingy();

  TblEntry name();

  uint32_t hitpoints();

  Portrait portrait();

  static const int portrait_none = 65535;

private:
  DataHub &mDatahub;
  uint8_t mId;
};

class NoPortraitException : public std::exception
{
public:
  NoPortraitException(uint16_t portraid_id) {m_portraid_id = portraid_id;}

  virtual ~NoPortraitException() throw() {}

  const char *what() const throw();

private:
  uint16_t m_portraid_id;
};


} /* namespace dat */

#endif /* UNIT_H */
