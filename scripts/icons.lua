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

local wireframe_red = {200, 24, 24}
local wireframe_yellow = {252, 252, 56}
local wireframe_green = {16, 252, 24}

local terranPaletteSwap = {
  "HitPoints", {
    208, -- health colors for terran/protoss starts at 208
    { -- # health steps
      { -- # of alternatives for step
        {wireframe_red, wireframe_red, wireframe_red, wireframe_yellow}, -- 4 colors
        {wireframe_red, wireframe_red, wireframe_yellow, wireframe_red},
        {wireframe_red, wireframe_yellow, wireframe_red, wireframe_red},
        {wireframe_yellow, wireframe_red, wireframe_red, wireframe_red},
      },
      {
        {wireframe_yellow, wireframe_red, wireframe_red, wireframe_yellow},
        {wireframe_red, wireframe_yellow, wireframe_yellow, wireframe_red},
        {wireframe_red, wireframe_yellow, wireframe_red, wireframe_yellow},
        {wireframe_yellow, wireframe_red, wireframe_yellow, wireframe_red},
      },
      {
        {wireframe_yellow, wireframe_yellow, wireframe_yellow, wireframe_yellow},
        {wireframe_yellow, wireframe_yellow, wireframe_yellow, wireframe_yellow},
        {wireframe_yellow, wireframe_yellow, wireframe_yellow, wireframe_yellow},
        {wireframe_yellow, wireframe_yellow, wireframe_yellow, wireframe_yellow},
      },
      {
        {wireframe_yellow, wireframe_green, wireframe_yellow, wireframe_green},
        {wireframe_green, wireframe_yellow, wireframe_green, wireframe_yellow},
        {wireframe_green, wireframe_green, wireframe_yellow, wireframe_green},
        {wireframe_yellow, wireframe_yellow, wireframe_green, wireframe_yellow},
      },
      {
        {wireframe_yellow, wireframe_green, wireframe_green, wireframe_green},
        {wireframe_green, wireframe_yellow, wireframe_green, wireframe_green},
        {wireframe_green, wireframe_green, wireframe_yellow, wireframe_green},
        {wireframe_green, wireframe_green, wireframe_green, wireframe_yellow},
      },
      {
        {wireframe_green, wireframe_green, wireframe_green, wireframe_green},
        {wireframe_green, wireframe_green, wireframe_green, wireframe_green},
        {wireframe_green, wireframe_green, wireframe_green, wireframe_green},
        {wireframe_green, wireframe_green, wireframe_green, wireframe_green},
      },
    },
  },
}

local zergPaletteSwap = {
  "HitPoints", {
    216, -- health colors for zerg starts at 216
    { -- # health steps
      { -- # of alternatives for step
        {{136, 64, 156}, {8, 52, 152}, {4, 32, 100}, {4, 32, 100}},
      },
      {
        {{232, 80, 20}, {168, 8, 8}, {132, 4, 4}, {8, 52, 152}},
      },
      {
        {{232, 80, 20}, {168, 8, 8}, {200, 24, 24}, {104, 48, 120}},
      },
      {
        {{16, 252, 24}, {248, 140, 20}, {160, 84, 28}, {104, 48, 120}},
      },
      {
        {{16, 252, 24}, {248, 140, 20}, {160, 84, 28}, {168, 8, 8}},
      },
      {
        {{252, 252, 56}, {16, 252, 24}, {248, 140, 20}, {200, 24, 24}},
      },
    },
  },
}

local protossPaletteSwap = {
  "HitPoints", terranPaletteSwap[2],
  "ShieldPoints", {
    192, -- shields are at 192 + 193
    { -- # shield steps
      {
        {{8, 8, 8}, {8, 8, 8}},
      },
      {
        {{0, 16, 52}, {8, 8, 8}}
      },
      {
        {{4, 32, 100}, {0, 16, 52}},
      },
      {
        {{4, 32, 100}, {4, 32, 100}},
      },
      {
        {{8, 52, 152}, {4, 32, 100}},
      },
      {
        {{8, 52, 152}, {8, 52, 152}},
      },
      {
        {{12, 72, 204}, {8, 52, 152}},
      },
      {
        {{12, 72, 204}, {12, 72, 204}},
      },
    }
  }
}

for i = 1,table.getn(icons) do
  icon = CIcon:New(icons[i][1])
  icon.G = CPlayerColorGraphic:New("cmdicons.png", 36, 34)
  icon.Frame = icons[i][2]

  if string.find(icons[i][1], "icon-terran-", 1, true) then
    DefinePaletteSwap(icons[i][1], terranPaletteSwap)
  elseif string.find(icons[i][1], "icon-zerg-", 1, true) then
    DefinePaletteSwap(icons[i][1], zergPaletteSwap)
  elseif string.find(icons[i][1], "icon-protoss-", 1, true) then
    DefinePaletteSwap(icons[i][1], protossPaletteSwap)
  end

  icon:ClearExtraGraphics()
  icon:AddSingleSelectionGraphic(CPlayerColorGraphic:New("wirefram.png", 64, 64))
  icon:AddGroupSelectionGraphic(CPlayerColorGraphic:New("grpwire.png", 32, 32))
  icon:AddContainedGraphic(CPlayerColorGraphic:New("tranwire.png", 64, 64))
end
