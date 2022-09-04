--
-- unit-protoss-observer
--


DefineAnimations("animations-protoss-observer-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 2", --[[ active overlay 58 ]]
    "wait 1", "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-protoss-observer-death", { Name = "Dead Overlord",
  Image = image_unit_zerg_zovdeath,
  Animations = "animations-zerg-overlord-death", Icon = "icon-zerg-overlord",
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Vanishes = true,
  Sounds = {} } )


DefineAnimations("animations-protoss-observer", {
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
    --"sound zerg-overlord-death", "wait 1",
  },
})

DefineUnitType("unit-protoss-observer", {
  Animations = "animations-protoss-observer", Icon = "icon-protoss-observer",
  Costs = {"time", 45, "minerals", 100},
  RepairHp = 4,
  Speed = 20, 
  DrawLevel = 45,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 0,
  DetectCloak = true,
  --CanTransport = {},
  --MaxOnBoard = 6,
  --Corpse = "unit-zerg-overlord-death",
  SelectableByRectangle = true,
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  Sounds = {
    "selected", "protoss-observer-selected",
    "acknowledge", "protoss-observer-acknowledge",
    "ready", "protoss-observer-ready",
    "help", "protoss-observer-attacked",
    "dead", "protoss-observer-death"} } )

