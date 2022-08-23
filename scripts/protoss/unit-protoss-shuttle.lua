--
-- unit-protoss-shuttle
--


DefineAnimations("animations-protoss-shuttle-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 2", --[[ active overlay 58 ]]
    "wait 1", "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-protoss-shuttle-death", { Name = "Dead Shuttle",
  Image = {"file", "zerg/units/overlord death.png", "size", {72, 72}},
  Animations = "animations-zerg-overlord-death", Icon = "icon-zerg-overlord",
  NumDirections = 1,
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Vanishes = true,
  Sounds = {} } )


DefineAnimations("animations-protoss-shuttle", {
  Still = {
    "frame 0", "wait 125",
  },
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "unbreakable end", "wait 1",},
  Death = {
    "sound zerg-overlord-death", "wait 1",
  },
})


DefineUnitType("unit-protoss-shuttle", {
  Animations = "animations-protoss-shuttle", Icon = "icon-protoss-shuttle",
  Costs = {"time", 45, "minerals", 100},
  RepairHp = 4,
  Speed = 0, 
  NumDirections = 16,
  DrawLevel = 45,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 9,
  DetectCloak = true,
  CanTransport = {},
  MaxOnBoard = 6,
  --Corpse = "unit-zerg-overlord-death",
  SelectableByRectangle = true,
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  Sounds = {
    "selected", "protoss-shuttle-selected",
    "acknowledge", "protoss-shuttle-acknowledge",
    "ready", "protoss-shuttle-ready",
    "help", "protoss-units-attacked",
    "dead", "protoss-shuttle-death"} } )
