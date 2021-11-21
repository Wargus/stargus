meta:
  id: file_tbl
  endian: le
  encoding: ASCII
  
seq:
  - id: num_offsets
    type: s2
  # Just read offsets normally
  - id: ofs_files
    type: s2
    repeat: expr
    repeat-expr: num_offsets
instances:
  tbl_entries:
    type: tbl_entry(_index)
    repeat: expr
    repeat-expr: num_offsets - 1
types:
  tbl_entry:
    params:
      - id: i
        type: s2
    instances:
      entry:
        pos: _parent.ofs_files[i]
        size: _parent.ofs_files[i + 1] - _parent.ofs_files[i]
        type: str