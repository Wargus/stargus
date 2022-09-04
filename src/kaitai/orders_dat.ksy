meta:
  id: orders_dat
  endian: le
  bit-endian: le

seq:
  - id: label
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Probably the label of the order. Doesn't do anything - used only for convenience. [pointer to stat_txt.tbl]

  - id: use_weapon_targeting
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Order will use the weapons.dat targeting settings.

  - id: unknown2
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: unknown3
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: unknown4
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: unknown5
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: interruptible
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Order's execution can be interrupted by calling another order (e.g. movement or something). Does not work for the "Die" order.

  - id: unknown7
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: queueable
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: unknown9
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Order execution can be queued using the SHIFT+click combination, up to 16 times.

  - id: unknown10
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: unknown11
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: unknown12
    type: u1
    repeat: expr
    repeat-expr: num_lines

  - id: targeting
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Weapon used by the order to determine the targeting rules, if "Use Weapon Targeting" is checked. [pointer to weapons.dat]

  - id: energy
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Technology used to determine the energy cost of calling the order. [pointer to techdata.dat]

  - id: animation
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Unit Iscript animation to use while calling the order.

  - id: highlight
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Determines which icon on the button panel is highlightened when the order is being called. If the selected icon is not present, no icon is highlightened. 65535 = no highlight at all [pointer to cmdicons.grp]

  - id: unknown17
    type: u2
    repeat: expr
    repeat-expr: num_lines

  - id: obscured_order
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Order to be run if the target is obscured by the Fog-of-War. [pointer to orders.dat]

instances:
  num_lines:
    value: file_size / record_size
    doc: |
      A division of file size though the record size gives the number of records in the file to parse.

  record_size:
    value: 22
    doc: |
      The size of one data record. This is all type sizes in the format summarized.

  file_size:
    value: '_io.size'
