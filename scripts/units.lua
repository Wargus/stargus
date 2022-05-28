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
--      units.lua - Define the used unit-types.
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

UnitTypeFiles = {}

Load("scripts/terran/units.lua")
Load("scripts/zerg/units.lua")
Load("scripts/protoss/units.lua")
Load("scripts/neutral/units.lua")

Load("luagen/units/luagen-units.lua")


for idx,icon in ipairs(icons) do
    local iconname = icon[1]
    
    local foldername, repls = string.gsub(iconname, "icon%-terran%-", "t")
    local prefix = "t"
    if repls ~= 1 then
        foldername, repls = string.gsub(iconname, "icon%-protoss%-", "p")
        prefix = "p"
    end
    if repls ~= 1 then
        foldername, repls = string.gsub(iconname, "icon%-zerg%-", "z")
        prefix = "z"
    end
    
    if repls == 1 then
        -- a terran, protoss, or zerg unit
        local unitname, _ = string.gsub(iconname, "icon", "unit")
        foldername = foldername:sub(1, 8)
        folderprefix = "videos/portrait/"
        
        local portrait_table = {}
        for _idx,foldername_to_try in ipairs({foldername, prefix .. "advisor"}) do
            -- should have either their own portrait or the advisor portrait
            for i=0,4,1 do
                local filename = folderprefix .. foldername_to_try .. "/" .. foldername_to_try:sub(1, 3) .. "fid0" .. i .. ".mng"
                if CanAccessFile(filename) then
                    portrait_table[#portrait_table + 1] = filename
                end
            end
            if #portrait_table > 1 then
                portrait_table[#portrait_table + 1] = "talking"
                for i=0,4,1 do
                    local filename = folderprefix .. foldername_to_try .. "/" .. foldername_to_try:sub(1, 3) .. "tlk0" .. i .. ".mng"
                    if CanAccessFile(filename) then
                        portrait_table[#portrait_table + 1] = filename
                    end
                end
            end

            if #portrait_table > 1 then
                print("Using " .. portrait_table[1] .. " and following for " .. unitname)
                --DefineUnitType(unitname, { Portrait = portrait_table })
                break
            end
        end
    else
        -- a neutral unit
    end
end
