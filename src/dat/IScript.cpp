/*
 * IScript.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "IScript.h"
#include "Logger.h"

// system
#include <iostream>

using namespace std;

static Logger logger = Logger("startool.dat.IScript");

namespace dat
{

IScript::IScript(DataHub &datahub, unsigned int id) :
  ObjectAccess(datahub, datahub.getIScriptImage(id))
{
}

IScript::~IScript()
{
}

void IScript::printAnimScript(int num)
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  iscript_bin_t::scpe_type_t* scpe = mDatahub.iscript->scpe()->at(mId);

  std::vector<iscript_bin_t::scpe_content_type_t*>* scpe_content_vec = scpe->scpe_content();

  // calculate the offset hash list per iscript (maybe cache this?)
  unordered_set<uint16_t> scpe_offset_table;
  for(auto scpe_content : *scpe_content_vec)
  {
    scpe_offset_table.insert(scpe_content->scpe_opcode_offset());
  }

  iscript_bin_t::scpe_content_type_t* scpe_content = scpe_content_vec->at(num);
  opcode_list_type_t* opcode_list_type = scpe_content->scpe_opcode_list();

  std::vector<kaitai::kstruct*>* opcode_list = opcode_list_type->read_list(scpe_offset_table);

  for(auto opcode_ks : *opcode_list)
  {
    iscript_bin_t::opcode_type_t *opcode = static_cast<iscript_bin_t::opcode_type_t*>(opcode_ks);

    cout << "code: " << hex << opcode->code() << endl;
  }
}

bool IScript::is_format_bw()
{
  return !mDatahub.iscript->version_tag();
}

} /* namespace dat */
