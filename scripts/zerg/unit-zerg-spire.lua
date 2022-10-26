--
-- unit-zerg-spire
--


DefineAnimations("animations-zerg-spire", {
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 4", "frame 1", "wait 2",
    "frame 0", "wait 4",
  },
  Train = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-spire", {
  Animations = "animations-zerg-spire", Icon = "icon-zerg-spire",
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
  UpgradeTo = 100,
  RightMouseAction = "attack",
  RegenerationRate = 1,
  CanAttack = true,
  BuilderLost = true,
  CanTargetLand = true,
  VisibleUnderFog = true,
  Sounds = {
    "selected", "zerg-spire-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
	
CUpgrade:New("upgrade-zerg-greater-spire")
	
DefineButton( { Pos = 7, Level = 0, Icon = "icon-zerg-greater-spire",
  Action = "upgrade-to", Value = "unit-zerg-greater-spire",
  Key = "w", Hint = "Mutate to Greater Spire",
  ForUnit = {"unit-zerg-spire"} } )


CUpgrade:New("upgrade-zerg-flyer-attacks1")
CUpgrade:New("upgrade-zerg-flyer-attacks2")
CUpgrade:New("upgrade-zerg-flyer-attacks3")
CUpgrade:New("upgrade-zerg-flyer-carapace1")
CUpgrade:New("upgrade-zerg-flyer-carapace2")
CUpgrade:New("upgrade-zerg-flyer-carapace3")



DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-upgrade-flyer-attack",
  Action = "research", Value = "upgrade-zerg-flyer-attacks1",
  Allowed = "check-single-research",
  Key = "w", Hint = "Upgrade Flyer Attacks",
  ForUnit = {"unit-zerg-evolution-chamber"} } )
DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-upgrade-flyer-attack",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-zerg-flyer-attacks2",
  Key = "w", Hint = "Upgrade Flyer Attacks",
  ForUnit = {"unit-zerg-spire"} } )
DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-upgrade-flyer-attack",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-zerg-flyer-attacks3",
  Key = "w", Hint = "Upgrade Flyer Attacks",
  ForUnit = {"unit-zerg-spire"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-zerg-upgrade-zerg-carapace",
  Action = "research", Value = "upgrade-zerg-flyer-carapace1",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Flyer Carapace",
  ForUnit = {"unit-zerg-spire"} } )
DefineButton( { Pos = 2, Level = 0, Icon = "icon-zerg-upgrade-zerg-carapace",
  Action = "research", Value = "upgrade-zerg-flyer-carapace2",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Flyer Carapace",
  ForUnit = {"unit-zerg-spire"} } )
DefineButton( { Pos = 2, Level = 0, Icon = "icon-zerg-upgrade-zerg-carapace",
  Action = "research", Value = "upgrade-zerg-flyer-carapace3",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Flyer Carapace",
  ForUnit = {"unit-zerg-spire"} } )
