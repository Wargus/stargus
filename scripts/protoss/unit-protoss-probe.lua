--
-- unit-protoss-probe
--

DefineAnimations("animations-protoss-probe", {
Still = {"frame 0", "wait 125",},
  Move = {"unbreakable begin",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",},
  Harvest_minerals = {"unbreakable begin", "sound protoss-probe-mine", "wait 75","sound protoss-probe-mine", "unbreakable end", "wait 1",},
  Repair = {"unbreakable begin",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",},
  Build = {"unbreakable begin",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "wait 1", "move 4", "wait 1",
    "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "frame 50", "wait 3", "frame 55", "wait 3", "frame 60", "wait 100",
    "frame 60", "unbreakable end", "wait 1",},
})


DefineUnitType("unit-protoss-probe", {
  DrawLevel = 19,
  Animations = "animations-protoss-probe", Icon = "icon-protoss-probe",
  Speed = 10,
  DrawLevel = 40,
  BasicDamage = 3, PiercingDamage = 2, Missile = "missile-none",
  MaxAttackRange = 1,
  Priority = 50,
  Points = 30,
  Demand = 1,
  --ExplodeWhenKilled = "missile-terran-explosion-small",
  RightMouseAction = "harvest",
  CanAttack = true, RepairRange = 1,
  CanTargetLand = true,
  Coward = true,
  CanGatherResources = {
   {"file-when-loaded", "graphics/unit/protoss/probe.png",
    "resource-id", "minerals",
    "harvest-from-outside",
    "resource-capacity", 8,
    "wait-at-resource", 150,
    "wait-at-depot", 50},
   {"file-when-loaded", "graphics/unit/protoss/probe.png",
    "resource-id", "gas",
    "resource-capacity", 8,
    "wait-at-resource", 50,
    "wait-at-depot", 50,}},
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "protoss-probe-selected",
    "acknowledge", "protoss-probe-acknowledge",
    "ready", "protoss-probe-ready",
    "help", "protoss-units-attacked",
    "dead", "protoss-probe-death"} } )

DefineUnitType("unit-protoss-pylon", {})
DefineUnitType("unit-protoss-nexus", {})
DefineUnitType("unit-protoss-gateway", {})
DefineUnitType("unit-protoss-photon-cannon", {})
DefineUnitType("unit-protoss-assimulator", {})
DefineUnitType("unit-protoss-forge", {})
DefineUnitType("unit-protoss-cybernetics-core", {})
DefineUnitType("unit-protoss-robotics-support-bay", {})
DefineUnitType("unit-protoss-stargate", {})
DefineUnitType("unit-protoss-citadel-of-adun", {})
DefineUnitType("unit-protoss-fleet-beacon", {})
DefineUnitType("unit-protoss-templar-archives", {})
DefineUnitType("unit-protoss-observatory", {})
DefineUnitType("unit-protoss-arbiter-tribunal", {})
DefineUnitType("unit-protoss-robotics-facility", {})

--
-- Default
--
DefineButton( { Pos = 1, Level = 0, Icon = "icon-move",
  Action = "move",
  Key = "m", Hint = "~!Move",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-stop",
  Action = "stop",
  Key = "s", Hint = "~!Stop",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-attack",
  Action = "attack",
  Key = "a", Hint = "~!Attack",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-repair",
  Action = "repair",
  Key = "r", Hint = "~!Repair",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 5, Level = 0, Icon = "icon-gather",
  Action = "harvest",
  Key = "g", Hint = "~!Gather",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 7, Level = 0, Icon = "icon-build",
  Action = "button", Value = 1,
  Key = "b", Hint = "~!Build Structure",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 8, Level = 0, Icon = "icon-advanced-build",
  Action = "button", Value = 2,
  Key = "v", Hint = "Build Ad~!vanced Structure",
  ForUnit = {"unit-protoss-probe"} } )


--
-- Build
--
DefineButton( { Pos = 1, Level = 1, Icon = "icon-protoss-nexus",
  Action = "build", Value = "unit-protoss-nexus",
  Key = "x", Hint = "~!Nexus",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 2, Level = 1, Icon = "icon-protoss-pylon",
  Action = "build", Value = "unit-protoss-pylon",
  Key = "p", Hint = "~!Pylon",
  ForUnit = {"unit-protoss-probe"} } )
  
 DefineButton( { Pos = 3, Level = 1, Icon = "icon-protoss-assimilator",
  Action = "build", Value = "unit-protoss-assimulator",
  Key = "a", Hint = "~!Assimulator",
  ForUnit = {"unit-protoss-probe"} } )
  
  
DefineButton( { Pos = 4, Level = 1, Icon = "icon-protoss-gateway",
  Action = "build", Value = "unit-protoss-gateway",
  Key = "g", Hint = "~!Gateway",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 5, Level = 1, Icon = "icon-protoss-forge",
  Action = "build", Value = "unit-protoss-forge",
  Key = "f", Hint = "~!Forge",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 6, Level = 1, Icon = "icon-protoss-photon-cannon",
  Action = "build", Value = "unit-protoss-photon-cannon",
  Key = "c", Hint = "Photon ~!Cannon",
  ForUnit = {"unit-protoss-probe"} } )
  
DefineButton( { Pos = 7, Level = 1, Icon = "icon-protoss-cybernetics-core",
  Action = "build", Value = "unit-protoss-cybernetics-core",
  Key = "c", Hint = "C~!ybernetics Core",
  ForUnit = {"unit-protoss-probe"} } )
  
DefineButton( { Pos = 8, Level = 1, Icon = "icon-protoss-shield-battery",
  Action = "build", Value = "unit-protoss-shield-battery",
  Key = "c", Hint = "~!Shield Battery",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 9, Level = 1, Icon = "icon-cancel",
  Action = "button", Value = 0,
  Key = "\27", Hint = "~<ESC~> - Cancel",
  ForUnit = {"unit-protoss-probe"} } )

--
-- Advanced Build
--
DefineButton( { Pos = 1, Level = 2, Icon = "icon-protoss-robotics-facility",
  Action = "build", Value = "unit-protoss-robotics-facility",
  Key = "c", Hint = "Robotics Facility",
  ForUnit = {"unit-protoss-probe"} } )
  
DefineButton( { Pos = 2, Level = 2, Icon = "icon-protoss-stargate",
  Action = "build", Value = "unit-protoss-stargate",
  Key = "c", Hint = "~!Stargate",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 3, Level = 2, Icon = "icon-protoss-citadel-of-adun",
  Action = "build", Value = "unit-protoss-citadel-of-adun",
  Key = "c", Hint = "~!",
  ForUnit = {"unit-protoss-probe"} } )

DefineButton( { Pos = 4, Level = 2, Icon = "icon-protoss-robotics-support-bay",
  Action = "build", Value = "unit-protoss-robotics-support-bay",
  Key = "c", Hint = "~!Robotics Support Bay",
  ForUnit = {"unit-protoss-probe"} } )
  
DefineButton( { Pos = 5, Level = 2, Icon = "icon-protoss-fleet-beacon",
  Action = "build", Value = "unit-protoss-fleet-beacon",
  Key = "c", Hint = "Fleet Beacon",
  ForUnit = {"unit-protoss-probe"} } )
  
 DefineButton( { Pos = 6, Level = 2, Icon = "icon-protoss-templar-archives",
  Action = "build", Value = "unit-protoss-templar-archives",
  Key = "c", Hint = "Templar Archives",
  ForUnit = {"unit-protoss-probe"} } )
  
DefineButton( { Pos = 7, Level = 2, Icon = "icon-protoss-observatory",
  Action = "build", Value = "unit-protoss-observatory",
  Key = "c", Hint = "Observatory",
  ForUnit = {"unit-protoss-probe"} } )
  
DefineButton( { Pos = 8, Level = 2, Icon = "icon-protoss-arbiter-tribunal",
  Action = "build", Value = "unit-protoss-arbiter-tribunal",
  Key = "c", Hint = "Arbiter Tribunal",
  ForUnit = {"unit-protoss-probe"} } )
  
  
DefineButton( { Pos = 9, Level = 2, Icon = "icon-cancel",
  Action = "button", Value = 0,
  Key = "\27", Hint = "~<ESC~> - Cancel",
  ForUnit = {"unit-protoss-probe"} } )
