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
#include <iterator>

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



std::vector<iscript_bin_t::opcode_type_t*> IScript::getAnimationScript(IScript::AnimationType animationType)
{
  return getAnimationScript(static_cast<unsigned int>(animationType));
}

std::vector<iscript_bin_t::opcode_type_t*> IScript::getAnimationScript(unsigned int animationType)
{
  LOG4CXX_TRACE(logger,  to_string(mId) + ":" + to_string(animationType) + "=>" + LOG_CUR_FUNC + "()");

  iscript_bin_t::scpe_type_t* scpe = mDatahub.iscript->scpe()->at(mId);

  std::vector<iscript_bin_t::scpe_content_type_t*>* scpe_content_vec = scpe->scpe_content();

  // calculate the offset hash list per iscript (TODO: maybe cache this?)
  unordered_set<uint16_t> scpe_offset_table;
  for(auto scpe_content : *scpe_content_vec)
  {
    scpe_offset_table.insert(scpe_content->scpe_opcode_offset());
  }

  iscript_bin_t::scpe_content_type_t* scpe_content = scpe_content_vec->at(animationType);
  opcode_list_type_t* opcode_list_type = scpe_content->scpe_opcode_list();

  // if kaitai animation script object is null give a empty vector back (TODO: maybe change design)
  if(!opcode_list_type)
  {
    return std::vector<iscript_bin_t::opcode_type_t*>();
  }
  // else... parse the object....

  std::vector<kaitai::kstruct*>* opcode_vec_ks = opcode_list_type->read_list(scpe_offset_table);

  std::vector<iscript_bin_t::opcode_type_t*> opcode_vec(opcode_vec_ks->size());

  std::transform(opcode_vec_ks->begin(), opcode_vec_ks->end(), opcode_vec.begin(),
                 [](auto ptr) {return static_cast<iscript_bin_t::opcode_type_t*>(ptr); });

  return opcode_vec;
}

int8_t IScript::getAnimationCount()
{
  LOG4CXX_TRACE(logger,  to_string(mId) + "=>" + LOG_CUR_FUNC + "()");

  return mDatahub.iscript->scpe()->at(mId)->num_scpe_content();
}

bool IScript::is_format_bw()
{
  return !mDatahub.iscript->version_tag();
}

} /* namespace dat */
