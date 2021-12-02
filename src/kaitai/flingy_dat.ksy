meta:
  id: flingy_dat
  endian: le
  bit-endian: le
  
# There're some different flingy.dat versions out there available.
# 'num_lines' == number of max weapons+1 in units.dat
#
params:
  - id: num_lines
    type: u1
    
seq:
  - id: sprite
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The sprites.dat entry corresponding to the flingy.dat entry. [pointer to sprites.dat]
    
  - id: speed
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Maximum speed at which the sprite will move. Measured in pixels-per-frame, but written as "Speed*(320/3)" (rounded up, it's weird, but that's how it works). Works ONLY if "Move Control" is set to "Flingy.dat Control".
    
  - id: acceleration
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      How fast the sprite speeds up or slows down. Added to or subtracted from current speed until it reaches the Top Speed or 0. Measured in pixels-per-frame.  Works ONLY if "Move Control" is set to "Flingy.dat Control".
    
  - id: halt_distance
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Distance from its destination at which the sprite will begin to deccelerate from its Top Speed to a complete halt. Measured in pixels*256.
    
  - id: turn_radius
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The distance the sprite requires to "wipe around" to turn to another direction. Works ONLY if "Move Control" is set to "Flingy.dat Control".
    
  - id: unused
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Unused.
    
  - id: movement_control
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Indicates the mechanism that is used to control the movement of the flingy.dat entry. "Flingy.dat Control" makes use of the Acceleration, Speed, Turn Style and Turn Radius properties, i.e. the values in this editor will be used. "Iscript.bin Control" ignores these properties and follows only the Iscript opcode sequence. "Partially Mobile/Weapon" is used for various weapons sprites, not completely understood.

# set those intances to debug the values while development
# in this case the parameters at top of this file have to be commented out
#instances:
#  num_lines:
#    value: 184

