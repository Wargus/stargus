Load("scripts/protoss/unit-protoss-nexus.lua")
Load("scripts/protoss/unit-protoss-pylon.lua")
Load("scripts/protoss/unit-protoss-gateway.lua")
Load("scripts/protoss/unit-protoss-zealot.lua")
Load("scripts/protoss/unit-protoss-dragoon.lua")
Load("scripts/protoss/unit-protoss-photon-cannon.lua")
Load("scripts/protoss/unit-protoss-assimulator.lua")
Load("scripts/protoss/unit-protoss-forge.lua")
Load("scripts/protoss/unit-protoss-probe.lua")
--Load("scripts/protoss/unit-protoss-dragoon.lua")
--Load("scripts/zerg/unit-zerg-spawning-pool.lua")
--Load("scripts/protoss/unit-zerg-overlord.lua")

--
-- Buttons
--
DefineButton( { Pos = 1, Level = 0, Icon = "icon-move",
  Action = "move",
  Key = "m", Hint = "~!Move",
  ForUnit = {
    "zerg-group",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "unit-protoss-dragoon",
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-dropship",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-science-vessel",
    "unit-protoss-probe",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-stop",
  Action = "stop",
  Key = "s", Hint = "~!Stop",
  ForUnit = {
    "zerg-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "unit-protoss-photon-cannon",
    "unit-terran-dropship",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-missile-turret",
    "unit-terran-science-vessel",
    "unit-protoss-probe",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-attack",
  Action = "attack",
  Key = "a", Hint = "~!Attack",
  ForUnit = {
    "zerg-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "unit-protoss-photon-cannon",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-protoss-probe",
    "unit-terran-missile-turret",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-patrol",
  Action = "patrol",
  Key = "p", Hint = "~!Patrol",
  ForUnit = {
    "zerg-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-dropship",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-missile-turret",
    "unit-terran-science-vessel",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 5, Level = 0, Icon = "icon-hold-position",
  Action = "stand-ground",
  Key = "h", Hint = "~!Hold Position",
  ForUnit = {
    "zerg-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-dropship",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-missile-turret",
    "unit-terran-science-vessel",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 6, Level = 0, Icon = "icon-rally-point",
  Action = "move",
  Key = "r", Hint = "Set ~!Rally Point",
  ForUnit = {
    "zerg-group",
    "unit-protoss-nexus",
    "unit-terran-barracks",
    "unit-protoss-nexus",
    "unit-terran-starport",
  } } )



--
-- Allow
--
DefineAllow("unit-protoss-probe",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-zealot",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-dragoon",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-ghost",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-goliath",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-marine",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-science-vessel", "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-probe",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-siege-tank",     "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-vulture",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-wraith",         "AAAAAAAAAAAAAAAA")

DefineAllow("unit-protoss-nexus",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-pylon",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-gateway",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-photon-cannon",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-assimulator",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-forge",  "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-factory",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-missile-turret",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-refinery",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-science-facility", "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-starport",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-supply-depot",     "AAAAAAAAAAAAAAAA")

