meta:
  id: sfxdata_dat
  endian: le
  bit-endian: le
  
# There're some different sfxdata.dat versions out there available.
# 'num_lines' == number of highest *_sounds_* in units.dat
params:
  - id: num_lines
    type: u2

seq:
  - id: sound_file
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The actual wave file associated with the sfxdata entry. [pointer to sfxdata.tbl]
    
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
    
# set those intances to debug the values while development
# in this case the parameters at top of this file have to be commented out
#instances:
#  num_lines:
#    value: 967