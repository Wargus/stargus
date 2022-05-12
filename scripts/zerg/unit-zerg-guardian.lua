--
-- unit-zerg-guardian
--


DefineAnimations("animations-zerg-guardian-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 2", --[[ active overlay 58 ]]
    "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-guardian-death", { Name = "Dead Guardian",
  Animations = "animations-zerg-guardian-death", Icon = "icon-zerg-guardian",
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


DefineAnimations("animations-zerg-guardian", {
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
  Attack = {"unbreakable begin", "attack", "sound zerg-guardian-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound zerg-guardian-death",
    --[[active overlay 41,0]] "wait 1", "unbreakable end", "wait 1",},
})


DefineUnitType("unit-zerg-guardian", { Name = "Guardian",
  Image = {"file", "zerg/units/guardian.png", "size", {96, 96}},
  Shadow = {"file", "zerg/units/guardian.png", "size", {96, 96}, "offset", {0, 42}},
  DrawLevel = 45, NumDirections = 32,
  Animations = "animations-zerg-guardian", Icon = "icon-zerg-guardian",
  Costs = {"time", 250, "minerals", 150, "gas", 200},
  Speed = 14,
  HitPoints = 150,
  DrawLevel = 60,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 11, ComputerReactionRange = 8, PersonReactionRange = 8,
  Armor = 2, BasicDamage = 20, PiercingDamage = 16, --, Missile = "missile-zerg-guardian-glaive-wurm",
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 2,
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true, CanTargetAir = true,
  AirUnit = true,
  DetectCloak = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-guardian-selected",
    "acknowledge", "zerg-guardian-acknowledgement",
    "ready", "zerg-guardian-ready",
    "help", "zerg-units-attacked",
    "dead", "zerg-guardian-death"} } )

