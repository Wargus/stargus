meta:
  id: portdata_dat
  endian: le
  bit-endian: le

seq:
  - id: video_idle
    type: u4
    repeat: expr
    repeat-expr: num_lines / 2
    doc: |
      Smacker portrait video for idle animations. [1-based pointer to portdata.tbl]

  - id: video_talking
    type: u4
    repeat: expr
    repeat-expr: num_lines / 2
    doc: |
      Smacker portrait video for talking animations. [1-based pointer to portdata.tbl]


  - id: change_idle
    type: u1
    repeat: expr
    repeat-expr: num_lines / 2
    doc: |
      Controls how often the first idle animation, with the index of 0, will be overlooked and a portrait with different index will be played. The higher the value and the more it gets near 100, the more often will the first animation be skipped. Values over 100 make the game use only the first portrait.

  - id: change_talking
    type: u1
    repeat: expr
    repeat-expr: num_lines / 2
    doc: |
      Controls how often the first talking animation, with the index of 0, will be overlooked and a portrait with different index will be played. The higher the value and the more it gets near 100, the more often will the first animation be skipped. Values over 100 make the game use only the first portrait.


  - id: unknown1_idle
    type: u1
    repeat: expr
    repeat-expr: num_lines / 2

  - id: unknown1_talking
    type: u1
    repeat: expr
    repeat-expr: num_lines / 2


instances:
  num_lines:
    value: file_size / record_size
    doc: |
      A division of file size though the record size gives the number of records in the file to parse.

  record_size:
    value: 6
    doc: |
      The size of one data record. This is all type sizes in the format summarized.

  file_size:
    value: '_io.size'
