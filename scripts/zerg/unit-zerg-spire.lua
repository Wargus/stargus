--
-- unit-zerg-spire
--


DefineAnimations("animations-zerg-spire", {
  Still = {
    "frame 0", "random-wait 1 3", "label 51D2", "frame 1", "wait 2",
    "frame 2", "wait 4", "frame 1", "wait 2", "frame 0", "wait 4", "goto 51D2",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-spire", { Name = "Spire",
  Image = {"file", "zerg/units/spire.png", "size",  {128, 128}},
  Shadow = {"file", "zerg/units/spire shadow.png", "size",  {128, 128}},
  Animations = "animations-zerg-spire", Icon = "icon-zerg-spire",
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
  UpgradeTo = 100,
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
	
CUpgrade:New("upgrade-zerg-greater-spire")
	
DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-greater-spire",
  Action = "upgrade-to", Value = "unit-zerg-greater-spire",
  Key = "w", Hint = "Mutate to Greater Spire",
  ForUnit = {"unit-zerg-spire"} } )
