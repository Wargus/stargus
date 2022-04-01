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
--      ui.lua - Define the terran user interface
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

function LoadUI(race)

local offx = (Video.Width - 640) / 2
local offy = Video.Height - 480

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

if (race == "terran") then
  AddFiller("ui/tconsole.png", offx, offy)
elseif (race == "zerg") then
  AddFiller("ui/zconsole.png", offx, offy)
else
  AddFiller("ui/pconsole.png", offx, offy)
end

UI.InfoPanel.X = offx + 168
UI.InfoPanel.Y = offy + 396

b = CUIButton:new()
b.X = offx + 168
b.Y = offy + 396
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

AddSelectedButton(offx + 168, offy + 396)
AddSelectedButton(offx + 168, offy + 433)
AddSelectedButton(offx + 204, offy + 396)
AddSelectedButton(offx + 204, offy + 433)
AddSelectedButton(offx + 240, offy + 396)
AddSelectedButton(offx + 240, offy + 433)
AddSelectedButton(offx + 276, offy + 396)
AddSelectedButton(offx + 276, offy + 433)
AddSelectedButton(offx + 312, offy + 396)
AddSelectedButton(offx + 312, offy + 433)
AddSelectedButton(offx + 348, offy + 396)
AddSelectedButton(offx + 348, offy + 433)

UI.MaxSelectedFont = Fonts["game"]
UI.MaxSelectedTextX = offx + 10
UI.MaxSelectedTextY = offy + 160 + 10

b = CUIButton:new()
b.X = offx + 240
b.Y = offy + 396
b.Style = FindButtonStyle("icon")
UI.SingleTrainingButton = b

UI.TrainingButtons:clear()

function AddTrainingButton(x, y)
    b = CUIButton:new_local()
    b.X = x
    b.Y = y
    b.Style = FindButtonStyle("training")
    UI.TrainingButtons:push_back(b)
end

AddTrainingButton(offx + 240, offy + 396)
AddTrainingButton(offx + 240, offy + 434)
AddTrainingButton(offx + 280, offy + 434)
AddTrainingButton(offx + 320, offy + 434)
AddTrainingButton(offx + 360, offy + 434)

b = CUIButton:new()
b.X = offx + 240
b.Y = offy + 396
b.Style = FindButtonStyle("icon")
UI.UpgradingButton = b

b = CUIButton:new()
b.X = offx + 240
b.Y = offy + 396
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

AddTransportingButton(offx + 240, offy + 396)
AddTransportingButton(offx + 240, offy + 433)
AddTransportingButton(offx + 276, offy + 396)
AddTransportingButton(offx + 276, offy + 433)
AddTransportingButton(offx + 312, offy + 396)
AddTransportingButton(offx + 312, offy + 433)
AddTransportingButton(offx + 348, offy + 396)
AddTransportingButton(offx + 348, offy + 433)

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

AddButtonPanelButton(offx + 507, offy + 358)
AddButtonPanelButton(offx + 553, offy + 358)
AddButtonPanelButton(offx + 599, offy + 358)
AddButtonPanelButton(offx + 507, offy + 398)
AddButtonPanelButton(offx + 553, offy + 398)
AddButtonPanelButton(offx + 599, offy + 398)
AddButtonPanelButton(offx + 507, offy + 438)
AddButtonPanelButton(offx + 553, offy + 438)
AddButtonPanelButton(offx + 599, offy + 438)

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
UI.MenuButton.Style = FindButtonStyle(race .. " menu button")
UI.MenuButton:SetCallback(function() RunGameMenu() end)

UI.NetworkMenuButton.X = offx + 416 
UI.NetworkMenuButton.Y = offy + 388 
UI.NetworkMenuButton.Text = "MENU"
UI.NetworkMenuButton.Style = FindButtonStyle(race .. " menu button")
UI.NetworkMenuButton:SetCallback(function() RunGameMenu() end)

UI.NetworkDiplomacyButton.X = offx + 76
UI.NetworkDiplomacyButton.Y = offy + 320
--UI.NetworkDiplomacyButton.Text = "Diplomacy"
UI.NetworkDiplomacyButton.Style = FindButtonStyle(race .. " diplomacy button")
UI.NetworkDiplomacyButton:SetCallback(function() RunDiplomacyMenu() end)

UI.LifeBarColorNames:clear()
UI.LifeBarColorNames:push_back("green")
UI.LifeBarColorNames:push_back("yellow")
UI.LifeBarColorNames:push_back("orange")
UI.LifeBarColorNames:push_back("red")
UI.LifeBarYOffset = -8
UI.LifeBarBorder = false
UI.LifeBarPadding = 4

-- minimap terrain at 3,320

end -- function LoadUI

