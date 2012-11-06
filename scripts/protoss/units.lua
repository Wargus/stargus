Load("scripts/protoss/unit-protoss-nexus.lua")
Load("scripts/protoss/unit-protoss-pylon.lua")
Load("scripts/protoss/unit-protoss-gateway.lua")
Load("scripts/protoss/unit-protoss-zealot.lua")
Load("scripts/protoss/unit-protoss-dragoon.lua")
Load("scripts/protoss/unit-protoss-photon-cannon.lua")
Load("scripts/protoss/unit-protoss-assimulator.lua")
Load("scripts/protoss/unit-protoss-forge.lua")
Load("scripts/protoss/unit-protoss-cybernetics-core.lua")
Load("scripts/protoss/unit-protoss-shield-battery.lua")
Load("scripts/protoss/unit-protoss-robotics-support-bay.lua")
Load("scripts/protoss/unit-protoss-probe.lua")
Load("scripts/protoss/unit-protoss-stargate.lua")
Load("scripts/protoss/unit-protoss-citadel-of-adun.lua")
Load("scripts/protoss/unit-protoss-fleet-beacon.lua")
Load("scripts/protoss/unit-protoss-templar-archives.lua")
Load("scripts/protoss/unit-protoss-observatory.lua")
Load("scripts/protoss/unit-protoss-arbiter-tribunal.lua")
Load("scripts/protoss/unit-protoss-robotics-facility.lua")
Load("scripts/protoss/unit-protoss-high-templar.lua")
Load("scripts/protoss/unit-protoss-dark-templar.lua")
Load("scripts/protoss/unit-protoss-observer.lua")
Load("scripts/protoss/unit-protoss-reaver.lua")
Load("scripts/protoss/unit-protoss-shuttle.lua")
--Load("scipts/protoss/unit-protoss-scout.lua")


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
    "unit-protoss-high-templar",
    "unit-protoss-observer",
    "unit-protoss-reaver",
    "unit-protoss-shuttle",
    --"unit-protoss-scout",
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
    "unit-protoss-high-templar",
    "unit-protoss-dark-templar",
    "unit-protoss-observer",
    "unit-protoss-reaver",
    "unit-protoss-shuttle",
    --"unit-protoss-scout",
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
    "unit-protoss-dark-templar",
    "unit-protoss-reaver",
    --"unit-protoss-scout",
  } } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-patrol",
  Action = "patrol",
  Key = "p", Hint = "~!Patrol",
  ForUnit = {
    "protoss-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "unit-protoss-high-templar",
    "unit-protoss-dark-templar",
    "unit-protoss-observer",
    "unit-protoss-reaver",
    "unit-protoss-shuttle",
    --"unit-protoss-scout",
  } } )

DefineButton( { Pos = 5, Level = 0, Icon = "icon-hold-position",
  Action = "stand-ground",
  Key = "h", Hint = "~!Hold Position",
  ForUnit = {
    "protoss-group",
    "unit-protoss-dragoon",
    "unit-protoss-probe",
    "unit-protoss-zealot",
    "unit-protoss-high-templar",
    "unit-protoss-dark-templar",
    "unit-protoss-observer",
    "unit-protoss-reaver",
    "unit-protoss-shuttle",
    --"unit-protoss-scout",
  } } )

DefineButton( { Pos = 6, Level = 0, Icon = "icon-rally-point",
  Action = "move",
  Key = "r", Hint = "Set ~!Rally Point",
  ForUnit = {
    "unit-protoss-nexus",
    "unit-protoss-gateway",
    "unit-protoss-robotics-facility",
    "unit-protoss-stargate",
  } } )



--
-- Allow
--
DefineAllow("unit-protoss-probe",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-zealot",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-dragoon",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-probe",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-high-templar",	"AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-dark-templar",	"AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-observer",	"AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-reaver",	"AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-shuttle",	"AAAAAAAAAAAAAAAA")
--DefineAllow("unit-protoss-scout",	"AAAAAAAAAAAAAAAA")


DefineAllow("unit-protoss-nexus",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-pylon",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-gateway",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-photon-cannon",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-assimulator",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-forge",  "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-cybernetics-core",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-shield-battery",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-robotics-support-bay",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-stargate",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-citadel-of-adun",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-fleet-beacon",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-templar-archives",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-observatory",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-arbiter-tribunal",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-protoss-robotics-facility",          "AAAAAAAAAAAAAAAA")

