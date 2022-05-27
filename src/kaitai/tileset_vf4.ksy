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
        type: minitile_flags_types
        repeat: expr
        repeat-expr: 16
        
  minitile_flags_types:
    seq:
      - id: flags_raw
        type: u2
        
    instances:
      walkable:
        value: flags_raw & 0x01
        
      mid_elevation:
        value: flags_raw & 0x02
        
      high_elevation:
        value: flags_raw & 0x04
        
      blocks_view:
        value: flags_raw & 0x08
        
      ramp:
        value: flags_raw & 0x10
        