meta:
  id: sprites_dat
  endian: le
  bit-endian: le

seq:
  - id: image
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The images.dat entry corresponding to the sprites.dat entry [pointer to images.dat]

  - id: health_bar
    type: u1
    repeat: expr
    repeat-expr: num_lines-130
    doc: |
      The length of the Hit Points/Shields/Energy bar below the sprite, in pixels. The way the actual number of "boxes" is calculated is the following: substract 1 from the value, divide the result by 3 and round it down. Even though a sprite may actually USE less than 6 boxes, 6 boxes is the minimal amount that will be SHOWN in-game (just that some will not be functional). Values below 6 will all result in 1 box being USED.
      This property is only available from unit index 130 to num_lines

  - id: unknown2
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      tbd

  - id: is_visible
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Sprite will start as visible. Unchecked, used to hide the "White Circle", the Zerg Beacon used by Subterranean Spines, and few other things.

  - id: select_circle_image_size
    type: u1
    repeat: expr
    repeat-expr: num_lines-130
    doc: |
      The size of the in-game selection circle. The different sizes are actually different images.dat entries, so in order to use custom ones you need to replace them. The "Dashed" selection circles are used to mark allied units in multiplayer games, but if used on the players own units they will not disappear after deselecting the unit, and also they will NOT be removed on its death, still providing limited vision to the player.[pointer to images.dat, starting at ID#561 as 0]
      This property is only available from unit index 130 to num_lines

  - id: select_circle_vertical_pos
    type: u1
    repeat: expr
    repeat-expr: num_lines-130
    doc: |
      The vertical position of the in-game selection circle and the Health/Shield/Energy bar. The higher the number, the more downwards from the main sprite will they be positioned. Around 127 the display "loops back" and appears actually ABOVE the main sprite. 255 will put it back in its original position.
      This property is only available from unit index 130 to num_lines

instances:
  num_lines:
    value: 'file_size_rest / record_size + 130'
    doc: |
      A division of the dynamic rest file size though the record size gives the number of records in the file to parse.
      The static first 130 are then added to this number.

  record_size:
    value: 7
    doc: |
      The size of one data record. This is all type sizes in the format summarized (starting from record 130).

  record_size_first_130:
    value: 4
    doc: |
      The size of one data record. This is all type sizes in the format summarized (the first 130 records).

  file_size_first_130:
    value: 'record_size_first_130 * 130'
    doc: |
      File size for the first 130 records that is always static size.

  file_size_rest:
    value: 'file_size - file_size_first_130'
    doc:   |
      File size for the records after 130. This number might change from file to file.

  file_size:
    value: '_io.size'
