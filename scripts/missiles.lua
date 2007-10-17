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
--      missiles.lua - Define the used missiles.
--
--      (c) Copyright 1998-2004 by Lutz Sammer, Fabrice Rossi,
--                                 Jimmy Salmon and Crestez Leonard
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
--      $Id: missiles.lua 1253 2005-07-03 14:48:14Z jsalmon3 $


Load("scripts/terran/missiles.lua")
Load("scripts/zerg/missiles.lua")

DefineMissileType("missile-small-fire",
  { File = "neutral/building burnc.png", Size = {64, 96}, Frames = 6, NumDirections = 1,
  DrawLevel = 200, Class = "missile-class-fire", Sleep = 8, Speed = 16, Range = 1 } )

DefineMissileType("missile-big-fire",
  { File = "neutral/building burnf.png", Size = {64, 96}, Frames = 10, NumDirections = 1,
  DrawLevel = 200, Class = "missile-class-fire", Sleep = 8, Speed = 16, Range = 1 } )

DefineMissileType("missile-impact",
  { File = "neutral/missiles/blastcan.png", Size = {32, 32}, Frames = 17, NumDirections = 1,
  DrawLevel = 50, Class = "missile-class-stay", Sleep = 1, Speed = 16, Range = 1 } )

DefineMissileType("missile-explosion",
  { File = "neutral/missiles/explo1.png", Size = {44, 59}, Frames = 10, NumDirections = 1,
  DrawLevel = 50, Class = "missile-class-stay", Sleep = 1, Speed = 16, Range = 1 } )

DefineMissileType("missile-small-cannon",
  { File = "neutral/missiles/blastcan.png", Size = {32, 32}, Frames = 17, NumDirections = 5,
  DrawLevel = 50, ImpactSound = "explosion",
  Class = "missile-class-parabolic", Sleep = 1, Speed = 16, Range = 1,
  ImpactMissile = "missile-cannon-explosion" } )

DefineMissileType("missile-cannon-explosion",
  { File = "neutral/missiles/blastcan.png", Size = {32, 32}, Frames = 17, NumDirections = 1,
  DrawLevel = 50, Class = "missile-class-stay", Sleep = 1, Speed = 16, Range = 1 } )

DefineMissileType("missile-green-cross",
  { File = "ui/cursors/targg.png", Size = {128, 128}, Frames = 2, NumDirections = 1,
  DrawLevel = 150, Class = "missile-class-cycle-once", Sleep = 1, Speed = 16, Range = 1 } )

DefineMissileType("missile-red-cross",
  { File = "ui/cursors/targr.png", Size = {128, 128}, Frames = 2, NumDirections = 1,
  DrawLevel = 150, Class = "missile-class-cycle-once", Sleep = 1, Speed = 16, Range = 1 } )

DefineMissileType("missile-none",
  { Size = {32, 32}, DrawLevel = 50,
  Class = "missile-class-none", Sleep = 1, Speed = 16, Range = 1 } )

DefineMissileType("missile-hit",
  { Size = {15, 15}, DrawLevel = 150,
  Class = "missile-class-hit", Sleep = 1, Speed = 1, Range = 16 } )

DefineBurningBuilding(
  {"percent", 0, "missile", "missile-big-fire"},
  {"percent", 50, "missile", "missile-small-fire"},
  {"percent", 75 } -- no missile
)
