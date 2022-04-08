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

local inner_shields = {{16, 252, 24}, {0, 16, 52}, {4, 32, 100}, {4, 32, 100}, {8, 52, 152}, {8, 52, 152}, {12, 72, 204}, {12, 72, 204}}
local outer_shields = {{16, 252, 24}, {16, 252, 24}, {0, 16, 52}, {4, 32, 100}, {4, 32, 100}, {8, 52, 152}, {8, 52, 152}, {12, 72, 204}}

local wireframe_red = {200, 24, 24}
local wireframe_yellow = {252, 252, 56}
local wireframe_green = {16, 252, 24}

local infrared_1 = {{136, 64, 156}, {232, 80, 20}, {232, 80, 20}, {16, 252, 24}, {16, 252, 24}, {252, 252, 56}}
local infrared_2 = {{8, 52, 152}, {168, 8, 8}, {168, 8, 8}, {248, 140, 20}, {248, 140, 20}, {16, 252, 24}}
local infrared_3 = {{4, 32, 100}, {132, 4, 4}, {200, 24, 24}, {160, 84, 28}, {160, 84, 28}, {248, 140, 20}}
local infrared_4 = {{4, 32, 100}, {8, 52, 152}, {104, 48, 120}, {104, 48, 120}, {168, 8, 8}, {200, 24, 24}}

local function loadWireframes(tbl, file, w, h)
  for r=4,0,-2 do
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

    health:SetPaletteColor(216, unpack(infrared_1[#tbl + 1]))
    health:SetPaletteColor(217, unpack(infrared_2[#tbl + 1]))
    health:SetPaletteColor(218, unpack(infrared_3[#tbl + 1]))
    health:SetPaletteColor(219, unpack(infrared_4[#tbl + 1]))

    tbl[#tbl + 1] = health
  end
  for y=2,0,-1 do
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

    health:SetPaletteColor(216, unpack(infrared_1[#tbl + 1]))
    health:SetPaletteColor(217, unpack(infrared_2[#tbl + 1]))
    health:SetPaletteColor(218, unpack(infrared_3[#tbl + 1]))
    health:SetPaletteColor(219, unpack(infrared_4[#tbl + 1]))

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
end
