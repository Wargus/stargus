meta:
  id: tileset_cv5
  endian: le
  bit-endian: le
  
seq:
  - id: element
    type: group
    repeat: eos

types:
  group:
    seq:
      - id: doodad
        type: u2

      - id: ground
        type: ground_nibbles
        
      - id: unknown1
        type: u2
        
      - id: unknown2
        type: u2
        
      - id: unknown3
        type: u2
        
      - id: unknown4
        type: u2
        
      - id: unknown5
        type: u2
        
      - id: unknown6
        type: u2
        
      - id: unknown7
        type: u2
        
      - id: unknown8
        type: u2
        
      - id: megatile_references
        type: u2
        repeat: expr
        repeat-expr: 16
        
  ground_nibbles:
    seq:
      - id: one
        type: b4
        
      - id: two
        type: b4
        
      - id: tree
        type: b4
        
      - id: four
        type: b4