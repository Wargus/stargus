meta:
  id: tileset_dddata_bin
  endian: le
  bit-endian: le
  
seq:
  - id: doodad
    type: doodad_type
    repeat: eos

types:
  doodad_type:
    seq:
      - id: placing
        type: u2
        repeat: expr
        repeat-expr: 512