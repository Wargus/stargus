--       _________ __                 __
--      /   _____//  |_____________ _/  |______     ____  __ __  ______
--      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
--      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ \ 
--     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
--             \/                  \/          \//_____/            \/ 
--  ______________________                           ______________________
--                        T H E   W A R   B E G I N S
--         Stratagus - A free fantasy real time strategy game engine
--
--      stratagus.lua - The craft configuration language.
--
--      (c) Copyright 2005-2006 by Jimmy Salmon
--
--      This program is free software; you can redistribute it and/or modify
--      it under the terms of the GNU General Public License as published by
--      the Free Software Foundation; either version 2 of the License, or
--      (at your option) any later version.
--  
--      This program is distributed in the hope that it will be useful,
--      but WITHOUT ANY WARRANTY; without even the implied warranty of
--      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--      GNU General Public License for more details.
--  
--      You should have received a copy of the GNU General Public License
--      along with this program; if not, write to the Free Software
--      Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
--

-- For documentation see stratagus/doc/scripts/scripts.html
--print("Stratagus default config file loading ...\n")

-- Config file version
--(define media-version (list 'wc2 'class 'wc2 'version '(1 18 0)))

-------------------------------------------------------------------------------
--  Version
-------------------------------------------------------------------------------

Name = "Stargus"
Version = "3.1.3"
Homepage = "https://github.com/Wargus/stargus"
Licence = "GPL v2"
Copyright = "Copyright (c) 1998-2015 by The Stratagus Project and Pali Rohar"

-- activate debugging
pcall(function() require("scripts/mobdebug").start() end)

-------------------------------------------------------------------------------
--  Config-Part
-------------------------------------------------------------------------------

InitFuncs = {}
function InitFuncs:add(f)
  table.insert(self, f)
end

function InitGameVariables()
  for i=1,table.getn(InitFuncs) do
    InitFuncs[i]()
  end
end

--  Edit the next sections to get your look and feel.
--  Note, some of those values are overridden by user preferences,
--  see preferences.lua

--  Enter your default title screen.
SetTitleScreens(
  {Image = "videos/blizzard.ogv"},
  {Image = "ui/title.png", Music = "music/title.ogg",  Timeout = 5}
)

--  Set the game name. It's used so we can mantain different savegames
--  and setting. Might also be used for multiplayer.
SetGameName("sc")
SetFullGameName(Name)

SetSelectionStyle("ellipse", 0.589)
Preference.ShowSightRange = false
Preference.ShowAttackRange = false
Preference.ShowReactionRange = false

Preference.ShowOrders = 2

-- SetMetaServer("stratagus.game-host.org", 7775)

--  Enable/disable the short display of the orders after command.
--  FIXME: planned
--(set-order-feedback! #t)
--(set-order-feedback! #f)

-------------------------------------------------------------------------------
--  Game modification

--  Edit this to enable/disable extended features.
--    Currently enables some additional buttons.
extensions = true
--extensions = false

--  Edit this to enable/disable the training queues.
SetTrainingQueue(true)
--SetTrainingQueue(false)

--  Edit this to enable/disable building capture.
--SetBuildingCapture(true)
SetBuildingCapture(false)

--  Edit this to enable/disable the reveal of the attacker.
--SetRevealAttacker(true)
SetRevealAttacker(true)
SetRevelationType("all-units")

-------------------------------------------------------------------------------

--  If you prefer fighters are attacking by right clicking empty space
--  uncomment this (you must comment the next).
--  FIXME: this option will be renamed
--RightButtonAttacks()

--  If you prefer fighters are moving by right clicking empty space
--  uncomment this.
--  FIXME: this option will be renamed
RightButtonMoves()

--  Set the name of the missile to use when clicking
SetClickMissile("missile-green-cross")

--  Set the name of the missile to use when displaying damage
SetDamageMissile("missile-hit")

--  Edit this to enable/disable grabbing the mouse.
SetGrabMouse(false)

--  Edit this to enable/disable stopping scrolling on mouse leave.
SetLeaveStops(true)

--  Edit this to enable/disable mouse scrolling.
SetMouseScroll(true)
--SetMouseScroll(false)

--  Edit this to enable/disable keyboard scrolling.
SetKeyScroll(true)
--SetKeyScroll(false)

--  While middle-mouse is pressed:
--  Pixels to move per scrolled mouse pixel, negative = reversed
SetMouseScrollSpeedDefault(4)

--  Same if Control is pressed
SetMouseScrollSpeedControl(15)

--  Change next, for the wanted double-click delay (in ms).
SetDoubleClickDelay(300)

--  Change next, for the wanted hold-click delay (in ms).
SetHoldClickDelay(1000)

--  Uncomment next, to reveal the complete map.
--RevealMap()

--  Choose your default fog of war state (enabled #t/disabled #f).
--    disabled is a C&C like fog of war.
SetFogOfWar(true)
--SetFogOfWar(false)
SetFogOfWarBlur(2.0, 1.5, 3) -- radiuses for simple and bilinear FOW postprocessing, number of blur iterations
-- Set opacity levels of fog for explored, "known"(when map revealed) and hidden tiles
SetFogOfWarOpacityLevels(0x7F, 0xBE, 0xFE)
-- Set opacity levels of fog for explored, "known"(when map revealed) and hidden tiles in the minimap
SetMMFogOfWarOpacityLevels(0x55, 0xAA, 0xFF) -- default values

SetFogOfWarType("enhanced") -- set to "fast", "tiled", or "enhanced"
SetFogOfWarBilinear(true)

if CanAccessFile("tilesets/fog.png") then
  SetFogOfWarGraphics("tilesets/fog.png")
else
  SetFogOfWarGraphics("contrib/fog.png")
end

SetTileSize(32, 32)

--  Choose your default for minimap with/without terrain.
SetMinimapTerrain(true)
--SetMinimapTerrain(false)

Preference.GrayscaleIcons = true

SetFontCodePage(437)

-------------------------------------------------------------------------------

--  Define default resources

-- FIXME: Must be removed: Use and write (define-resource)
--
--  (define-resource 'gold 'name "Gold"
--    'start-resource-default 2000
--    'start-resource-low 2000
--    'start-resource-medium 5000
--    'start-resource-high 10000
--    'income 100)
--  FIXME: Must describe how geting resources work.
--

DefineDefaultIncomes(
  0, 100, 100, 100, 100, 100, 100)

DefineDefaultActions(
  "stop", "harvest", "harvest", "unused", "unused", "unused", "unused")

DefineDefaultResourceNames(
  "time", "minerals", "gas", "unused", "unused", "unused", "unused")

DefineDefaultResourceAmounts(
  "minerals", 100000,
  "gas", 50000)

DefineDefaultResourceMaxAmounts(-1, -1, -1, -1, -1, -1)
  
-------------------------------------------------------------------------------

DefinePlayerColorIndex(8, 8)

DefinePlayerColors({
  "red", {{244, 4, 4}, {168, 8, 8}, {168, 8, 8}, {132, 4, 4},
    {96, 0, 0}, {72, 0, 0}, {52, 0, 0}, {16, 0, 0}},
  "blue", {{12, 72, 204}, {8, 52, 152}, {8, 52, 152}, {20, 52, 124},
    {4, 32, 100}, {0, 8, 80}, { 0, 16, 52}, { 0, 0, 24}},
  "green", {{44, 180, 148}, {32, 144, 112}, {32, 144, 112}, {32, 144, 112},
    {16, 84, 60}, {16, 84, 60}, {16, 84, 60}, {0, 40, 0}},
  "violet", {{136, 64, 156}, {136, 64, 156}, {136, 64, 156}, {104, 48, 120},
    {72, 28, 80}, {72, 28, 80}, {72, 28, 80}, {56, 16, 32}},
  "orange", {{248, 140, 20}, {232, 120, 36}, {188, 104, 36}, {160, 84, 28},
    {124, 64, 24}, {92, 44, 20}, {52, 32, 12}, {28, 16, 8}},
  "black", {{112, 48, 20}, {92, 44, 20}, {92, 44, 20}, {68, 52, 8},
    {68, 52, 8}, {52, 32, 12}, {52, 16, 8}, {28, 16, 8}},
  "white", {{204, 224, 208}, {196, 192, 188}, {176, 176, 176}, {152, 148, 140},
    {132, 116, 116}, {88, 88, 104}, {68, 68, 68}, {40, 40, 48}},
  "yellow", {{252, 252, 56}, {220, 220, 60}, {188, 184, 52}, {156, 144, 64},
    {112, 100, 32}, {92, 84, 20}, {68, 52, 8}, {28, 16, 8}},

  "green", {{8, 128, 8}, {0, 100, 0}, {0, 100, 0}, {0, 100, 0},
    {0, 68, 0}, {0, 68, 0}, {0, 68, 0}, {0, 40, 0}},
  "light-yellow", {{252, 252, 124}, {252, 252, 124}, {204, 184, 96}, {188, 164, 92},
    {156, 144, 64}, {116, 104, 56}, {104, 76, 52}, {56, 48, 36}},
  "green", {{44, 180, 148}, {20, 132, 92}, {4, 84, 44}, {0, 40, 12},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  "violet", {{152, 72, 176}, {116, 44, 132}, {80, 24, 88}, {44, 8, 44},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  "orange", {{248, 140, 20}, {200, 96, 16}, {152, 60, 16}, {108, 32, 12},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  "black", {{40, 40, 60}, {28, 28, 44}, {20, 20, 32}, {12, 12, 20},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  "white", {{224, 224, 224}, {152, 152, 180}, {84, 84, 128}, {36, 40, 76},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  "yellow", {{252, 252, 72}, {228, 204, 40}, {204, 160, 16}, {180, 116, 0},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
})


-------------------------------------------------------------------------------

--  Edit next to increase the speed, for debugging.

--  Decrease the mining time by this factor.
--SetSpeedResourcesHarvest("gold", 10)
--  Decrease the time in a gold deposit by this factor.
--SetSpeedResourcesReturn("gold", 10)
--  Decrease the time for chopping a tree by this factor.
--SetSpeedResourcesHarvest("wood", 10)
--  Decrease the time in a wood deposit by this factor.
--SetSpeedResourcesReturn("wood", 10)
--  Decrease the time for haul oil by this factor.
--SetSpeedResourcesHarvest("oil", 10)
--  Decrease the time in an oil deposit by this factor.
--SetSpeedResourcesReturn("oil", 10)
--  Decrease the time to build a unit by this factor.
--SetSpeedBuild(10)
--  Decrease the time to train a unit by this factor.
--SetSpeedTrain(10)
--  Decrease the time to upgrade a unit by this factor.
--SetSpeedUpgrade(10)
--  Decrease the time to research by this factor.
--SetSpeedResearch(10)

--  You can do all the above with this
InitFuncs:add(function()
  SetSpeeds(1)
end)

-------------------------------------------------------------------------------

AStar("fixed-unit-cost", 1000, "moving-unit-cost", 20, "know-unseen-terrain", "unseen-terrain-cost", 2)

-------------------------------------------------------------------------------

--  Maximum number of selectable units
SetMaxSelectable(18)

--  All player food unit limit
SetAllPlayersUnitLimit(400)
--  All player building limit
SetAllPlayersBuildingLimit(400)
--  All player total unit limit
SetAllPlayersTotalUnitLimit(1000)

-------------------------------------------------------------------------------
--  Default triggers for single player
--    (FIXME: must be combined with game types)

function SinglePlayerTriggers()
  function SinglePlayerTriggers()
    AddTrigger(
      function() return GetPlayerData(GetThisPlayer(), "TotalNumUnits") == 0 end,
      function() return ActionDefeat() end)
  
    AddTrigger(
      function() return GetNumOpponents(GetThisPlayer()) == 0 end,
      function() return ActionVictory() end)
  end
end

-------------------------------------------------------------------------------
--  Tables-Part
-------------------------------------------------------------------------------

Load("preferences.lua")

if (preferences == nil) then
  preferences = {
    VideoWidth = 800,
    VideoHeight = 600,
    VideoFullScreen = false,
    PlayerName = "Player",
    FogOfWar = true,
    ShowCommandKey = true,
    GroupKeys = "0123456789`",
    GameSpeed = 30,
    EffectsEnabled = true,
    EffectsVolume = 128,
    MusicEnabled = true,
    MusicVolume = 128,
    StratagusTranslation = "",
    GameTranslation = "",
    TipNumber = 0,
    ShowTips = true,
    GrabMouse = false,
  }
end

SetVideoResolution(preferences.VideoWidth, preferences.VideoHeight)
SetVideoFullScreen(preferences.VideoFullScreen)
SetLocalPlayerName(preferences.PlayerName)
SetFogOfWar(preferences.FogOfWar)
UI.ButtonPanel.ShowCommandKey = preferences.ShowCommandKey
SetGroupKeys(preferences.GroupKeys)
SetGameSpeed(preferences.GameSpeed)
SetEffectsEnabled(preferences.EffectsEnabled)
SetEffectsVolume(preferences.EffectsVolume)
SetMusicEnabled(preferences.MusicEnabled)
SetMusicVolume(preferences.MusicVolume)
SetTranslationsFiles(preferences.StratagusTranslation, preferences.GameTranslation)
SetGrabMouse(preferences.GrabMouse)

--- Uses Stratagus Library path!
Load("scripts/sc.lua")

Load("scripts/icons.lua")
Load("scripts/sound.lua")
Load("scripts/missiles.lua")
Load("scripts/spells.lua")
Load("scripts/units.lua")
Load("scripts/upgrade.lua")
Load("scripts/fonts.lua")
Load("scripts/buttons.lua")
Load("scripts/ui.lua")
Load("scripts/ai.lua")
Load("scripts/commands.lua")
Load("scripts/cheats.lua")

--print("... ready!\n")
