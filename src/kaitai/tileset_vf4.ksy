meta:
  id: tileset_vf4
  endian: le
  bit-endian: le
  
seq:
  - id: id
    type: minitile_flags
    repeat: eos

    
types:
  minitile_flags:
    seq:
      - id: flags
        type: u2
        repeat: expr
        repeat-expr: 16