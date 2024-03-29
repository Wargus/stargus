--
-- unit-terran-armory
--

DefineAnimations("animations-terran-armory", {
  Still = {
    "frame 0", "wait 125",
  },
  Research = {--[[FIXME: active overlay 269]]
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-armory", {
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

DefineUnitType("unit-terran-armory", {
  Animations = "animations-terran-armory", Icon = "icon-terran-armory",
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-armory",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  DrawLevel = 50,
  BuilderOutside = true,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 30, AnnoyComputerFactor = 35,
  Points = 160,
  --Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  VisibleUnderFog = true, 
  Sounds = {
    "selected", "terran-armory-selected",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )
