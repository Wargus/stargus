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
--      (c) Copyright 2005-2006 by Jimmy Salmon
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
--      $Id: ui.lua 1228 2005-06-25 21:43:51Z jsalmon3 $



--;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
--  * Race Terran.
--;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

function TerranScreen(screen_width, screen_height)
  local info_panel_x = 0
  local info_panel_y = 160

  DefineUI("terran", screen_width, screen_height,
    "normal-font-color", "white",
    "reverse-font-color", "yellow",

    "filler", {
      File = "ui/tconsole.png",
      Pos = { 0, 0}},

    "resources", {
      "gold", { File = "ui/icons.png", Frame = 0,
        Pos = { 436, 3}, Size = {54, 14}, TextPos = { 452, 3}},
      "wood", { File = "ui/icons.png", Frame = 2,
        Pos = { 504, 3}, Size = {54, 14}, TextPos = { 520, 3}},
      "food", { File = "ui/icons.png", Frame = 5,
        Pos = { 572, 3}, Size = {54, 14}, TextPos = { 588, 3}},
    },

    "info-panel", {
      "panels", {
        "panel-general-contents",
--        "panel-attack-unit-contents",
        "panel-all-unit-contents",
        "panel-building-contents"
      },
      "selected", {
        "single", {
          "icon", {
            "pos", {183, 413}, "style", "icon"}},
        "multiple", {
          "icons", {
            { "pos", {info_panel_x +   9, info_panel_y + 9}, "style", "icon"},
            { "pos", {info_panel_x +  65, info_panel_y + 9}, "style", "icon"},
            { "pos", {info_panel_x + 121, info_panel_y + 9}, "style", "icon"},
            { "pos", {info_panel_x +   9, info_panel_y + 63}, "style", "icon"},
            { "pos", {info_panel_x +  65, info_panel_y + 63}, "style", "icon"},
            { "pos", {info_panel_x + 121, info_panel_y + 63}, "style", "icon"},
            { "pos", {info_panel_x +   9, info_panel_y + 117}, "style", "icon"},
            { "pos", {info_panel_x +  65, info_panel_y + 117}, "style", "icon"},
            { "pos", {info_panel_x + 121, info_panel_y + 117}, "style", "icon"}},
          "max-text", {
            "font", "game",
            "pos", { info_panel_x + 10, info_panel_y + 10}}}
      },
      "training", {
        "single", {
          "text", {
            "text", "Training:",
            "font", "game",
            "pos", { info_panel_x + 37, info_panel_y + 8 + 78}},
          "icon", {
            "pos", { info_panel_x + 110, info_panel_y + 11 + 70},
            "style", "icon"}},
        "multiple", {
          "icons", {
            { "pos", {  9, 219}, "style", "icon"},
            { "pos", { 65, 219}, "style", "icon"},
            { "pos", {121, 219}, "style", "icon"},
            { "pos", {  9, 266}, "style", "icon"},
            { "pos", { 65, 266}, "style", "icon"},
            { "pos", {121, 266}, "style", "icon"}}}
      },
      "upgrading", {
        "icon", {
          "pos", { info_panel_x + 110, info_panel_y + 11 + 70},
          "style", "icon"},
      },
      "researching", {
        "icon", {
          "pos", { info_panel_x + 110, info_panel_y + 11 + 70},
          "style", "icon"}
      },
      "transporting", {
        "icons", {
          { "pos", {  9, 223}, "style", "icon"},
          { "pos", { 65, 223}, "style", "icon"},
          { "pos", {121, 223}, "style", "icon"},
          { "pos", {  9, 277}, "style", "icon"},
          { "pos", { 65, 277}, "style", "icon"},
          { "pos", {121, 277}, "style", "icon"}}
      },
      "completed-bar", {
        "color", {48, 100, 4}
      }
    },

    "button-panel", {
      "icons", {
        {"pos", {505, 358}, "style", "icon"},
        {"pos", {551, 358}, "style", "icon"},
        {"pos", {597, 358}, "style", "icon"},
        {"pos", {505, 398}, "style", "icon"},
        {"pos", {551, 398}, "style", "icon"},
        {"pos", {597, 398}, "style", "icon"},
        {"pos", {505, 438}, "style", "icon"},
        {"pos", {551, 438}, "style", "icon"},
        {"pos", {597, 438}, "style", "icon"}},
      "auto-cast-border-color", {0, 0, 252},
    },

    "map-area", {
      Pos = {0, 0},
      Size = {
        screen_width,
        screen_height - 0 - 106}},

    "menu-panel", {
      "menu-button", {
        Pos = {416, 388},
        Caption = "MENU",
        Style = "menu button"},
      "network-menu-button", {
        Pos = {6, 2},
        Caption = "Menu",
        Style = "network"},
      "network-diplomacy-button", {
        Pos = {90, 2},
        Caption = "Diplomacy",
        Style = "network"},
    },

    "minimap", {
      Pos = {7, 348},
      Size = {128, 128}},

    "status-line", {
      TextPos = {172, 350},
      Font = "game",
      Width = screen_width - 16 - 2 - 176},

    "cursors", {
      Point = "cursor-point",
      Glass = "cursor-glass",
      Cross = "cursor-cross",
      Yellow = "cursor-yellow-hair",
      Green = "cursor-green-hair",
      Red = "cursor-red-hair",
      Scroll = "cursor-scroll",
      ArrowE = "cursor-arrow-e",
      ArrowNE = "cursor-arrow-ne",
      ArrowN = "cursor-arrow-n",
      ArrowNW = "cursor-arrow-nw",
      ArrowW = "cursor-arrow-w",
      ArrowSW = "cursor-arrow-sw",
      ArrowS = "cursor-arrow-s",
      ArrowSE = "cursor-arrow-se"},

    "menu-panels", {
      "panel5", "ui/tconsole.png"},

    "victory-background", "terran/victory screen.png",
    "defeat-background", "terran/defeat screen.png")
end

TerranScreen(640, 480)
TerranScreen(800, 600)
TerranScreen(1024, 768)
TerranScreen(1280, 960)
TerranScreen(1600, 1200)
