Load("scripts/protoss/unit-protoss-nexus.lua")
Load("scripts/protoss/unit-protoss-pylon.lua")
Load("scripts/protoss/unit-protoss-gateway.lua")
Load("scripts/protoss/unit-protoss-zealot.lua")
Load("scripts/protoss/unit-protoss-dragoon.lua")
Load("scripts/protoss/unit-protoss-photon-cannon.lua")
Load("scripts/protoss/unit-protoss-assimulator.lua")
Load("scripts/protoss/unit-protoss-forge.lua")
Load("scripts/protoss/unit-protoss-cybernetics-core.lua")
Load("scripts/protoss/unit-protoss-probe.lua")

--
-- Buttons
--
DefineButton( { Pos = 1, Level = 0, Icon = "icon-move",
  Action = "move",
  Key = "m", Hint = "~!Move",
  ForUnit = {
    "protoss-group",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "unit-protoss-dragoon",
  } } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-stop",
  Action = "stop",
  Key = "s", Hint = "~!Stop",
  ForUnit = {
    "protoss-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "unit-protoss-photon-cannon",
  } } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-attack",
  Action = "attack",
  Key = "a", Hint = "~!Attack",
  ForUnit = {
    "protoss-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "unit-protoss-photon-cannon",
  } } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-patrol",
  Action = "patrol",
  Key = "p", Hint = "~!Patrol",
  ForUnit = {
    "protoss-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
  } } )

DefineButton( { Pos = 5, Level = 0, Icon = "icon-hold-position",
  Action = "stand-ground",
  Key = "h", Hint = "~!Hold Position",
  ForUnit = {
    "protoss-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
  } } )

DefineButton( { Pos = 6, Level = 0, Icon = "icon-rally-point",
  Action = "move",
  Key = "r", Hint = "Set ~!Rally Point",
  ForUnit = {
    "unit-protoss-nexus",
    "unit-protoss-gateway",
  } } )



--
-- Allow
--
DefineAllow("unit-protoss-probe",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-zealot",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-dragoon",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-probe",            "AAAAAAAAAAAAAAAA")

DefineAllow("unit-protoss-nexus",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-pylon",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-gateway",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-photon-cannon",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-assimulator",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-forge",  "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-cybernetics-core",          "AAAAAAAAAAAAAAAA")

