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



local protoss_icons = {
  {"icon-protoss-corsair", 60},
  {"icon-protoss-dark-templar", 61},
  {"icon-protoss-dark-archon", 63},
  {"icon-protoss-probe", 64},
  {"icon-protoss-zealot", 65},
  {"icon-protoss-dragoon", 66},
  {"icon-protoss-high-templar", 67},
  {"icon-protoss-archon", 68},
  {"icon-protoss-shuttle", 69},
  {"icon-protoss-scout", 70},
  {"icon-protoss-arbiter", 71},
  {"icon-protoss-carrier", 72},
  {"icon-protoss-interceptor", 73},
  {"icon-protoss-dark-templar-hero", 74},
  {"icon-protoss-zeratul-dark-templar", 75},
  {"icon-protoss-tassadar-zeratul-archon", 76},
  {"icon-protoss-fenix-zealot", 77},
  {"icon-protoss-fenix-dragoon", 78},
  {"icon-protoss-tassadar-templar", 79},
  {"icon-protoss-reaver", 83},
  {"icon-protoss-observer", 84},
  {"icon-protoss-scarab", 85},
  {"icon-protoss-nexus", 154},
  {"icon-protoss-robotics-facility", 155},
  {"icon-protoss-pylon", 156},
  {"icon-protoss-assimilator", 157},
  {"icon-protoss-observatory", 159},
  {"icon-protoss-gateway", 160},
  {"icon-protoss-photon-cannon", 162},
  {"icon-protoss-citadel-of-adun", 163},
  {"icon-protoss-cybernetics-core", 164},
  {"icon-protoss-templar-archives", 165},
  {"icon-protoss-forge", 166},
  {"icon-protoss-stargate", 167},
  {"icon-protoss-fleet-beacon", 169},
  {"icon-protoss-arbiter-tribunal", 170},
  {"icon-protoss-robotics-support-bay", 171},
  {"icon-protoss-shield-battery", 172},
  {"icon-protoss-temple", 174},
}

local pos = table.getn(icons) + 1

for i = 1,table.getn(protoss_icons) do
  icons[pos] = protoss_icons[i]
  pos = pos + 1
end


