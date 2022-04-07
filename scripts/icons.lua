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
  {"icon-zerg-build", 257},
  {"icon-zerg-advanced-build", 258},
}

Load("scripts/terran/icons.lua")
Load("scripts/zerg/icons.lua")
Load("scripts/protoss/icons.lua")

local wireframe_red = {164, 0, 0}
local wireframe_yellow = {244, 224,  32}
local wireframe_green = {44, 250, 58}

local wireframe_infrared = {{255, 57, 12}, {250, 120, 0}, {210, 104, 0}, {200, 128, 64}}

local function loadWireframes(tbl, file, w, h)
  for r=4,0,-1 do
    local health = CPlayerColorGraphic:ForceNew(file, w, h)
    health:Load()
    local idx = 208
    for j=1,r,1 do
      health:SetPaletteColor(idx, unpack(wireframe_red))
      idx = idx + 1
    end
    for j=idx,211,1 do
      health:SetPaletteColor(j, unpack(wireframe_yellow))
    end

    -- TODO: better zerg
    for j=1,4,1 do
      local this_infrared_level = {unpack(wireframe_infrared[j])}
      local y = 4 - r
      health:SetPaletteColor(j + 215, this_infrared_level[1] - r * 20 - y * 10, this_infrared_level[2] - r * 20 - y * 10, this_infrared_level[3] - r * 20 - y * 10)
    end

    tbl[#tbl + 1] = health
  end
  for y=3,0,-1 do
    local health = CPlayerColorGraphic:ForceNew(file, w, h)
    health:Load()
    local idx = 208
    for j=1,y,1 do
      health:SetPaletteColor(idx, unpack(wireframe_yellow))
      idx = idx + 1
    end
    for j=idx,211,1 do
      health:SetPaletteColor(j, unpack(wireframe_green))
    end

    -- TODO: better zerg
    for j=1,4,1 do
      local this_infrared_level = {unpack(wireframe_infrared[j])}      
      health:SetPaletteColor(j + 215, this_infrared_level[1] - y * 10, this_infrared_level[2] - y * 10, this_infrared_level[3] - y * 10)
    end

    tbl[#tbl + 1] = health
  end
end

local wireframes_single = {}
local wireframes_group = {}
local wireframes_transported = {}
loadWireframes(wireframes_single, "wirefram.png", 64, 64)
loadWireframes(wireframes_group, "grpwire.png", 32, 32)
loadWireframes(wireframes_transported, "tranwire.png", 64, 64)

for i = 1,table.getn(icons) do
  icon = CIcon:New(icons[i][1])
  icon.G = CPlayerColorGraphic:New("cmdicons.png", 36, 34)
  icon.Frame = icons[i][2]

  icon:ClearExtraGraphics()
  for i,g in ipairs(wireframes_single) do
    icon:AddSingleSelectionGraphic(g)
  end
  for i,g in ipairs(wireframes_group) do
    icon:AddGroupSelectionGraphic(g)
  end
  for i,g in ipairs(wireframes_transported) do
    icon:AddContainedGraphic(g)
  end
  -- todo zerg colors
end
