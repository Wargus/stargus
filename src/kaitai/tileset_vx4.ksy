meta:
  id: tileset_vx4
  endian: le
  bit-endian: le
  
seq:
  - id: elements
    type: megatile_type
    repeat: eos

types:
  megatile_type:
    seq:
      - id: graphic_ref
        type: graphic_ref_type
        repeat: expr
        repeat-expr: 16
        
  graphic_ref_type:
    seq:
      - id: vr4_ref_raw
        type: b15
      - id: horizontal_flip
        type: b1
        
    instances:
      vr4_ref:
        value: vr4_ref_raw >> 1
    