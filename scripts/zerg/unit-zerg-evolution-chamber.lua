--
-- unit-zerg-evolution-chamber
--


DefineAnimations("animations-zerg-evolution-chamber", {
  Still = {
    "frame 0", "random-wait 1 3", "label 4930", "frame 1", "wait 3",
    "frame 2", "wait 3", "frame 0", "wait 3", "goto 4930",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-evolution-chamber", { Name = "Evolution Chamber",
  Image = {"file", "zerg/units/evolution chamber.png", "size",  {96, 128}},
  Shadow = {"file", "zerg/units/evolution chamber shadow.png", "size",  {128, 160}},
  Animations = "animations-zerg-evolution-chamber", Icon = "icon-zerg-evolution-chamber",
  Costs = {"time", 200, "minerals", 75},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  HitPoints = 400,
  DrawLevel = 30,
  TileSize = {2, 2}, BoxSize = {63, 63},--FIXME:wrong size
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
    "selected", "zerg-evolution-chamber-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
