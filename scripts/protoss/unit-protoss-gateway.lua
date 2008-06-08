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

DefineUnitType("unit-protoss-gateway", { Name = "Protoss Gateway",
  Image = {"file", "protoss/units/gateway.png", "size", {128, 160}},
  Shadow = {"file", "protoss/units/pgashad.png", "size", {128, 160}},
  Animations = "animations-protoss-gateway", Icon = "icon-protoss-gateway",
  Costs = {"time", 200, "minerals", 150},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-protoss-gateway",
  Speed = 0,
  HitPoints = 1000,
  DrawLevel = 50,
  TileSize = {4, 3}, BoxSize = {127, 95},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 30, AnnoyComputerFactor = 35,
  Points = 160,
  --Corpse = "unit-destroyed-3x3-place",
  --ExplodeWhenKilled = "missile-terran-explosion-large",
  BuilderOutside = true,  
  AutoBuildRate = 2,
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "distance", { Distance = 3, DistanceType = "<", Type = "unit-protoss-pylon"} } },
  Sounds = {
    "selected", "protoss-gateway-selected",
    "ready", "protoss-building-done",
    "help", "protoss-base-attacked",
    "dead", "protoss-explosion-large"} } )


DefineUnitType("unit-protoss-zealot", {})
DefineUnitType("unit-protoss-dragoon", {})


DefineButton( { Pos = 1, Level = 0, Icon = "icon-protoss-zealot",
  Action = "train-unit", Value = "unit-protoss-zealot",
  Key = "z", Hint = "Warp in Zealot",
  ForUnit = {"unit-protoss-gateway"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-protoss-dragoon",
  Action = "train-unit", Value = "unit-protoss-dragoon",
  Key = "d", Hint = "Warp in Dragoon",
  ForUnit = {"unit-protoss-gateway"} } )
