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


DefineUnitType("unit-zerg-ultralisk-cavern", { Name = "Ultralisk Cavern",
  Image = {"file", "zerg/units/ultralisk cavern.png", "size",  {160, 128}},
  Shadow = {"file", "zerg/units/ultralisk cavern shadow.png", "size",  {160, 128}},
  Animations = "animations-zerg-ultralisk-cavern", Icon = "icon-zerg-ultralisk-cavern",
  Costs = {"time", 200, "minerals", 75},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  HitPoints = 400,
  DrawLevel = 30,
  TileSize = {2, 2}, BoxSize = {63, 63},
  SightRange = 4,
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
    "selected", "zerg-ultralisk-cavern-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
