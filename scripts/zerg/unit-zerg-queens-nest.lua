--
-- unit-zerg-queens-nest
--


DefineAnimations("animations-zerg-queens-nest", {
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 2", "frame 1", "wait 2",
    "frame 0", "wait 2",
  },
})


DefineUnitType("unit-zerg-queens-nest", {
  Animations = "animations-zerg-queens-nest", Icon = "icon-zerg-queens-nest",
  Costs = {"time", 200, "minerals", 100, "gas", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  DrawLevel = 30,
  Armor = 20, BasicDamage = 20, PiercingDamage = 5, Missile = "missile-none",
  Priority = 15, AnnoyComputerFactor = 20,
  Points = 170,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  RightMouseAction = "attack",
  RegenerationRate = 1,
  CanAttack = true,
  BuilderLost = true,
  CanTargetLand = true,
  Building = true, VisibleUnderFog = true,
  Sounds = {
    "selected", "zerg-queens-nest-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
