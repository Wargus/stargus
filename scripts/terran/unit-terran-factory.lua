--
-- unit-terran-factory
--

DefineAnimations("animations-terran-factory", {
  Still = {
    "frame 0", "wait 125",
  },
  Research = {--[[FIXME: active overlay 286]]
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-factory", {
  Files = image_325_terran_tbldlrg_var,
  ShadowFiles = image_325_terran_tbldlrg_var,
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

DefineUnitType("unit-terran-factory", {
  Animations = "animations-terran-factory", Icon = "icon-terran-factory",
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-factory",
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
  Sounds = {
    "selected", "terran-factory-selected",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

DefineUnitType("unit-terran-vulture", {})
DefineUnitType("unit-terran-siege-tank", {})
DefineUnitType("unit-terran-goliath", {})

DefineButton( { Pos = 1, Level = 0, Icon = "icon-terran-vulture",
  Action = "train-unit", Value = "unit-terran-vulture",
  Key = "v", Hint = "Build ~!Vulture",
  ForUnit = {"unit-terran-factory"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-terran-siege-tank",
  Action = "train-unit", Value = "unit-terran-siege-tank",
  Key = "t", Hint = "Build Siege ~!Tank",
  ForUnit = {"unit-terran-factory"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-terran-goliath",
  Action = "train-unit", Value = "unit-terran-goliath",
  Key = "g", Hint = "Build ~!Goliath",
  ForUnit = {"unit-terran-factory"} } )

