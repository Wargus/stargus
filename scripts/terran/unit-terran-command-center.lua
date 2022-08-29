--
-- unit-terran-command-center
--

DefineAnimations("animations-terran-command-center", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-command-center", {
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

DefineUnitType("unit-terran-command-center", {
  Animations = "animations-terran-command-center", Icon = "icon-terran-command-center",
  Costs = {"time", 255, "minerals", 400},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-command-center",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  DrawLevel = 50,
  BuilderOutside = true,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 35, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 10,
  Corpse = "unit-destroyed-4x4-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "distance", { Distance = 3, DistanceType = ">", Type = "unit-minerals1"} } },
  CanStore = {"gas", "minerals"},
  Sounds = {
    "selected", "button",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )


DefineUnitType("unit-terran-scv", {})
DefineUnitType("unit-terran-comsat-station", {})

DefineButton( { Pos = 1, Level = 0, Icon = "icon-terran-scv",
  Action = "train-unit", Value = "unit-terran-scv",
  Key = "s", Hint = "Build ~!SCV",
  ForUnit = {"unit-terran-command-center"} } )
  
DefineButton( { Pos = 7, Level = 0, Icon = "icon-terran-comsat-station",
  Action = "train-unit", Value = "unit-terran-comsat-station",
  Key = "c", Hint = "Comsat Station",
  ForUnit = {"unit-terran-command-center"} } )
--[[
DefineButton( { Pos = 8, Level = 0, Icon = "icon-terran-nuclear-silo",
  Action = "train-unit", Value = "unit-terran-nuclear-silo",
  Key = "c", Hint = "Nuclear Silo",
  ForUnit = {"unit-terran-command-center"} } )
]]
