meta:
  id: grp_file
  endian: le
  bit-endian: le
  encoding: ASCII
  
seq:
  - id: num_images
    type: u2
    doc: |
      test
      
  - id: max_width
    type: u2
    doc: |
      test
      
  - id: max_height
    type: u2
    doc: |
      test

  - id: image_frames
    type: image_frame_type
    repeat: expr
    repeat-expr: num_images
    doc: |
      test

types:
  image_frame_type:
    seq:
      - id: x_offset
        type: u1
        doc: |
          test
          
      - id: y_offset
        type: u1
        doc: |
          test
          
      - id: width
        type: u1
        doc: |
          test
          
      - id: height
        type: u1
        doc: |
          test
          
      - id: line_offset
        type: u4
        doc: |
         test
         
    instances:
      line_offsets:
        pos: line_offset
        type: line_offset_type(_index, _index != height - 1)
        repeat: expr
        repeat-expr: height

  line_offset_type:
    params:
      - id: index
        type: u2
        
      - id: has_next
        type: bool
    seq:
      - id: offset

        type: u2
        doc: |
          test
          
    instances:
      rle_offsets:
        pos: _parent.line_offset + offset
        size: 'has_next ? (_parent.line_offsets[index + 1].offset - offset) : _io.size - _io.pos'
