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

DefineUnitType("unit-terran-comsat-station", {
  Animations = "animations-terran-comsat-station", Icon = "icon-terran-comsat-station",
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
--  Construction = "construction-terran-comsat-station",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  DrawLevel = 50,
  BuilderOutside = true,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 35, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 10,
  Corpse = "unit-destroyed-4x4-place",
  ExplodeWhenKilled = "missile-terran-explosion-small",
  VisibleUnderFog = true, 
  BuildingRules = { { "addon", { OffsetX = 4, OffsetY = -5, Type = "unit-terran-command-center"}}},
  Sounds = {
    "selected", "button",
--    "ready", "",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

