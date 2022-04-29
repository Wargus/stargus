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
--      widgets.lua - Define the widgets
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

function DefineButtonStyles(race)
  DefineButtonStyle(race.." menu button", {
    Size = {64, 20},
    Font = "font8",
    TextNormalColor = "white",
    TextReverseColor = "white",
    TextAlign = "Center",
    TextPos = {33, 6},
    Default = {
      File = "ui/"..race.."/menu.png",
    },
    Hover = {
      TextNormalColor = "white",
    },
    Clicked = {
      File = "ui/"..race.."/menu pressed.png",
      TextPos = {31, 4},
    },
  })

  DefineButtonStyle(race.." diplomacy button", {
    Size = {64, 20},
    Font = "font8",
    TextNormalColor = "white",
    TextReverseColor = "white",
    TextAlign = "Center",
    TextPos = {33, 6},
    Default = {
      File = "ui/"..race.."/diplomacy.png",
    },
    Hover = {
      TextNormalColor = "white",
    },
    Clicked = {
      File = "ui/"..race.."/diplomacy pressed.png",
      TextPos = {31, 4},
    },
  })
  
  DefineButtonStyle(race.." minimap terrain button", {
    Size = {64, 20},
    Font = "font8",
    TextNormalColor = "white",
    TextReverseColor = "white",
    TextAlign = "Center",
    TextPos = {33, 6},
    Default = {
      File = "ui/"..race.."/minimap terrain.png",
    },
    Hover = {
      TextNormalColor = "white",
    },
    Clicked = {
      File = "ui/"..race.."/minimap terrain pressed.png",
      TextPos = {31, 4},
    },
  })
end

DefineButtonStyles("terran")
DefineButtonStyles("zerg")
DefineButtonStyles("protoss")


DefineButtonStyle("icon", {
  Size = {36, 34},
  Font = "game",
  TextNormalColor = "white",
  TextReverseColor = "white",
  TextAlign = "Right",
  TextPos = {36, 24},
  Default = {
    --[[Border = {
      Color = {0, 0, 0}, Size = 1,
    },]]
  },
  Hover = {
    TextNormalColor = "white",
    --[[Border = {
      Color = {128, 128, 128}, Size = 1,
    },]]
  },
--[[
  Selected = {
    Border = {
      Color = {0, 252, 0}, Size = 1,
    },
  },]]
  Clicked = {
    TextNormalColor = "white",
    --[[Border = {
      Color = {128, 128, 128}, Size = 1,
    },]]
  },
--[[
  Disabled = {
  },]]
})


DefineButtonStyle("training", {
  Size = {36, 34},
  Font = "game",
  TextNormalColor = "white",
  TextReverseColor = "white",
  TextAlign = "Right",
  TextPos = {36, 24},
  Default = {
  },
  Hover = {
    -- File = "ui/pcmdbtns.png", -- TODO: per race buttons
    -- Frame = 5,
    Size = {36, 34},
    Border = {
      SolidColor = {99, 99, 255},
      Size = 2,
    }
  },
--[[
  Selected = {
    Border = {
      Color = {0, 252, 0}, Size = 1,
    },
  },]]
  Clicked = {
    TextNormalColor = "white",
    --[[Border = {
      Color = {128, 128, 128}, Size = 1,
    },]]
  },
--[[
  Disabled = {
  },]]
})
