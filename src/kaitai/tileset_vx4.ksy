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
      - id: vr4_ref_flip_raw
        type: u2
        doc: |
          This is the raw parsed value. Use vr4_ref and horizontal_flip.
        
    instances:
      vr4_ref:
        value: vr4_ref_flip_raw >> 1
        doc: |
          The index reference in the vx4 data file
        
      horizontal_flip:
        value: vr4_ref_flip_raw & 1
        doc: |
          Flag if the minitile is flipped horizontal