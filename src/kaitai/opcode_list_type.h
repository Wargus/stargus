/*
 * opcode_list_type.h
 *
 *      Author: Andreas Volz
 */

#ifndef OPCODE_LIST_TYPE_H
#define OPCODE_LIST_TYPE_H

#include "kaitaistruct.h"

// system
#include <unordered_set>
#include <vector>

  // forward declarations
class iscript_bin_t;

class  opcode_list_type_t : public kaitai::kstruct
{
public:
  opcode_list_type_t(kaitai::kstruct* p__parent, iscript_bin_t* p__root, kaitai::kstream* p__io);
  ~opcode_list_type_t();

  std::vector<kaitai::kstruct*>* read_list(std::unordered_set<uint16_t> scpe_offset_table);

private:
  void _read();
  void _clean_up();

  std::unordered_set<uint16_t> m_scpe_offset_table;
  iscript_bin_t* m__root;
  kaitai::kstruct* m__parent;
  std::streampos m_pos;

  bool f_opcode_list;
  std::vector<kaitai::kstruct*>* m_opcode_list;
};

#endif /* OPCODE_LIST_TYPE_H */
