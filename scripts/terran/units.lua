Load("scripts/terran/unit-terran-academy.lua")
Load("scripts/terran/unit-terran-armory.lua")
Load("scripts/terran/unit-terran-barracks.lua")
Load("scripts/terran/unit-terran-bunker.lua")
Load("scripts/terran/unit-terran-command-center.lua")
Load("scripts/terran/unit-terran-engineering-bay.lua")
Load("scripts/terran/unit-terran-factory.lua")
Load("scripts/terran/unit-terran-missile-turret.lua")
Load("scripts/terran/unit-terran-refinery.lua")
Load("scripts/terran/unit-terran-science-facility.lua")
Load("scripts/terran/unit-terran-starport.lua")
Load("scripts/terran/unit-terran-supply-depot.lua")
Load("scripts/terran/unit-terran-comsat-station.lua")

Load("scripts/terran/unit-terran-battlecruiser.lua")
Load("scripts/terran/unit-terran-dropship.lua")
Load("scripts/terran/unit-terran-firebat.lua")
Load("scripts/terran/unit-terran-ghost.lua")
Load("scripts/terran/unit-terran-goliath.lua")
Load("scripts/terran/unit-terran-marine.lua")
Load("scripts/terran/unit-terran-science-vessel.lua")
Load("scripts/terran/unit-terran-scv.lua")
Load("scripts/terran/unit-terran-siege-tank.lua")
Load("scripts/terran/unit-terran-vulture.lua")
Load("scripts/terran/unit-terran-wraith.lua")

--
-- Buttons
--
DefineButton( { Pos = 1, Level = 0, Icon = "icon-move",
  Action = "move",
  Key = "m", Hint = "~!Move",
  ForUnit = {
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-dropship",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-science-vessel",
    "unit-terran-scv",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-stop",
  Action = "stop",
  Key = "s", Hint = "~!Stop",
  ForUnit = {
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-dropship",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-missile-turret",
    "unit-terran-science-vessel",
    "unit-terran-scv",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-attack",
  Action = "attack",
  Key = "a", Hint = "~!Attack",
  ForUnit = {
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-scv",
    "unit-terran-missile-turret",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-patrol",
  Action = "patrol",
  Key = "p", Hint = "~!Patrol",
  ForUnit = {
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
    "unit-terran-barracks",
    "unit-terran-command-center",
    "unit-terran-starport",
  } } )

DefineButton( { Pos = 9, Level = 0, Icon = "icon-terran-liftoff",
  Action = "move",
  Key = "l", Hint = "~!Liftoff",
  ForUnit = {
    "unit-terran-barracks",
    "unit-terran-command-center",
    "unit-terran-engineering-bay",
    "unit-terran-starport",
  } } )



--
-- Allow
--
DefineAllow("unit-terran-battlecruiser",  "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-dropship",       "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-firebat",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-ghost",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-goliath",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-marine",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-science-vessel", "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-scv",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-siege-tank",     "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-vulture",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-wraith",         "AAAAAAAAAAAAAAAA")

DefineAllow("unit-terran-academy",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-armory",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-barracks",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-bunker",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-command-center",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-engineering-bay",  "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-factory",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-missile-turret",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-refinery",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-science-facility", "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-starport",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-supply-depot",     "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-comsat-station",   "AAAAAAAAAAAAAAAA")