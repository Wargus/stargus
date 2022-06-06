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


DefineUnitType("unit-zerg-evolution-chamber", {
  Animations = "animations-zerg-evolution-chamber", Icon = "icon-zerg-evolution-chamber",
  Costs = {"time", 200, "minerals", 75},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  DrawLevel = 30,
  TileSize = {3, 2}, BoxSize = {100, 63},
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

CUpgrade:New("upgrade-zerg-melee-attacks1")
CUpgrade:New("upgrade-zerg-melee-attacks2")
CUpgrade:New("upgrade-zerg-melee-attacks3")
CUpgrade:New("upgrade-zerg-missle-attacks1")
CUpgrade:New("upgrade-zerg-missle-attacks2")
CUpgrade:New("upgrade-zerg-missle-attacks3")
CUpgrade:New("upgrade-zerg-carapace1")
CUpgrade:New("upgrade-zerg-carapace2")
CUpgrade:New("upgrade-zerg-carapace3")



DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-upgrade-melee-attack",
  Action = "research", Value = "upgrade-zerg-melee-attacks1",
  Allowed = "check-single-research",
  Key = "w", Hint = "Upgrade Melee Attacks",
  ForUnit = {"unit-zerg-evolution-chamber"} } )
DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-upgrade-melee-attack",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-zerg-melee-attacks2",
  Key = "w", Hint = "Upgrade Melee Attacks",
  ForUnit = {"unit-zerg-evolution-chamber"} } )
DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-upgrade-melee-attack",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-zerg-melee-attacks3",
  Key = "w", Hint = "Upgrade Melee Attacks",
  ForUnit = {"unit-zerg-evolution-chamber"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-zerg-upgrade-missle-attack",
  Action = "research", Value = "upgrade-zerg-missle-attacks1",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Missle Attacks",
  ForUnit = {"unit-zerg-evolution-chamber"} } )
DefineButton( { Pos = 2, Level = 0, Icon = "icon-zerg-upgrade-missle-attack",
  Action = "research", Value = "upgrade-zerg-missle-attacks2",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Missle Attacks",
  ForUnit = {"unit-zerg-evolution-chamber"} } )
DefineButton( { Pos = 2, Level = 0, Icon = "icon-zerg-upgrade-missle-attack",
  Action = "research", Value = "upgrade-zerg-missle-attacks3",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Missle Attacks",
  ForUnit = {"unit-zerg-evolution-chamber"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-zerg-upgrade-zerg-carapace",
  Action = "research", Value = "upgrade-zerg-carapace1",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Carapace",
  ForUnit = {"unit-zerg-evolution-chamber"} } )
DefineButton( { Pos = 3, Level = 0, Icon = "icon-zerg-upgrade-zerg-carapace",
  Action = "research", Value = "upgrade-zerg-carapace2",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Carapace",
  ForUnit = {"unit-zerg-evolution-chamber"} } )
DefineButton( { Pos = 3, Level = 0, Icon = "icon-zerg-upgrade-zerg-carapace",
  Action = "research", Value = "upgrade-zerg-carapace3",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Carapace",
  ForUnit = {"unit-zerg-evolution-chamber"} } )

