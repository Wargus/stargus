--
-- unit-protoss-gateway
--

DefineAnimations("animations-protoss-gateway", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-protoss-gateway", {
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

DefineUnitType("unit-protoss-gateway", {
  Animations = "animations-protoss-gateway", Icon = "icon-protoss-gateway",
  Costs = {"time", 200, "minerals", 150},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-protoss-gateway",
  Speed = 0,
  DrawLevel = 50,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 30, AnnoyComputerFactor = 35,
  Points = 160,
  --Corpse = "unit-destroyed-3x3-place",
  --ExplodeWhenKilled = "missile-terran-explosion-large",
  BuilderOutside = true,  
  AutoBuildRate = 2,
  VisibleUnderFog = true, 
  BuildingRules = { { "distance", { Distance = 3, DistanceType = "<", Type = "unit-protoss-pylon"} } },
  Sounds = {
    "selected", "protoss-gateway-selected",
    "ready", "protoss-building-done",
    "help", "protoss-base-attacked",
    "dead", "protoss-explosion-large"} } )


DefineUnitType("unit-protoss-zealot", {})
DefineUnitType("unit-protoss-dragoon", {})
DefineUnitType("unit-protoss-high-templar", {})
DefineUnitType("unit-protoss-dark-templar", {})


DefineButton( { Pos = 1, Level = 0, Icon = "icon-protoss-zealot",
  Action = "train-unit", Value = "unit-protoss-zealot",
  Key = "z", Hint = "Warp in Zealot",
  ForUnit = {"unit-protoss-gateway"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-protoss-dragoon",
  Action = "train-unit", Value = "unit-protoss-dragoon",
  Key = "d", Hint = "Warp in Dragoon",
  ForUnit = {"unit-protoss-gateway"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-protoss-high-templar",
  Action = "train-unit", Value = "unit-protoss-high-templar",
  Key = "d", Hint = "Warp in High Templar",
  ForUnit = {"unit-protoss-gateway"} } )
  
  DefineButton( { Pos = 4, Level = 0, Icon = "icon-protoss-dark-templar",
  Action = "train-unit", Value = "unit-protoss-dark-templar",
  Key = "d", Hint = "Warp in Dark Templar",
  ForUnit = {"unit-protoss-gateway"} } )
