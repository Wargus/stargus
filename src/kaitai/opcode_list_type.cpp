/*
 * opcode_list_type.cpp
 *
 *      Author: Andreas Volz
 */

#include "opcode_list_type.h"
#include "iscript_bin.h"

#include <iostream>

using namespace std;

opcode_list_type_t::opcode_list_type_t(kaitai::kstruct* p__parent, iscript_bin_t* p__root, kaitai::kstream* p__io) :
  kaitai::kstruct(p__io),
  m__root(p__root),
  m__parent(p__parent),
  m_pos(m__io->pos()),
  m_opcode_list(nullptr)
{

}

opcode_list_type_t::~opcode_list_type_t()
{
  _clean_up();
}

std::vector<kaitai::kstruct*>* opcode_list_type_t::read_list(std::unordered_set<uint16_t> scpe_offset_table)
{
  cout << "+read_list" << endl;
  cout << "m_opcode_list: " << m_opcode_list << endl;
  if (m_opcode_list)
  {
    return m_opcode_list;
  }
  else
  {
    m_opcode_list = new std::vector<kaitai::kstruct*>();
    cout << "new vector in opcode_list_type_t: " << m_opcode_list << endl;
  }

  m_scpe_offset_table = scpe_offset_table;

  std::streampos _pos = m__io->pos();
  m__io->seek(m_pos);
  try
  {
    _read();
  }
  catch(...)
  {
    _clean_up();
    throw;
  }
  m__io->seek(_pos);

  return m_opcode_list;
}

void opcode_list_type_t::_read()
{
  int scpe_opcode_offset = 0;
  do
  {
    iscript_bin_t::opcode_type_t *opcode = new iscript_bin_t::opcode_type_t(m__io, m__parent, m__root);
    m_opcode_list->push_back(opcode);

    // set next offset position
    scpe_opcode_offset = m__io->pos();
  }
  while((m_scpe_offset_table.find(scpe_opcode_offset) == m_scpe_offset_table.end()));
}

void opcode_list_type_t::_clean_up()
{
  cout << "delete vector in opcode_list_type_t: " << m_opcode_list << endl;
  delete m_opcode_list;
}
