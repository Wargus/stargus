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

DefineUnitType("unit-terran-factory", { Name = "Factory",
  Image = {"file", "terran/units/factory.png", "size",  {128, 160}},
  Shadow = {"file", "terran/units/factory shadow.png", "size",  {128, 160}},
  Animations = "animations-terran-factory", Icon = "icon-terran-factory",
  Costs = {"time", 200, "minerals", 200, "gas", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-factory",
  Speed = 0,
  HitPoints = 1250,
  DrawLevel = 50,
  TileSize = {4, 3}, BoxSize = {127, 95},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 15, AnnoyComputerFactor = 20,
  Points = 170,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  Sounds = {
    "selected", "terran-factory-selected",
--    "ready", "human-blacksmith-ready",
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
