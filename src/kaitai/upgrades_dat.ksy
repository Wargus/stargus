meta:
  id: upgrades_dat
  endian: le
  bit-endian: le
  
# There're some different weapons.dat versions out there available.
# 'num_lines' == number of highest armor_upgrade in units.dat and damage_upgrade in weapons.dat
#
params:
  - id: has_broodwar_flag
    type: b1
  - id: num_lines
    type: u1

seq:
  - id: mineral_cost_base
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Basic minerals cost for the upgrade.
    
  - id: mineral_cost_factor
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Additional cost in minerals, per level of the upgrade.
    
  - id: vespene_cost_base
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Basic Vespene gas cost for the upgrade.
    
  - id: vespene_cost_factor
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Additional cost in Vespene gas, per level of the upgrade.
    
  - id: research_time_base
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Basic research time for the upgrade, in 1/24ths of a second (at Fastest speed). A value of 0 will crash the original game.
    
  - id: research_time_factor
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Additional time the research takes, per level of the upgrade, in 1/24ths of a second (at Fastest speed).
    
  - id: unknown6
    type: u2
    repeat: expr
    repeat-expr: num_lines
    
  - id: icon
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Icon displayed for the upgrade. [pointer to a frame in unit\cmdbtns\cmdicons.grp]
    
  - id: label
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The name of the upgrade. Displayed in StarEdit and when you highlight the upgrade's icon during research. [pointer to stat_txt.tbl]
    
  - id: race
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Determines which race can use/research the upgrade. "All" will disable the tech in StarEdit (but not in-game).
      
  - id: max_repeats
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Total number of times the upgrade can be researched.
    
  - id: broodwar_flags
    type: u1
    repeat: expr
    repeat-expr: num_lines
    if: has_broodwar_flag == true
    doc: |
      Makes the upgrade available only while playing the BroodWar expansion set.

# set those intances to debug the values while development
# in this case the parameters at top of this file have to be commented out
#instances:
#  has_broodwar_flag:
#    value: false
#  num_lines:
#    value: 46