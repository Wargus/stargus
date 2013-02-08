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
--      maps.lua - Define map helper functions.
--
--      (c) Copyright 2005 by Francois Beerten
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

function DefineImageTilemodels(terrain, imgx, imgy)
   local til = {}

   for i = 0, imgx * imgy - 1 do
      til[i + 1] = i
   end

   DefineTileset(
     "name",  "Image terrain",
     "image", terrain,
     -- Slots descriptions
     "slots", {
       "solid", { "light-grass", "land",
      til}
     }
   )
DefineTileset(
     "name",  "Image terrain",
     "image", terrain,
     -- Slots descriptions
     "slots", {
       "solid", { "high-platform", "land",
      til}
     }
   )
DefineTileset(
     "name",  "Image terrain",
     "image", terrain,
     -- Slots descriptions
     "slots", {
       "solid", { "low-installation", "land",
      til}
     }
   )
DefineTileset(
     "name",  "Image terrain",
     "image", terrain,
     -- Slots descriptions
     "slots", {
       "solid", { "high-wall", "land",
      til}
     }
   )
DefineTileset(
     "name",  "Image terrain",
     "image", terrain,
     -- Slots descriptions
     "slots", {
       "solid", { "high-cliff", "land",
      til}
     }
   )
DefineTileset(
     "name",  "Image terrain",
     "image", terrain,
     -- Slots descriptions
     "slots", {
       "solid", { "low-water", "land",
      til}
     }
   )
end

function RepeatMap(mapx, mapy, imgx, imgy)
  -- Tile map
  for y = 0, mapy - 1 do
    for x = 0, mapx - 1 do
      SetTile(math.mod(x, imgx) + math.mod(y, imgy) * imgx, x, y)
    end
  end

  -- The terrain of image based maps shouldnt be editable by the stratagus 
  -- builtin editor and the editor shouldn't try to write the tiles map
  Editor.TerrainEditable = false
end



function DefineImageTerrain(terrain, mapx, mapy, imgx, imgy)
   DefineImageTilemodels(terrain, imgx, imgy)
   RepeatMap(mapx, mapy, imgx, imgy)
end

