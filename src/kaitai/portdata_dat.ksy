meta:
  id: portdata_dat
  endian: le
  bit-endian: le
  
# There're some different portdata.dat versions out there available.
# 'num_lines' == number of highest portraits + 2x4 flags in units.dat
#
params:
  - id: num_lines
    type: u1

seq:
  - id: portrait_file
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Base path to different portrait SMK (Smacker) animations. Consecutive animations takes increasing, 0-based indexes appended to this path. Putting 0 here will result in a frozen static image. [1-based pointer to portdata.tbl]
    
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

# set those intances to debug the values while development
# in this case the parameters at top of this file have to be commented out
#instances:
#  num_lines:
#    value: 90