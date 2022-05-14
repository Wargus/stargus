meta:
  id: tileset_vr4
  endian: le
  bit-endian: le
  
seq:
  - id: pixel_data
    type: pixel_type
    repeat: eos

    
types:
  pixel_type:
    seq:
      - id: color_palette
        size: 64