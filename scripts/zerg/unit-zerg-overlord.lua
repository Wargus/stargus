--
-- unit-terran-dropship
--

DefineAnimations("animations-zerg-overlord", {
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

DefineUnitType("unit-zerg-overlord", { Name = "Overlord",
  Image = {"file", "zerg/units/overlord.png", "size", {84, 84}},
  Shadow = {"file", "zerg/units/overlord.png", "size", {84, 84}, "offset", {0, 42}},
  DrawLevel = 45, NumDirections = 32,
  Animations = "animations-zerg-overlord", Icon = "icon-zerg-overlord",
  Costs = {"time", 250, "minerals", 100, "gas", 0},
  Speed = 14,
  HitPoints = 200,
  DrawLevel = 60,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 6, ComputerReactionRange = 8, PersonReactionRange = 6,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-none",
  Priority = 65,
  Points = 150,
  Demand = 2,
  Supply = 8,
  ExplodeWhenKilled = "missile-terran-explosion-small",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  RightMouseAction = "attack",
  CanAttack = true,
  AirUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-dropship-selected",
    "acknowledge", "terran-dropship-acknowledge",
    "ready", "terran-dropship-ready",
    "help", "basic human voices help 1",
    "dead", "terran-dropship-death"} } )
