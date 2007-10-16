--
-- unit-zerg-hatchery
--


DefineAnimations("animations-zerg-hatchery", {
  Still = {
    "frame 0", "random-wait 1 5", "label 4AEC", "frame 1", "wait 2",--FIXME: not original sc animations
    "frame 2", "wait 2", "frame 3", "wait 4", "frame 2", "wait 2",
    "frame 1", "wait 2", "frame 0", "wait 4", "goto 4AEC",
  },
  Train = {
    "frame 0", "wait 125",
  },
})


DefineUnitType("unit-zerg-hatchery", { Name = "Zerg Hatchery",
  Image = {"file", "zerg/units/hatchery.png", "size", {192, 160}},
  Shadow = {"file", "zerg/units/hatchery shadow.png", "size", {192, 160}},
  Animations = "animations-zerg-hatchery", Icon = "icon-zerg-hatchery",
  Costs = {"time", 255, "minerals", 300},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 0},
  Construction = "construction-zerg-large",
  Speed = 0,
  HitPoints = 1500,
  DrawLevel = 30,
  TileSize = {4, 3}, BoxSize = {126, 95},--FIXME: wrong size
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 35, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 8,
  RegenerationRate = 1,
--  ExplodeWhenKilled = "missle-zerg-rubble-large",
  Type = "land",
  Corpse = "unit-zerg-rubble-large",
  BuilderLost = true,
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "distance", { Distance = 3, DistanceType = ">", Type = "unit-minerals1"} } },
  CanStore = {"gas", "minerals"},
  Sounds = {
    "selected", "zerg-hatchery-selected",
--    "ready", "town-hall-ready",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )


DefineUnitType("unit-zerg-drone", {})
DefineUnitType("unit-zerg-zergling", {})
DefineUnitType("unit-zerg-hydralisk", {})
DefineUnitType("unit-zerg-ultralisk", {})
DefineUnitType("unit-zerg-overlord", {})
DefineUnitType("unit-zerg-queen", {})
DefineUnitType("unit-zerg-defiler", {})
DefineUnitType("unit-zerg-mutalisk", {})

DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-larva",
  Action = "button", Value = 1,
  Key = "b", Hint = "Select Larva",
  ForUnit = {"unit-zerg-hatchery"} } )

DefineButton( { Pos = 1, Level = 1, Icon = "icon-zerg-drone",
  Action = "train-unit", Value = "unit-zerg-drone",
  Key = "d", Hint = "Build Drone",
  ForUnit = {"unit-zerg-hatchery"} } )

DefineButton( { Pos = 2, Level = 1, Icon = "icon-zerg-zergling",
  Action = "train-unit", Value = "unit-zerg-zergling",
  Key = "z", Hint = "Zergling",
  ForUnit = {"unit-zerg-hatchery"} } )

DefineButton( { Pos = 3, Level = 1, Icon = "icon-zerg-hydralisk",
  Action = "train-unit", Value = "unit-zerg-hydralisk",
  Key = "h", Hint = "Hydralisk",
  ForUnit = {"unit-zerg-hatchery"} } )
  
DefineButton( { Pos = 4, Level = 1, Icon = "icon-zerg-ultralisk",
  Action = "train-unit", Value = "unit-zerg-ultralisk",
  Key = "u", Hint = "Ultralisk",
  ForUnit = {"unit-zerg-hatchery"} } )
  
DefineButton( { Pos = 5, Level = 1, Icon = "icon-zerg-overlord",
  Action = "train-unit", Value = "unit-zerg-overlord",
  Key = "o", Hint = "Overlord",
  ForUnit = {"unit-zerg-hatchery"} } )

DefineButton( { Pos = 7, Level = 1, Icon = "icon-zerg-mutalisk",
  Action = "train-unit", Value = "unit-zerg-mutalisk",
  Key = "m", Hint = "Mutalisk",
  ForUnit = {"unit-zerg-hatchery"} } )

DefineButton( { Pos = 8, Level = 1, Icon = "icon-zerg-queen",
  Action = "train-unit", Value = "unit-zerg-queen",
  Key = "q", Hint = "Queen",
  ForUnit = {"unit-zerg-hatchery"} } )

DefineButton( { Pos = 9, Level = 1, Icon = "icon-zerg-defiler",
  Action = "train-unit", Value = "unit-zerg-defiler",
  Key = "d", Hint = "Defiler",
  ForUnit = {"unit-zerg-hatchery"} } )
