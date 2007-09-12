DefineAnimations("animations-zerg-ultralisk-death", {
  Death = {"unbreakable begin", "frame 0", "wait 50", "frame 1", "wait 50", "frame 2", "wait 50", "frame 3", "wait 50", "frame 4", "wait 50", "unbreakable end", "wait 1", },
})

DefineUnitType("unit-zerg-ultralisk-death", { Name = "Dead Zergling",
  Image = {"file", "zerg/units/zuldeath.png", "size", {128, 128}},
  Animations = "animations-zerg-ultralisk-death", Icon = "icon-zerg-ultralisk",
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


DefineAnimations("animations-zerg-ultralisk", {
   Still = {
    "frame 119", "wait 125",
  },
  Move = {"unbreakable begin",
    "move 6", "wait 1", "frame 136", "move 3", "wait 1", "frame 153",
    "move 3", "wait 1", "frame 0", "move 3", "wait 1", "frame 17",
    "move 5", "wait 1", "frame 34", "move 5", "wait 1", "frame 51",
    "move 4", "wait 1", "frame 68",
    --FIXME: sub-tile movement
    --[["move 8", "wait 1", "frame 85",
    "move 6", "wait 1", "frame 102", "move 4",
    "unbreakable end", "wait 1", "frame 119",]]
    "move 3", "unbreakable end", "wait 1", "frame 119",
  },
  Attack = {
    "unbreakable begin", "frame 204", "wait 4", "sound zerg-ultralisk-attack", "frame 221", "wait 4", "frame 238", "wait 4", "attack", "sound zerg-ultralisk-hit",
    "unbreakable end", "wait 1",
  },
  Death = {
    "unbreakable begin",
   "frame 272", "wait 30", "frame 273", "wait 5", "frame 274", "wait 5", "frame 275", "wait 5", "frame 276", "wait 5", "frame 277", "wait 5", "frame 278", "wait 5", "frame 279", "wait 5", "frame 280", "wait 5", "frame 281", "wait 5", "frame 282", "wait 5",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-zerg-ultralisk", { Name = "Ultralisk",
  Image = {"file", "zerg/units/ultralisk.png", "size", {128, 128}},
  Shadow = {"file", "zerg/units/ultralisk shadow.png", "size", {128, 128}, "offset", {0, 7}},
  Animations = "animations-zerg-ultralisk", Icon = "icon-zerg-ultralisk",
  Costs = {"time", 120, "minerals", 200, "gas", 200},
  Speed = 12, NumDirections = 32,
  HitPoints = 400,
  DrawLevel = 40,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 4, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 3, BasicDamage = 20, PiercingDamage = 10, Missile = "missile-none",
  MaxAttackRange = 1,
  Priority = 60,
  Points = 30,
  Demand = 6,
--  ExplodeWhenKilled = "missile-zerg-hydralisk-explode",
  Type = "land",
  RegenerationRate = 1,
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  Corpse = "unit-zerg-ultralisk-death",
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-ultralisk-selected",
    "acknowledge", "zerg-ultralisk-acknowledgement",
    "ready", "zerg-ultralisk-ready",
    "help", "basic human voices help 1",
	"dead", "zerg-ultralisk-death"} } )


