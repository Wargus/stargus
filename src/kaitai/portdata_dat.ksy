meta:
  id: portdata_dat
  endian: le
  bit-endian: le

seq:
  - id: video
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Smacker portrait video for idle and talking animation. Add 110 to get the talking animation. [1-based pointer to portdata.tbl]

  - id: smk_change
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Controls how often the first SMK animation, with the index of 0, will be overlooked and a portrait with different index will be played. The higher the value and the more it gets near 100, the more often will the first SMK be skipped. Values over 100 make the game use only the first portrait.

  - id: unknown1
    type: u1
    repeat: expr
    repeat-expr: num_lines

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
