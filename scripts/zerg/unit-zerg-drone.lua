--
-- unit-zerg-drone
--


DefineAnimations("animations-zerg-drone", {
  Still = {"frame 0", "wait 125",},
  Move = {"unbreakable begin",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "sound zerg-drone-attack",
    "frame 85", "wait 2", "frame 102", "wait 2", "frame 119", "wait 2",
    "frame 136", "wait 2", "frame 85", "unbreakable end", "wait 1",
  },
  Harvest_minerals = {"unbreakable begin", "sound zerg-drone-attack",
    "frame 85", "wait 2", "frame 102", "wait 2", "frame 119", "wait 2",
    "frame 136", "wait 2", "frame 85", "unbreakable end", "wait 1",
  },
  Repair = {"unbreakable begin", "sound zerg-drone-attack",
    "frame 85", "wait 2", "frame 102", "wait 2", "frame 119", "wait 2",
    "frame 136", "wait 2", "frame 85", "unbreakable end", "wait 1",
  },
  Death = {"unbreakable begin",
    "frame 170", "wait 2", "frame 187", "wait 2", "frame 204", "wait 2",
    "frame 221", "wait 2", "frame 238", "wait 2", "frame 255", "wait 2",
    "frame 272", "wait 2", "frame 289", "wait 2", "unbreakable end", "wait 1",},
})


DefineUnitType("unit-zerg-drone", { Name = "Zerg Drone",
  Image = {"file", "zerg/units/drone.png", "size", {128, 128}},
  Shadow = {"file", "zerg/units/drone.png", "size", {128, 128}},
  NumDirections = 32,
  DrawLevel = 19,
  Animations = "animations-zerg-drone", Icon = "icon-zerg-drone",
  Costs = {"time", 25, "minerals", 50},
  Speed = 10,
  HitPoints = 40,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 7, ComputerReactionRange = 6, PersonReactionRange = 4,
  BasicDamage = 5, PiercingDamage = 2, Missile = "missile-zerg-spit",
  MaxAttackRange = 1,
  Priority = 50,
  RegenerationRate = 1,
  Points = 30,
  Demand = 1,
  Type = "land",
  RightMouseAction = "harvest",
  CanAttack = true, RepairRange = 1,
  CanTargetLand = true,
  LandUnit = true,
  Coward = true,
  CanGatherResources = {
   {"file-when-loaded", "zerg/units/drone.png",
    "resource-id", "minerals",
    "harvest-from-outside",
    "resource-capacity", 8,
    "wait-at-resource", 150,
    "wait-at-depot", 50},
   {"file-when-loaded", "zerg/units/drone.png",
    "resource-id", "gas",
    "resource-capacity", 8,
    "wait-at-resource", 50,
    "wait-at-depot", 50,}},
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-drone-selected",
    "acknowledge", "zerg-drone-acknowledgement",
    "ready", "zerg-drone-ready",
    "help", "zerg-units-attacked",
    "dead", "zerg-drone-death"} } )


--
-- Default
--
DefineButton( { Pos = 5, Level = 0, Icon = "icon-gather",
  Action = "harvest",
  Key = "g", Hint = "~!Gather",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 7, Level = 0, Icon = "icon-build",
  Action = "button", Value = 1,
  Key = "b", Hint = "~!Basic Mutation",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 8, Level = 0, Icon = "icon-advanced-build",
  Action = "button", Value = 2,
  Key = "v", Hint = "Ad~!vanced Mutation",
  ForUnit = {"unit-zerg-drone"} } )


--
-- Build
--
DefineUnitType("unit-zerg-hatchery", {})
DefineUnitType("unit-zerg-creep-colony", {})
DefineUnitType("unit-zerg-extractor", {})
DefineUnitType("unit-zerg-spawning-pool", {})
DefineUnitType("unit-zerg-evolution-chamber", {})
DefineUnitType("unit-zerg-hydralisk-den", {})

DefineUnitType("unit-zerg-spire", {})
DefineUnitType("unit-zerg-queens-nest", {})
DefineUnitType("unit-zerg-nydus-canal", {})
DefineUnitType("unit-zerg-ultralisk-cavern", {})
DefineUnitType("unit-zerg-defiler-mound", {})

DefineButton( { Pos = 1, Level = 1, Icon = "icon-zerg-hatchery",
  Action = "build", Value = "unit-zerg-hatchery",
  Key = "h", Hint = "Mutate into ~!Hatchery",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 2, Level = 1, Icon = "icon-zerg-creep-colony",
  Action = "build", Value = "unit-zerg-creep-colony",
  Key = "c", Hint = "Mutate into ~!Creep Colony",
  ForUnit = {"unit-zerg-drone"} } )
  
DefineButton( { Pos = 3, Level = 1, Icon = "icon-zerg-extractor",
  Action = "build", Value = "unit-zerg-extractor",
  Key = "e", Hint = "Mutate into ~!Extractor",
  ForUnit = {"unit-zerg-drone"} } )
  
DefineButton( { Pos = 4, Level = 1, Icon = "icon-zerg-spawning-pool",
  Action = "build", Value = "unit-zerg-spawning-pool",
  Key = "s", Hint = "Mutate into ~!Spawning Pool",
  ForUnit = {"unit-zerg-drone"} } )
  
DefineButton( { Pos = 5, Level = 1, Icon = "icon-zerg-evolution-chamber",
  Action = "build", Value = "unit-zerg-evolution-chamber",
  Key = "v", Hint = "Mutate into E~!volution Chamber",
  ForUnit = {"unit-zerg-drone"} } )
  
DefineButton( { Pos = 7, Level = 1, Icon = "icon-zerg-hydralisk-den",
  Action = "build", Value = "unit-zerg-hydralisk-den",
  Key = "d", Hint = "Mutate into Hydralisk ~!Den",
  ForUnit = {"unit-zerg-drone"} } )
  

DefineButton( { Pos = 1, Level = 2, Icon = "icon-zerg-spire",
  Action = "build", Value = "unit-zerg-spire",
  Key = "s", Hint = "Mutate into ~!Spire",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 2, Level = 2, Icon = "icon-zerg-queens-nest",
  Action = "build", Value = "unit-zerg-queens-nest",
  Key = "q", Hint = "Mutate into ~!Queen's Nest",
  ForUnit = {"unit-zerg-drone"} } )
  
DefineButton( { Pos = 3, Level = 2, Icon = "icon-zerg-nydus-canal",
  Action = "build", Value = "unit-zerg-nydus-canal",
  Key = "u", Hint = "Mutate into ~!Nydus Canal",
  ForUnit = {"unit-zerg-drone"} } )
  
DefineButton( { Pos = 4, Level = 2, Icon = "icon-zerg-ultralisk-cavern",
  Action = "build", Value = "unit-zerg-ultralisk-cavern",
  Key = "u", Hint = "Ultralisk Cavern",
  ForUnit = {"unit-zerg-drone"} } )
  
DefineButton( { Pos = 5, Level = 2, Icon = "icon-zerg-defiler-mound",
  Action = "build", Value = "unit-zerg-defiler-mound",
  Key = "u", Hint = "Mutate into ~!Defiler Mound",
  ForUnit = {"unit-zerg-drone"} } )
  

  
DefineButton( { Pos = 9, Level = 1, Icon = "icon-cancel",
  Action = "button", Value = 0,
  Key = "\27", Hint = "~<ESC~> - Cancel",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 9, Level = 2, Icon = "icon-cancel",
  Action = "button", Value = 0,
  Key = "\27", Hint = "~<ESC~> - Cancel",
  ForUnit = {"unit-zerg-drone"} } )

