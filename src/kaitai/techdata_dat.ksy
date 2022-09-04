meta:
  id: techdata_dat
  endian: le
  bit-endian: le

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
    value: 18
    doc: |
      The size of one data record. This is all type sizes in the format summarized.

  record_count:
    value: 'file_size / record_size'
    doc: |
      Count of records in the data file. (Need to check with modulo operator if this is the case)

  record_size_broodwar:
    value: 19
    doc: |
      The size of one data record. This is all type sizes in the format summarized. [broodwar data]

  record_count_broodwar:
    value: 'file_size / record_size_broodwar'
    doc: |
      Count of records in the data file. (Need to check with modulo operator if this is the case) [broodwar data]

  file_size:
    value: '_io.size'
