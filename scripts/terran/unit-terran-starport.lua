--
-- unit-terran-starport
--

DefineAnimations("animations-terran-starport", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {--[[FIXME: active overlay 320]]
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-starport", {
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
    Frame = 5}}
})

DefineUnitType("unit-terran-starport", { Name = "Starport",
  Shadow = {"file", "terran/units/starport shadow.png", "size", {128, 160}},
  Animations = "animations-terran-starport", Icon = "icon-terran-starport",
  Costs = {"time", 200, "minerals", 150, "gas", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-starport",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  DrawLevel = 50,
  BuilderOutside = true,
  TileSize = {4, 3}, BoxSize = {127, 95},
  SightRange = 1,
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

DefineUnitType("unit-terran-wraith", {})
DefineUnitType("unit-terran-dropship", {})
DefineUnitType("unit-terran-science-vessel", {})
DefineUnitType("unit-terran-battlecruiser", {})

DefineButton( { Pos = 1, Level = 0, Icon = "icon-terran-wraith",
  Action = "train-unit", Value = "unit-terran-wraith",
  Key = "w", Hint = "Build ~!Wraith",
  ForUnit = {"unit-terran-starport"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-terran-dropship",
  Action = "train-unit", Value = "unit-terran-dropship",
  Key = "d", Hint = "Build ~!Dropship",
  ForUnit = {"unit-terran-starport"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-terran-science-vessel",
  Action = "train-unit", Value = "unit-terran-science-vessel",
  Key = "v", Hint = "Build Science ~!Vessel",
  ForUnit = {"unit-terran-starport"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-terran-battlecruiser",
  Action = "train-unit", Value = "unit-terran-battlecruiser",
  Key = "b", Hint = "Build ~!Battlecruiser",
  ForUnit = {"unit-terran-starport"} } )

