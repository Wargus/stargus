--
-- unit-terran-bunker
--

DefineAnimations("animations-terran-bunker", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-bunker", {
  Files = {
    File = "terran/units/building construction medium.png",
    Size = {96, 96}},
  ShadowFiles = {
    File = "terran/units/building construction medium shadow.png",
    Size = {96, 96}},
  Constructions = {
   {Percent = 0,
    File = "construction",
    Frame = 0},
   {Percent = 20,
    File = "construction",
    Frame = 1},
   {Percent = 40,
    File = "construction",
    Frame = 2},
   {Percent = 60,
    File = "main",
    Frame = 1}}
})

DefineUnitType("unit-terran-bunker", { Name = "Bunker",
  Image = {"file", "terran/units/bunker.png", "size",  {96, 128}},
  Shadow = {"file", "terran/units/bunker shadow.png", "size",  {96, 128}},
  Animations = "animations-terran-bunker", Icon = "icon-terran-bunker",
  Costs = {"time", 200, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-bunker",
  Speed = 0,
  HitPoints = 350,
  DrawLevel = 50,
  TileSize = {3, 2}, BoxSize = {95, 63},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 15, AnnoyComputerFactor = 20,
  Points = 170,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  Building = true, VisibleUnderFog = true,
  AttackFromTransporter = true,
  CanTransport = {},
  MaxOnBoard = 4,
  Sounds = {
    "selected", "terran-bunker-selected",
    "ready", "terran-work-complete",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )
