
--
-- -- unit-protoss-fleet-beacon
--
DefineAnimations("animations-protoss-fleet-beacon", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-protoss-fleet-beacon", {
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

DefineUnitType("unit-protoss-fleet-beacon", {
  Animations = "animations-protoss-stargate", Icon = "icon-protoss-fleet-beacon",
  Costs = {"time", 30, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-protoss-fleet-beacon",
  Speed = 0,
  DrawLevel = 50,
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
