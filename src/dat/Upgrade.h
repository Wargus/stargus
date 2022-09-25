/*
 * Upgrade.h
 *
 *      Author: Andreas Volz
 */

#ifndef UPGRADE_H
#define UPGRADE_H

#include "ObjectAccess.h"

namespace dat
{

class Upgrade : public ObjectAccess
{
public:
  Upgrade(DataHub &datahub, unsigned int id);
  virtual ~Upgrade();

  uint16_t mineral_cost_base();

  uint16_t mineral_cost_factor();

  uint16_t vespene_cost_base();

  uint16_t vespene_cost_factor();

  uint16_t research_time_base();

  uint16_t research_time_factor();

  uint16_t unknown6();

  uint16_t icon();

  uint16_t label();
  TblEntry label_tbl();

  uint8_t race();

  uint8_t max_repeats();

  bool broodwar_flags();

  bool has_broodwar_flag();

  static const int label_none = 0;
};

} /* namespace dat */

#endif /* UPGRADE_H */
