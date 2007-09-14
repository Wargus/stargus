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
--      $Id: icons.lua 1264 2005-07-04 13:53:05Z jsalmon3 $



local protoss_icons = {
  {"icon-protoss-nexus", 154},
  {"icon-protoss-probe", 64},
  {"icon-protoss-zealot", 65},
  {"icon-protoss-pylon", 40},
  {"icon-protoss-dragoon", 66},
  {"icon-protoss-gateway", 43},
  {"icon-protoss-scourge", 47},
  {"icon-protoss-queen", 45},
  {"icon-protoss-ultralisk", 48},
  {"icon-protoss-defiler", 46},
  {"icon-protoss-hatchery", 131},
  {"icon-protoss-extractor", 160},
  {"icon-protoss-spawning-pool", 142},
  {"icon-protoss-drone-scv", 7},
  {"icon-protoss-hatchery", 115},

}

pos = table.getn(icons)+1;

for i = 1,table.getn(protoss_icons) do
	icons[pos] = protoss_icons[i]
	pos = pos + 1
end


