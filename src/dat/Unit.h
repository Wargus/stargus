/*
 * Unit.h
 *
 *      Author: Andreas Volz
 */

#ifndef UNIT_H
#define UNIT_H

// project
#include "Flingy.h"
#include "ObjectAccess.h"
#include "Portrait.h"

namespace dat
{

class Unit : public ObjectAccess
{
public:
  Unit(DataHub &datahub, unsigned int id);
  virtual ~Unit();

  Flingy flingy();

  std::shared_ptr<TblEntry> name();

  uint32_t hitpoints();

  Portrait portrait();

  uint8_t elevation_level();

  units_dat_t::unit_dimension_type_t *unit_dimension();

  uint8_t sight_range();

  units_dat_t::special_ability_flags_type_t *special_ability_flags();

  uint16_t build_time();

  uint16_t vespene_cost();

  uint16_t mineral_cost();

  /* constants */

  static const int portrait_none = 65535;

private:

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
