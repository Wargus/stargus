--
-- unit-zerg-hive
--


DefineAnimations("animations-zerg-hive", {
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 2", "frame 3", "wait 4",
    "frame 2", "wait 2", "frame 1", "wait 2", "frame 0", "wait 4",
  },
  Train = {
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-hive", {
  Animations = "animations-zerg-hive", Icon = "icon-zerg-hive",
  Costs = {"time", 255, "minerals", 300},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 0},
  Construction = "construction-zerg",
  Speed = 0,
  DrawLevel = 30,
  TileSize = {4, 3}, BoxSize = {126, 95},--FIXME: wrong size
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 35, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 8,
  RegenerationRate = 1,
--  ExplodeWhenKilled = "missle-zerg-rubble-large",
  Type = "land",
--  Corpse = "unit-zerg-rubble-large",
  BuilderLost = true,
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "distance", { Distance = 3, DistanceType = ">", Type = "unit-minerals1"} } },
  CanStore = {"gas", "minerals"},
  Sounds = {
    "selected", "zerg-hive-selected",
--    "ready", "town-hall-ready",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
