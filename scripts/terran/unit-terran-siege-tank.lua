--
-- unit-terran-siege-tank
--

DefineAnimations("animations-terran-siege-tank", {
  Still = {
    "frame 0", "wait 125",
  },
  Move = {"unbreakable begin",
    "move 4", "wait 1", "frame 0", "move 4", "wait 1", "frame 17",
    "move 4", "wait 1", "frame 34",
    --[[ FIXME: sub-tile movement ]]
    "move 4", "wait 1", "frame 0", "move 4", "wait 1", "frame 17",
    "move 4", "wait 1", "frame 34",
    "move 4", "wait 1", "frame 0", "move 4", "unbreakable end",
    "wait 1", "frame 17",
  },
  Attack = {
    "unbreakable begin", "sound terran-siege-tank-attack", "attack",
    "unbreakable end", "wait 1",
  },
  Death = {
    "unbreakable begin",
    --[[sound 317]] --[[active overlay 333,0]] "wait 3",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-terran-siege-tank", {
  Animations = "animations-terran-siege-tank", Icon = "icon-terran-siege-tank",
  Costs = {"time", 60, "minerals", 150, "gas", 100},
  Speed = 10,
  DrawLevel = 40,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-none",
  AnnoyComputerFactor = 55,
  MaxAttackRange = 1,
  Priority = 60,
  Points = 50,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-medium",
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-siege-tank-selected",
    "acknowledge", "terran-siege-tank-acknowledge",
    "ready", "terran-siege-tank-ready",
    "help", "terran-units-attacked",
    "dead", "terran-siege-tank-death"} } )

