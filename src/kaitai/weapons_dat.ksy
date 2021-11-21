meta:
  id: weapons_dat
  endian: le
seq:
  - id: weapon_label
    type: u2
    repeat: expr
    repeat-expr: 100
    # 200 bytes | 1 Integer / Weapon
    
  - id: missile_sprite
    type: u4
    repeat: expr
    repeat-expr: 100
    # 400 Bytes | 1 Long / Weapon
    
  - id: special_attack
    type: u1
    repeat: expr
    repeat-expr: 100
    # 100 Bytes | 1 Byte / Weapon
    
  - id: attack_type
    type: u2
    repeat: expr
    repeat-expr: 100
    enum: attack_type_value
    # 200 Bytes | 1 Integer / Weapon
    #  1 = Attacks Air only
    #  2 = Attacks Ground only
    #  3 = Attacks Ground and Air
    #  4 = Units Only (No Buildings)
    # 18 = Ground Units (No Hover) Only
    
  - id: minimum_range
    type: u4
    repeat: expr
    repeat-expr: 100
    # 400 Bytes |	1 Long / Weapon
    
  - id: maximum_range
    type: u4
    repeat: expr
    repeat-expr: 100
    # 400 Bytes |	1 Long / Weapon
    
  - id: upgrade_group
    type: u1
    repeat: expr
    repeat-expr: 100
    # 100 Bytes |	1 Byte / Weapon
    #  7 = Terran Infantry Weapons
    #  8 = Terran Vehicle Weapons
    #  9 = Terran Ship Weapons
    # 10 = Zerg Melee Attacks
    # 11 = Zerg Missile Attacks
    # 12 = Zerg Flyer Attacks
    # 13 = Protoss Ground Weapons
    # 14 = Protoss Air Weapons
    # 35 = Scarab
    # 45 = No upgrades
    
  - id: weapon_type
    type: u1
    repeat: expr
    repeat-expr: 100
    # 100 Bytes | 1	Byte / Weapon
    # 1 = Explosive
    # 2 = Concussive
    # 3 = Normal
    
  - id: weapon_behaviour
    type: u1
    repeat: expr
    repeat-expr: 100
    # 100 Bytes |	1 Byte / Weapon
    # 0 = Flies to target
    # 1 = Seeks Target
    # 2 = Appears on Target
    # 4 = Persistant Explosion
    # 5 = Wraps around Target?
    # 6 = Suicide
    # 7 = Bounce

  - id: missile_type
    type: u1
    repeat: expr
    repeat-expr: 100
    # 100 Bytes |	1 Byte / Weapon
    #  30 = Homing Missile
    #  60 = Unknown
    # 255 = Normal
    
  - id: explosive_type
    type: u1
    repeat: expr
    repeat-expr: 100
    # 100 Bytes | 1 Byte / Weapon
    #  1 = Normal
    #  2 = Normal
    #  3 = Normal
    #  4 = Lockdown
    #  5 = Unknown
    #  6 = Parasite
    #  7 = Spawn Broodlings
    #  8 = EMP Shockwave (No gfx, just energy drain)
    #  9 = Irradiate
    # 10 = Ensnare
    # 11 = Plague
    # 12 = Stasis
    # 13 = Dark Swarm
    # 14 = Normal
    # 15 = Normal
    
  - id: splash_minimum
    type: u2
    repeat: expr
    repeat-expr: 100
    # 200 Bytes |	1 Integer / Weapon 	
    
  - id: splash_medium
    type: u2
    repeat: expr
    repeat-expr: 100
    # 200 Bytes |	1 Integer / Weapon 	
    
  - id: splash_maximum
    type: u2
    repeat: expr
    repeat-expr: 100
    # 200 Bytes |	1 Integer / Weapon
    
  - id: damage
    type: u2
    repeat: expr
    repeat-expr: 100
    # 200 Bytes |	1 Integer / Weapon
    
  - id: bonus
    type: u2
    repeat: expr
    repeat-expr: 100
    # 200 Bytes | 1 Integer / Weapon
    
  - id: delay
    type: u1
    repeat: expr
    repeat-expr: 100
    # 100 Bytes |	1 Byte / Weapon
    
  - id: factor
    type: u1
    repeat: expr
    repeat-expr: 100
    # 100 Bytes |	1 Byte / Weapon
    
  - id: coordinate_group1
    type: coordinate_group_type
    repeat: expr
    repeat-expr: 100
    # 200 Bytes |	2 Bytes / Weapon
    # X Coordinate (Byte)
    # Y Coordinate (Byte)
    
  - id: coordinate_group2
    type: coordinate_group_type
    repeat: expr
    repeat-expr: 100
    # 200 Bytes |	2 Bytes / Weapon
    # X Coordinate (Byte)
    # Y Coordinate (Byte)
    
  - id: error_message
    type: u2
    repeat: expr
    repeat-expr: 100
    # 200 Bytes |	1 Integer / Weapon 	
    
  - id: weapon_icon
    type: u2
    repeat: expr
    repeat-expr: 100
    # 200 Bytes |	1 Integer / Weapon
    
enums:
  attack_type_value:
    1: air_only
    2: ground_only
    3: ground_and_air
    4: units_only # no buildings
    18: ground_units_only # no hover units
    
types:
  coordinate_group_type:
    seq:
      - id: x
        type: u1
      - id: y
        type: u1
