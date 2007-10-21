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
--      icons.lua - Define the icons.
--
--      (c) Copyright 2005 by Jimmy Salmon
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
--      $Id$



local zerg_icons = {
  {"icon-zerg-larva", 35},
  {"icon-zerg-egg", 36},
  {"icon-zerg-zergling", 37},
  {"icon-zerg-hydralisk", 38},
  {"icon-zerg-ultralisk", 39},
  {"icon-zerg-broodling", 40},
  {"icon-zerg-drone", 41},
  {"icon-zerg-overlord", 42},
  {"icon-zerg-mutalisk", 43},
  {"icon-zerg-guardian", 44},
  {"icon-zerg-queen", 45},
  {"icon-zerg-defiler", 46},
  {"icon-zerg-scourge", 47},
  {"icon-zerg-ultralisk", 48},
  {"icon-zerg-queen", 49},
  {"icon-zerg-hatchery", 131},
  {"icon-zerg-lair", 132},
  {"icon-zerg-hive", 133},
  {"icon-zerg-nydus-canal", 134},
  {"icon-zerg-hydralisk-den", 135},
  {"icon-zerg-defiler-mound", 136},
  {"icon-zerg-greater-spire", 137},
  {"icon-zerg-queens-nest", 138},
  {"icon-zerg-evolution-chamber", 139},
  {"icon-zerg-ultralisk-cavern", 140},
  {"icon-zerg-spire", 141},
  {"icon-zerg-spawning-pool", 142},
  {"icon-zerg-creep-colony", 143},
  {"icon-zerg-spore-colony", 144},
  {"icon-zerg-sunken-colony", 146},
  {"icon-zerg-overmind-with-shell", 147},
  {"icon-zerg-overmind", 148},
  {"icon-zerg-extractor", 149},
  {"icon-zerg-mature-chrysalis", 150},
  {"icon-zerg-cerebrate", 151},
  {"icon-zerg-cerebrate-daggoth", 152},
  {"icon-zerg-burrow-down", 259},
  {"icon-zerg-burrow-up", 259},
}

local pos = table.getn(icons) + 1

for i = 1,table.getn(zerg_icons) do
  icons[pos] = zerg_icons[i]
  pos = pos + 1
end


