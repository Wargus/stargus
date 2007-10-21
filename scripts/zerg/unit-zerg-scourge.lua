--
-- unit-zerg-scourge
--


DefineAnimations("animations-zerg-scourge", {
  Still = {
    "frame 0", "wait 2", "frame 17", "wait 2", "frame 34", "wait 2",
    "frame 51", "wait 2", "frame 68", "wait 2",
  },
  Move = {
    "unbreakable begin",
    "frame 0", "move 4", "wait 1", "frame 17", "move 3", "wait 1",
    "frame 34", "move 3", "wait 1", "frame 51", "move 3", "wait 1",
    "frame 68", "move 3", "wait 1", "frame 0", "move 4", "wait 1",
    "frame 17", "move 3", "wait 1", "frame 34", "move 3", "wait 1",
    "frame 51", "move 3", "wait 1", "frame 68", "move 3",
    "unbreakable end", "wait 1",
  },
  Attack = {"unbreakable begin", "attack", "sound zerg-scourge-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound zerg-scourge-death",
    --[[active overlay 41,0]] "wait 1", "unbreakable end", "wait 1",},
})


DefineUnitType("unit-zerg-scourge", { Name = "Scourge",
  Image = {"file", "zerg/units/scourge.png", "size", {48, 48}},
  Shadow = {"file", "zerg/units/scourge.png", "size", {48, 48}, "offset", {0, 42}},
  DrawLevel = 45, NumDirections = 32,
  Animations = "animations-zerg-scourge", Icon = "icon-zerg-scourge",
  Costs = {"time", 250, "minerals", 150, "gas", 100},
  Speed = 14,
  HitPoints = 120,
  DrawLevel = 60,
  TileSize = {1, 1}, BoxSize = {63, 63},--FIXME:wrong boxsize
  SightRange = 6, ComputerReactionRange = 8, PersonReactionRange = 6,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-zerg-scourge-glaive-wurm",
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-small",--FIXME:wrong explosion
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true, CanTargetAir = true,
  AirUnit = true,
  DetectCloak = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-scourge-selected",
    "acknowledge", "zerg-scourge-acknowledge",
    "ready", "zerg-scourge-ready",
    "help", "zerg-units-attacked",
    "dead", "zerg-scourge-death"} } )
