Load("scripts/zerg/unit-zerg-hatchery.lua")
Load("scripts/protoss/unit-protoss-probe.lua")
Load("scripts/zerg/unit-zerg-zergling.lua")
Load("scripts/zerg/unit-zerg-hydralisk.lua")
--Load("scripts/zerg/unit-zerg-spawning-pool.lua")
Load("scripts/zerg/unit-zerg-overlord.lua")

--
-- Buttons
--
DefineButton( { Pos = 1, Level = 0, Icon = "icon-move",
  Action = "move",
  Key = "m", Hint = "~!Move",
  ForUnit = {
    "zerg-group",
    "unit-zerg-drone",
    "unit-zerg-zergling",
    "unit-zerg-hydralisk",
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-dropship",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-science-vessel",
    "unit-zerg-drone",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-stop",
  Action = "stop",
  Key = "s", Hint = "~!Stop",
  ForUnit = {
    "zerg-group",
    "unit-zerg-hydralisk",
    "unit-zerg-drone",
    "unit-zerg-zergling",
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-dropship",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-terran-missile-turret",
    "unit-terran-science-vessel",
    "unit-zerg-drone",
    "unit-terran-siege-tank",
    "unit-terran-vulture",
    "unit-terran-wraith",
  } } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-attack",
  Action = "attack",
  Key = "a", Hint = "~!Attack",
  ForUnit = {
    "zerg-group",
    "unit-zerg-hydralisk",
    "unit-zerg-drone",
    "unit-zerg-zergling",
    "terran-group",
    "unit-terran-battlecruiser",
    "unit-terran-firebat",
    "unit-terran-ghost",
    "unit-terran-goliath",
    "unit-terran-marine",
    "unit-zerg-drone",
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
    "unit-zerg-hydralisk",
    "unit-zerg-drone",
    "unit-zerg-zergling",
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
    "unit-zerg-hydralisk",
    "unit-zerg-drone",
    "unit-zerg-zergling",
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
    "unit-zerg-hatchery",
    "unit-terran-barracks",
    "unit-zerg-hatchery",
    "unit-terran-starport",
  } } )



--
-- Allow
--
DefineAllow("unit-zerg-drone",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-zergling",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-hydralisk",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-ghost",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-goliath",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-marine",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-science-vessel", "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-drone",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-siege-tank",     "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-vulture",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-wraith",         "AAAAAAAAAAAAAAAA")

DefineAllow("unit-zerg-hatchery",          "AAAAAAAAAAAAAAAA")
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

