--
-- unit-terran-bunker
--

DefineAnimations("animations-terran-bunker", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-bunker", {
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

DefineUnitType("unit-terran-bunker", {
  Animations = "animations-terran-bunker", Icon = "icon-terran-bunker",
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-bunker",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  DrawLevel = 50,
  BuilderOutside = true,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 15, AnnoyComputerFactor = 20,
  Points = 170,
  --Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  VisibleUnderFog = true,
  AttackFromTransporter = true,
  CanTransport = {},
  MaxOnBoard = 4,
  Sounds = {
    "selected", "button",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

