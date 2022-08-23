--
-- unit-zerg-ultralisk
--


DefineAnimations("animations-zerg-ultralisk-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 50", "frame 1", "wait 50", "frame 2", "wait 50",
    "frame 3", "wait 50", "frame 4", "wait 50",
    "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-ultralisk-death", { Name = "Dead Zergling",
  Image = {"file", "zerg/units/ultralisk death.png", "size", {128, 128}},
  Animations = "animations-zerg-ultralisk-death", Icon = "icon-zerg-ultralisk",
  NumDirections = 1,
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {63, 63},--FIXME: wrong boxsize
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Vanishes = true,
  Sounds = {} } )


DefineAnimations("animations-zerg-ultralisk", {
  Still = {
    "label 45F1", "frame 153", "goto 79BA",
    "label 79BA", "wait 125", "goto 79BA",
    "random-goto 50 4654",
    "frame 153", "rotate -2", "wait 1", "frame 0", "rotate -2", "wait 1",
    "frame 17", "rotate -2", "wait 1", "frame 34", "rotate -2", "wait 1",
    "frame 51", "rotate -2", "wait 1", "frame 68", "rotate -2", "wait 1",
    "frame 85", "rotate -2", "wait 1", "frame 102", "rotate -2", "wait 1",
    "frame 119", "rotate -2", "wait 1", "goto 45F1",
    "label 4654", "frame 153", "rotate 2", "wait 1", "frame 0", "rotate 2", "wait 1",
    "frame 17", "rotate 2", "wait 1", "frame 34", "rotate 2", "wait 1",
    "frame 51", "rotate 2", "wait 1", "frame 68", "rotate 2", "wait 1",
    "frame 85", "rotate 2", "wait 1", "frame 102", "rotate 2", "wait 1",
    "frame 119", "rotate 2", "wait 1", "goto 45F1",
  },
  Move = {
    "unbreakable begin",
    "move 3", "wait 1", "frame 0", "move 8", "wait 2", "frame 17",
    "move 5", "wait 1", "frame 34", "move 4", "wait 1", "frame 51",
    "move 4", "wait 2", "frame 68", "move 8", "wait 1", "frame 85",
    "unbreakable end", "wait 1",
    "unbreakable begin",
    "move 8", "wait 1", "frame 102", "move 8", "wait 1", "frame 119",
    "move 8", "wait 1", "frame 136", "move 8",
    "unbreakable end", "wait 1", "frame 153",
  },
  Attack = {
    "frame 238", "wait 1",
    "unbreakable begin",
    "sound zerg-ultralisk-attack", "wait 2", "frame 221", "wait 2",
    "frame 204", "sound zerg-ultralisk-hit", "attack", "wait 2",
    "frame 187", "wait 2", "frame 204", "wait 2", "frame 221", "wait 2",
    "frame 238", "wait 2",
    "unbreakable end",
  },
  Death = {
    "unbreakable begin",
    "frame 255", "wait 2", "frame 256", "wait 2", "frame 257", "wait 2",
    "frame 258", "wait 2", "frame 259", "wait 2", "frame 260", "wait 2",
    "frame 261", "wait 2", "frame 262", "wait 2", "frame 263", "wait 2",
    "frame 264", "wait 2",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-zerg-ultralisk", {
  Animations = "animations-zerg-ultralisk", Icon = "icon-zerg-ultralisk",
  Costs = {"time", 200, "minerals", 200, "gas", 200},
  Speed = 12, NumDirections = 32,
  DrawLevel = 40,
  SightRange = 5, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 3, BasicDamage = 20, PiercingDamage = 10, Missile = "missile-none",
  AnnoyComputerFactor = 55,
  MaxAttackRange = 1,
  Priority = 60,
  Points = 30,
  Demand = 6,
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
    "help", "zerg-units-attacked",
	"dead", "zerg-ultralisk-death"} } )


