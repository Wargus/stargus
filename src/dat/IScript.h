/*
 * IScript.h
 *
 *      Author: Andreas Volz
 */

#ifndef ISCRIPT_H
#define ISCRIPT_H

// project
#include "ObjectAccess.h"

namespace dat
{

class IScript: public ObjectAccess
{
public:
  IScript(DataHub &datahub, unsigned int id);
  virtual ~IScript();

  void printAnimScript(int num);

  /**
   * @return true in case the iscript format is broodwar. (Nothing to do as the parser detects and handles the format itself)
   */
  bool is_format_bw();

private:

};

} /* namespace dat */

#endif /* ISCRIPT_H */
