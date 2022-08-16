meta:
  id: upgrades_dat
  endian: le
  bit-endian: le

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

instances:
  has_broodwar_flag:
    value: 'file_size % record_size == 0 ? false : true'
    doc: |
      true in case the brodowar data is parsed

  num_lines:
    value: 'file_size % record_size == 0 ? record_count : record_count_broodwar'
    doc: |
      A division of file size though the record size gives the number of records in the file to parse.

  record_size:
    value: 20
    doc: |
      The size of one data record. This is all type sizes in the format summarized.

  record_count:
    value: 'file_size / record_size'
    doc: |
      Count of records in the data file. (Need to check with modulo operator if this is the case)

  record_size_broodwar:
    value: 21
    doc: |
      The size of one data record. This is all type sizes in the format summarized. [broodwar data]

  record_count_broodwar:
    value: 'file_size / record_size_broodwar'
    doc: |
      Count of records in the data file. (Need to check with modulo operator if this is the case) [broodwar data]

  file_size:
    value: '_io.size'
