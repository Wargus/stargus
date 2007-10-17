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


local terran_icons = {
  {"icon-terran-marine", 0},
  {"icon-terran-ghost", 1},
  {"icon-terran-vulture", 2},
  {"icon-terran-goliath", 3},
  {"icon-terran-tank", 5},
  {"icon-terran-scv", 7},
  {"icon-terran-wraith", 8},
  {"icon-terran-science-vessel", 9},
  {"icon-terran-gui-montang", 10},
  {"icon-terran-dropship", 11},
  {"icon-terran-battlecruiser", 12},
  {"icon-terran-vulture-spider-mine", 13},
  {"icon-terran-nuclear-missile", 14},
  {"icon-terran-terran-civilian", 15},
  {"icon-terran-sarah-kerrigan", 16},
  {"icon-terran-jim-raynor-vulture", 19},
  {"icon-terran-jim-raynor-marine", 20},
  {"icon-terran-siege-tank", 31},
  {"icon-terran-firebat", 32},
  {"icon-terran-command-center", 106},
  {"icon-terran-comsat-station", 107},
  {"icon-terran-nuclear-silo", 108},
  {"icon-terran-supply-depot", 109},
  {"icon-terran-refinery", 110},
  {"icon-terran-barracks", 111},
  {"icon-terran-academy", 112},
  {"icon-terran-factory", 113},
  {"icon-terran-starport", 114},
  {"icon-terran-control-tower", 115},
  {"icon-terran-science-facility", 116},
  {"icon-terran-covert-ops", 117},
  {"icon-terran-physics-lab", 118},
  {"icon-terran-machine-shop", 120},
  {"icon-terran-engineering-bay", 122},
  {"icon-terran-armory", 123},
  {"icon-terran-missile-turret", 124},
  {"icon-terran-bunker", 125},
  {"icon-terran-stim-pack", 237},
  {"icon-terran-u238-shells", 238},
  {"icon-terran-emp-shockwave", 241},
  {"icon-terran-irradiate", 242},
  {"icon-terran-spider-mines", 243},
  {"icon-terran-siege-tank", 245},
  {"icon-terran-titan-reactor", 248},
  {"icon-terran-scanner-sweep", 250},
  {"icon-terran-yamato-gun", 251},
  {"icon-terran-cloak", 252},
  {"icon-terran-liftoff", 282},
  {"icon-terran-land", 283},
  {"icon-terran-apollo-reactor", 284},
  {"icon-terran-colossus-reactor", 285},
  {"icon-terran-ion-thrusters", 287},
  {"icon-terran-upgrade-infantry-weapons", 288},
  {"icon-terran-upgrade-vehicle-weapons", 289},
  {"icon-terran-upgrade-ship-weapons", 290},
  {"icon-terran-upgrade-ship-plating", 291},
  {"icon-terran-upgrade-infantry-armor", 292},
  {"icon-terran-upgrade-ship-plating", 293},
  {"icon-terran-nuke", 311},
}

pos = table.getn(icons)+1;

for i = 1,table.getn(terran_icons) do
	icons[pos] = terran_icons[i]
	pos = pos + 1
end


