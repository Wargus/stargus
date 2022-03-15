meta:
  id: file_tbl
  endian: le
  encoding: ASCII
  
seq:
  - id: num_offsets
    type: u2
  # Just read offsets normally
  - id: ofs_files
    type: u2
    repeat: expr
    repeat-expr: num_offsets
instances:
  tbl_entries:
    type: tbl_entry(_index)
    repeat: expr
    repeat-expr: num_offsets
types:
  tbl_entry:
    params:
      - id: i
        type: u2
    instances:
      len:
        value: '_parent.ofs_files[i + 1] - _parent.ofs_files[i]'
      dyn_end:
        value: 'i + 1 < _parent.num_offsets ? len : _io.size - _parent.ofs_files[i]'
      entry:
        pos: _parent.ofs_files[i]
        type: u1
        repeat: expr
        repeat-expr: dyn_end