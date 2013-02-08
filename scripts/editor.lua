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
--      editor.lua - Editor configuration and functions.
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

--	Set which icons to display
SetEditorSelectIcon("icon-stop")
SetEditorUnitsIcon("icon-terran-marine")


--
--	editor-unit-types a sorted list of unit-types for the editor.
--	FIXME: this is only a temporary hack, for better sorted units.
--
DefineEditorUnitTypes({
  "unit-minerals1",
  "unit-minerals2",
  "unit-minerals3",
  "unit-vespene-geyser",

  -- Terran
  "unit-terran-marine",
  "unit-terran-ghost",
  "unit-terran-vulture",
  "unit-terran-goliath",
  "unit-terran-siege-tank",
  "unit-terran-scv",
  "unit-terran-firebat",
  "unit-terran-wraith",
  "unit-terran-science-vessel",
  "unit-terran-dropship",
  "unit-terran-battlecruiser",

  "unit-terran-command-center",
  "unit-terran-supply-depot",
  "unit-terran-refinery",
  "unit-terran-barracks",
  "unit-terran-academy",
  "unit-terran-factory",
  "unit-terran-starport",
  "unit-terran-science-facility",
  "unit-terran-engineering-bay",
  "unit-terran-armory",
  "unit-terran-missile-turret",
  "unit-terran-bunker",

})
