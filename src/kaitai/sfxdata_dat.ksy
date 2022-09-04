meta:
  id: sfxdata_dat
  endian: le
  bit-endian: le

seq:
  - id: sound_file
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The actual wave file associated with the sfxdata entry. [pointer to sfxdata.tbl]

#Unknown 1: priority
#Unknown 2: Various flags:
#- 1 preload
#- 2 unitSpeech
#- 16 oneAtTime
#- 32 neverPreempt
#Unknown 3: lengthAdjust
#Unknown 4: minVolume

  - id: unknown1
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: unknown2
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: unknown3
    type: u2
    repeat: expr
    repeat-expr: num_lines

  - id: unknown4
    type: u1
    repeat: expr
    repeat-expr: num_lines

instances:
  num_lines:
    value: file_size / record_size
    doc: |
      A division of file size though the record size gives the number of records in the file to parse.

  record_size:
    value: 9
    doc: |
      The size of one data record. This is all type sizes in the format summarized.

  file_size:
    value: '_io.size'