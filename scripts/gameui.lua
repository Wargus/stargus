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

  local original_width = 640
  local original_height = 480
  local offx = 0
  local offx_right = Video.Width - 235
  local offy = Video.Height - original_height

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

    local console_left = 275
    local console_middle = 21
    local console_right = 344

    AddFiller("ui/tconsole_left.png", 0, offy)

    local middle_num = (Video.Width - console_left - console_right) / console_middle

    for i=0,middle_num do
      AddFiller("ui/tconsole_middle.png", console_left + i*console_middle, offy)  
    end
    
    AddFiller("ui/tconsole_right.png", Video.Width - console_right, offy)

    UI.DefaultUnitPortrait = "unit-terran-command-center"
    
  elseif (race == "zerg") then
    
    local console_left = 274
    local console_middle = 7
    local console_right = 359
    
    AddFiller("ui/zconsole_left.png", 0, offy)

    local middle_num = (Video.Width - console_left - console_right) / console_middle

    for i=0,middle_num do
      AddFiller("ui/zconsole_middle.png", console_left + i*console_middle, offy)  
    end
    
    AddFiller("ui/zconsole_right.png", Video.Width - console_right, offy)
    
    UI.DefaultUnitPortrait = "unit-zerg-hive"
    
  else -- Protoss
    local console_left = 227
    local console_middle = 38
    local console_right = 375
    
    AddFiller("ui/pconsole_left.png", 0, offy)

    local middle_num = (Video.Width - console_left - console_right) / console_middle

    for i=0,middle_num do
      AddFiller("ui/pconsole_middle.png", console_left + i*console_middle, offy)  
    end
    
    AddFiller("ui/pconsole_right.png", Video.Width - console_right, offy)
    
    UI.DefaultUnitPortrait = "unit-protoss-nexus"
    
  end

  UI.InfoPanel.X = offx + 168
  UI.InfoPanel.Y = offy + 396

  -- Units Portrait
  b = CUIButton:new()
  b.X = offx_right + 10
  b.Y = offy + 411
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

  local selected_width = 36
  local selected_height = 37
  
  -- offset for the action button group on the right side
  local selected_offy = 396
  local selected_offx = 168

  local selected_box_num = (offx_right - selected_offx) / selected_width

  -- those are the buttons for the selected units
  for i=0,selected_box_num do
    AddSelectedButton(offx + selected_offx + i*selected_width, offy + selected_offy + 0*selected_height)
    AddSelectedButton(offx + selected_offx + i*selected_width, offy + selected_offy + 1*selected_height)
  end
  
  -- the screen resolution influences number of selectable units
  SetMaxSelectable(selected_box_num*2)

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
  AddTrainingButton(offx + 278, offy + 434)
  AddTrainingButton(offx + 316, offy + 434)
  AddTrainingButton(offx + 354, offy + 434)

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
  
  local action_width = 46
  local action_height = 40
  
  -- offset for the action button group on the right side
  local action_offy = 360
  local action_offx = 103
  
  -- those are the buttons for move, attack,...
  AddButtonPanelButton(offx_right + action_offx + 0*action_width, offy + action_offy + 0*action_height)
  AddButtonPanelButton(offx_right + action_offx + 1*action_width, offy + action_offy + 0*action_height)
  AddButtonPanelButton(offx_right + action_offx + 2*action_width, offy + action_offy + 0*action_height)
  
  AddButtonPanelButton(offx_right + action_offx + 0*action_width, offy + action_offy + 1*action_height)
  AddButtonPanelButton(offx_right + action_offx + 1*action_width, offy + action_offy + 1*action_height)
  AddButtonPanelButton(offx_right + action_offx + 2*action_width, offy + action_offy + 1*action_height)
  
  AddButtonPanelButton(offx_right + action_offx + 0*action_width, offy + action_offy + 2*action_height)
  AddButtonPanelButton(offx_right + action_offx + 1*action_width, offy + action_offy + 2*action_height)
  AddButtonPanelButton(offx_right + action_offx + 2*action_width, offy + action_offy + 2*action_height)
  AddButtonPanelButton(offx_right + action_offx + 3*action_width, offy + action_offy + 2*action_height)

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

  UI.MenuButton.X = offx_right + 10
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

  local minimapButton = CUIUserButton:new_local()
  minimapButton.Button = CUIButton:new_local()
  minimapButton.Button.X = offx + 6
  minimapButton.Button.Y = offy + 320
  minimapButton.Button:SetCallback(function() UiToggleTerrain() end)
  minimapButton.Button.Style = FindButtonStyle(race .. " minimap terrain button")
  UI.UserButtons:push_back(minimapButton)

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

