--
-- unit-zerg-spawning-pool
--


DefineAnimations("animations-zerg-spawning-pool", {
  Still = {
    "frame 0", "random-wait 1 3", "label 4987", "frame 0", "wait 2",
    "frame 2", "wait 2", "frame 3", "wait 2", "goto 4987",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-spawning-pool", { Name = "Spawning Pool",
  Image = {"file", "zerg/units/spawning pool.png", "size", {96, 128}},
  Shadow = {"file", "zerg/units/spawning pool shadow.png", "size", {96, 128}},
  Animations = "animations-zerg-spawning-pool", Icon = "icon-zerg-spawning-pool",
  Costs = {"time", 200, "minerals", 150},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  HitPoints = 1000,
  DrawLevel = 30,
  TileSize = {2, 1}, BoxSize = {96, 80},--FIXME:wrong size
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 30, AnnoyComputerFactor = 35,
  Points = 160,
  RegenerationRate = 1,
  BuilderLost = true,
--  Corpse = "unit-zerg-rubble-large",
  ExplodeWhenKilled = "missile-none",
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  Sounds = {
    "selected", "zerg-spawning-pool-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
--[[	
CUpgrade:New("upgrade-zerg-zergling-speed")
	
DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-zergling-speed",
  Action = "research", Value = "upgrade-zerg-zergling-speed",
  Allowed = "check-single-research",
  Key = "w", Hint = "Upgrade Zergling Speed",
  ForUnit = {"unit-zerg-spawning-pool"} } )

--]]
