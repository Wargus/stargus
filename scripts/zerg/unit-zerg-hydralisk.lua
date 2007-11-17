--
-- unit-zerg-hydralisk
--


DefineAnimations("animations-zerg-hydralisk-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 50", "frame 1", "wait 50", "frame 2", "wait 50",
    "frame 3", "wait 50",
    "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-hydralisk-death", { Name = "Dead Hydralisk",
  Image = {"file", "zerg/units/hydralisk death.png", "size", {128, 128}},
  Animations = "animations-zerg-hydralisk-death", Icon = "icon-zerg-hydralisk",
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


DefineAnimations("animations-zerg-hydralisk", {
  Still = {
    "label 3FBB", "frame 85",
    "label 3FBE", "random-wait 63 75",
      "random-goto 10 3FCC", "random-goto 50 3FF2", "goto 3FBE",
    "label 3FCC", "frame 0", "wait 1", "frame 17", "wait 1", "frame 34", "wait 1",
      "frame 51", "wait 25", "frame 34", "wait 1", "frame 17", "wait 1",
      "frame 0", "wait 1", "goto 3FBB",
    "label 3FF2", "random-goto 50 4023", "frame 102", "wait 1", "rotate -2",
      "frame 119", "wait 1", "rotate -2", "frame 136", "wait 1", "rotate -2",
      "frame 153", "wait 1", "rotate -2", "frame 170", "wait 1", "rotate -2",
      "frame 187", "wait 1", "rotate -2", "goto 3FBB",
    "label 4023", "frame 102", "wait 1", "rotate 2",
      "frame 119", "wait 1", "rotate 2", "frame 136", "wait 1", "rotate 2",
      "frame 153", "wait 1", "rotate 2", "frame 170", "wait 1", "rotate 2",
      "frame 187", "wait 1", "rotate 2", "goto 3FBB",
  },
  Move = {
    "unbreakable begin",
    "move 3", "wait 1", "frame 102", "move 3", "wait 1", "frame 119",
    "move 3", "wait 1", "frame 136", "move 7", "wait 1", "frame 153",
    "move 6", "wait 1", "frame 170", "move 7", "wait 1", "frame 187",
    "move 3",
    "unbreakable end", "wait 1", "frame 85",
  },
  Attack = {
    "frame 0", "wait 1", "unbreakable begin",
    "frame 17", "wait 1", "frame 34", "wait 1", "frame 51", "wait 2",
    "frame 68", "sound zerg-hydralisk-attack", "attack", "wait 1", "frame 51",
    "unbreakable end", "wait 1",
  },
  Death = {
    "unbreakable begin",
    "exact-frame 204", "wait 2", "exact-frame 205", "wait 2", "exact-frame 206", "wait 2",
    "exact-frame 207", "wait 2", "exact-frame 208", "wait 2", "exact-frame 209", "wait 2",
    "exact-frame 210", "wait 2", "exact-frame 211", "wait 2",
    "unbreakable end", "wait 1",
  },
--[[ Burrow =
    "frame 212", "wait 1", "frame 229", "wait 1", "frame 246", "wait 1",
    "frame 263", "wait 1", "frame 280", "wait 1" ]]
})

DefineUnitType("unit-zerg-hydralisk", { Name = "Hydralisk",
  Image = {"file", "zerg/units/hydralisk.png", "size", {128, 128}},
  Shadow = {"file", "zerg/units/hydralisk shadow.png", "size", {128, 128}, "offset", {0, 7}},
  Animations = "animations-zerg-hydralisk", Icon = "icon-zerg-hydralisk",
  Costs = {"time", 35, "minerals", 75, "gas", 25,},
  Speed = 0, NumDirections = 32,
  HitPoints = 80,
  DrawLevel = 40,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 6, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 2, BasicDamage = 10, PiercingDamage = 4, Missile = "missile-none",
  MaxAttackRange = 5,
  Priority = 60,
  Points = 50,
  Demand = 1,
  RegenerationRate = 1,
  Corpse = "unit-zerg-hydralisk-death",
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  CanTargetAir = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-hydralisk-selected",
    "acknowledge", "zerg-hydralisk-acknowledgement",
    "ready", "zerg-hydralisk-ready",
    "help", "zerg-units-attacked",
	"dead", "zerg-hydralisk-death"} } )


