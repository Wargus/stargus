--
-- unit-terran-science-vessel
--

DefineAnimations("animations-terran-science-vessel", {
  Still = {"frame 0", "wait 125",},
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "attack", "sound terran-science-vessel-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound terran-science-vessel-death",
    --[[active overlay 333,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-terran-science-vessel", {
  DrawLevel = 45,
  Animations = "animations-terran-science-vessel", Icon = "icon-terran-science-vessel",
  Costs = {"time", 250, "minerals", 100, "gas", 225},
  Speed = 14,
  DrawLevel = 60,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-none",
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-medium",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true, CanTargetAir = true,
  DetectCloak = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-science-vessel-selected",
    "acknowledge", "terran-science-vessel-acknowledge",
    "ready", "terran-science-vessel-ready",
    "help", "terran-units-attacked",
    "dead", "terran-science-vessel-death"} } )

