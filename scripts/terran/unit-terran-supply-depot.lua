--
-- unit-terran-supply-depot
--

DefineAnimations("animations-terran-supply-depot", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-supply-depot", {
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

DefineUnitType("unit-terran-supply-depot", {
  Animations = "animations-terran-supply-depot", Icon = "icon-terran-supply-depot",
  Costs = {"time", 100, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-supply-depot",
  BurnPercent = 30,
  BurnDamageRate = 1,
  Speed = 0,
  DrawLevel = 50,
  BuilderOutside = true,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 100,
  Supply = 8,
  Corpse = "unit-destroyed-2x2-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  VisibleUnderFog = true, 
  Sounds = {
    "selected", "terran-supply-depot-selected",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

