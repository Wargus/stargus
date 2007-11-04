--
-- unit-terran-battlecruiser
--

DefineAnimations("animations-terran-battlecruiser", {
  Still = {"frame 0", "wait 125",},
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "attack", "sound terran-battlecruiser-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound terran-battlecruiser-death",
    --[[active overlay 333,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-terran-battlecruiser", { Name = "Battlecruiser",
  Image = {"file", "terran/units/battlecruiser.png", "size", {120, 120}},
  Shadow = {"file", "terran/units/battlecruiser.png", "size", {120, 120}, "offset", {0, 42}},
  DrawLevel = 45, NumDirections = 32,
  Animations = "animations-terran-battlecruiser", Icon = "icon-terran-battlecruiser",
  Costs = {"time", 250, "minerals", 400, "gas", 300},
  Speed = 14,
  HitPoints = 500,
  DrawLevel = 60,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 6, ComputerReactionRange = 8, PersonReactionRange = 6,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-terran-battlecruiser-laser",
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 6,
  ExplodeWhenKilled = "missile-terran-explosion-medium",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true, CanTargetAir = true,
  AirUnit = true,
  DetectCloak = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-battlecruiser-selected",
    "acknowledge", "terran-battlecruiser-acknowledge",
    "ready", "terran-battlecruiser-ready",
    "help", "terran-units-attacked",
    "dead", "terran-battlecruiser-death"} } )
