--
-- unit-terran-missile-turret
--

DefineAnimations("animations-terran-missile-turret", {
  Still = {
    "frame 2", "wait 125",
  },
  Attack = {--[[FIXME: active overlay 297]]
    "frame 2", "wait 125",
  },
})

DefineConstruction("construction-terran-missile-turret", {
  Files = image_329_terran_tbldsml_var,
  ShadowFiles = image_329_terran_tbldsml_var,
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

DefineUnitType("unit-terran-missile-turret", {
  Animations = "animations-terran-missile-turret", Icon = "icon-terran-missile-turret",
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-missile-turret",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  DrawLevel = 50,
  BuilderOutside = true,
  Armor = 20, BasicDamage = 50, PiercingDamage = 0, Missile = "missile-small-cannon",
  MinAttackRange = 2, MaxAttackRange = 7,
  Priority = 40, AnnoyComputerFactor = 50,
  Points = 250,
  Corpse = "unit-destroyed-2x2-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true,
  VisibleUnderFog = true, 
  DetectCloak = true,
  Sounds = {
    "selected", "terran-missile-turret-selected",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

