DefineAnimations("animations-protoss-zealot-death", {
  Death = {"unbreakable begin", "frame 296", "wait 50", "unbreakable end", "wait 1", },
})

DefineUnitType("unit-protoss-zealot-death", { Name = "Dead Zergling",
  Image = {"file", "zerg/units/zergling.png", "size", {128, 128}},
  Animations = "animations-protoss-zealot-death", Icon = "icon-zerg-zergling",
  NumDirections = 1,
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Vanishes = true,
  Sounds = {} } )



DefineAnimations("animations-protoss-zealot", {
  Still = {
    "label 70FD", "frame 68",
    "label 7100", "random-wait 63 75", "random-goto 10 7124",
      "random-goto 50 710E", "goto 7100",
    "label 710E", "frame 85", "wait 1", "frame 102", "wait 1",
      "random-rotate 3", "wait 1", "frame 85", "wait 1", "goto 70FD",
    "label 7124", "frame 0", "wait 1", "frame 17", "wait 1", "frame 34",
      "random-goto 75 7170",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "rotate -2", "wait 3",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "wait 6",
      "rotate 2", "wait 3", "rotate 2", "wait 3", "rotate 2", "wait 3",
      "rotate 2", "wait 3", "rotate 2", "wait 3", "wait 6",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "rotate -2", "wait 3",
      "goto 7172",
    "label 7170", "wait 13",
    "label 7172", "frame 17", "wait 1", "frame 0", "wait 1", "goto 70FD",
  },
  Move = {"unbreakable begin",
    "move 4", "wait 1", "frame 85", "move 4", "wait 1", "frame 102",
    "move 4", "wait 1", "frame 119", "move 4", "wait 1", "frame 136",
    "move 4", "wait 1", "frame 153", "move 4", "wait 1", "frame 170",
    "move 4", "wait 1", "frame 187",
    --FIXME: subtile movement not supported
    --[["move 4", "wait 1", "frame 204",]]
    "move 4", "unbreakable end", "wait 1", "frame 68",
  },
--  StartAttack = {"frame 0", "wait 1", "frame 17", "wait 1", "frame 34",},
  Attack = {
    "wait 1", "unbreakable begin", "sound terran-marine-attack", "attack",
    "frame 51", "wait 1", "frame 34", "wait 1", "frame 51", "wait 1",
    "frame 34", "wait 1", "frame 51", "wait 1", "frame 34",
    "unbreakable end", "wait 1",
  },
--  EndAttack = {"frame 17", "wait 1", "frame 0", "wait 1", --[[goto 70FD]]},
  Death = {
    "unbreakable begin",
    "sound zerg-zergling-death", "exact-frame 289", "wait 2",
    "exact-frame 290", "wait 2", "exact-frame 291", "wait 2",
    "exact-frame 292", "wait 2", "exact-frame 293", "wait 2",
    "exact-frame 294", "wait 2", "exact-frame 295", "wait 2",
    "exact-frame 296", "wait 2", "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-protoss-zealot", { Name = "Zealot",
  Image = {"file", "protoss/units/zealot.png", "size", {128, 128}},
  Shadow = {"file", "protoss/units/pzeshad.png", "size", {128, 128}},
  Animations = "animations-protoss-zealot", Icon = "icon-protoss-zealot",
  Costs = {"time", 60, "minerals", 50},
  Speed = 10, NumDirections = 32,
  HitPoints = 25,
  DrawLevel = 40,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 4, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-none",
  MaxAttackRange = 1,
  Priority = 60,
  Points = 50,
  Demand = 1,
  Corpse = "unit-protoss-zealot-death",
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "protoss-zealot-selected",
    "acknowledge", "protoss-zealot-acknowledge",
    "ready", "protoss-zealot-ready",
    "help", "protoss-zealot-attacked",} } )


