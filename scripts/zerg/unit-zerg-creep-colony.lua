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


DefineUnitType("unit-zerg-creep-colony", {
  Animations = "animations-zerg-creep-colony", Icon = "icon-zerg-creep-colony",
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
  RightMouseAction = "attack",
  RegenerationRate = 1,
  CanAttack = true,
  BuilderLost = true,
  CanTargetLand = true,
  VisibleUnderFog = true,
  Sounds = {
    "selected", "zerg-creep-colony-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
	

DefineUnitType("unit-zerg-spore-colony", {})
DefineUnitType("unit-zerg-sunken-colony", {})
	
DefineButton( { Pos = 7, Level = 0, Icon = "icon-zerg-spore-colony",
  Action = "upgrade-to", Value = "unit-zerg-spore-colony",
  Key = "s", Hint = "Mutate into ~!Spore Colony",
  ForUnit = {"unit-zerg-creep-colony"} } )

DefineButton( { Pos = 8, Level = 0, Icon = "icon-zerg-sunken-colony",
  Action = "upgrade-to", Value = "unit-zerg-sunken-colony",
  Key = "u", Hint = "Mutate into S~!unken Colony",
  ForUnit = {"unit-zerg-creep-colony"} } )

