



DefineAnimations("animations-zerg-hydralisk-death", {
  Death = {"unbreakable begin", "frame 0", "wait 40", "frame 1", "wait 40",
    "frame 2", "wait 40", "frame 3", "wait 40", "frame 4", "unbreakable end", "wait 1", },
})

DefineUnitType("unit-zerg-hydralisk-death", { Name = "DEAD HYDRLAISK",
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
    "frame 187", "wait 125",
  },
  Move = {"unbreakable begin",
    "move 6", "wait 1", "frame 136", "move 3", "wait 1", "frame 153",
    "move 3", "wait 1", "frame 0", "move 3", "wait 1", "frame 17",--FIXME:not original sc animations
    "move 5", "wait 1", "frame 34", "move 5", "wait 1", "frame 51",
    "move 4", "wait 1", "frame 68",
    --FIXME: sub-tile movement
    --[["move 8", "wait 1", "frame 85",
    "move 6", "wait 1", "frame 102", "move 4",
    "unbreakable end", "wait 1", "frame 119",]]
    "move 3", "unbreakable end", "wait 1", "frame 119",
	},
  Attack = {
    "unbreakable begin", "wait 5", "frame 68", "sound hydralisk-attack", "attack",
    "unbreakable end", "wait 5",
  },
  Death = {
    "unbreakable begin",
   "frame 208", "wait 3", "frame 209", "wait 3", "frame 210", "wait 3", "frame 211", "wait 3", "frame 212", "wait 3", "frame 213", "wait 3", "frame 214", "wait 3", "frame 215", "wait 3", "frame 216",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-zerg-hydralisk", { Name = "Hydralisk",
  Image = {"file", "zerg/units/hydralisk.png", "size", {128, 128}},
  Shadow = {"file", "zerg/units/hydralisk shadow.png", "size", {128, 128}, "offset", {0, 7}},
  Animations = "animations-zerg-hydralisk", Icon = "icon-zerg-hydralisk",
  Costs = {"time", 35, "minerals", 75, "gas", 25,},
  Speed = 0, NumDirections = 32,
  HitPoints = 80,
  DrawLevel = 40,
  TileSize = {1, 1}, BoxSize = {31, 31},--FIXME:wrong size
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
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-hydralisk-selected",
    "acknowledge", "zerg-hydralisk-acknowledgement",
    "ready", "zerg-hydralisk-ready",
    "help", "zerg-units-attacked",
	"dead", "zerg-hydralisk-death"} } )


