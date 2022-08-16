meta:
  id: weapons_dat
  endian: le

seq:
  - id: label
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The name of the weapon, displayed when you highlight its icon in the control bar. [pointer to stat_txt.tbl]

  - id: graphics
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The main graphics that the weapon uses. 0-Scourge = No graphics.[pointer to flingy.dat]

  - id: explosion
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Effect the weapon has on the area around the target after hitting its target. Used to determine different type of spell effects and splash damage.
      TODO: create enum
      0 = Nothing
      1 = Lockdown
      2 = Irradiate
      3 = Spider Mines (Chase Unit)
      4 = Normal
      5 = No Damage
      6 = No Damage
      7 = EMP Shockwave
      8 = Yamato Gun
      9 = No Damage
      10 = No Damage
      11 = No Damage
      12 = No Damage
      13 = Broodling
      14 = Dark Swarm
      15 = Plague
      16 = Consume
      17 = Ensnare
      18 = Parasite
      19 = Psi Storm
      20 = Normal
      21 = Normal
      22 = Stasis
      23 = 1/4 Damage?
      24 = Normal
      25 = 1/3 Damage?

  - id: target_flags
    type: u2
    repeat: expr
    repeat-expr: num_lines
    enum: attack_type_enum
    # TODO: work on this bitfield!
    # 200 Bytes | 1 Integer / Weapon
    #  1 = Attacks Air only
    #  2 = Attacks Ground only
    #  3 = Attacks Ground and Air
    #  4 = Units Only (No Buildings)
    # 18 = Ground Units (No Hover) Only

  - id: minimum_range
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Minimal range from which the weapon can be used.
      TODO: StaDat shows here value/16 but no sure why.

  - id: maximum_range
    type: u4
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Maximal range from which the weapon can be used.
      TODO: StaDat shows here value/16 but no sure why.

  - id: damage_upgrade
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The upgrade that will increase the damage dealt by the weapon by the "Bonus" value.
      Pointer to [upgrades.dat]

  - id: weapon_type
    type: u1
    enum: weapon_type_enum
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The type of damage the weapon does. Normal, Explosive and Concussive do different amount of damage to units of different Size (Small, Medium or Large): Normal does equal damage to Small, Medium and Large. Explosive does 50% to Small and 75% to Medium. Concussive does 50% to Medium and 25% to Large.  Independent deals 1 point of damage every second attack, regardless of target's armor.

  - id: weapon_behaviour
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Determines how the weapon sprite will "behave" when it attacks the target. Weapon behaviours that "Follow" will track the target as it moves, those that "Don't Follow" will strike the place where the target was at the moment of attack.
      TODO: take enum values from StarDat
    # 0 = Flies to target
    # 1 = Seeks Target
    # 2 = Appears on Target
    # 4 = Persistant Explosion
    # 5 = Wraps around Target?
    # 6 = Suicide
    # 7 = Bounce

  - id: remove_after
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Time until the weapon is removed if it does not hit a target. 1 game second equals: on Fastest-24, on Faster-21, on Fast-18, on Normal-15, on Slow-12, on Slower-9 and on Slowest-6.

  - id: explosive_type
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Effect the weapon has on the area around the target after hitting its target. Used to determine different type of spell effects and splash damage.
    # TODO: copy values from StarDat
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

  - id: inner_splash_range
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Distance from the target at which the weapon will deal 100% of its base damage. Works ONLY if the "Explosion" is set to "Nuclear Missile", "Splash (Radial)", "Splash (Enemy)" or "Splash (Air)".

  - id: medium_splash_range
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Distance from the target at which the weapon will deal 50% of its base damage. Works ONLY if the "Explosion" is set to "Nuclear Missile", "Splash (Radial)", "Splash (Enemy)" or "Splash (Air)".

  - id: outer_splash_range
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Distance from the target at which the weapon will deal 25% of its base damage. Works ONLY if the "Explosion" is set to "Nuclear Missile", "Splash (Radial)", "Splash (Enemy)" or "Splash (Air)".

  - id: damage_amount
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The basic amount of damage the weapon will inflict when it hits.

  - id: damage_bonus
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The amount of damage added to the basic value for each level of the upgrade.

  - id: weapon_cooldown
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      "Reload time" - time delay between two attacks. Depends on the game speed used. 1 game second equals: on Fastest-24, on Faster-21, on Fast-18, on Normal-15, on Slow-12, on Slower-9 and on Slowest-6. Value of 0 will crash the game.

  - id: damage_factor
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Usually, multiple this value by the Damage Amount to get the total damage that is DISPLAYED for the weapon. To a degree also the number of weapons used per attack, but anything other than 2 will result in 1 weapon being used. (e.g. Goliath, Scout and Valkyrie use 2 missiles per attack).

  - id: attack_angle
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Angle within which the weapon can be fired without waiting for the unit's graphics to turn. 128 = 180 degrees.

  - id: launch_spin
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Angle by which the weapon's sprite will spin after it is spawned. 128 = 180 degrees.

  - id: x_offset
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Distance (in pixels) from the front of the attacking unit (depending on which direction it is facing), at which the weapon's sprite will be spawned.

  - id: y_offset
    type: u1
    repeat: expr
    repeat-expr: num_lines
    doc: |
      Distance (in pixels) from the top of the attacking unit, at which the weapon's sprite will be spawned.

  - id: error_message
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The line displayed when the weapon is to acquire an invalid target (e.g. attacking a Mutalisk with a ground-only weapon, like Flamethrower) [pointer to stat_txt.tbl]

  - id: icon
    type: u2
    repeat: expr
    repeat-expr: num_lines
    doc: |
      The icon used for the weapon. [pointer to a frame in unit\cmdbtns\cmdicons.grp]

instances:
  num_lines:
    value: file_size / record_size
    doc: |
      A division of file size though the record size gives the number of records in the file to parse.

  record_size:
    value: 42
    doc: |
      The size of one data record. This is all type sizes in the format summarized.

  file_size:
    value: '_io.size'

enums:
  attack_type_enum:
    1: air_only
    2: ground_only
    3: ground_and_air
    4: units_only # no buildings
    18: ground_units_only # no hover units

  weapon_type_enum:
    0: ndependent
    1: explosive
    2: concussive
    3: normal
    4: ignore_amor

