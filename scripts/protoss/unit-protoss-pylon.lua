--
-- unit-protoss-pylon
--

DefineAnimations("animations-protoss-pylon", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-protoss-pylon", {
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

DefineUnitType("unit-protoss-pylon", { Name = "Supply Depot",
  Image = {"file", "graphics/protoss/units/pylon.png", "size", {64, 64}},
  Shadow = {"file", "graphics/protoss/units/ppyshad.png", "size", {64, 64}},
  Animations = "animations-protoss-pylon", Icon = "icon-protoss-pylon",
  Costs = {"time", 100, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-protoss-pylon",
  Speed = 0,
  HitPoints = 600,
  DrawLevel = 50,
  TileSize = {2, 2}, BoxSize = {63, 63},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 100,
  BuilderOutside = true,
  AutoBuildRate = 30,
  Supply = 8,
  Corpse = "unit-destroyed-2x2-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  Sounds = {
    "selected", "protoss-pylon-selected",
--    "acknowledge", "farm-acknowledge",
   "ready", "protoss-building-done",
    "help", "protoss-base-attacked",
    "dead", "explosion-protoss-large"} } )

