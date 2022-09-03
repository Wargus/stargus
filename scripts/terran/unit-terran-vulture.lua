--
-- unit-terran-vulture
--

DefineAnimations("animations-terran-vulture", {
  Still = {
    "frame 0", "wait 125",
  },
  Move = {
    "unbreakable begin", -- accellerate
      "frame 0", "move 1", "wait 1", "frame 0", "move 1", "wait 1",
      "frame 0", "move 1", "wait 1", "frame 0", "move 1", "wait 1",
      "frame 0", "move 2", "wait 1", "frame 0", "move 2", "wait 1",
    "unbreakable end", "wait 1",
    "unbreakable begin", -- accellerate 2
      "frame 0", "move 2", "wait 1", "frame 0", "move 3", "wait 1", "frame 0", "move 3",
    "unbreakable end", "wait 1",
    "label fullspeed", "unbreakable begin", "frame 0", "move 4", "wait 1", "frame 0", "move 4", "unbreakable end", "wait 1",
    "goto fullspeed",
  },
  Attack = {
    "unbreakable begin", "attack",
    "unbreakable end", "wait 1",
  },
--
  Death = {
    "unbreakable begin",
    "sound terran-vulture-death", --[[active overlay 332,0]] "wait 3",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-terran-vulture", {
  Animations = "animations-terran-vulture", Icon = "icon-terran-vulture",
  Costs = {"time", 60, "minerals", 75},
  Speed = 10, NumDirections = 32,
  DrawLevel = 40,
  TileSize = {5, 5}, BoxSize = {47, 47}, Offset = {1, -2}, BoxOffset = {1, -2},
  BoardSize = 2,
  SightRange = 16, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-terran-vulture-grenade",
  AnnoyComputerFactor = 55,
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
    "selected", "terran-vulture-selected",
    "acknowledge", "terran-vulture-acknowledge",
    "ready", "terran-vulture-ready",
    "help", "terran-units-attacked",} } )

-- TODO: temporarily Jim is the same as any other vulture
CopyUnitType("unit-terran-vulture", "Jim-Raynor-(Vulture)")
DefineUnitType("Jim-Raynor-(Vulture)", { Name = "Jim Raynor" })
