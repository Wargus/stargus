meta:
  id: tileset_vx4
  endian: le
  bit-endian: le
  
seq:
  - id: id
    type: tile
    repeat: eos

types:
  tile:
    seq:
      - id: flags
        type: u2
        repeat: expr
        repeat-expr: 16