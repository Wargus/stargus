--
-- -- unit-protoss-stargate
--
DefineAnimations("animations-protoss-stargate", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-protoss-stargate", {
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

DefineUnitType("unit-protoss-stargate", { Name = "Stargate",
  Image = {"file", "protoss/units/stargate.png", "size", {128, 160}},
  Shadow = {"file", "protoss/units/psgshad.png", "size", {128, 160}},
  Animations = "animations-protoss-stargate", Icon = "icon-protoss-stargate",
  Costs = {"time", 30, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-protoss-stargate",
  Speed = 0,
  HitPoints = 1000,
  DrawLevel = 50,
  TileSize = {3, 2}, BoxSize = {95, 63},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 30, AnnoyComputerFactor = 35,
  Points = 160,
  BuilderOutside = true,
  AutoBuildRate = 2,
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "distance", { Distance = 3, DistanceType = "<", Type = "unit-protoss-pylon"} } },
  Sounds = {
    "selected", "protoss-cybernetics-core-selected",
    "ready", "protoss-building-done",
    "help", "protoss-base-attacked",
    "dead", "protoss-explosion-large"} } )

--DefineUnitType("unit-protoss-scout", {})

--DefineButton( { Pos = 1, Level = 0, Icon = "icon-protoss-scout",
--  Action = "train-unit", Value = "unit-protoss-scout",
--  Key = "z", Hint = "Warp in Scout",
--  ForUnit = {"unit-protoss-stargate"} } )
