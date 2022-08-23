--
-- -- unit-protoss-robotics-facility
--
DefineAnimations("animations-protoss-robotics-facility", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-protoss-robotics-facility", {
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

DefineUnitType("unit-protoss-robotics-facility", {
  Animations = "animations-protoss-robotics-facility", Icon = "icon-protoss-robotics-facility",
  Costs = {"time", 30, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-protoss-robotics-facility",
  Speed = 0,
  DrawLevel = 50,
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


DefineUnitType("unit-protoss-shuttle", {})
DefineUnitType("unit-protoss-reaver", {})
DefineUnitType("unit-protoss-observer", {})

DefineButton( { Pos = 1, Level = 0, Icon = "icon-protoss-shuttle",
  Action = "train-unit", Value = "unit-protoss-shuttle",
  Key = "z", Hint = "Warp in Shuttle",
  ForUnit = {"unit-protoss-robotics-facility"} } )
  
DefineButton( { Pos = 2, Level = 0, Icon = "icon-protoss-reaver",
  Action = "train-unit", Value = "unit-protoss-reaver",
  Key = "z", Hint = "Warp in Reaver",
  ForUnit = {"unit-protoss-robotics-facility"} } )
  
DefineButton( { Pos = 3, Level = 0, Icon = "icon-protoss-observer",
  Action = "train-unit", Value = "unit-protoss-observer",
  Key = "z", Hint = "Warp in Observer",
  ForUnit = {"unit-protoss-robotics-facility"} } )
