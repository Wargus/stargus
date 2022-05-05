meta:
  id: units_dat
  endian: le
  bit-endian: le

# There're some different units.dat versions out there available.
# Here is a list of files with md5sums which have been identified until now:
#
# -46ed51df10eda16215ccd5c18b736731
#   has_brood_war_unit_flag=false
#   has_max_air_hits=false
#   has_max_ground_hits=false
#
# -e8d54a9ffe73a0db123907b7a7b2140a
# -cecac677ae61351aaa3e52884de4abed
#   has_brood_war_unit_flag=true
#   has_max_air_hits=true
#   has_max_ground_hits=true
#
params:
  - id: has_broodwar_flag
    type: b1
  - id: has_max_air_hits
    type: b1
  - id: has_max_ground_hits
    type: b1

seq:
  - id: flingy
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Unit's main graphics object. [pointer to flingy.dat]

  - id: subunit1
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Main subunit to the unit. Various turrets mostly. [pointer to units.dat]

  - id: subunit2
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Secondary subunit. Unused. [pointer to units.dat]
    
  - id: infestation
    type: u2
    repeat: expr
    repeat-expr: 96
    doc: |
      Unit to transform into after Infestation. Exists only for units of ID 106-201 (buildings). [pointer to units.dat]

  - id: construction_animation
    type: u4
    repeat: expr
    repeat-expr: 228
    doc: |
      Construction graphics of the unit (used mostly with buildings). 0-Scourge = No graphics. [pointer to images.dat]

  - id: unit_direction
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Direction unit will face after it is created. Values start at 0 (the unit will face the top of the screen) and go on clockwise through subsequent turning stages until 31 (unit will face a little left from the complete turn). Value of 32 means unit will face a random direction.

  - id: shield_enable
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Enables Shields for the unit. Works for any unit, not only Protoss. Terran and zerg buildings with shields do NOT acquire full shield capacity during construction.

  - id: shield_amount
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of Shield Points the unit has. Shields are reduced before the unit's Hit Points are affected.

  - id: hit_points
    type: hit_points_type
    repeat: expr
    repeat-expr: 228
    doc: |
      Unit Hit Points (HP) or "life" amount.

  - id: elevation_level
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      The elevation level at which the unit moves. It can be used to make units moves like flyers, but still be attacked by ground weapons and act as ground units to specific special abilities (like Recall). Higher values puts the unit higher over terrain and other units.

  - id: unknown
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      TODO: this might be "movement_type" but meaning is unclear

  - id: rank
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Controls ground units movement: units with lower Rank will stop and wait to allow units with higher Rank to continue movement. Has no effects on air units. Also the order this unit is displayed in its folder in StarEdit. Max of 255.
      also known as 'sublabel'

  - id: ai_computer_idle
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Order given to the unit if it is under computer control and does nothing. [pointer to orders.dat]      name 'Computer AI Idle'

  - id: ai_human_idle
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Order given to the unit if it is under a human player's control and does nothing. [pointer to orders.dat]

  - id: ai_return_to_idle
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Order executed after the unit has finished executing another order and returns to Idle state. [pointer to orders.dat]

  - id: ai_attack_unit
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Order executed if the units is ordered to attack an enemy unit, also through the Right-Click action. [pointer to orders.dat]

  - id: ai_attack_move
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Order executed if the unit is ordered to Attack Ground. [pointer to orders.dat]

  - id: ground_weapon
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Weapon used for attacking "ground" units - those with the "Flying Target" advanced flag unchecked. [pointer to weapons.dat]

  - id: max_ground_hits
    type: u1
    repeat: expr
    repeat-expr: 228
    if: has_max_ground_hits == true
    doc: |
      Max number of times unit hits its target per Ground attack. This value is for statistics purposes only. Changing it only affects the value displayed in StarEdit.
      Only some variants of units.dat have this data block. If your version has this block activate the parameter.

  - id: air_weapon
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Weapon used for attacking "air" or "flying" units - those with the "Flying Target" advanced flag checked. [pointer to weapons.dat]

  - id: max_air_hits
    type: u1
    repeat: expr
    repeat-expr: 228
    if: has_max_air_hits == true
    doc: |
      Max number of times unit hits its target per Air attack. This value is for statistics purposes only. Changing it only affects the value displayed in StarEdit.
      Only some variants of units.dat have this data block. If your version has this block activate the parameter.
      
  - id: ai_internal
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Some AI-related property. Not completely understood.

  - id: special_ability_flags
    type: special_ability_flags_type
    size: 4
    repeat: expr
    repeat-expr: 228
    doc: |
      Advanced flags. Check the type for detail specification.

  - id: target_acquisition_range
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Range at which the Carrier will launch Interceptors and Reaver Scarabs. Also determines the range at which melee units and Medics will pickup targets. Value of 0 makes the game use the Weapons.dat for range data. 1 range unit here equals 2 range units in weapons.dat.

  - id: sight_range
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Range (in matrices) indicating how much Fog-Of-War will the unit clear up.

  - id: armor_upgrade
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Researching this upgrade will improve the unit's Armor by 1. [pointer to upgrades.dat]

  - id: unit_size
    type: u1
    enum: unit_size_enum
    repeat: expr
    repeat-expr: 228
    doc: |
      Used to calculate the "Explosive" and "Concussive" weapons damage: Explosive (50% to Small, 75% to Medium), Concussive (50% to Medium, 25% to Large). "Independent" - the unit will lose 1 HP every second attack it takes (by no matter what unit or which weapon and regardless of its Armor. Spell effects may vary, e.g. Plague works normally, but Irradiate doesn't).

  - id: armor
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Unit basic Armor level. Armor is subtracted from damage caused by every attack from another unit. If Armor is higher than the attack damage, the unit will act as if was of "Independent" Unit Size.

  - id: right_click_action
    type: u1
    enum: right_click_action_enum
    repeat: expr
    repeat-expr: 228
    doc: |
      Determines what actions may, or may not be taken by the unit if it is given an order through the Right-Click action.

  - id: ready_sound
    type: u2
    repeat: expr
    repeat-expr: 106
    doc: |
      Sound played after the unit is trained/built. 0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat] 
      Only unit id 0 to 106 have this sound.

  - id: what_sound_start
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      First of the "What" sounds - played when you select the unit.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]

  - id: what_sound_end
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Last of the "What" sounds - played when you select the unit.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]

  - id: piss_sound_start
    type: u2
    repeat: expr
    repeat-expr: 106
    doc: |
      First of the "Annoyed" sounds - played when you click multiple times on the same unit.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]

  - id: piss_sound_end
    type: u2
    repeat: expr
    repeat-expr: 106
    doc: |
      Last of the "Annoyed" sounds - played when you click multiple times on the same unit.  0=No sound, substract 1 to get the target sfxdata entry. [pointer to sfxdata.dat]

  - id: yes_sound_start
    type: u2
    repeat: expr
    repeat-expr: 106
    doc: |
      First of the "Yes" sounds - played when you give the unit an order.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]

  - id: yes_sound_end
    type: u2
    repeat: expr
    repeat-expr: 106
    doc: |
      Last of the "Yes" sounds - played when you give the unit an order.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]

  - id: staredit_placement_box
    type: staredit_placement_box_type
    repeat: expr
    repeat-expr: 228
    doc: |
      Width/Height of the green placement rectangle in StarEdit, in pixels.

  - id: addon_position
    type: addon_position_type
    repeat: expr
    repeat-expr: 96
    doc: |
      Horizontal/vertical distance in pixels at which an addon will be placed. Exists only for units of ID 106-201 (buildings).

  - id: unit_dimension
    type: unit_dimension_type
    repeat: expr
    repeat-expr: 228
    doc: |
      Space the unit takes from its position. Measured in pixels.

  - id: portrait
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Unit's Idle portrait. Talking Portraits are determined by adding 110 to this value [pointer to portdata.dat]

  - id: mineral_cost
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of minerals needed to train/build the unit.

  - id: vespene_cost
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of Vespene Gas needed to train/build the unit.

  - id: build_time
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of time it takes to train/build the unit, in 1/24ths of a second (at Fastest speed).

  - id: requirements
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      TBD

  - id: staredit_group_flags
    type: staredit_group_flags_type
    repeat: expr
    repeat-expr: 228
    size: 1
    doc: |
      Flags used in StarEdit. Check the type for detail specification.

  - id: supply_provided
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of Supply/Psi/Control required to train/build the unit. Halves are rounded down for the display, but calculated normally.
      TODO: check why StarDat shows always the half of what is in units.dat

  - id: supply_required
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of Supply/Psi/Control required to train/build the unit. Halves are rounded down for the display, but calculated normally.
      TODO: check why StarDat shows always the half of what is in units.dat

  - id: space_required
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of loading space the unit takes up in a transport. If it is higher than the transport's loading space, the unit cannot be loaded. It DOES NOT resize the unit's wireframe when inside the transport.

  - id: space_provided
    type: u1
    repeat: expr
    repeat-expr: 228
    doc: |
      Amout of loading space the unit has. Used with dropships. This IS NOT the number of units the transporting unit may carry as different unit may take up different amount of loading space.

  - id: build_score
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of points given for training/building the unit, counted to the total score after the end of a game.

  - id: destroy_score
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      Amount of points given for destroying the unit, counted to the total score after the end of a game. It is also used by the AI for targetting purposes. Units with a higher destroy score will be targeted first.

  - id: unit_map_string
    type: u2
    repeat: expr
    repeat-expr: 228
    doc: |
      If this property is different from 0, the unit's name will be read from the strings stored within the map (CHK) that is currently loaded, instead of the stat_txt.tbl file.

  - id: broodwar_flag
    type: u1
    repeat: expr
    repeat-expr: 228
    if: has_broodwar_flag == true
    doc: |
      Makes the unit available only while playing BroodWar expansion set.
      Only some variants of units.dat have this data block. If your version has this block activate the parameter.

  - id: staredit_availability_flags
    type: staredit_availability_flags_type
    size: 2
    repeat: expr
    repeat-expr: 228
    doc: |
      Flags used in StarEdit. Check the type for detail specification.

# set those intances to debug the values while development
# in this case the parameters at top of this file have to be commented out
#instances:
#  has_broodwar_flag:
#    value: false
#  has_max_air_hits:
#    value: false
#  has_max_ground_hits:
#    value: false

types:
  staredit_placement_box_type:
    seq:
      - id: width
        type: u2
      - id: height
        type: u2

  addon_position_type:
    seq:
      - id: horizontal
        type: u2
      - id: vertical
        type: u2

  hit_points_type:
    seq:
      - id: hitpoints
        type: u2be
      - id: unused
        type: u2be

  unit_dimension_type:
    seq:
      - id: left
        type: u2
      - id: up
        type: u2
      - id: right
        type: u2
      - id: down
        type: u2
   
  special_ability_flags_type:
    seq:
      - id: building
        type: b1  # 0b0000_0001 = 0x01
      - id: addon
        type: b1  # 0b0000_0010 = 0x02
      - id: flyer
        type: b1  # 0b0000_0100 = 0x04
      - id: resourceminer
        type: b1  # 0b0000_1000 = 0x08
      - id: subunit
        type: b1  # 0b0001_0000 = 0x10
      - id: flyingbuilding
        type: b1  # 0b0010_0000 = 0x20
      - id: hero
        type: b1  # 0b0100_0000 = 0x40
      - id: regenerate
        type: b1  # 0b1000_0000 = 0x80
      - id: animatedidle
        type: b1  # 0b0000_0001_0000_0000 = 0x100
      - id: cloakable
        type: b1  # 0b0000_0010_0000_0000 = 0x200
      - id: twounitsinoneegg
        type: b1  # 0b0000_0100_0000_0000 = 0x400
      - id: singleentity
        type: b1  # 0b0000_1000_0000_0000 = 0x800
      - id: resourcedepot
        type: b1  # 0b0001_0000_0000_0000 = 0x1000
      - id: resourcecontainter
        type: b1  # 0b0010_0000_0000_0000 = 0x2000
      - id: robotic
        type: b1  # 0b0100_0000_0000_0000 = 0x4000
      - id: detector
        type: b1  # 0b1000_0000_0000_0000 = 0x8000
      - id: organic
        type: b1  # 0b0000_0000_0000_0001_0000_0000_0000_0000 = 0x10000
      - id: requirescreep
        type: b1  # 0b0000_0000_0000_0010_0000_0000_0000_0000 = 0x20000
      - id: unused
        type: b1  # 0b0000_0000_0000_0100_0000_0000_0000_0000 = 0x40000
      - id: requirespsi
        type: b1  # 0b0000_0000_0000_1000_0000_0000_0000_0000 = 0x80000
      - id: burrowable
        type: b1  # 0b0000_0000_0001_0000_0000_0000_0000_0000 = 0x100000
      - id: spellcaster
        type: b1  # 0b0000_0000_0010_0000_0000_0000_0000_0000 = 0x200000
      - id: permanentcloak
        type: b1  # 0b0000_0000_0100_0000_0000_0000_0000_0000 = 0x400000
      - id: pickupitem
        type: b1  # 0b0000_0000_1000_0000_0000_0000_0000_0000 = 0x800000
      - id: ignoresupplycheck
        type: b1  # 0b0000_0001_0000_0000_0000_0000_0000_0000 = 0x1000000
      - id: usemediumoverlays
        type: b1  # 0b0000_0010_0000_0000_0000_0000_0000_0000 = 0x2000000
      - id: uselargeoverlays
        type: b1  # 0b0000_0100_0000_0000_0000_0000_0000_0000 = 0x4000000
      - id: battlereactions
        type: b1  # 0b0000_1000_0000_0000_0000_0000_0000_0000 = 0x8000000
      - id: fullautoattack
        type: b1  # 0b0001_0000_0000_0000_0000_0000_0000_0000 = 0x1000000
      - id: invincible
        type: b1  # 0b0010_0000_0000_0000_0000_0000_0000_0000 = 0x2000000
      - id: mechanical
        type: b1  # 0b0100_0000_0000_0000_0000_0000_0000_0000 = 0x4000000
      - id: producesunits
        type: b1  # 0b1000_0000_0000_0000_0000_0000_0000_0000 = 0x8000000
    doc: |
      building: Unit is considered as a building for targeting purposes, and affects Addons-related properties. Also allows for other units to be built/trained 'inside' the unit and makes the unit placement dependent on the "Placement Box" property instead of the "Unit Dimensions".
      addon: Makes the building placeable in a special way, dependent on the main building. If unchecked, the building will still use the standard way of placing the addon, but after lift-off, it will be inaccessible.
      flyer: If unchecked, the unit is targeted by Ground weapons. If checked, unit can be targeted by Air weapons. It also makes the unit "fly" in the way that it chooses the shortest path to its destination, moving over terrain and other units.
      resourceminer: Unit can gather/return resources. Does NOT affect building construction abilities (except a tiny Drone glitch if you cancel a building morph). Requires a .LOO file pointed from the "Overlay 3" property in Images.dat to work. Vespene Gas harvesting seems good for all units, but Minerals may cause crashes, depending on the unit you use (e.g. Marine is OK, but the Firebat will crash)
      subunit: Makes the unit a "sub-unit", i.e. allows it to be a part of another unit (like the tank turret to the tank body) through the Subunit property (see Graphics tab). A non-subunit-type unit used as a subunit will crash the game. To have a sub-unit properly placed on a unit, you also require altering the images.dat properties of the base sprite as well as certain other settings. Expect crashes more than often while working with this property.
      flyingbuilding: Allows/Disallows the unit to be in the "In Transit" (or "Flying") state both in the game and in StarEdit, but it will crash if the unit does not have a Lift-off and Landing animations (in Iscript.bin). Does not affect buttons available for the unit.
      hero: Unit has all its upgrades researched from the start and receives a white wireframe box (instead of the standard blue one). If a unit is also a spellcaster, it will have 250 energy points, regardless if there is an energy upgrade for it or not. 
      regenerate: Unit will slowly regain Hit Points, until its full HP capacity.
      animatedidle: 
      cloakable: Allows/Disallows the unit to use the Cloak technology. It does NOT give/remove the "Cloak" button but allows the unit to display the "Group (Cloakers)" button set when selected in a group.
      twounitsinoneegg: 2 units will come out of one Zerg Egg instead of just one. The cost for morphing will NOT be doubled, but the amount of the used supplies will equal 2 times the normal amount. To accomplish the full effect you will also have to add a "Construction" graphics and set a "Landing Dust" overlay to it.
      singleentity: Unit cannot be selected in a group, but only as a single unit. Unit cannot be selected by dragging a selection box, by a SHIFT-Click nor a double-click.
      resourcedepot: Makes a building (and ONLY a building) a place workers can return resources to. Also makes it impossible to place/land the building next to a unit with the "Resource Container" property.
      resourcecontainter: Unit does not generate an error message if targeted for Gathering by a worker. Allows/Disallows to set unit's resources capacity in StarEdit, but does not make a unit other than original resource actually store resources in-game. Unchecked, makes the original resources capacity equal to 0, although workers will still try to harvest it. Prevents "Resource Depots" from being located next to it.
      robotic: Unit is treated as a robotic-type target for weapons and spells (e.g. it cannot be targeted with Spawn Broodlings)
      detector: Unit can detect cloaked enemy units and receives the "Detector" title under its name.
      organic: Unit is treated as an organic-type target for weapons and spells (e.g. Maelstrom).
      requirescreep: Building MUST be built on creep. It will also get a creep outline around it.
      unused: 
      requirespsi: Unit must be built within a PSI field, like that produced by pylons. If it is not within a PSI field, it will become "Disabled" and not function. Can be given to any unit. You can also disable it on Protoss buildings so they can be built anywhere. 
      burrowable: Allows/Disallows the unit to use the Burrow technology. It does NOT give/remove the "Burrow" button.
      spellcaster: Unit receives a mana bar and will slowly regain mana points through time. Combined with the Permanent Cloak property, will prevent unit from regaining mana.
      permanentcloak: Unit is constantly cloaked. If the unit is also a Spellcaster, giving this property will make it lose mana until 0.
      pickupitem: Related to powerups. Not completely understood.
      ignoresupplycheck: Even if you don't have the supply available to build the unit, the engine will still build it and add that to your supply.
      usemediumoverlays: Unit will use medium spell overlay graphics.
      uselargeoverlays: Unit will use large spell overlay graphics.
      battlereactions: Unit will show battle reactions,i.e. if it sees an enemy it will move to it and attack, if it is attacked by an unreachable enemy (e.g. an Air unit and it doesn't have an Air weapon) it will run away. Works ONLY if the unit's Idle AI Orders are set to Guard.
      fullautoattack: Unit will attack any enemy that enters its firing range. If unchecked, unit will attack the enemy ONLY if it is facing its direction, e.g. because it has an animated idle state. 
      invincible: Unit cannot be a target of any sort of weapons or spells. It also hides the unit's Hit Points value.
      mechanical: Unit is treated as a mechanical-type target for weapons and spells (e.g. Lockdown). It can also be repaired by SCVs.
      producesunits: 
        
  staredit_group_flags_type:
    seq:
      - id: zerg
        type: b1  # 0b0000_0001 = 0x01
      - id: terran
        type: b1  # 0b0000_0010 = 0x02
      - id: protoss
        type: b1  # 0b0000_0100 = 0x04
      - id: men
        type: b1  # 0b0000_1000 = 0x08
      - id: building
        type: b1  # 0b0001_0000 = 0x10
      - id: factory
        type: b1  # 0b0010_0000 = 0x20
      - id: independent
        type: b1  # 0b0100_0000 = 0x40
      - id: neutral
        type: b1  # 0b1000_0000 = 0x80
    doc: |
      zerg: Unit is from race "Zerg"
      terran: Unit is from race "Terran"
      protoss: Unit is from race "Protoss"
      men: Unit is a "Men"-type unit for triggers.
      building: Unit is a "Building"-type unit for triggers.
      factory: Unit is a "Factory"-type unit for triggers.
      independent: Unit is treated as an Independent unit (abandoned unit type).
      neutral: Unit is treated as a Neutral unit.
        
  staredit_availability_flags_type:
    seq:
      - id: non_neutral
        type: b1  # 0b0000_0001 = 0x01
      - id: unit_listing
        type: b1  # 0b0000_0010 = 0x02
      - id: mission_briefing
        type: b1  # 0b0000_0100 = 0x04
      - id: player_settings
        type: b1  # 0b0000_1000 = 0x08
      - id: all_races
        type: b1  # 0b0001_0000 = 0x10
      - id: set_doodad_state
        type: b1  # 0b0010_0000 = 0x20
      - id: non_location_triggers
        type: b1  # 0b0100_0000 = 0x40
      - id: unit_hero_settings
        type: b1  # 0b1000_0000 = 0x80
      - id: location_triggers
        type: b1  # 0b0000_0001_0000_0000 = 0x100
      - id: brood_war_only
        type: b1  # 0b0000_0010_0000_0000 = 0x200
      - type: b6  # 0b1111_1100_0000_0000
    doc: |
      non_neutral: Unit belongs to a 1-8 Player, takes its corresponding color and appears in the player's corresponding menu in the unit listing on the left. If unchecked, the unit belongs to the 12th Player (neutral), takes the dark aqua color and appears under the "Neutral" menu in the unit listing.
      unit_listing: Unit is availabe in the unit listing on the left and in the Brush Palette.
      mission_briefing: Unit's portrait is available in Mission Briefing.
      player_settings: Unit is available in the Player Settings.
      all_races: Unit is available for all races in the unit list in StarEdit.
      set_doodad_state: Unit is available for the "Set Doodad State" trigger.
      non_location_triggers: Unit appears in the unit selection box when using Non-locational triggers (Remove, Kill etc.)
      unit_hero_settings: Unit is available in Unit&Hero Settings.
      location_triggers: Unit appears in the unit selection box when using locational triggers (Remove at, Kill at etc.). Even if unchecked, the unit WILL appear for selection when using the "Create at" trigger action.
      brood_war_only: Unit is available only if BroodWar Expansion is installed.
   
enums:
  unit_size_enum:
    0: indendent
    1: small
    2: medium
    3: large

  right_click_action_enum:
    0: no_commands_auo_attack
    1: normal_movement_normal_attack
    2: normal_movement_no_attack
    3: no_movement_normal_attack
    4: harvest
    5: harvest_repair
    6: nothing_with_indicator
