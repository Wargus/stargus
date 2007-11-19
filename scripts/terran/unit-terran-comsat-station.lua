--
-- unit-terran-command-center
--

DefineAnimations("animations-terran-comsat-station", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})

DefineUnitType("unit-terran-comsat-station", { Name = "Comsat Station",
  Image = {"file", "terran/units/comsat station.png", "size", {128, 64}},
  Shadow = {"file", "terran/units/comsat station shadow.png", "size", {128, 64}},
  Animations = "animations-terran-comsat-station", Icon = "icon-terran-comsat-station",
  Costs = {"time", 75, "minerals", 50},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
--  Construction = "construction-terran-comsat-station",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  HitPoints = 1500,
  DrawLevel = 50,
  TileSize = {2, 2}, BoxSize = {55, 55},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 35, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 10,
  Corpse = "unit-destroyed-4x4-place",
  ExplodeWhenKilled = "missile-terran-explosion-small",
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "addon", { OffsetX = 4, OffsetY = -5, Type = "unit-terran-command-center"}}},
  Sounds = {
    "selected", "button",
--    "ready", "",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

