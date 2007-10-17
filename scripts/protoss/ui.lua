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
--      ui.lua - Define the human user interface
--
--      (c) Copyright 2005-2007 by Jimmy Salmon
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



--;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
--  * Race Terran.
--;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

local offx = (Video.Width - 640) / 2
local offy = Video.Height - 480

function ProtossScreen(screen_width, screen_height)
  local info_panel_x = 0
  local info_panel_y = 160

  local ui = {
    "info-panel", {
      "panels", {"panel-general-contents", --[["panel-attack-unit-contents",]]
        "panel-all-unit-contents", "panel-building-contents"},
      "completed-bar", {
        "color", {48, 100, 4}
      }
    }
  }
end

UI.NormalFontColor = "white"
UI.ReverseFontColor = "yellow"

UI.Fillers:clear()

function AddFiller(file, x, y)
    b = CFiller:new_local()
    b.G = CGraphic:New(file)
    b.X = x
    b.Y = y
    UI.Fillers:push_back(b)
end

AddFiller("ui/pconsole.png", offx, offy)


UI.InfoPanel.X = offx + 0
UI.InfoPanel.Y = offy + 160

b = CUIButton:new()
b.X = offx + 9
b.Y = offy + 160 + 9
b.Style = FindButtonStyle("icon")
UI.SingleSelectedButton = b

UI.SelectedButtons:clear()

function AddSelectedButton(x, y)
    b = CUIButton:new_local()
    b.X = x
    b.Y = y
    b.Style = FindButtonStyle("icon")
    UI.SelectedButtons:push_back(b)
end

AddSelectedButton(offx + 9,   offy + 160 + 9)
AddSelectedButton(offx + 65,  offy + 160 + 9)
AddSelectedButton(offx + 121, offy + 160 + 9)
AddSelectedButton(offx + 9,   offy + 160 + 63)
AddSelectedButton(offx + 65,  offy + 160 + 63)
AddSelectedButton(offx + 121, offy + 160 + 63)
AddSelectedButton(offx + 9,   offy + 160 + 117)
AddSelectedButton(offx + 65,  offy + 160 + 117)
AddSelectedButton(offx + 121, offy + 160 + 117)

UI.MaxSelectedFont = Fonts["game"]
UI.MaxSelectedTextX = offx + 10
UI.MaxSelectedTextY = offy + 160 + 10

b = CUIButton:new()
b.X = offx + 110
b.Y = offy + 160 + 11 + 70
b.Style = FindButtonStyle("icon")
UI.SingleTrainingButton = b

UI.TrainingButtons:clear()

function AddTrainingButton(x, y)
    b = CUIButton:new_local()
    b.X = x
    b.Y = y
    b.Style = FindButtonStyle("icon")
    UI.TrainingButtons:push_back(b)
end

AddTrainingButton(offx + 9,   offy + 219)
AddTrainingButton(offx + 65,  offy + 219)
AddTrainingButton(offx + 121, offy + 219)
AddTrainingButton(offx + 9,   offy + 266)
AddTrainingButton(offx + 65,  offy + 266)
AddTrainingButton(offx + 121, offy + 266)

b = CUIButton:new()
b.X = offx + 110
b.Y = offy + 160 + 11 + 70
b.Style = FindButtonStyle("icon")
UI.UpgradingButton = b

b = CUIButton:new()
b.X = offx + 110
b.Y = offy + 160 + 11 + 70
b.Style = FindButtonStyle("icon")
UI.ResearchingButton = b

UI.TransportingButtons:clear()

function AddTransportingButton(x, y)
    b = CUIButton:new_local()
    b.X = x
    b.Y = y
    b.Style = FindButtonStyle("icon")
    UI.TransportingButtons:push_back(b)
end

AddTransportingButton(offx + 9,   offy + 223)
AddTransportingButton(offx + 65,  offy + 223)
AddTransportingButton(offx + 121, offy + 223)
AddTransportingButton(offx + 9,   offy + 277)
AddTransportingButton(offx + 65,  offy + 277)
AddTransportingButton(offx + 121, offy + 277)

UI.CompletedBarColorRGB = CColor(48, 100, 4)
UI.CompletedBarShadow = true

UI.ButtonPanel.Buttons:clear()

function AddButtonPanelButton(x, y)
    b = CUIButton:new_local()
    b.X = x
    b.Y = y
    b.Style = FindButtonStyle("icon")
    UI.ButtonPanel.Buttons:push_back(b)
end

AddButtonPanelButton(offx + 505, offy + 358)
AddButtonPanelButton(offx + 551, offy + 358)
AddButtonPanelButton(offx + 597, offy + 358)
AddButtonPanelButton(offx + 505, offy + 398)
AddButtonPanelButton(offx + 551, offy + 398)
AddButtonPanelButton(offx + 597, offy + 398)
AddButtonPanelButton(offx + 505, offy + 438)
AddButtonPanelButton(offx + 551, offy + 438)
AddButtonPanelButton(offx + 597, offy + 438)

UI.ButtonPanel.X = offx + 0
UI.ButtonPanel.Y = offy + 336
UI.ButtonPanel.AutoCastBorderColorRGB = CColor(0, 0, 252)

UI.MapArea.X = 0
UI.MapArea.Y = 0
UI.MapArea.EndX = Video.Width - 1
UI.MapArea.EndY = Video.Height - 107

UI.Minimap.X = offx + 6
UI.Minimap.Y = offy + 348
UI.Minimap.W = 128
UI.Minimap.H = 128

UI.StatusLine.TextX = offx + 172
UI.StatusLine.TextY = offy + 350
UI.StatusLine.Width = Video.Width - offx - 172
UI.StatusLine.Font = Fonts["game"]

-- minerals
UI.Resources[1].G = CGraphic:New("ui/icons.png", 54, 14)
UI.Resources[1].IconFrame = 0
UI.Resources[1].IconX = offx + 436
UI.Resources[1].IconY = 3
UI.Resources[1].TextX = offx + 452
UI.Resources[1].TextY = 3

-- gas
UI.Resources[2].G = CGraphic:New("ui/icons.png", 54, 14)
UI.Resources[2].IconFrame = 2
UI.Resources[2].IconX = offx + 504
UI.Resources[2].IconY = 3
UI.Resources[2].TextX = offx + 520
UI.Resources[2].TextY = 3

-- food
UI.Resources[FoodCost].G = CGraphic:New("ui/icons.png", 54, 14)
UI.Resources[FoodCost].IconFrame = 5
UI.Resources[FoodCost].IconX = offx + 572
UI.Resources[FoodCost].IconY = 3
UI.Resources[FoodCost].TextX = offx + 588
UI.Resources[FoodCost].TextY = 3

-- score
--[[
UI.Resources[ScoreCost].G = CGraphic:New("ui/score.png", 14, 14)
UI.Resources[ScoreCost].IconFrame = 0
UI.Resources[ScoreCost].IconX = Video.Width - 16 - 68
UI.Resources[ScoreCost].IconY = 0
UI.Resources[ScoreCost].TextX = Video.Width - 16 - 68 + 18
UI.Resources[ScoreCost].TextY = 1
]]

UI.MenuButton.X = offx + 416
UI.MenuButton.Y = offy + 388
UI.MenuButton.Text = "MENU"
UI.MenuButton.Style = FindButtonStyle("terran menu button")
UI.MenuButton:SetCallback(function() RunGameMenu() end)

UI.NetworkMenuButton.X = offx + 416 
UI.NetworkMenuButton.Y = offy + 388 
UI.NetworkMenuButton.Text = "MENU"
UI.NetworkMenuButton.Style = FindButtonStyle("terran menu button")
UI.NetworkMenuButton:SetCallback(function() RunGameMenu() end)

UI.NetworkDiplomacyButton.X = offx + 76
UI.NetworkDiplomacyButton.Y = offy + 320
--UI.NetworkDiplomacyButton.Text = "Diplomacy"
UI.NetworkDiplomacyButton.Style = FindButtonStyle("terran diplomacy button")
UI.NetworkDiplomacyButton:SetCallback(function() RunDiplomacyMenu() end)

-- minimap terrain at 3,320

