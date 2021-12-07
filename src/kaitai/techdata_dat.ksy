meta:
  id: techdata_dat
  endian: le
  bit-endian: le
  
# There're some different weapons.dat versions out there available.
# 'num_lines' == number of highest energy in orders.dat
#
params:
  - id: has_broodwar_flag
    type: b1
  - id: num_lines
    type: u1

seq:
  - id: mineral_cost
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Minerals cost for the research of the technology.
      
  - id: vespene_cost
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Vespene gas cost for the research of the technology.
      
  - id: research_time
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Research time of the technology in 1/24ths of a second (at Fastest speed). Value of 0 will crash the game.
      
  - id: energy_required
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Energy cost for using the technology.

  - id: unknown4
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      unknown
      
  - id: icon
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Icon displayed for the technology. [pointer to a frame in unit\cmdbtns\cmdicons.grp]
      
  - id: label
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The name of the technology. Displayed in StarEdit and when you highlight the tech's icon during research. [pointer to stat_txt.tbl]
      
  - id: race
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Determines which race can use/research the technology. "All" will disable the tech in StarEdit (but not in-game).
      
  - id: unused
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      unused
      
  - id: broodwar_flag
    type: u1
    repeat: expr
    repeat-expr: num_lines
    if: has_broodwar_flag == true
    doc: |
      Makes the technology available only while playing the BroodWar expansion set.

# set those intances to debug the values while development
# in this case the parameters at top of this file have to be commented out
#instances:
#  has_broodwar_flag:
#    value: true
#  num_lines:
#    value: 44