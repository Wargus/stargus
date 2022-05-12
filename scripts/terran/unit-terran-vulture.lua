--
-- unit-terran-vulture
--

DefineAnimations("animations-terran-vulture", {
  Still = {
    "frame 0", "wait 125",
  },
  Move = {"unbreakable begin",
    "move 4", "wait 1", "frame 0", "move 4", "wait 1", "frame 0",
    "move 4", "wait 1", "frame 0", "move 4", "wait 1", "frame 0",
    "move 4", "wait 1", "frame 0", "move 4", "wait 1", "frame 0",
    "move 4", "wait 1", "frame 0", "move 4", "unbreakable end",
    "wait 1", "frame 0",},
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

DefineUnitType("unit-terran-vulture", { Name = "Vulture",
  Shadow = {"file", "terran/units/vulture.png", "size", {100, 100}, "offset", {0, 7}},
  Animations = "animations-terran-vulture", Icon = "icon-terran-vulture",
  Costs = {"time", 60, "minerals", 75},
  Speed = 10, NumDirections = 32,
  HitPoints = 80,
  DrawLevel = 40,
  TileSize = {1, 1}, BoxSize = {31, 31},
  BoardSize = 2,
  SightRange = 4, ComputerReactionRange = 6, PersonReactionRange = 4,
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
