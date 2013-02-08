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
--      wc2.lua - WC2 compatibility level
--
--      (c) Copyright 2001-2006 by Lutz Sammer and Jimmy Salmon
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

DefineRaceNames(
  "race", {
    "name", "terran",
    "display", "Terran",
    "visible"},
  "race", {
    "name", "zerg",
    "display", "Zerg",
    "visible"},
  "race", {
    "name", "protoss",
    "display", "Protoss",
    "visible"},
  "race", {
    "name", "neutral",
    "display", "Neutral"})


local t = {
  {"unit-terran-scv", "unit-zerg-drone", "unit-protoss-probe"},
  {"unit-terran-command-center", "unit-zerg-hatchery", "unit-protoss-nexus"},
}

local TerranEquivalent = {}
local ZergEquivalent = {}
local ProtossEquivalent = {}

for i=1,table.getn(t) do
  TerranEquivalent[t[i][2]] = t[i][1]
  TerranEquivalent[t[i][3]] = t[i][1]
  ZergEquivalent[t[i][1]] = t[i][2]
  ZergEquivalent[t[i][3]] = t[i][2]
  ProtossEquivalent[t[i][1]] = t[i][3]
  ProtossEquivalent[t[i][2]] = t[i][3]
end

-- Convert a unit type to the equivalent for a different race
function ConvertUnitType(unittype, race)
  local equiv

  if (race == "terran") then
    equiv = TerranEquivalent[unittype]
  elseif (race == "zerg") then
    equiv = ZergEquivalent[unittype]
  else
    equiv = ProtossEquivalent[unittype]
  end

  if (equiv ~= nil) then
    return equiv
  else
    return unittype
  end
end


if (OldSetPlayerData == nil) then
  OldSetPlayerData = SetPlayerData
end

-- Override with game settings
function SetPlayerData(player, data, arg1, arg2)
  if (GameCycle ~= 0) then
    return OldSetPlayerData(player, data, arg1, arg2)
  end

  local res = {arg2, arg2}

  if (data == "RaceName") then
    -- FIXME: support multiplayer
    if (ThisPlayer ~= nil and ThisPlayer.Index == player) then
      if (GameSettings.Presets[0].Race == 1) then
        arg1 = "terran"
      elseif (GameSettings.Presets[0].Race == 2) then
        arg1 = "zerg"
	SetMusic("zerg")
      elseif (GameSettings.Presets[0].Race == 3) then
        arg1 = "protoss"
	SetMusic("protoss")
      end
    end
  elseif (data == "Resources") then
    res = {50, 0}
    if (arg1 == "minerals") then
      arg2 = res[1]
    elseif (arg1 == "gas") then
      arg2 = res[2]
    end
  end

  OldSetPlayerData(player, data, arg1, arg2)


  if (data == "RaceName") then
    -- If this is 1 peasant mode add the peasant now
    if (GameSettings.NumUnits == 1) then
      if (player ~= 15 and Players[player].Type ~= PlayerNobody) then
        local unittype = ConvertUnitType("unit-terran-scv", GetPlayerData(player, "RaceName"))
        CreateUnit(unittype, player, {Players[player].StartPos.x, Players[player].StartPos.y})
      end
    end
    -- Set AI
    if (arg1 == "terran") then
      SetAiType(player, "terran-ai")
    elseif (arg1 == "zerg") then
      SetAiType(player, "zerg-ai")
    else
      SetAiType(player, "protoss-ai")
    end
  end
end

if (OldDefinePlayerTypes == nil) then
  OldDefinePlayerTypes = DefinePlayerTypes
end

function DefinePlayerTypes(p1, p2, p3, p4, p5, p6, p7, p8)
  local p = {p1, p2, p3, p4, p5, p6, p7, p8}
  local foundperson = false
  local nump = GameSettings.Opponents
  if (nump == 0) then nump = 8 end

  -- FIXME: should randomly pick players to use
  for i=1,8 do
    if (p[i] == "person" or p[i] == "computer") then
      if (p[i] == "person" and foundperson == false) then
        foundperson = true
      else
        if (nump == 0) then
          p[i] = "nobody"
        else
          nump = nump - 1
        end
      end
    end
  end

  OldDefinePlayerTypes(p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8])
end

function MapLoaded()
  for i=0,7 do
    if (Players[i].Type ~= PlayerNobody) then
      if (Players[i]:GetUnitCount() == 0) then
        CreateUnit(ConvertUnitType("unit-terran-command-center", GetPlayerData(i, "RaceName")),
          i, {Players[i].StartPos.x, Players[i].StartPos.y})
        for j=0,3 do
          CreateUnit(ConvertUnitType("unit-terran-scv", GetPlayerData(i, "RaceName")),
            i, {Players[i].StartPos.x + j, Players[i].StartPos.y + 3})
        end
      end
    end
  end

  LoadUI(GetPlayerData(GetThisPlayer(), "RaceName"))
end

