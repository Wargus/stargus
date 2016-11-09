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
--      spells.lua - The spells.
--
--      (c) Copyright 1998-2005 by Joris Dauphin and Jimmy Salmon.
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

-- For documentation see stratagus/doc/ccl/ccl.html

DefineBoolFlags("isundead", "organic", "hero", "volatile", "mechanical")
-- mechanical for goliath, tank, dragoon, etc. Can be repaired by the scv (terran), spawn broodling spell can only hit mechanical units
--medics (broodwar) can heal organic units; marine, firebat, etc.

--
--  Speed     : just drawing
--  ShadowFly : Shadow of flying unit (0:big, 1:normal, 2:small)
--  Level     : Increase each time an upgrade is applyed to an unit.
--  CreepDistance : Distance in tiles that creep grows from a Zerg building
--  LarvaTimeout  : Timeout until a new larva spawns in a Zerg spawning pool
--
DefineVariables("Speed", "ShadowFly", {Max = 2}, "Level", "CreepDistance", {Max = 10}, "LarvaTimeout", {Max = 20})

-- And declare upgrade for dependency...
-- For human
CUpgrade:New("upgrade-holy-vision")
CUpgrade:New("upgrade-healing")
CUpgrade:New("upgrade-exorcism")
CUpgrade:New("upgrade-flame-shield")
CUpgrade:New("upgrade-fireball")
CUpgrade:New("upgrade-slow")
CUpgrade:New("upgrade-invisibility")
CUpgrade:New("upgrade-polymorph")
CUpgrade:New("upgrade-blizzard")
-- For orc
CUpgrade:New("upgrade-eye-of-kilrogg")
CUpgrade:New("upgrade-bloodlust")
CUpgrade:New("upgrade-raise-dead")
CUpgrade:New("upgrade-death-coil")
CUpgrade:New("upgrade-whirlwind")
CUpgrade:New("upgrade-haste")
CUpgrade:New("upgrade-unholy-armor")
CUpgrade:New("upgrade-runes")
CUpgrade:New("upgrade-death-and-decay")

