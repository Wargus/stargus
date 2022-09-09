--
-- unit-protoss-pylon
--

DefineAnimations("animations-protoss-pylon", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-protoss-pylon", {
  Files = image_327_terran_tbldmed_var,
  ShadowFiles = image_327_terran_tbldmed_var,
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

DefineUnitType("unit-protoss-pylon", {
  Animations = "animations-protoss-pylon", Icon = "icon-protoss-pylon",
  Costs = {"time", 100, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-protoss-pylon",
  Speed = 0,
  DrawLevel = 50,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 100,
  BuilderOutside = true,
  AutoBuildRate = 30,
  Supply = 8,
  Corpse = "unit-destroyed-2x2-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  VisibleUnderFog = true, 
  Sounds = {
    "selected", "protoss-pylon-selected",
--    "acknowledge", "farm-acknowledge",
   "ready", "protoss-building-done",
    "help", "protoss-base-attacked",
    "dead", "explosion-protoss-large"} } )

