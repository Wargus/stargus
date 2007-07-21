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
--      ai.lua - Define the AI.
--
--      (c) Copyright 2007 by Jimmy Salmon
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
--      $Id: ai.lua 983 2004-02-29 21:18:19Z jsalmon3 $


race1 = "terran"
race2 = "zerg"
race3 = "terran"
race4 = "protoss"


--=============================================================================
--
--  AI helper table, the AI must know where to build units,
--  where to research spells, where to upgrade units.
--  If this is allowed and which dependencies exists, isn't
--  handled here. (see upgrade.lua)
--
--  NOTE: perhaps this could later be used to build the buttons?
--
--  DefineAiHelper(list)
--

--;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
--  * Race terran.
--;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

DefineAiHelper(
  {"build", "unit-terran-scv",
  "unit-terran-academy", "unit-terran-armory", "unit-terran-barracks",
  "unit-terran-bunker", "unit-terran-command-center", "unit-terran-engineering-bay",
  "unit-terran-factory", "unit-terran-missile-turret", "unit-terran-refinery",
  "unit-terran-science-facility", "unit-terran-starport", "unit-terran-supply-depot"},

  {"train", "unit-terran-barracks", "unit-terran-marine", "unit-terran-firebat", "unit-terran-ghost"},
  {"train", "unit-terran-command-center", "unit-terran-scv"},
  {"train", "unit-terran-factory", "unit-terran-vulture", "unit-terran-siege-tank", "unit-terran-goliath"},
  {"train", "unit-terran-starport", "unit-terran-wraith", "unit-terran-dropship", "unit-terran-science-vessel", "unit-terran-battlecruiser"},

  {"research", "unit-terran-academy", "upgrade-terran-u238-shells", "upgrade-terran-stim-pack"},
  {"research", "unit-terran-engineering-bay",
  "upgrade-terran-infantry-weapons1", "upgrade-terran-infantry-weapons2", "upgrade-terran-infantry-weapons3",
  "upgrade-terran-infantry-armor1", "upgrade-terran-infantry-armor2", "upgrade-terran-infantry-armor3"},

  {"repair", "unit-terran-scv",
  "unit-terran-academy", "unit-terran-armory", "unit-terran-barracks",
  "unit-terran-bunker", "unit-terran-command-center", "unit-terran-engineering-bay",
  "unit-terran-factory", "unit-terran-missile-turret", "unit-terran-refinery",
  "unit-terran-science-facility", "unit-terran-starport", "unit-terran-supply-depot"},

  {"unit-limit", "unit-terran-supply-depot", "food"}
)


Load("scripts/ai/terran.lua")

function AiPassive()
end

DefineAi("ai-passive", "*", "ai-passive", AiPassive)
