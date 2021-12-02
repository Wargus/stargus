meta:
  id: images_dat
  endian: le
  bit-endian: le
  
# There're some different images.dat.dat versions out there available.
# 'num_lines' == number of highest sprite.dat image_file value
#
params:
  - id: num_lines
    type: u2
    
seq:
  - id: grp_file
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
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The drawing function used for the image. This property has rather various effects and not all options works with all entries so expect crashes. It can produce very interesting effects though, especially spell-related.
      
  - id: remapping
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      An additional remapping "palette" that is to be used. Each tileset has its own files responsible for remapping. Used only if the Draw property is set to "9-Use Remapping". Values 8 and 9 produce a weird effect and most probably are a result of an error in Starcraft.
    
  - id: iscript_id
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
    
# set those intances to debug the values while development
# in this case the parameters at top of this file have to be commented out
#instances:
#  num_lines:
#    value: 755


