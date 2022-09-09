--
-- unit-terran-battlecruiser
--

DefineAnimations("animations-terran-battlecruiser", {
  Still = {"frame 0", "wait 125",},
  Move = {
    "unbreakable begin", -- accellerate
      "frame 0", "move 1", "wait 1", "frame 0", "move 2", "wait 1",
      "frame 0", "move 3", "wait 1", "frame 0", "move 2",
    "unbreakable end", "wait 1",
    "label fullspeed", "unbreakable begin", "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1", "frame 0", "move 3", "unbreakable end", "wait 1",
    "goto fullspeed",},
  Attack = {"unbreakable begin", "attack", "sound terran-battlecruiser-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound terran-battlecruiser-death",
    --[[active overlay 333,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-terran-battlecruiser", {
  DrawLevel = 45,
  Animations = "animations-terran-battlecruiser", Icon = "icon-terran-battlecruiser",
  Costs = {"time", 250, "minerals", 400, "gas", 300},
  Speed = 14,
  DrawLevel = 60,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-terran-battlecruiser-laser",
  AnnoyComputerFactor = 55,
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 6,
  ExplodeWhenKilled = "missile-terran-explosion-medium",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true, CanTargetAir = true,
  DetectCloak = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-battlecruiser-selected",
    "acknowledge", "terran-battlecruiser-acknowledge",
    "ready", "terran-battlecruiser-ready",
    "help", "terran-units-attacked",
    "dead", "terran-battlecruiser-death"} } )
