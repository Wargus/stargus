--
-- unit-terran-vulture
--


DefineAnimations("animations-protoss-dragoon", {
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
    "unbreakable begin", "sound hydralisk-attack", "attack",
    "unbreakable end", "wait 1",
  },
  Death = {
    "unbreakable begin",
    --[[sound 8]] --[[active overlay 332,0]] "wait 3",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-protoss-dragoon", { Name = "Dragoon",
--  Image = {"file", "zerg/units/hydralisk.png", "size", {128, 128}},
--  Shadow = {"file", "zerg/units/hydralisk.png", "size", {128, 128}, "offset", {0, 7}},
  Image = {"file", "protoss/units/dragoon.png", "size", {96,96}},
  Shadow = {"file", "protoss/units/pdrshad.png", "size", {96,96}, "offset", {0, 7}},
  Animations = "animations-protoss-dragoon", Icon = "icon-terran-bunker",
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
  ExplodeWhenKilled = "missile-terran-explosion-small",
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-hydralisk-selected",
    "acknowledge", "zerg-hydralisk-acknowledge",
    "ready", "zerg-hydralisk-ready",
    "help", "basic human voices help 1",} } )


