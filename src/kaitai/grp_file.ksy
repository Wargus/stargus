meta:
  id: grp_file
  endian: le
  bit-endian: le
  
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
    type: image_frame_type(_index)
    repeat: expr
    repeat-expr: num_images
    doc: |
      test

types:
  image_frame_type:
    params:
      - id: frame_id
        type: u2
        
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
        
      - id: has_line
        type: bool
        doc: |
          boolean value if the current line is followed by another line in the same frame
        
    seq:
      - id: offset
        type: u2
        doc: |
          test
          
    instances:
      start:
        value: '_parent.line_offset + offset'
        doc: |
          start position of the current RLE line
          
      file_size:
        value: '_io.size'
        doc: |
          size of the complete file
          
      has_frame:
        value: '(_root.num_images-1 - _parent.frame_id) > 0'
        doc: |
          boolean value if the current frame is followed by another frame
        
      last_line_len:
        value: 'has_frame ? _root.image_frames[_parent.frame_id+1].line_offset - start : file_size - start'
        doc: |
          if a next frame is available then
            take the line_offset from the next frame AND substract start
          else (last frame)
            from last position in the file substract the start position
          => the result is the length of the last line of a frame
        
      len:
        value: 'has_line ? _parent.line_offsets[index + 1].offset - offset : last_line_len'
        doc: |
          check if there is another line following and depending in the result take next offset or complex calculation of last line
        
      rle_offsets:
        pos: start
        size: len # real impelentation reads the data into a string as this is faster
        
        # This is to debug the above code by reading the data into an array
        #type: u1
        #repeat: expr
        #repeat-expr: len
