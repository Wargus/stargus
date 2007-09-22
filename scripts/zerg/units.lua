Load("scripts/zerg/neutral.lua")
Load("scripts/zerg/unit-zerg-hatchery.lua")
Load("scripts/zerg/unit-zerg-drone.lua")
Load("scripts/zerg/unit-zerg-zergling.lua")
Load("scripts/zerg/unit-zerg-hydralisk.lua")
Load("scripts/zerg/unit-zerg-spawning-pool.lua")
Load("scripts/zerg/unit-zerg-ultralisk.lua")
Load("scripts/zerg/unit-zerg-extractor.lua")
Load("scripts/zerg/unit-zerg-mut.lua")
Load("scripts/zerg/unit-zerg-overlord.lua")
Load("scripts/zerg/unit-zerg-queen.lua")
Load("scripts/zerg/unit-zerg-sunken-colony.lua")
Load("scripts/zerg/unit-zerg-creep-colony.lua")
Load("scripts/zerg/unit-zerg-defiler.lua")
Load("scripts/zerg/unit-zerg-hydralisk-den.lua")
Load("scripts/zerg/unit-zerg-ultralisk-cavern.lua")
Load("scripts/zerg/unit-zerg-evolution-chamber.lua")
Load("scripts/zerg/unit-zerg-spire.lua")
Load("scripts/zerg/unit-zerg-greater-spire.lua")
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
	"unit-zerg-overlord",
    "unit-zerg-hydralisk",
	"unit-zerg-ultralisk",
	"unit-zerg-defiler",
	"unit-zerg-mut",
	"unit-zerg-queen",
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
	"unit-zerg-mut",
	"unit-zerg-overlord",
    "unit-zerg-hydralisk",
	"unit-zerg-queen",
    "unit-zerg-drone",
    "unit-zerg-zergling",
	"unit-zerg-ultralisk",
	"unit-zerg-defiler",
	"unit-zerg-sunken-colony",
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
	"unit-zerg-mut",
	"unit-zerg-ultralisk",
    "unit-zerg-hydralisk",
    "unit-zerg-drone",
    "unit-zerg-zergling",
	"unit-zerg-sunken-colony",
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
	"unit-zerg-mut",
	"unit-zerg-ultralisk",
	"unit-zerg-overlord",
    "unit-zerg-hydralisk",
	"unit-zerg-queen",
	"unit-zerg-defiler",
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
	"unit-zerg-mut",
	"unit-zerg-queen",
	"unit-zerg-overlord",
    "unit-zerg-hydralisk",
	"unit-zerg-defiler",
    "unit-zerg-ultralisk",
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
    "unit-zerg-lair",
    "unit-zerg-hive",
    "unit-terran-starport",
  } } )



--
-- Allow
--
DefineAllow("unit-zerg-drone",              "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-zergling",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-hydralisk",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-ultralisk",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-mut",                "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-overlord",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-queen",              "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-drone",              "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-defiler",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-vulture",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-wraith",           "AAAAAAAAAAAAAAAA")

DefineAllow("unit-zerg-hatchery",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-spawning-pool",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-extractor",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-sunken-colony",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-cc",                 "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-hydralisk-den",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-ultralisk-cavern",   "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-evolution-chamber",  "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-spire",              "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-greater-spire",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-starport",         "AAAAAAAAAAAAAAAA")
DefineAllow("unit-terran-supply-depot",     "AAAAAAAAAAAAAAAA")

