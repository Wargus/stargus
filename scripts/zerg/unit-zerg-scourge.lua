--
-- unit-zerg-scourge
--


DefineAnimations("animations-zerg-scourge-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 50", "frame 1", "wait 50", "frame 2", "wait 50",
    "frame 3", "wait 50",
    "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-scourge-death", { Name = "Dead Scourge",
  Image = {"file", "zerg/units/scourge death.png", "size", {36, 36}},
  Animations = "animations-zerg-scourge-death", Icon = "icon-zerg-scourge",
  NumDirections = 1,
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  SelectableByRectangle = false,
  Vanishes = true,
  Sounds = {} } )


DefineAnimations("animations-zerg-scourge", {
  Still = {
    "frame 0", "wait 3", "frame 17", "wait 3", "frame 34", "wait 3",
    "frame 51", "wait 3", "frame 68", "wait 3",
  },
  Move = {
    "unbreakable begin",
    "frame 0", "move 4", "wait 2", "frame 17", "move 3", "wait 2",
    "frame 34", "move 3", "wait 2", "frame 51", "move 3", "wait 2",
    "frame 68", "move 3", "wait 2", "frame 0", "move 4", "wait 2",
    "frame 17", "move 3", "wait 2", "frame 34", "move 3", "wait 2",
    "frame 51", "move 3", "wait 2", "frame 68", "move 3", "wait 1",
    "unbreakable end", "wait 1",
  },
  Attack = {
    "unbreakable begin",
    "sound zerg-scourge-attack", "frame 0", "wait 1", "attack",
    "unbreakable end", "wait 1",
  },
  Death = {
    "unbreakable begin", "sound zerg-scourge-death",
    "wait 1", "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-scourge", {
  Shadow = {"file", "zerg/units/scourge.png", "size", {48, 48}, "offset", {0, 42}},
  DrawLevel = 45, NumDirections = 32,
  Animations = "animations-zerg-scourge", Icon = "icon-zerg-scourge",
  Costs = {"time", 250, "minerals", 12, "gas", 38},
  Speed = 14,
  DrawLevel = 60,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 5, ComputerReactionRange = 5, PersonReactionRange = 5,
  Armor = 0, BasicDamage = 110, PiercingDamage = 16, Missile = "missile-none",
  MaxAttackRange = 1,
  Priority = 65,
  Points = 150,
  Demand = 1,
  Corpse = "unit-zerg-scourge-death",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = false, CanTargetSea = false, CanTargetAir = true,
  AirUnit = true,
  DetectCloak = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-scourge-selected",
    "acknowledge", "zerg-scourge-acknowledgement",
    "ready", "zerg-scourge-ready",
    "help", "zerg-units-attacked",
    "dead", "zerg-scourge-death"} } )

