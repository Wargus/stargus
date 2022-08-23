--
-- unit-terran-goliath
--


DefineAnimations("animations-terran-goliath", {
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
    "unbreakable begin", "sound terran-goliath-attack", "attack",
    "unbreakable end", "wait 1",
  },
  Death = {
    "unbreakable begin",
    --[[sound 8]] --[[active overlay 332,0]] "wait 3",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-terran-goliath", {
  Animations = "animations-terran-goliath", Icon = "icon-terran-goliath",
  Costs = {"time", 60, "minerals", 100, "gas", 50},
  Speed = 10, NumDirections = 32,
  DrawLevel = 40,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-none",
  AnnoyComputerFactor = 55,
  MaxAttackRange = 1,
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
    "selected", "terran-goliath-selected",
    "acknowledge", "terran-goliath-acknowledge",
    "ready", "terran-goliath-ready",
    "help", "terran-units-attacked",
    "dead", "terran-goliath-death"} } )

