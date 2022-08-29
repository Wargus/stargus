--
-- unit-terran-barracks
--

DefineAnimations("animations-terran-barracks", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {
    "frame 7", "wait 4", "frame 8", "wait 2", "frame 7", "wait 2",
    "frame 8", "wait 2", "frame 7", "wait 4", "frame 8", "wait 2",
    "frame 7", "wait 2",
  },
})

DefineConstruction("construction-terran-barracks", {
  Files = {
    File = image_unit_terran_tbldlrg_file,
    Size = image_unit_terran_tbldlrg_size},
  ShadowFiles = {
    File = image_unit_terran_tbldlrg_file,
    Size = image_unit_terran_tbldlrg_size},
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

DefineUnitType("unit-terran-barracks", {
  Animations = "animations-terran-barracks", Icon = "icon-terran-barracks",
  Costs = {"time", 200, "minerals", 150},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-barracks",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  DrawLevel = 50,
  BuilderOutside = true,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 30, AnnoyComputerFactor = 35,
  Points = 160,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  Sounds = {
    "selected", "button",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )


DefineUnitType("unit-terran-marine", {})
DefineUnitType("unit-terran-firebat", {})
DefineUnitType("unit-terran-ghost", {})

DefineButton( { Pos = 1, Level = 0, Icon = "icon-terran-marine",
  Action = "train-unit", Value = "unit-terran-marine",
  Key = "m", Hint = "Train ~!Marine",
  ForUnit = {"unit-terran-barracks"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-terran-firebat",
  Action = "train-unit", Value = "unit-terran-firebat",
  Key = "f", Hint = "Train ~!Firebat",
  ForUnit = {"unit-terran-barracks"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-terran-ghost",
  Action = "train-unit", Value = "unit-terran-ghost",
  Key = "g", Hint = "Train ~!Ghost",
  ForUnit = {"unit-terran-barracks"} } )
