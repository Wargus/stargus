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
#include "Sfx.h"

namespace dat
{

class Unit : public ObjectAccess
{
public:
  Unit(DataHub &datahub, unsigned int id);
  virtual ~Unit();

  Flingy flingy();

  TblEntry name();

  uint32_t hitpoints();

  Portrait portrait();

  uint8_t elevation_level();

  units_dat_t::unit_dimension_type_t *unit_dimension();

  uint8_t sight_range();

  units_dat_t::special_ability_flags_type_t *special_ability_flags();

  uint16_t build_time();

  uint16_t vespene_cost();

  uint16_t mineral_cost();

  Sfx ready_sound();

  /* constants */

  static const int portrait_none = 65535;
  static const int sound_none = 0;

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

class NoSfxException : public std::exception
{
public:
  NoSfxException(uint16_t sfx_id) {m_sfx_id = sfx_id;}

  virtual ~NoSfxException() throw() {}

  const char *what() const throw();

private:
  uint16_t m_sfx_id;
};


} /* namespace dat */

#endif /* UNIT_H */
