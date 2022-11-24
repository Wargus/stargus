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

private:

};

} /* namespace dat */

#endif /* ISCRIPT_H */
