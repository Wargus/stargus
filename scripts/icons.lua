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




icons = {
  {"icon-minerals1", 176},
  {"icon-minerals2", 177},
  {"icon-minerals3", 178},
  {"icon-vespene-geyser", 188},
  {"icon-move", 228},
  {"icon-stop", 229},
  {"icon-attack", 230},
  {"icon-gather", 231},
  {"icon-repair", 232},
  {"icon-build", 234},
  {"icon-advanced-build", 235},
  {"icon-cancel", 236},
  {"icon-patrol", 254},
  {"icon-hold-position", 255},
  {"icon-rally-point", 286},
}

Load("scripts/terran/icons.lua")
Load("scripts/zerg/icons.lua")
Load("scripts/protoss/icons.lua")


for i = 1,table.getn(icons) do
  icon = CIcon:New(icons[i][1])
  icon.G = CGraphic:New("cmdicons.png", 36, 34)
  icon.Frame = icons[i][2]
end


