--
-- unit-zerg-hydralisk-den
--


DefineAnimations("animations-zerg-hydralisk-den", {
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 4", "frame 1", "wait 2",
    "frame 0", "wait 4",
  },
})


DefineUnitType("unit-zerg-hydralisk-den", {
  Animations = "animations-zerg-hydralisk-den", Icon = "icon-zerg-hydralisk-den",
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  DrawLevel = 30,
  Armor = 20, BasicDamage = 20, PiercingDamage = 5, Missile = "missile-none",
  Priority = 15, AnnoyComputerFactor = 20,
  Points = 170,
  --Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  RightMouseAction = "attack",
  RegenerationRate = 1,
  CanAttack = true,
  BuilderLost = true,
  CanTargetLand = true,
  VisibleUnderFog = true,
  Sounds = {
    "selected", "zerg-hydralisk-den-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
