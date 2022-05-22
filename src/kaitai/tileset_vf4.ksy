meta:
  id: tileset_vf4
  endian: le
  bit-endian: le
  
seq:
  - id: elements
    type: minitile
    repeat: eos

types:
  minitile:
    seq:
      - id: flags
        type: minitile_flags
        repeat: expr
        repeat-expr: 16
        
  minitile_flags:
    seq:
      - id: walkable
        type: b1  # 0b0000_0001 = 0x01
      - id: mid_elevation
        type: b1  # 0b0000_0010 = 0x02
      - id: high_elevation
        type: b1  # 0b0000_0100 = 0x04
      - id: blocks_view
        type: b1  # 0b0000_1000 = 0x08
      - id: ramp
        type: b1  # 0b0001_0000 = 0x10
      - type: b3  # 0b1110_0000