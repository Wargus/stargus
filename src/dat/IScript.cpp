/*
 * IScript.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "IScript.h"
#include "Logger.h"

using namespace std;

static Logger logger = Logger("startool.dat.IScript");

namespace dat
{

IScript::IScript(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, id)
{

}

IScript::~IScript()
{

}

} /* namespace dat */
