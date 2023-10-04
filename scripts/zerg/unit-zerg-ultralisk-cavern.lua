--
-- unit-zerg-ultralisk-cavern
--


DefineAnimations("animations-zerg-ultralisk-cavern", {
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 4", "frame 1", "wait 2",
    "frame 0", "wait 4",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-ultralisk-cavern", {
  Animations = "animations-zerg-ultralisk-cavern", Icon = "icon-zerg-ultralisk-cavern",
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
    "selected", "zerg-ultralisk-cavern-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
