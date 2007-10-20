--
-- unit-zerg-greater-spire
--


DefineAnimations("animations-zerg-greater-spire", {
  Still = {
    "frame 0", "random-wait 1 5", "label 4E8C", "frame 0", "wait 2",
    "frame 1", "wait 2", "frame 2", "wait 2", "goto 4E8C",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-greater-spire", { Name = "Spire",
  Image = {"file", "zerg/units/greater spire.png", "size",  {128, 192}},
  Shadow = {"file", "zerg/units/greater spire shadow.png", "size",  {128, 192}},
  Animations = "animations-zerg-greater-spire", Icon = "icon-zerg-greater-spire",
  Costs = {"time", 200, "minerals", 75},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  HitPoints = 400,
  DrawLevel = 30,
  TileSize = {2, 2}, BoxSize = {63, 63},--FIXME:wrong box size
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
    "selected", "zerg-spire-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
