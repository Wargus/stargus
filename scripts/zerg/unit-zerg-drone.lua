--
-- unit-zerg-drone
--

DefineAnimations("animations-zerg-drone", {
Still = {"frame 0", "wait 125",},
  Move = {"unbreakable begin",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "frame 1", "wait 1", "unbreakable end", "wait 1",},
  Harvest_minerals = {"unbreakable begin", "frame 102", "wait 3", "frame 122", "wait 3", "frame 139", "wait 3", "frame 156", "wait 3", "frame 173", "wait 3", "frame 190", "wait 3", "unbreakable end", "wait 2",
  },
  Repair = {"unbreakable begin", "frame 34", "sound scv-attack",
    "wait 1", "frame 17", "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "wait 2", "frame 170", "wait 2",
    "frame 187", "wait 2", "frame 204", "wait 2", "frame 221", "wait 2", "frame 238", "unbreakable end", "wait 1",},
})


DefineUnitType("unit-zerg-drone", { Name = "Zerg Drone",
  Image = {"file", "zerg/units/drone.png", "size", {128, 128}},
  Shadow = {"file", "zerg/units/drone.png", "size", {128, 128}},
  NumDirections = 32,
  DrawLevel = 19,
  Animations = "animations-zerg-drone", Icon = "icon-zerg-drone",
  Costs = {"time", 45, "minerals", 50},
  Speed = 10,
  HitPoints = 60,
  DrawLevel = 40,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 4, ComputerReactionRange = 6, PersonReactionRange = 4,
  BasicDamage = 3, PiercingDamage = 2, Missile = "missile-zerg-spit",
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
  BuilderLost = true,
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
    "help", "terran-units-attacked",
    "dead", "zerg-drone-death"} } )


--
-- Default
--
DefineButton( { Pos = 1, Level = 0, Icon = "icon-move",
  Action = "move",
  Key = "m", Hint = "~!Move",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-stop",
  Action = "stop",
  Key = "s", Hint = "~!Stop",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-attack",
  Action = "attack",
  Key = "a", Hint = "~!Attack",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-repair",
  Action = "repair",
  Key = "r", Hint = "~!Repair",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 5, Level = 0, Icon = "icon-gather",
  Action = "harvest",
  Key = "g", Hint = "~!Gather",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 7, Level = 0, Icon = "icon-build",
  Action = "button", Value = 1,
  Key = "b", Hint = "~!Build Structure",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 8, Level = 0, Icon = "icon-advanced-build",
  Action = "button", Value = 2,
  Key = "v", Hint = "Build Ad~!vanced Structure",
  ForUnit = {"unit-zerg-drone"} } )


--
-- Build
--
DefineUnitType("unit-zerg-extractor", {})
DefineUnitType("unit-zerg-spawning-pool", {})
DefineUnitType("unit-zerg-sunken-colony", {})
DefineButton( { Pos = 1, Level = 1, Icon = "icon-zerg-hatchery",
  Action = "build", Value = "unit-zerg-hatchery",
  Key = "h", Hint = "Hatchery",
  ForUnit = {"unit-zerg-drone"} } )

DefineButton( { Pos = 2, Level = 1, Icon = "icon-zerg-spawning-pool",
  Action = "build", Value = "unit-zerg-spawning-pool",
  Key = "s", Hint = "Spawning Pool",
  ForUnit = {"unit-zerg-drone"} } )
  
  DefineButton( { Pos = 3, Level = 1, Icon = "icon-zerg-extractor",
  Action = "build", Value = "unit-zerg-extractor",
  Key = "e", Hint = "Extractor",
  ForUnit = {"unit-zerg-drone"} } )
  
  DefineButton( { Pos = 4, Level = 1, Icon = "icon-terran-bunker",
  Action = "build", Value = "unit-zerg-sunken-colony",
  Key = "s", Hint = "Sunken Colony",
  ForUnit = {"unit-zerg-drone"} } )

  
DefineButton( { Pos = 9, Level = 1, Icon = "icon-cancel",
  Action = "button", Value = 0,
  Key = "\27", Hint = "~<ESC~> - Cancel",
  ForUnit = {"unit-zerg-drone"} } )

--
-- Advanced Build
--

DefineButton( { Pos = 9, Level = 2, Icon = "icon-cancel",
  Action = "button", Value = 0,
  Key = "\27", Hint = "~<ESC~> - Cancel",
  ForUnit = {"unit-zerg-drone"} } )
