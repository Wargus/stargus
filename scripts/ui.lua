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
DefineSprites({Name="sprite-mana", File="ui/ppbrfull.png",
  Offset={0, -1}, Size={108, 9}})
--HealthSprite("ui/health.png", 1, -7, 7, 7)
--HealthSprite("ui/ppbrfull.png", 0, -1, 108, 9)
DefineSprites({Name="sprite-health", File="ui/ppbrfull.png",
  Offset={0, -1}, Size={108, 9}})

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
DefineDecorations({Index="HitPoints", HideNeutral=true, CenterX=true,
  OffsetPercent={50, 100}, Method={"sprite", {"sprite-health"}}})

--ShowManaBar()
--ShowManaVertical()
--ShowManaHorizontal()
--ShowManaDot()
DefineDecorations({Index="Mana", HideNeutral=true, CenterX=true,
  OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
DefineDecorations({Index="Transport", HideNeutral=true, CenterX=true,
  OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
DefineDecorations({Index="Research", HideNeutral=true, CenterX=true,
  OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
DefineDecorations({Index="Training", HideNeutral=true, CenterX=true,
  OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
DefineDecorations({Index="UpgradeTo", HideNeutral=true, CenterX=true,
  OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
DefineDecorations({Index="GiveResource", HideNeutral=true, CenterX=true,
  OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})
DefineDecorations({Index="CarryResource", HideNeutral=true, CenterX=true,
  OffsetPercent={50, 100}, Method={"sprite", {"sprite-mana"}}})

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
ProgressBarFull = CGraphic:New("ui/tpbrfull.png", 9, 9)
ProgressBarFull:Load()

DefinePanelContents(
-- Default presentation. ------------------------
  {
  Ident = "panel-general-contents",
  Pos = {offx, offy}, DefaultFont = "game",
  Contents = {
  -- { Pos = {offx + 332, 472}, Condition = {ShowOpponent = false, HideNeutral = true},
  --   More = {"LifeBar", {Variable = "HitPoints", Height = 5, Width = 65, Border = false, Colors = {{75, "green"}, {50, "yellow"}, {25, "orange"}, {0, "red"}}}}
  -- },
  { Pos = {offx + 198, offy + 454}, Condition = {ShowOpponent = false, HideNeutral = true},
    More = {"FormattedText2", {
      Font = "small", Variable = "HitPoints", Format = "%d/%d",
      Component1 = "Value", Component2 = "Max", Centered = true}}
  },
  { Pos = {offx + 205, offy + 271}, More = {"Text", {Text = Line(1, UnitName("Active"), 110, "game"), Centered = false}} },
  { Pos = {offx + 205, offy + 286}, More = {"Text", {Text = Line(2, UnitName("Active"), 110, "game"), Centered = false}} },

-- Resource Left
  { Pos = {offx + 205, offy + 301}, Condition = {ShowOpponent = false, GiveResource = "only"},
    More = {"FormattedText2", {Format = "%s Left:%d", Variable = "GiveResource",
          Component1 = "Name", Component2 = "Value", Centered = true}}
  },

-- Construction
  { Pos = {offx + 205, info_panel_y + 100}, Condition = {ShowOpponent = false, HideNeutral = true, Build = "only"},
    More = {"CompleteBar", {Variable = "Build", Width = 100, Height = 6, Color = "green", Border = true}}
  },
  { Pos = {offx + 205, info_panel_y + 84}, Condition = {ShowOpponent = false, HideNeutral = true, Build = "only"},
    More = {"Text", "Under Construction", "Centered", false}},

  { Pos = {offx + 165, info_panel_y + 78}, Condition = {ShowOpponent = false, HideNeutral = true, Build = "only"},
    More = {"Icon", {Unit = "Worker"}}}
  } },
-- Supply Building constructed.----------------
  {
  Ident = "panel-building-contents",
  Pos = {info_panel_x, info_panel_y}, DefaultFont = "game",
  Condition = {ShowOpponent = false, HideNeutral = true, Build = "false", Supply = "only", Training = "false", UpgradeTo = "false"},
-- FIXME more condition. not town hall.
  Contents = {
-- Food building
  { Pos = {offx + 200, offy + 86},
          More = {
            "Text",
            {
                Text = Concat(_("Supply~|: "),
                              String(PlayerData(ActiveUnitVar("Player", "Value"), "Supply", "")))
            }
          }
        },
  { Pos = {offx + 200, offy + 102},
          More = {
            "Text",
            {
                Text = Concat(_("Demand~|: "),
                              If(GreaterThan(
                                    PlayerData(ActiveUnitVar("Player", "Value"), "Demand", ""),
                                    PlayerData(ActiveUnitVar("Player", "Value"), "Supply", "")),
                                InverseVideo(String(PlayerData(ActiveUnitVar("Player", "Value"), "Demand", ""))),
                                String(PlayerData(ActiveUnitVar("Player", "Value"), "Demand", ""))))
            }
          }
        },

  } },
-- All own unit -----------------
  {
  Ident = "panel-all-unit-contents",
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
-- Training
  -- { Pos = {offx + 205, offy + 100}, Condition = {Training = "only"},
  --   More = {"CompleteBar", {Variable = "Training", Width = 100, Height = 6, Color = "green", Border = true}}
  -- },
  { Pos = {offx + 205, offy + 100}, Condition = {Training = "only"}, More = {"Graphic", "ui/tpbrempt.png"}},
  { Pos = {offx + 205 + 0*9, offy + 100}, Condition = {Training = ">6"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 0}}},
  { Pos = {offx + 205 + 1*9, offy + 100}, Condition = {Training = ">14"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 1}}},
  { Pos = {offx + 205 + 2*9, offy + 100}, Condition = {Training = ">23"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 2}}},
  { Pos = {offx + 205 + 3*9, offy + 100}, Condition = {Training = ">31"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 3}}},
  { Pos = {offx + 205 + 4*9, offy + 100}, Condition = {Training = ">39"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 4}}},
  { Pos = {offx + 205 + 5*9, offy + 100}, Condition = {Training = ">48"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 5}}},
  { Pos = {offx + 205 + 6*9, offy + 100}, Condition = {Training = ">56"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 6}}},
  { Pos = {offx + 205 + 7*9, offy + 100}, Condition = {Training = ">64"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 7}}},
  { Pos = {offx + 205 + 8*9, offy + 100}, Condition = {Training = ">73"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 8}}},
  { Pos = {offx + 205 + 9*9, offy + 100}, Condition = {Training = ">81"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 9}}},
  { Pos = {offx + 205 + 10*9, offy + 100}, Condition = {Training = ">89"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 10}}},
  { Pos = {offx + 205 + 11*9, offy + 100}, Condition = {Training = ">98"}, More = {"Graphic", {Graphic = "ui/tpbrfull.png", Frame = 11}}},
  { Pos = {offx + 205, offy + 84}, Condition = {Training = "only"}, More = {"Text", "Training", "Centered", false}},

-- Upgrading To
  { Pos = {offx + 12, offy + 153}, Condition = {UpgradeTo = "only"},
    More = {"CompleteBar", {Variable = "UpgradeTo", Width = 152, Height = 12}}
  },
  { Pos = {offx + 37, offy + 86}, More = {"Text", "Upgrading:"}, Condition = {UpgradeTo = "only"} },
  { Pos = {offx + 50, offy + 154}, More = {"Text", "% Complete"}, Condition = {UpgradeTo = "only"} },
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
