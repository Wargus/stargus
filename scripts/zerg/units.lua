Load("scripts/zerg/construction.lua")

Load("scripts/zerg/unit-zerg-creep-colony.lua")
Load("scripts/zerg/unit-zerg-defiler-mound.lua")
Load("scripts/zerg/unit-zerg-evolution-chamber.lua")
Load("scripts/zerg/unit-zerg-extractor.lua")
Load("scripts/zerg/unit-zerg-greater-spire.lua")
Load("scripts/zerg/unit-zerg-hatchery.lua")
Load("scripts/zerg/unit-zerg-hive.lua")
Load("scripts/zerg/unit-zerg-hydralisk-den.lua")
Load("scripts/zerg/unit-zerg-lair.lua")
Load("scripts/zerg/unit-zerg-nydus-canal.lua")
Load("scripts/zerg/unit-zerg-queens-nest.lua")
Load("scripts/zerg/unit-zerg-spawning-pool.lua")
Load("scripts/zerg/unit-zerg-spire.lua")
Load("scripts/zerg/unit-zerg-spore-colony.lua")
Load("scripts/zerg/unit-zerg-sunken-colony.lua")
Load("scripts/zerg/unit-zerg-ultralisk-cavern.lua")

Load("scripts/zerg/unit-zerg-larva.lua")

Load("scripts/zerg/unit-zerg-defiler.lua")
Load("scripts/zerg/unit-zerg-drone.lua")
Load("scripts/zerg/unit-zerg-egg.lua")
Load("scripts/zerg/unit-zerg-guardian.lua")
Load("scripts/zerg/unit-zerg-hydralisk.lua")
Load("scripts/zerg/unit-zerg-mutalisk.lua")
Load("scripts/zerg/unit-zerg-overlord.lua")
Load("scripts/zerg/unit-zerg-queen.lua")
Load("scripts/zerg/unit-zerg-scourge.lua")
Load("scripts/zerg/unit-zerg-ultralisk.lua")
Load("scripts/zerg/unit-zerg-zergling.lua")


--
-- Buttons
--
DefineButton( { Pos = 1, Level = 0, Icon = "icon-move",
  Action = "move",
  Key = "m", Hint = "~!Move",
  ForUnit = {
    "zerg-group",
	"unit-zerg-defiler",
    "unit-zerg-drone",
    "unit-zerg-guardian",
    "unit-zerg-hydralisk",
	"unit-zerg-mutalisk",
	"unit-zerg-overlord",
	"unit-zerg-queen",
	"unit-zerg-scourge",
	"unit-zerg-ultralisk",
    "unit-zerg-zergling",
  } } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-stop",
  Action = "stop",
  Key = "s", Hint = "~!Stop",
  ForUnit = {
    "zerg-group",
    "unit-zerg-defiler",
    "unit-zerg-drone",
    "unit-zerg-guardian",
    "unit-zerg-hydralisk",
    "unit-zerg-mutalisk",
    "unit-zerg-overlord",
    "unit-zerg-queen",
    "unit-zerg-scourge",
    "unit-zerg-ultralisk",
    "unit-zerg-zergling",
    "unit-zerg-spore-colony",
    "unit-zerg-sunken-colony",
  } } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-attack",
  Action = "attack",
  Key = "a", Hint = "~!Attack",
  ForUnit = {
    "zerg-group",
    "unit-zerg-defiler",
    "unit-zerg-drone",
    "unit-zerg-guardian",
    "unit-zerg-hydralisk",
    "unit-zerg-mutalisk",
    "unit-zerg-queen",
    "unit-zerg-scourge",
    "unit-zerg-ultralisk",
    "unit-zerg-zergling",
    "unit-zerg-spore-colony",
    "unit-zerg-sunken-colony",
  } } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-patrol",
  Action = "patrol",
  Key = "p", Hint = "~!Patrol",
  ForUnit = {
    "zerg-group",
    "unit-zerg-defiler",
    "unit-zerg-guardian",
    "unit-zerg-hydralisk",
    "unit-zerg-mutalisk",
    "unit-zerg-queen",
    "unit-zerg-scourge",
    "unit-zerg-ultralisk",
    "unit-zerg-zergling",
  } } )

DefineButton( { Pos = 5, Level = 0, Icon = "icon-hold-position",
  Action = "stand-ground",
  Key = "h", Hint = "~!Hold Position",
  ForUnit = {
    "zerg-group",
    "unit-zerg-defiler",
    "unit-zerg-guardian",
    "unit-zerg-hydralisk",
    "unit-zerg-mutalisk",
    "unit-zerg-queen",
    "unit-zerg-scourge",
    "unit-zerg-ultralisk",
    "unit-zerg-zergling",
  } } )

--[[
DefineButton( { Pos = 2, Level = 0, Icon = "icon-rally-point",
  Action = "move",
  Key = "r", Hint = "Set ~!Rally Point",
  ForUnit = { } } )
]]


--
-- Allow
--
DefineAllow("unit-zerg-defiler",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-larva",              "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-drone",              "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-egg",                "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-guardian",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-hydralisk",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-mutalisk",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-overlord",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-queen",              "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-scourge",            "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-ultralisk",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-zergling",           "AAAAAAAAAAAAAAAA")

DefineAllow("unit-zerg-creep-colony",       "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-defiler-mound",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-evolution-chamber",  "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-extractor",          "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-greater-spire",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-hatchery",           "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-hive",               "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-hydralisk-den",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-lair",               "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-nydus-canal",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-queens-nest",        "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-spawning-pool",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-spire",              "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-spore-colony",       "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-sunken-colony",      "AAAAAAAAAAAAAAAA")
DefineAllow("unit-zerg-ultralisk-cavern",   "AAAAAAAAAAAAAAAA")


--DefineAllow("unit-zerg-rubble-large",       "AAAAAAAAAAAAAAAA")

