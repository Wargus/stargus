--
-- unit-terran-scv
--

DefineAnimations("animations-terran-scv", {
  Still = {"frame 0", "wait 125",},
  Move = {"unbreakable begin",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "frame 34", "sound terran-scv-attack",
    "wait 1", "frame 17", "unbreakable end", "wait 1",},
  Harvest_minerals = {"unbreakable begin", "frame 34", "sound terran-scv-attack",
    "wait 1", "frame 17", "unbreakable end", "wait 1",},
  Repair = {"unbreakable begin", "frame 34", "sound terran-scv-attack",
    "wait 1", "frame 17", "unbreakable end", "wait 1",},
  Build = {"unbreakable begin", "frame 34", "sound terran-scv-attack",
    "wait 1", "frame 17", "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "frame 50", "wait 3", "frame 55", "wait 3", "frame 60", "wait 100",
    "frame 60", "unbreakable end", "wait 1",},
})


DefineUnitType("unit-terran-scv", { Name = "Terran SCV",
  Image = {"file", "terran/units/scv.png", "size", {72, 72}},
  Shadow = {"file", "terran/units/scv.png", "size", {72, 72}, "offset", {0, -7}},
  NumDirections = 32,
  DrawLevel = 19,
  Animations = "animations-terran-scv", Icon = "icon-terran-scv",
  Costs = {"time", 45, "minerals", 50},
  Speed = 10,
  HitPoints = 60,
  DrawLevel = 40,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 4, ComputerReactionRange = 6, PersonReactionRange = 4,
  BasicDamage = 3, PiercingDamage = 2, Missile = "missile-none",
  MaxAttackRange = 1,
  Priority = 50,
  Points = 30,
  Demand = 1,
  ExplodeWhenKilled = "missile-terran-explosion-small",
  Type = "land",
  RightMouseAction = "harvest",
  CanAttack = true, RepairRange = 1,
  CanTargetLand = true,
  LandUnit = true,
  Coward = true,
  CanGatherResources = {
   {"file-when-loaded", "terran/units/scv.png",
    "resource-id", "minerals",
    "harvest-from-outside",
    "resource-capacity", 8,
    "wait-at-resource", 150,
    "wait-at-depot", 50},
   {"file-when-loaded", "terran/units/scv.png",
    "resource-id", "gas",
    "resource-capacity", 8,
    "wait-at-resource", 50,
    "wait-at-depot", 50,}},
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-scv-selected",
    "acknowledge", "terran-scv-acknowledge",
    "ready", "terran-scv-ready",
    "help", "terran-units-attacked",
    "dead", "terran-scv-death"} } )


--
-- Default
--
DefineButton( { Pos = 1, Level = 0, Icon = "icon-move",
  Action = "move",
  Key = "m", Hint = "~!Move",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-stop",
  Action = "stop",
  Key = "s", Hint = "~!Stop",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-attack",
  Action = "attack",
  Key = "a", Hint = "~!Attack",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-repair",
  Action = "repair",
  Key = "r", Hint = "~!Repair",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 5, Level = 0, Icon = "icon-gather",
  Action = "harvest",
  Key = "g", Hint = "~!Gather",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 7, Level = 0, Icon = "icon-build",
  Action = "button", Value = 1,
  Key = "b", Hint = "~!Build Structure",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 8, Level = 0, Icon = "icon-advanced-build",
  Action = "button", Value = 2,
  Key = "v", Hint = "Build Ad~!vanced Structure",
  ForUnit = {"unit-terran-scv"} } )


--
-- Build
--
DefineButton( { Pos = 1, Level = 1, Icon = "icon-terran-command-center",
  Action = "build", Value = "unit-terran-command-center",
  Key = "c", Hint = "Build ~!Command Center",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 2, Level = 1, Icon = "icon-terran-supply-depot",
  Action = "build", Value = "unit-terran-supply-depot",
  Key = "s", Hint = "Build ~!Supply Depot",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 3, Level = 1, Icon = "icon-terran-refinery",
  Action = "build", Value = "unit-terran-refinery",
  Key = "r", Hint = "Build ~!Refinery",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 4, Level = 1, Icon = "icon-terran-barracks",
  Action = "build", Value = "unit-terran-barracks",
  Key = "b", Hint = "Build ~!Barracks",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 5, Level = 1, Icon = "icon-terran-engineering-bay",
  Action = "build", Value = "unit-terran-engineering-bay",
  Key = "e", Hint = "Build ~!Engineering Bay",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 6, Level = 1, Icon = "icon-terran-missile-turret",
  Action = "build", Value = "unit-terran-missile-turret",
  Key = "t", Hint = "Build Missile ~!Turret",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 7, Level = 1, Icon = "icon-terran-academy",
  Action = "build", Value = "unit-terran-academy",
  Key = "a", Hint = "Build ~!Academy",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 8, Level = 1, Icon = "icon-terran-bunker",
  Action = "build", Value = "unit-terran-bunker",
  Key = "u", Hint = "Build B~!unker",
  ForUnit = {"unit-terran-scv"} } )
  
DefineButton( { Pos = 9, Level = 1, Icon = "icon-cancel",
  Action = "button", Value = 0,
  Key = "\27", Hint = "~<ESC~> - Cancel",
  ForUnit = {"unit-terran-scv"} } )

--
-- Advanced Build
--
DefineButton( { Pos = 1, Level = 2, Icon = "icon-terran-factory",
  Action = "build", Value = "unit-terran-factory",
  Key = "f", Hint = "Build ~!Factory",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 2, Level = 2, Icon = "icon-terran-starport",
  Action = "build", Value = "unit-terran-starport",
  Key = "s", Hint = "Build ~!Starport",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 3, Level = 2, Icon = "icon-terran-science-facility",
  Action = "build", Value = "unit-terran-science-facility",
  Key = "i", Hint = "Build Sc~!ience Facility",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 4, Level = 2, Icon = "icon-terran-armory",
  Action = "build", Value = "unit-terran-armory",
  Key = "a", Hint = "Build ~!Armory",
  ForUnit = {"unit-terran-scv"} } )

DefineButton( { Pos = 9, Level = 2, Icon = "icon-cancel",
  Action = "button", Value = 0,
  Key = "\27", Hint = "~<ESC~> - Cancel",
  ForUnit = {"unit-terran-scv"} } )
