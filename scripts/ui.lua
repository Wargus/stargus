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
--      ui.lua - Define the user interface
--
--      (c) Copyright 2004-2006 by Jimmy Salmon
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

Load("scripts/widgets.lua")
Load("scripts/gameui.lua")

--
--  Define Decorations.
--

--ManaSprite("ui/mana.png", -7, -7, 7, 7)
--ManaSprite("ui/ppbrfull.png", 0, -1, 108, 9)
-- DefineSprites({Name="sprite-mana", File="ui/ppbrfull.png",
--   Offset={0, -1}, Size={108, 9}})
--HealthSprite("ui/health.png", 1, -7, 7, 7)
--HealthSprite("ui/ppbrfull.png", 0, -1, 108, 9)
-- DefineSprites({Name="sprite-health", File="ui/ppbrfull.png",
--   Offset={0, -1}, Size={108, 9}})

--DefineSprites({Name = "sprite-spell", File = "ui/bloodlust,haste,slow,invisible,shield.png",
--        Offset = {1, 1}, Size = {16, 16}})

--DefineDecorations({Index = "Bloodlust", ShowOpponent = true,
--  Offset = {0, 0}, Method = {"static-sprite", {"sprite-spell", 0}}})
--DefineDecorations({Index = "Haste", ShowOpponent = true,
--  Offset = {16, 0}, Method = {"static-sprite", {"sprite-spell", 1}}})
--DefineDecorations({Index = "Slow", ShowOpponent = true,
--  Offset = {16, 0}, Method = {"static-sprite", {"sprite-spell", 2}}})
--DefineDecorations({Index = "Invisible", ShowOpponent = true,
--  Offset = {32, 0}, Method = {"static-sprite", {"sprite-spell", 3}}})
--DefineDecorations({Index = "UnholyArmor", ShowOpponent = true,
--  Offset = {48, 0}, Method = {"static-sprite", {"sprite-spell", 4}}})

--ShowHealthBar()
--ShowHealthVertical()
--ShowHealthHorizontal()
--ShowHealthDot()
-- DefineDecorations({Index="HitPoints", HideNeutral=true, CenterX=true,
--   OffsetPercent={50, 100}, Method={"sprite", {"sprite-health"}}})

--ShowManaBar()
--ShowManaVertical()
--ShowManaHorizontal()
--ShowManaDot()
-- DefineDecorations({Index="Mana", HideNeutral=true, CenterX=true,
--   OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
-- DefineDecorations({Index="Transport", HideNeutral=true, CenterX=true,
--   OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
-- DefineDecorations({Index="Research", HideNeutral=true, CenterX=true,
--   OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
-- DefineDecorations({Index="Training", HideNeutral=true, CenterX=true,
--   OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
-- DefineDecorations({Index="UpgradeTo", HideNeutral=true, CenterX=true,
--   OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
-- DefineDecorations({Index="GiveResource", HideNeutral=true, CenterX=true,
--   OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
-- DefineDecorations({Index="CarryResource", HideNeutral=true, CenterX=true,
--   OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})

--ShowNoFull()
--ShowFull()

--  Uncomment next, to show bars and dots always on top.
--  FIXME: planned feature
--DecorationOnTop()

local offx = (Video.Width - 640) / 2
local offy = Video.Height - 480

--
--  Define Panels
--
local info_panel_x = offx + 0
local info_panel_y = offy + 200

local min_damage = Div(ActiveUnitVar("PiercingDamage"), 2)
local max_damage = Add(ActiveUnitVar("PiercingDamage"), ActiveUnitVar("BasicDamage"))
local damage_bonus = Sub(ActiveUnitVar("PiercingDamage", "Value", "Type"),
              ActiveUnitVar("PiercingDamage", "Value", "Initial"));

MainPanelGraphics = CGraphic:New("pcmdbtns.png", 36, 36)
MainPanelGraphics:Load()
ProgressBarEmpty = CGraphic:New("ui/tpbrempt.png", 108, 9)
ProgressBarEmpty:Load()
ProgressBarFull = CGraphic:New("ui/tpbrfull.png", 3, 9)
ProgressBarFull:Load()

DefinePanelContents(
-- Default presentation. ------------------------
  {
    Ident = "panel-general-contents",
    Pos = {info_panel_x, info_panel_x},
    DefaultFont = "game",
    Contents = {
      -- { Pos = {offx + 332, 472}, Condition = {ShowOpponent = false, HideNeutral = true},
      --   More = {"LifeBar", {Variable = "HitPoints", Height = 5, Width = 65, Border = false, Colors = {{75, "green"}, {50, "yellow"}, {25, "orange"}, {0, "red"}}}}
      -- },
      {
        Pos = {200, 500}, Condition = {ShowOpponent = false, HideNeutral = true},
        More = {"FormattedText2", {
          Font = "small", Variable = "HitPoints", Format = "~light-green~%d/%d",
          Component1 = "Value", Component2 = "Max", Centered = true}}
      },
      { Pos = {280, 428}, More = {"Text", {Text = Line(1, UnitName("Active"), 110, "game"), Centered = false}} },
      { Pos = {280, 436}, More = {"Text", {Text = Line(2, UnitName("Active"), 110, "game"), Centered = false}} },

      -- Resource Left
      { Pos = {205, 301}, Condition = {ShowOpponent = false, GiveResource = "only"},
        More = {"FormattedText2", {
          Format = "%s Left:%d", Variable = "GiveResource",
          Component1 = "Name", Component2 = "Value", Centered = true}}
      },
    }
  },
  {
    Ident = "panel-supply-building-contents",
    Pos = {info_panel_x, info_panel_y}, DefaultFont = "game",
    Condition = {ShowOpponent = false, HideNeutral = true, Build = "false", Supply = "only", Training = "false", UpgradeTo = "false"},
    Contents = {
      {
        Pos = {offx + 200, offy + 86},
        More = { "Text", { Text = Concat(_("Supply~|: "), String(PlayerData(ActiveUnitVar("Player", "Value"), "Supply", ""))) } }
      },
      {
        Pos = {offx + 200, offy + 102},
        More = {
          "Text",
          {
            Text = Concat(_("Demand~|: "),
            If(GreaterThan(
            PlayerData(ActiveUnitVar("Player", "Value"), "Demand", ""),
            PlayerData(ActiveUnitVar("Player", "Value"), "Supply", "")),
            InverseVideo(String(PlayerData(ActiveUnitVar("Player", "Value"), "Demand", ""))),
            String(PlayerData(ActiveUnitVar("Player", "Value"), "Demand", ""))))
          },
        },
      },
    },
  },
  {
    Ident = "panel-unit-under-construction",
    Pos = {info_panel_x, info_panel_y},
    DefaultFont = "game",
    Condition = {ShowOpponent = false, Build = "only"},
    Contents = {
      -- { Pos = {offx + 205, info_panel_y + 100}, Condition = {ShowOpponent = false, HideNeutral = true, Build = "only"},
      --   More = {"CompleteBar", {Variable = "Build", Width = 100, Height = 6, Color = "green", Border = true}}
      -- },
      { Pos = {offx + 199, offy + 100}, Condition = {Build = "only"}, More = {"Graphic", "ui/tpbrempt.png"}},
      { Pos = {offx + 199 +  1*3, offy + 100}, Condition = {Build =  ">3"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  1}}},
      { Pos = {offx + 199 +  2*3, offy + 100}, Condition = {Build =  ">6"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  2}}},
      { Pos = {offx + 199 +  3*3, offy + 100}, Condition = {Build =  ">9"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  3}}},
      { Pos = {offx + 199 +  4*3, offy + 100}, Condition = {Build = ">12"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  4}}},
      { Pos = {offx + 199 +  5*3, offy + 100}, Condition = {Build = ">15"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  5}}},
      { Pos = {offx + 199 +  6*3, offy + 100}, Condition = {Build = ">18"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  6}}},
      { Pos = {offx + 199 +  7*3, offy + 100}, Condition = {Build = ">21"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  7}}},
      { Pos = {offx + 199 +  8*3, offy + 100}, Condition = {Build = ">24"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  8}}},
      { Pos = {offx + 199 +  9*3, offy + 100}, Condition = {Build = ">27"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  9}}},
      { Pos = {offx + 199 + 10*3, offy + 100}, Condition = {Build = ">30"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 10}}},
      { Pos = {offx + 199 + 11*3, offy + 100}, Condition = {Build = ">33"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 11}}},
      { Pos = {offx + 199 + 12*3, offy + 100}, Condition = {Build = ">36"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 12}}},
      { Pos = {offx + 199 + 13*3, offy + 100}, Condition = {Build = ">39"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 13}}},
      { Pos = {offx + 199 + 14*3, offy + 100}, Condition = {Build = ">42"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 14}}},
      { Pos = {offx + 199 + 15*3, offy + 100}, Condition = {Build = ">45"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 15}}},
      { Pos = {offx + 199 + 16*3, offy + 100}, Condition = {Build = ">48"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 16}}},
      { Pos = {offx + 199 + 17*3, offy + 100}, Condition = {Build = ">51"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 17}}},
      { Pos = {offx + 199 + 18*3, offy + 100}, Condition = {Build = ">54"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 18}}},
      { Pos = {offx + 199 + 19*3, offy + 100}, Condition = {Build = ">57"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 19}}},
      { Pos = {offx + 199 + 20*3, offy + 100}, Condition = {Build = ">60"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 20}}},
      { Pos = {offx + 199 + 21*3, offy + 100}, Condition = {Build = ">63"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 21}}},
      { Pos = {offx + 199 + 22*3, offy + 100}, Condition = {Build = ">66"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 22}}},
      { Pos = {offx + 199 + 23*3, offy + 100}, Condition = {Build = ">69"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 23}}},
      { Pos = {offx + 199 + 24*3, offy + 100}, Condition = {Build = ">72"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 24}}},
      { Pos = {offx + 199 + 25*3, offy + 100}, Condition = {Build = ">75"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 25}}},
      { Pos = {offx + 199 + 26*3, offy + 100}, Condition = {Build = ">78"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 26}}},
      { Pos = {offx + 199 + 27*3, offy + 100}, Condition = {Build = ">81"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 27}}},
      { Pos = {offx + 199 + 28*3, offy + 100}, Condition = {Build = ">84"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 28}}},
      { Pos = {offx + 199 + 29*3, offy + 100}, Condition = {Build = ">87"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 29}}},
      { Pos = {offx + 199 + 30*3, offy + 100}, Condition = {Build = ">90"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 30}}},
      { Pos = {offx + 199 + 31*3, offy + 100}, Condition = {Build = ">93"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 31}}},
      { Pos = {offx + 199 + 32*3, offy + 100}, Condition = {Build = ">96"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 32}}},
      { Pos = {offx + 199 + 33*3, offy + 100}, Condition = {Build = ">99"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 33}}},
      
      { Pos = {offx + 205, info_panel_y + 84}, More = {"Text", "Under Construction", "Centered", false} },

      -- { Pos = {offx + 165, info_panel_y + 78}, Condition = {ShowOpponent = false, HideNeutral = true, Build = "only"},
      --   More = {"Icon", {Unit = "Worker"}}}
    }
  },
  {
    Ident = "panel-training-contents",
    Pos = {info_panel_x, info_panel_y},
    DefaultFont = "game",
    Condition = {ShowOpponent = false, HideNeutral = true, Training = "only"},
    Contents = {
      -- boxes
      { Pos = {238, 194}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      { Pos = {238, 232}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      { Pos = {276, 232}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      { Pos = {314, 232}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      { Pos = {352, 232}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      -- numbers
      { Pos = {238 + 7, 194 + 10}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 12}}},
      { Pos = {238 + 7, 232 + 10}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 14}}},
      { Pos = {276 + 7, 232 + 10}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 16}}},
      { Pos = {314 + 7, 232 + 10}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 18}}},
      { Pos = {352 + 7, 232 + 10}, Condition = {Training = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 20}}},
      -- progressbar
      { Pos = {offx + 199, offy + 100}, Condition = {Training = "only"}, More = {"Graphic", "ui/tpbrempt.png"}},
      { Pos = {offx + 199 +  1*3, offy + 100}, Condition = {Training =  ">3"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  1}}},
      { Pos = {offx + 199 +  2*3, offy + 100}, Condition = {Training =  ">6"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  2}}},
      { Pos = {offx + 199 +  3*3, offy + 100}, Condition = {Training =  ">9"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  3}}},
      { Pos = {offx + 199 +  4*3, offy + 100}, Condition = {Training = ">12"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  4}}},
      { Pos = {offx + 199 +  5*3, offy + 100}, Condition = {Training = ">15"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  5}}},
      { Pos = {offx + 199 +  6*3, offy + 100}, Condition = {Training = ">18"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  6}}},
      { Pos = {offx + 199 +  7*3, offy + 100}, Condition = {Training = ">21"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  7}}},
      { Pos = {offx + 199 +  8*3, offy + 100}, Condition = {Training = ">24"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  8}}},
      { Pos = {offx + 199 +  9*3, offy + 100}, Condition = {Training = ">27"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  9}}},
      { Pos = {offx + 199 + 10*3, offy + 100}, Condition = {Training = ">30"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 10}}},
      { Pos = {offx + 199 + 11*3, offy + 100}, Condition = {Training = ">33"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 11}}},
      { Pos = {offx + 199 + 12*3, offy + 100}, Condition = {Training = ">36"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 12}}},
      { Pos = {offx + 199 + 13*3, offy + 100}, Condition = {Training = ">39"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 13}}},
      { Pos = {offx + 199 + 14*3, offy + 100}, Condition = {Training = ">42"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 14}}},
      { Pos = {offx + 199 + 15*3, offy + 100}, Condition = {Training = ">45"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 15}}},
      { Pos = {offx + 199 + 16*3, offy + 100}, Condition = {Training = ">48"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 16}}},
      { Pos = {offx + 199 + 17*3, offy + 100}, Condition = {Training = ">51"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 17}}},
      { Pos = {offx + 199 + 18*3, offy + 100}, Condition = {Training = ">54"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 18}}},
      { Pos = {offx + 199 + 19*3, offy + 100}, Condition = {Training = ">57"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 19}}},
      { Pos = {offx + 199 + 20*3, offy + 100}, Condition = {Training = ">60"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 20}}},
      { Pos = {offx + 199 + 21*3, offy + 100}, Condition = {Training = ">63"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 21}}},
      { Pos = {offx + 199 + 22*3, offy + 100}, Condition = {Training = ">66"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 22}}},
      { Pos = {offx + 199 + 23*3, offy + 100}, Condition = {Training = ">69"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 23}}},
      { Pos = {offx + 199 + 24*3, offy + 100}, Condition = {Training = ">72"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 24}}},
      { Pos = {offx + 199 + 25*3, offy + 100}, Condition = {Training = ">75"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 25}}},
      { Pos = {offx + 199 + 26*3, offy + 100}, Condition = {Training = ">78"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 26}}},
      { Pos = {offx + 199 + 27*3, offy + 100}, Condition = {Training = ">81"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 27}}},
      { Pos = {offx + 199 + 28*3, offy + 100}, Condition = {Training = ">84"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 28}}},
      { Pos = {offx + 199 + 29*3, offy + 100}, Condition = {Training = ">87"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 29}}},
      { Pos = {offx + 199 + 30*3, offy + 100}, Condition = {Training = ">90"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 30}}},
      { Pos = {offx + 199 + 31*3, offy + 100}, Condition = {Training = ">93"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 31}}},
      { Pos = {offx + 199 + 32*3, offy + 100}, Condition = {Training = ">96"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 32}}},
      { Pos = {offx + 199 + 33*3, offy + 100}, Condition = {Training = ">99"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 33}}},
    }, 
  },
  {
    Ident = "panel-upgrading-contents",
    Pos = {info_panel_x, info_panel_y},
    DefaultFont = "game",
    Condition = {ShowOpponent = false, HideNeutral = true, UpgradeTo = "only"},
    Contents = {
      -- boxes
      { Pos = {238, 194}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      { Pos = {238, 232}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      { Pos = {276, 232}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      { Pos = {314, 232}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      { Pos = {352, 232}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 6}}},
      -- numbers
      { Pos = {238 + 7, 194 + 10}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 12}}},
      { Pos = {238 + 7, 232 + 10}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 14}}},
      { Pos = {276 + 7, 232 + 10}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 16}}},
      { Pos = {314 + 7, 232 + 10}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 18}}},
      { Pos = {352 + 7, 232 + 10}, Condition = {UpgradeTo = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 20}}},
      -- progressbar
      { Pos = {offx + 199, offy + 100}, Condition = {UpgradeTo = "only"}, More = {"Graphic", "ui/tpbrempt.png"}},
      { Pos = {offx + 199 +  1*3, offy + 100}, Condition = {UpgradeTo =  ">3"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  1}}},
      { Pos = {offx + 199 +  2*3, offy + 100}, Condition = {UpgradeTo =  ">6"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  2}}},
      { Pos = {offx + 199 +  3*3, offy + 100}, Condition = {UpgradeTo =  ">9"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  3}}},
      { Pos = {offx + 199 +  4*3, offy + 100}, Condition = {UpgradeTo = ">12"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  4}}},
      { Pos = {offx + 199 +  5*3, offy + 100}, Condition = {UpgradeTo = ">15"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  5}}},
      { Pos = {offx + 199 +  6*3, offy + 100}, Condition = {UpgradeTo = ">18"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  6}}},
      { Pos = {offx + 199 +  7*3, offy + 100}, Condition = {UpgradeTo = ">21"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  7}}},
      { Pos = {offx + 199 +  8*3, offy + 100}, Condition = {UpgradeTo = ">24"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  8}}},
      { Pos = {offx + 199 +  9*3, offy + 100}, Condition = {UpgradeTo = ">27"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame =  9}}},
      { Pos = {offx + 199 + 10*3, offy + 100}, Condition = {UpgradeTo = ">30"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 10}}},
      { Pos = {offx + 199 + 11*3, offy + 100}, Condition = {UpgradeTo = ">33"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 11}}},
      { Pos = {offx + 199 + 12*3, offy + 100}, Condition = {UpgradeTo = ">36"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 12}}},
      { Pos = {offx + 199 + 13*3, offy + 100}, Condition = {UpgradeTo = ">39"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 13}}},
      { Pos = {offx + 199 + 14*3, offy + 100}, Condition = {UpgradeTo = ">42"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 14}}},
      { Pos = {offx + 199 + 15*3, offy + 100}, Condition = {UpgradeTo = ">45"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 15}}},
      { Pos = {offx + 199 + 16*3, offy + 100}, Condition = {UpgradeTo = ">48"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 16}}},
      { Pos = {offx + 199 + 17*3, offy + 100}, Condition = {UpgradeTo = ">51"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 17}}},
      { Pos = {offx + 199 + 18*3, offy + 100}, Condition = {UpgradeTo = ">54"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 18}}},
      { Pos = {offx + 199 + 19*3, offy + 100}, Condition = {UpgradeTo = ">57"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 19}}},
      { Pos = {offx + 199 + 20*3, offy + 100}, Condition = {UpgradeTo = ">60"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 20}}},
      { Pos = {offx + 199 + 21*3, offy + 100}, Condition = {UpgradeTo = ">63"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 21}}},
      { Pos = {offx + 199 + 22*3, offy + 100}, Condition = {UpgradeTo = ">66"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 22}}},
      { Pos = {offx + 199 + 23*3, offy + 100}, Condition = {UpgradeTo = ">69"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 23}}},
      { Pos = {offx + 199 + 24*3, offy + 100}, Condition = {UpgradeTo = ">72"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 24}}},
      { Pos = {offx + 199 + 25*3, offy + 100}, Condition = {UpgradeTo = ">75"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 25}}},
      { Pos = {offx + 199 + 26*3, offy + 100}, Condition = {UpgradeTo = ">78"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 26}}},
      { Pos = {offx + 199 + 27*3, offy + 100}, Condition = {UpgradeTo = ">81"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 27}}},
      { Pos = {offx + 199 + 28*3, offy + 100}, Condition = {UpgradeTo = ">84"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 28}}},
      { Pos = {offx + 199 + 29*3, offy + 100}, Condition = {UpgradeTo = ">87"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 29}}},
      { Pos = {offx + 199 + 30*3, offy + 100}, Condition = {UpgradeTo = ">90"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 30}}},
      { Pos = {offx + 199 + 31*3, offy + 100}, Condition = {UpgradeTo = ">93"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 31}}},
      { Pos = {offx + 199 + 32*3, offy + 100}, Condition = {UpgradeTo = ">96"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 32}}},
      { Pos = {offx + 199 + 33*3, offy + 100}, Condition = {UpgradeTo = ">99"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 33}}},
    }, 
  },
  {
    Ident = "panel-armored-unit-contents",
    Pos = {info_panel_x, info_panel_y},
    DefaultFont = "small",
    Condition = {ShowOpponent = false, HideNeutral = false, Build = "false", Training = "false"},
    Contents = {
      { Pos = {238 + 9, 232 + 12}, Condition = {Armor = "only"}, More = {"Graphic", {Graphic = "cmdicons.png", Frame = 292}}},
      { Pos = {238 + 7, 232 + 10}, Condition = {Armor = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 24}}},
      { Pos = {238 + 7 + 24, 232 + 34}, Condition = {Armor = "only"},  More = {"Text", { Text = "", Variable = "Armor", Stat = true, Centered = true}}},

      { Pos = {276 + 9, 232 + 12}, Condition = {PiercingDamage = "only"}, More = {"Graphic", {Graphic = "cmdicons.png", Frame = 290}}},
      { Pos = {276 + 7, 232 + 10}, Condition = {PiercingDamage = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 24}}},
      { Pos = {276 + 7 + 24, 232 + 34}, Condition = {PiercingDamage = "only"},  More = {"Text", { Text = "", Variable = "PiercingDamage", Stat = true, Centered = true}}},

      { Pos = {314 + 9, 232 + 12}, Condition = {AttackRange = "only"}, More = {"Graphic", {Graphic = "cmdicons.png", Frame = 288}}},
      { Pos = {314 + 7, 232 + 10}, Condition = {AttackRange = "only"}, More = {"Graphic", {Graphic = "pcmdbtns.png", Frame = 24}}},
      { Pos = {314 + 7 + 24, 232 + 34}, Condition = {AttackRange = "only"},  More = {"Text", { Text = "", Variable = "AttackRange", Stat = true, Centered = true}}},
    }
  },
  {
    Ident = "panel-own-unit-contents",
    Pos = {info_panel_x, info_panel_y},
    DefaultFont = "game",
    Condition = {ShowOpponent = false, HideNeutral = true, Build = "false"},
    Contents = {
    --[[
      { Pos = {37, 86}, Condition = {PiercingDamage = "only"},
        More = {"Text", {Text = Concat("Damage: ", String(min_damage), "-", String(max_damage),
                    If(Equal(0, damage_bonus), "",
                      InverseVideo(Concat("+", String(damage_bonus)))) )}}

      },

      { Pos = {47, 102}, Condition = {AttackRange = "only"},
        More = {"Text", {
              Text = "Range: ", Variable = "AttackRange" , Stat = true}}
      },
    ]]
    -- Research
    { Pos = {offx + 12, offy + 153}, Condition = {Research = "only"},
      More = {"CompleteBar", {Variable = "Research", Width = 152, Height = 12}}
    },
    { Pos = {offx + 16, offy + 86}, Condition = {Research = "only"}, More = {"Text", "Researching:"}},
    { Pos = {offx + 50, offy + 154}, Condition = {Research = "only"}, More = {"Text", "% Complete"}},
  -- Mana
  { Pos = {offx + 16, offy + 148}, Condition = {Mana = "only"},
    More = {"CompleteBar", {Variable = "Mana", Height = 16, Width = 140, Border = true}}
  },
  { Pos = {offx + 86, offy + 150}, More = {"Text", {Variable = "Mana"}}, Condition = {Mana = "only"} },

  -- Ressource Carry
  { Pos = {offx + 61, offy + 149}, Condition = {CarryResource = "only"},
    More = {"FormattedText2", {Format = "Carry: %d %s", Variable = "CarryResource",
        Component1 = "Value", Component2 = "Name"}}
  }

  } }--,
-- Attack Unit -----------------------------
--[[
  {
  Ident = "panel-attack-unit-contents",
  Pos = {info_panel_x, info_panel_y},
  DefaultFont = "game",
  Condition = {ShowOpponent = false, HideNeutral = true, Building = "false", Build = "false"},
  Contents = {
-- Unit caracteristics
  { Pos = {114, 41},
    More = {"FormattedText", {Variable = "Level", Format = "Level ~<%d~>"}}
  },
  { Pos = {114, 56},
    More = {"FormattedText2", {Centered = true,
      Variable1 = "Xp", Variable2 = "Kill", Format = "XP:~<%d~> Kills:~<%d~>"}}
  },
  { Pos = {47, 71}, Condition = {Armor = "only"},
    More = {"Text", {
          Text = "Armor: ", Variable = "Armor", Stat = true}}
  },
  { Pos = {54, 118}, Condition = {SightRange = "only"},
    More = {"Text", {Text = "Sight: ", Variable = "SightRange", Stat = true}}
  },
  { Pos = {53, 133}, Condition = {Speed = "only"},
    More = {"Text", {Text = "Speed: ", Variable = "Speed", Stat = true}}
  } } }
]]
  )

UI.MessageFont = Fonts["game"]
UI.MessageScrollSpeed = 5

DefineCursor({
  Name = "cursor-point",
  Race = "any",
  File = "ui/cursors/arrow.png",
  Rate = 50,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-glass",
  Race = "any",
  File = "ui/cursors/magg.png",
  Rate = 50,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-cross",
  Race = "any",
  File = "ui/cursors/drag.png",
  Rate = 50,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-scroll",
  Race = "any",
  File = "ui/cursors/drag.png",
  HotSpot = {63, 63},
  Size = {128, 128}})
  
  
DefineCursor({
  Name = "cursor-green-hair",
  Race = "any",
  File = "ui/cursors/targg.png",
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-yellow-hair",
  Race = "any",
  File = "ui/cursors/targn.png",
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-red-hair",
  Race = "any",
  File = "ui/cursors/targr.png",
  HotSpot = {63, 63},
  Size = {128, 128}})



DefineCursor({
  Name = "cursor-arrow-e",
  Race = "any",
  File = "ui/cursors/scrollr.png",
  Rate = 67,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-arrow-ne",
  Race = "any",
  File = "ui/cursors/scrollur.png",
  Rate = 67,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-arrow-n",
  Race = "any",
  File = "ui/cursors/scrollu.png",
  Rate = 67,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-arrow-nw",
  Race = "any",
  File = "ui/cursors/scrollul.png",
  Rate = 67,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-arrow-w",
  Race = "any",
  File = "ui/cursors/scrolll.png",
  Rate = 67,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-arrow-s",
  Race = "any",
  File = "ui/cursors/scrolld.png",
  Rate = 67,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-arrow-sw",
  Race = "any",
  File = "ui/cursors/scrolldl.png",
  Rate = 67,
  HotSpot = {63, 63},
  Size = {128, 128}})
DefineCursor({
  Name = "cursor-arrow-se",
  Race = "any",
  File = "ui/cursors/scrolldr.png",
  Rate = 67,
  HotSpot = {63, 63},
  Size = {128, 128}})
