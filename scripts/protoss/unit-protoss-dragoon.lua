--
-- unit-protoss-dragoon
--


DefineAnimations("animations-protoss-dragoon", {
   Still = {
    "frame 0", "wait 125",
  },
  Move = {"unbreakable begin",
    "move 4", "wait 1", "frame 136",
    "move 6", "wait 1", "frame 153",
    "move 8", "wait 1", "frame 170",
    "move 8", "wait 1", "frame 187",
    "move 2", "wait 1", "frame 204",
    "move 2", "wait 1", "frame 221",
    "move 6", "wait 1", "frame 238",
    "move 6", "wait 1", "frame 255",
    "unbreakable end",
  },
  Attack = {
    "unbreakable begin", "frame 272", "wait 2", "frame 289", "wait 2", "frame 306", "wait 2", "frame 323",
    "wait 2", "frame 340", "wait 2", "frame 357", "attack",
    "unbreakable end", "wait 2",
  },
  Death = {
    "unbreakable begin",
    "frame 408", "wait 2", "frame 409", "wait 2", "frame 410", "wait 2", "frame 411", "wait 2", "frame 412",
    "wait 2", "frame 413", "wait 2", "frame 414",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-protoss-dragoon", { Name = "Dragoon",
  Image = {"file", "protoss/units/dragoon.png", "size", {96,96}},
  Shadow = {"file", "protoss/units/pdrshad.png", "size", {96,96}, "offset", {0, 7}},
  Animations = "animations-protoss-dragoon", Icon = "icon-protoss-dragoon",
  Costs = {"time", 60, "minerals", 75},
  Speed = 10, NumDirections = 32,
  HitPoints = 80,
  DrawLevel = 40,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 4, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 2, BasicDamage = 10, PiercingDamage = 3, Missile = "missile-none",
  MaxAttackRange = 2,
  Priority = 60,
  Points = 50,
  Demand = 2,
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "protoss-dragoon-selected",
    "acknowledge", "protoss-dragoon-acknowledge",
    "ready", "protoss-dragoon-ready",
    "help", "protoss-units-attacked",} } )

