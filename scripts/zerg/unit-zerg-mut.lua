--
-- unit-zerg-mut
--

DefineAnimations("animations-zerg-mut", {
  Still = {"frame 0", "wait 125",--[[FIXME: shift down 79A2]]},
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "attack", "sound zerg-mut-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound zerg-mut-death",
    --[[active overlay 332,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-zerg-mut", { Name = "Wraith",
  Image = {"file", "terran/units/wraith.png", "size", {64, 64}},
  Shadow = {"file", "terran/units/wraith.png", "size", {64, 64}, "offset", {0, 42}},
  DrawLevel = 45, NumDirections = 32,
  Animations = "animations-zerg-mut", Icon = "icon-zerg-mut",
  Costs = {"time", 250, "minerals", 150, "gas", 100},
  Speed = 14,
  HitPoints = 120,
  DrawLevel = 60,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 6, ComputerReactionRange = 8, PersonReactionRange = 6,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-griffon-hammer",
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-small",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true, CanTargetAir = true,
  AirUnit = true,
  DetectCloak = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-mut-selected",
    "acknowledge", "zerg-mut-acknowledge",
    "ready", "zerg-mut-ready",
    "help", "basic human voices help 1",
    "dead", "zerg-mut-death"} } )
