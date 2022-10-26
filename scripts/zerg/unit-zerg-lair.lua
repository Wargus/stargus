--
-- unit-zerg-lair
--


DefineAnimations("animations-zerg-lair", {
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 2", "frame 3", "wait 4",
    "frame 2", "wait 2", "frame 1", "wait 2", "frame 0", "wait 4",
  },
  Train = {
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-lair", {
  Animations = "animations-zerg-lair", Icon = "icon-zerg-lair",
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 0},
  Construction = "construction-zerg",
  Speed = 0,
  DrawLevel = 30,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 35, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 8,
  RegenerationRate = 1,
--  ExplodeWhenKilled = "missle-zerg-rubble-large",
--  Corpse = "unit-zerg-rubble-large",
  BuilderLost = true,
  VisibleUnderFog = true, 
  BuildingRules = { { "distance", { Distance = 3, DistanceType = ">", Type = "unit-minerals1"} } },
  CanStore = {"gas", "minerals"},
  Sounds = {
    "selected", "zerg-lair-selected",
--    "ready", "town-hall-ready",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
