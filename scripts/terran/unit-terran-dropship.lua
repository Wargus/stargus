--
-- unit-terran-dropship
--

DefineAnimations("animations-terran-dropship", {
  Still = {"frame 0", "wait 125",--[[FIXME: shift down 79A2]]},
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound terran-dropship-death",
    --[[active overlay 332,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-terran-dropship", {
  -- Shadow = {"file", "terran/units/dropship.png", "size", {60, 60}, "offset", {0, 42}},
  Shadow = {"offset", {0, 42}, "scale", 1},
  DrawLevel = 45, NumDirections = 32,
  Animations = "animations-terran-dropship", Icon = "icon-terran-dropship",
  Costs = {"time", 250, "minerals", 400, "gas", 300},
  Speed = 14,
  DrawLevel = 60,
  MaxOnBoard = 8,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 6, ComputerReactionRange = 8, PersonReactionRange = 6,
  Armor = 5, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-small",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  RightMouseAction = "move",
  CanAttack = false,
  AirUnit = true,
  CanTransport = {},
  DetectCloak = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-dropship-selected",
    "acknowledge", "terran-dropship-acknowledge",
    "ready", "terran-dropship-ready",
    "help", "terran-units-attacked",
    "dead", "terran-dropship-death"} } )

