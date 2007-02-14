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
    File = "terran/units/building construction large.png",
    Size = {160, 128}},
  ShadowFiles = {
    File = "terran/units/building construction large shadow.png",
    Size = {128, 128}},
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

DefineUnitType("unit-terran-command-center", { Name = "Command Center",
  Image = {"file", "terran/units/command center.png", "size", {128, 160}},
  Shadow = {"file", "terran/units/command center shadow.png", "size", {128, 160}},
  Animations = "animations-terran-command-center", Icon = "icon-terran-command-center",
  Costs = {"time", 255, "minerals", 400},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-command-center",
  Speed = 0,
  HitPoints = 1500,
  DrawLevel = 50,
  TileSize = {4, 3}, BoxSize = {126, 95},
  SightRange = 1,
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
--    "ready", "town-hall-ready",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )


DefineUnitType("unit-terran-scv", {})

DefineButton( { Pos = 1, Level = 0, Icon = "icon-terran-scv",
  Action = "train-unit", Value = "unit-terran-scv",
  Key = "s", Hint = "Build ~!SCV",
  ForUnit = {"unit-terran-command-center"} } )

--[[
DefineButton( { Pos = 7, Level = 0, Icon = "icon-terran-comsat-station",
  Action = "train-unit", Value = "unit-terran-comsat-station",
  Key = "c", Hint = "Comsat Station",
  ForUnit = {"unit-terran-command-center"} } )

DefineButton( { Pos = 8, Level = 0, Icon = "icon-terran-nuclear-silo",
  Action = "train-unit", Value = "unit-terran-nuclear-silo",
  Key = "c", Hint = "Nuclear Silo",
  ForUnit = {"unit-terran-command-center"} } )
]]
