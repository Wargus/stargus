DefineAnimations("animations-zerg-spawning-pool", {
  Still = {
    "frame 0", "wait 125",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})
--todo change animations from terran-command-center to zerg-hatchery
DefineConstruction("construction-zerg-spawning-pool", {
  Files = {
    File = "terran/units/building construction large.png",
    Size = {160, 128}},
  ShadowFiles = {
    File = "terran/units/building construction large shadow.png",
    Size = {128, 128}},
  Constructions = {
   {Percent = 0,
    File = "construction",
    Frame = 0},
   {Percent = 20,
    File = "construction",
    Frame = 1},
   {Percent = 40,
    File = "construction",
    Frame = 2},
   {Percent = 60,
    File = "main",
    Frame = 1}}
})

DefineUnitType("unit-zerg-spawning-pool", { Name = "Spawning Pool",
  Image = {"file", "zerg/units/spawning pool.png", "size", {96, 128}},
  Shadow = {"file", "zerg/units/spawning pool shadow.png", "size", {96, 128}},
  Animations = "animations-zerg-spawning-pool", Icon = "icon-zerg-spawning-pool",
  Costs = {"time", 200, "minerals", 150},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg-spawning-pool",
  Speed = 0,
  HitPoints = 1000,
  DrawLevel = 50,
  TileSize = {4, 3}, BoxSize = {127, 95},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 30, AnnoyComputerFactor = 35,
  Points = 160,
  Corpse = "unit-destroyed-3x3-place",--FIXME
  ExplodeWhenKilled = "missile-terran-explosion-large",--FIXME
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  Sounds = {
    "selected", "zerg-spawning-pool-selected",
    "ready", "zerg-work-complete",
    "help", "zerg-base-attacked",
    "dead", "explosion-large"} } )

