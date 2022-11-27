meta:
  id: iscript_bin
  endian: le
  ks-opaque-types: true
  
seq:
  - id: first_word
    type: u2
  
instances:
  version_tag:
    pos: 0x2
    type: u4
    doc: |
      value is 0x0 in case of broodwar and any other value for plain old starcraft
    
  entree_table_pos:
    value: 'version_tag == 0x0 ? first_word : 0x0'

  entree_offsets:
    type: entree_offset_type
    pos: entree_table_pos
    repeat: until
    repeat-until: '(_.iscript_id == 0xFFFF) ? ( _.offset == 0x0) : false'
    doc: |
      read entree offsets until the magic stop sign '0xFFFF 0x0000' is found
      
  scpe:
    type: scpe_type(_index)
    repeat: expr
    repeat-expr: _root.entree_offsets.size
    doc: |
      tbd

types:
  entree_offset_type:
    seq:
      - id: iscript_id
        type: u2
      - id: offset
        type: u2

  scpe_type:
    params:
      - id: i
        type: u2
    instances:
      scpe_header:
        pos: _parent.entree_offsets[i].offset
        type: scpe_header_type
      num_scpe_content:
        value:  |
          (scpe_header.scpe_content_type == 0) ? 2 : 
          (scpe_header.scpe_content_type == 1) ? 2 :
          (scpe_header.scpe_content_type == 2) ? 4 : 
          (scpe_header.scpe_content_type == 12) ? 14 : 
          (scpe_header.scpe_content_type == 13) ? 14 : 
          (scpe_header.scpe_content_type == 14) ? 15 : 
          (scpe_header.scpe_content_type == 15) ? 15 : 
          (scpe_header.scpe_content_type == 20) ? 21 : 
          (scpe_header.scpe_content_type == 21) ? 21 : 
          (scpe_header.scpe_content_type == 23) ? 23 : 
          (scpe_header.scpe_content_type == 24) ? 25 : 
          (scpe_header.scpe_content_type == 26) ? 27 : 
          (scpe_header.scpe_content_type == 27) ? 27 : 
          (scpe_header.scpe_content_type == 28) ? 27 : 
          (scpe_header.scpe_content_type == 29) ? 27 : 
          0
      scpe_content:
        pos: _parent.entree_offsets[i].offset + 8
        type: scpe_content_type
        repeat: expr
        repeat-expr: num_scpe_content
        
  scpe_header_type:
    seq:
      - id: scpe_magic
        type: u4
      - id: scpe_content_type
        type: u1
      - id: padding
        size: 3
        
  scpe_content_type:
    seq:
      - id: scpe_opcode_offset
        type: u2
    instances:
      scpe_opcode_list:
        pos: scpe_opcode_offset
        if: scpe_opcode_offset != 0
        #type: opcode_list_type(_parent, _root) # custom ks-opaque-types for C++ generation
        type: opcode_type # for kaitai IDE development parse only one element

  opcode_type:
    seq:
      - id: code
        type: u1
        enum: opcode
      - id: args
        type:
          switch-on: code
          cases:
            'opcode::playfram'         : u2_type
            'opcode::playframtile'     : u2_type
            'opcode::sethorpos'        : u1_type
            'opcode::setvertpos'       : u1_type
            'opcode::setpos'           : pos_type
            'opcode::wait'             : u1_type
            'opcode::waitrand'         : waitrand_type
            'opcode::goto'             : u2_type #INSTR_JMP
            'opcode::imgol'            : imgl_type
            'opcode::imgul'            : imgl_type
            'opcode::imgolorig'        : u2_type
            'opcode::switchul'         : u2_type
            'opcode::unknown_0c'       : empty_type
            'opcode::imgoluselo'       : imgl_type
            'opcode::imguluselo'       : imgl_type
            'opcode::sprol'            : sprl_type
            'opcode::highsprol'        : sprl_type
            'opcode::lowsprul'         : sprl_type
            'opcode::uflunstable'      : u2_type
            'opcode::spruluselo'       : sprl_type
            'opcode::sprul'            : sprl_type
            'opcode::sproluselo'       : sprov_type
            'opcode::end'              : empty_type #INSTR_TERM
            'opcode::setflipstate'     : u1_type
            'opcode::playsnd'          : u2_type
            'opcode::playsndrand'      : playsounds_type
            'opcode::playsndbtwn'      : playsndbtwn_type
            'opcode::domissiledmg'     : empty_type
            'opcode::attackmelee'      : playsounds_type
            'opcode::followmaingraphic': empty_type
            'opcode::randcondjmp'      : randcondjmp_type #INSTR_COND_JMP
            'opcode::turnccwise'       : u1_type
            'opcode::turncwise'        : u1_type
            'opcode::turn1cwise'       : empty_type
            'opcode::turnrand'         : u1_type
            'opcode::setspawnframe'    : u1_type
            'opcode::sigorder'         : u1_type
            'opcode::attackwith'       : u1_type
            'opcode::attack'           : empty_type
            'opcode::castspell'        : empty_type
            'opcode::useweapon'        : u1_type
            'opcode::move'             : u1_type
            'opcode::gotorepeatattk'   : empty_type
            'opcode::engframe'         : u1_type
            'opcode::engset'           : u1_type
            'opcode::unknown_2d'       : empty_type
            'opcode::nobrkcodestart'   : empty_type
            'opcode::nobrkcodeend'     : empty_type
            'opcode::ignorerest'       : empty_type
            'opcode::attkshiftproj'    : u1_type
            'opcode::tmprmgraphicstart': empty_type
            'opcode::tmprmgraphicend'  : empty_type
            'opcode::setfldirect'      : u1_type
            'opcode::call'             : u2_type #INSTR_COND_JMP
            'opcode::return'           : empty_type #INSTR_TERM
            'opcode::setflspeed'       : u2_type
            'opcode::creategasoverlays': u1_type
            'opcode::pwrupcondjmp'     : u2_type #INSTR_COND_JMP
            'opcode::trgtrangecondjmp' : trgtrangecondjmp_type #INSTR_COND_JMP
            'opcode::trgtarccondjmp'   : trgcondjmp_type #INSTR_COND_JMP
            'opcode::curdirectcondjmp' : trgcondjmp_type #INSTR_COND_JMP
            'opcode::imgulnextid'      : pos_type
            'opcode::unknown_3e'       : empty_type
            'opcode::liftoffcondjmp'   : u2_type #INSTR_COND_JMP
            'opcode::warpoverlay'      : u2_type
            'opcode::orderdone'        : u1_type
            'opcode::grdsprol'         : sprl_type
            'opcode::unknown_43'       : empty_type
            'opcode::dogrddamage'      : empty_type
            _: empty_type
        
  empty_type:
    seq: []
        
  u1_type:
    seq:
      - id: value
        type: u1
       
  u2_type:
    seq:
      - id: value
        type: u2
        
  pos_type:
    seq:
      - id: x
        type: u1
      - id: y
        type: u1
        
  waitrand_type:
    seq:
      - id: ticks1
        type: u1
      - id: ticks2
        type: u1
        
  imgl_type:
    seq:
      - id: image
        type: u2
      - id: pos
        type: pos_type
        
  sprl_type:
    seq:
      - id: sprite
        type: u2
      - id: pos
        type: pos_type
      
  sprov_type:
    seq:
      - id: sprite
        type: u2
      - id: overlay
        type: u1
      
  playsndbtwn_type:
    seq:
      - id: firstsound
        type: u2
      - id: lastsound
        type: u2
        
  playsounds_type:
    seq:
      - id: number_sounds
        type: u1
      - id: sound
        type: u2
        repeat: expr
        repeat-expr: number_sounds
  
  randcondjmp_type:
    seq:
      - id: randchance
        type: u1
      - id: labelname
        type: u2

  trgtrangecondjmp_type:
    seq:
      - id: distance
        type: u2
      - id: labelname
        type: u2
  
  trgcondjmp_type:
    seq:
      - id: angle1
        type: u2
      - id: angle2
        type: u2
      - id: labelname
        type: u2
  
enums:
  opcode:
    0x00: playfram           # <frame#>: # displays a particular frame, adjusted for direction.
    0x01: playframtile       # <frame#>: # displays a particular frame dependent on tileset.
    0x02: sethorpos          # <x>: # sets the current horizontal offset of the current image overlay.
    0x03: setvertpos         # <y>: # sets the vertical position of an image overlay.
    0x04: setpos             # <x> <y>: # sets the current horizontal and vertical position of the current image overlay.
    0x05: wait               # <#ticks>: # pauses script execution for a specific number of ticks.
    0x06: waitrand           # <#ticks1> <#ticks2>: # pauses script execution for a random number of ticks given two possible wait times. 
    0x07: goto               # <labelname>: # unconditionally jumps to a specific code block.
    0x08: imgol              # <image#> <x> <y>: # displays an active image overlay at an animation level higher than the current image overlay at a specified offset position.
    0x09: imgul              # <image#> <x> <y>: # displays an active image overlay at an animation level lower than the current image overlay at a specified offset position.
    0x0a: imgolorig          # <image#>: # displays an active image overlay at an animation level higher than the current image overlay at the relative origin offset position.
    0x0b: switchul           # <image#>: # only for powerups. Hypothesised to replace the image overlay that was first created by the current image overlay.
    0x0c: unknown_0c         # no parameters: # unknown.
    0x0d: imgoluselo         # <image#> <x> <y>: # displays an active image overlay at an animation level higher than the current image overlay, using a LO* file to determine the offset position.
    0x0e: imguluselo         # <image#> <x> <y>: # displays an active image overlay at an animation level lower than the current image overlay, using a LO* file to determine the offset position.
    0x0f: sprol              # <sprite#> <x> <y>: # spawns a sprite one animation level above the current image overlay at a specific offset position.
    0x10: highsprol          # <sprite#> <x> <y>: # spawns a sprite at the highest animation level at a specific offset position.
    0x11: lowsprul           # <sprite#> <x> <y>: # spawns a sprite at the lowest animation level at a specific offset position.
    0x12: uflunstable        # <flingy#: # creates an flingy with restrictions; supposedly crashes in most cases.
    0x13: spruluselo         # <sprite#> <x> <y>: # spawns a sprite one animation level below the current image overlay at a specific offset position. The new sprite inherits the direction of the current sprite. Requires LO* file for unknown reason.
    0x14: sprul              # <sprite#> <x> <y>: # spawns a sprite one animation level below the current image overlay at a specific offset position. The new sprite inherits the direction of the current sprite.
    0x15: sproluselo         # <sprite#> <overlay#>: # spawns a sprite one animation level above the current image overlay, using a specified LO* file for the offset position information. The new sprite inherits the direction of the current sprite.
    0x16: end                # no parameters: # destroys the current active image overlay, also removing the current sprite if the image overlay is the last in one in the current sprite.
    0x17: setflipstate       # <flipstate>: # sets flip state of the current image overlay.
    0x18: playsnd            # <sound#>: # plays a sound.
    0x19: playsndrand        # <#sounds> <sound#> <...>: # plays a random sound from a list.
    0x1a: playsndbtwn        # <firstsound#> <lastsound#>: # plays a random sound between two inclusive sfxdata.dat entry IDs.
    0x1b: domissiledmg       # no parameters: # causes the damage of a weapon flingy to be applied according to its weapons.dat entry.
    0x1c: attackmelee        # <#sounds> <sound#> <...>: # applies damage to target without creating a flingy and plays a sound.
    0x1d: followmaingraphic  # no parameters: # causes the current image overlay to display the same frame as the parent image overlay.
    0x1e: randcondjmp        # <randchance#> <labelname>: # random jump, chance of performing jump depends on the parameter.
    0x1f: turnccwise         # <turnamount>: # turns the flingy counterclockwise by a particular amount.
    0x20: turncwise          # <turnamount>: # turns the flingy clockwise by a particular amount.
    0x21: turn1cwise         # no parameters: # turns the flingy clockwise by one direction unit.
    0x22: turnrand           # <turnamount>: # turns the flingy a specified amount in a random direction, with a heavy bias towards turning clockwise.
    0x23: setspawnframe      # <direction>: # in specific situations, performs a natural rotation to the given direction.
    0x24: sigorder           # <signal#>: # allows the current unit's order to proceed if it has paused for an animation to be completed.
    0x25: attackwith         # <ground = 1, air = 2>: # attack with either the ground or air weapon depending on a parameter.
    0x26: attack             # no parameters: # attack with either the ground or air weapon depending on target.
    0x27: castspell          # no parameters: # identifies when a spell should be cast in a spellcasting animation. The spell is determined by the unit's current order.
    0x28: useweapon          # <weapon#>: # makes the unit use a specific weapons.dat ID on its target.
    0x29: move               # <movedistance>: # sets the unit to move forward a certain number of pixels at the end of the current tick.
    0x2a: gotorepeatattk     # no parameters: # signals to StarCraft that after this point, when the unit's cooldown time is over, the repeat attack animation can be called.
    0x2b: engframe           # <frame#>: # plays a particular frame, often used in engine glow animations.
    0x2c: engset             # <frameset#>: # plays a particular frame set, often used in engine glow animations.
    0x2d: unknown_2d         # no parameters: # hypothesised to hide the current image overlay until the next animation.
    0x2e: nobrkcodestart     # no parameters: # holds the processing of player orders until a nobrkcodeend is encountered.
    0x2f: nobrkcodeend       # no parameters: # allows the processing of player orders after a nobrkcodestart instruction.
    0x30: ignorerest         # no parameters: # conceptually, this causes the script to stop until the next animation is called.
    0x31: attkshiftproj      # <distance>: # creates the weapon flingy at a particular distance in front of the unit.
    0x32: tmprmgraphicstart  # no parameters: # sets the current image overlay state to hidden.
    0x33: tmprmgraphicend    # no parameters: # sets the current image overlay state to visible.
    0x34: setfldirect        # <direction>: # sets the current direction of the flingy.
    0x35: call               # <labelname>: # calls a code block.
    0x36: return             # no parameters: # returns from call.
    0x37: setflspeed         # <speed>: # sets the flingy.dat speed of the current flingy.
    0x38: creategasoverlays  # <gasoverlay#>: # creates gas image overlays at offsets specified by LO* files.
    0x39: pwrupcondjmp       # <labelname>: # jumps to a code block if the current unit is a powerup and it is currently picked up.
    0x3a: trgtrangecondjmp   # <distance> <labelname>: # jumps to a block depending on the distance to the target.
    0x3b: trgtarccondjmp     # <angle1> <angle2> <labelname>: # jumps to a block depending on the current angle of the target.
    0x3c: curdirectcondjmp   # <angle1> <angle2> <labelname>: # only for units. Jump to a code block if the current sprite is facing a particular direction.
    0x3d: imgulnextid        # <x> <y>: # displays an active image overlay at the shadow animation level at a specified offset position. The image overlay that will be displayed is the one that is after the current image overlay in images.dat.
    0x3e: unknown_3e         # no parameters: # unknown.
    0x3f: liftoffcondjmp     # <labelname>: # jumps to a code block when the current unit that is a building that is lifted off.
    0x40: warpoverlay        # <frame#>: # hypothesised to display the current image overlay's frame clipped to the outline of the parent image overlay.
    0x41: orderdone          # <signal#>: # most likely used with orders that continually repeat, like the Medic's healing and the Valkyrie's afterburners (which no longer exist), to clear the sigorder flag to stop the order.
    0x42: grdsprol           # <sprite#> <x> <y>: # spawns a sprite one animation level above the current image overlay at a specific offset position, but only if the current sprite is over ground-passable terrain.
    0x43: unknown_43         # no parameters: # unknown.
    0x44: dogrddamage        # no parameters: # applies damage like domissiledmg when on ground-unit-passable terrain.
    
