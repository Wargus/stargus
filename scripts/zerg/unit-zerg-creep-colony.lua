--
-- unit-zerg-creep-colony
--


DefineAnimations("animations-zerg-creep-colony", {
  --[[ active overlay 108 ]]
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 2", "frame 3", "wait 2",
    "frame 0", "wait 2",
  },
})


DefineUnitType("unit-zerg-creep-colony", { Name = "Creep Colony",
  Image = {"file", "zerg/units/creep colony.png", "size",  {128, 64}},
  Shadow = {"file", "zerg/units/creep colony shadow.png", "size",  {128, 96}},
  Animations = "animations-zerg-creep-colony", Icon = "icon-zerg-creep-colony",
  Costs = {"time", 200, "minerals", 75},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  HitPoints = 400,
  DrawLevel = 30,
  TileSize = {2, 2}, BoxSize = {63, 63},--FIXME: wrong boxsize
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
    "selected", "zerg-creep-colony-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
	
DefineUnitType("unit-zerg-sunken-colony", {})

	
DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-sunken-colony",
  Action = "upgrade-to", Value = "unit-zerg-sunken-colony",
  Key = "s", Hint = "Spawning Pool",
  ForUnit = {"unit-zerg-creep-colony"} } )
