meta:
  id: images_dat
  endian: le
  bit-endian: le

seq:
  - id: grp
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Indicates the GRP graphics used by the current images.dat entry. If the value exceeds the number of lines in images.tbl, SC won't load. [pointer to images.tbl, -1 based]

  - id: gfx_turns
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Determines if the game engine dynamically adds up to 16 frames and/or mirror them during animations, depending on what direction the sprite is facing. Unchecked, makes the sprite follow its Iscript animation with exactly the frame numbers contained in it.

  - id: clickable
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Determines if the graphics can be selected using the mouse cursor. Also determines the presence (or lack of) the cursor selection graphics. DOES NOT make the unit not at all selectable - it is still possible using the selection box.

  - id: use_full_iscript
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Allows running for Iscript animations other than the Initial and Death animations. Unchecked, prevents the sprite movement, attack, spellcasting etc. If the Movement Control for the corresponding flingy.dat entry is set to "Flingy.dat Control", the sprite movement WILL take place, but without any animation.

  - id: draw_if_cloaked
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Makes the image appear/disappear when cloacked.

  - id: draw_function
    type: u1
    enum: draw_function_enum
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The drawing function used for the image. This property has rather various effects and not all options works with all entries so expect crashes. It can produce very interesting effects though, especially spell-related.
      0 - normal\n
      1 - doesn't draw hallucination\n
      2 - non-vision cloaking\n
      3 - non-vision cloaked\n
      4 - non-vision uncloaking\n
      5 - vision cloaking\n
      6 - vision cloaked\n
      7 - vision uncloaking\n
      8 - EMP shockwave\n
      9 - uses remapping\n
      10 - shadow\n
      11 - HP bar\n
      12 - warp texture\n
      13 - selection circle remapping\n
      14 - draw original player color (used for flags -- player color stored in coloring data)\n
      15 - draw update rect\n
      16 - hallucination\n
      17 - warp flash\n

  - id: remapping
    type: u1
    enum: remapping_enum
    repeat: expr
    repeat-expr: num_lines
    doc: |
      An additional remapping "palette" that is to be used. Each tileset has its own files responsible for remapping. Used only if the Draw property is set to "9-Use Remapping". Values 8 and 9 produce a weird effect and most probably are a result of an error in Starcraft.
      If 'draw_function' is 9:
      0 = No remapping\n
      1 = ofire.pcx (Orange)\n
      2 = gfire.pcx (Green)\n
      3 = bfire.pcx (Blue)\n
      4 = bexpl.pcx (Blue2)\n
      5 = Special (Own cloak)\n
      6 = (crash)\n
      7 = (crash)\n
      8 = Unk8 (?)\n
      9 = Unk9 (?)\n

  - id: iscript
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Indicates the animation ID in the Iscript.bin file used to manage the animation of the current entry's GRP graphics. [pointer to Iscript.bin]

  - id: shield_overlay
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Overlay used to place the Images.dat entry #424 ("Shield Overlay"), if the unit has shields and is hit. [pointer to images.tbl]

  - id: attack_overlay
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      This one usually controls a part of the attack animation. Except for the Bunker (which is hardcoded), the use of this property is not specific, but removing it will hang the game if unit's Iscript animation calls for the overlay with the opcodes: 0xD(imgoluselo), 0xE(imguluselo) or 0x15(sproluselo).[pointer to a LOG\LOL\LOX\LOA file in images.tbl]

  - id: damage_overlay
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The "Flames/Bleeding" overlay control, dependent on the current HP value. If the number of frames of the used GRP file is higher than the number of frames of the overlay, the game will crash.[pointer to a LOF file in images.tbl]

  - id: special_overlay
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      This one is used for various purposes: for "Resource Miners", it controls where they "hold" the resources;for the gas-containers, it controls the placement of the smoke graphics (iscript connection via the "creategasoverlays" (0x38) opcode); for the base-turret units, it controls the placement of the turret (also "imgoluselo" connection); for the Battlecruiser, it is the location of the Yamato Gun graphics.[pointer to a LOS\LOL\LOO\LOA\LOB file in images.tbl]

  - id: landing_dust_overlay
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Complementary to "Lift-off Dust", this one controls the placement of the landing dust. Some units (Dropship,Science Vessel) originally had this one too, but the idea was abandoned.Also used for the "2 in 1 Egg" zerg units, to determine the location where to put the 2 spawned units.[pointer to a LOB\LOU file in images.tbl]

  - id: lift_off_dust_overlay
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Complementary to "Landing Dust", this one controls the placement of the lifting-off dust. Some units (Dropship, Science Vessel) originally had this too, but the idea was abandoned. [pointer to a LOD file in images.tbl]

instances:
  num_lines:
    value: file_size / record_size
    doc: |
      A division of file size though the record size gives the number of records in the file to parse.

  record_size:
    value: 38
    doc: |
      The size of one data record. This is all type sizes in the format summarized.

  file_size:
    value: '_io.size'
    
enums:
  draw_function_enum:
    0: normal
    1: no_hallucination
    2: non_vision_cloaking
    3: non_vision_cloaked
    4: non_vision_uncloaking
    5: vision_cloaking
    6: vision_cloaked
    7: vision_uncloaking
    8: emp_shockwave
    9: remapping
    10: shadow
    11: hp_bar
    12: warp_texture
    13: sel_circle_remapping
    14: player_color
    15: update_rect
    16: hallucination
    17: warp_flash

  remapping_enum:
    0: no_remapping
    1: ofire
    2: gfire
    3: bfire
    4: bexpl
    5: special
    6: unknown1
    7: unknown2
    8: unknown3
    9: unknown4

