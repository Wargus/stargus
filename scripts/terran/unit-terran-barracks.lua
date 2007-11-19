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

DefineUnitType("unit-terran-barracks", { Name = "Barracks",
  Image = {"file", "terran/units/barracks.png", "size", {192, 160}},
  Shadow = {"file", "terran/units/barracks shadow.png", "size", {192, 160}},
  Animations = "animations-terran-barracks", Icon = "icon-terran-barracks",
  Costs = {"time", 200, "minerals", 150},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-barracks",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  HitPoints = 1000,
  DrawLevel = 50,
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
