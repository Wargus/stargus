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
--      cheats.lua - Cheats
--
--      (c) Copyright 2001-2007 by Lutz Sammer and Jimmy Salmon
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

speedcheat = false
godcheat = false

function HandleCheats(str)
  local resources = { "minerals", "gas" }

  if (str == "show me the money") then
    AddMessage("Cheat Enabled")
    SetPlayerData(GetThisPlayer(), "Resources", "minerals",
      GetPlayerData(GetThisPlayer(), "Resources", "minerals") + 10000)
    SetPlayerData(GetThisPlayer(), "Resources", "gas",
      GetPlayerData(GetThisPlayer(), "Resources", "gas") + 10000)

  elseif (str == "whats mine is mine") then
    AddMessage("Cheat Enabled")
    SetPlayerData(GetThisPlayer(), "Resources", "minerals",
      GetPlayerData(GetThisPlayer(), "Resources", "minerals") + 10000)

  elseif (str == "breathe deep") then
    AddMessage("Cheat Enabled")
    SetPlayerData(GetThisPlayer(), "Resources", "gas",
      GetPlayerData(GetThisPlayer(), "Resources", "gas") + 10000)

  elseif (str == "black sheep wall") then
    AddMessage("Cheat Enabled")
    SetFogOfWar(false)
    RevealMap()

  elseif (str == "war aint what it used to be") then
    AddMessage("Cheat Enabled")
    SetFogOfWar(false)

  elseif (str == "operation cwal") then
    if (speedcheat) then
      speedcheat = false
      AddMessage("Cheat Disabled")
      for i = 1,table.getn(resources) do
        SetSpeedResourcesHarvest(resources[i], 1)
        SetSpeedResourcesReturn(resources[i], 1)
      end
      SetSpeedBuild(1)
      SetSpeedTrain(1)
      SetSpeedUpgrade(1)
      SetSpeedResearch(1)
    else
      speedcheat = true
      AddMessage("Cheat Enabled")
      for i = 1,table.getn(resources) do
        SetSpeedResourcesHarvest(resources[i], 10)
        SetSpeedResourcesReturn(resources[i], 10)
      end
      SetSpeedBuild(10)
      SetSpeedTrain(10)
      SetSpeedUpgrade(10)
      SetSpeedResearch(10)
      for i = 1,table.getn(resources) do
        SetPlayerData(GetThisPlayer(), "Resources", resources[i],
          GetPlayerData(GetThisPlayer(), "Resources", resources[i]) + 32000)
      end
    end

  elseif (str == "there is no cow level") then
    AddMessage("Cheat Enabled")
    ActionVictory()

  elseif (str == "game over man") then
    AddMessage("Cheat Enabled")
    ActionDefeat()

  elseif (str == "power overwhelming") then
    if (godcheat) then
      godcheat = false
      SetGodMode(false)
      AddMessage("Cheat Disabled")
    else
      godcheat = true
      SetGodMode(true)
      AddMessage("Cheat Enabled")
    end

  else
    return false
  end
  return true
end
