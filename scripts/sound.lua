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
--      sound.lua - Define the used sounds.
--
--      (c) Copyright 2004-2007 by Jimmy Salmon
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

--  Uncomment this to enable threaded sound
--SoundThread()

------------------------------------------------------------------------------
--  Music part

------------------------------------------------------------------------------
--  MusicStopped is called if the current music is finished.
--
--    This is a random music player demo
--

local playlist = {
  "music/title.ogg"
}

function SetMusic(music)
  if (music == "menu") then
    playlist = {"music/title.ogg"}
  elseif (music == "terran") then
    playlist = {
      "music/terran/1.ogg",
      "music/terran/2.ogg",
      "music/terran/3.ogg"
    }
  elseif (music == "zerg") then
    playlist = {
      "music/zerg/1.ogg",
      "music/zerg/2.ogg",
      "music/zerg/3.ogg"
    }
  elseif (music == "protoss") then
    playlist = {
      "music/protoss/1.ogg",
      "music/protoss/2.ogg",
      "music/protoss/3.ogg"
    }
  end
  MusicStopped()
end

function MusicStopped()
  if (table.getn(playlist) ~= 0) then
    PlayMusic(playlist[math.random(table.getn(playlist))])
  end
end

-- SetCdMode("off")
MakeSound("building-placed", "terran/building place.ogg")
MakeSound("button", "ui/button.ogg")
MakeSound("buzz", "ui/buzz.ogg")

-- Explosions

MakeSound("explosion-large", "misc/explolrg.ogg")
MakeSound("explosion-medium", "misc/explomed.ogg")


Load("scripts/terran/sound.lua")
Load("scripts/zerg/sound.lua")
Load("scripts/protoss/sound.lua")


------------------------------------------------------------------------------
--  Define sound remapping. (FIXME: somebody must clean the order.)
--
--MapSound("peon-acknowledge", "basic orc voices acknowledge")

--  Define sounds used by game
--
DefineGameSounds(
  "placement-error", {"terran", SoundForName("buzz")},
  "placement-error", {"zerg", SoundForName("buzz")},
  "placement-error", {"protoss", SoundForName("buzz")},
  "placement-success", {"terran", SoundForName("building-placed")},
  "placement-success", {"zerg", SoundForName("building-placed")},
  "placement-success", {"protoss", SoundForName("building-placed")},
  "click", SoundForName("button")

-- FIXME: Not ready
--  "transport-docking",
--  "building-construction",

--  "work-complete", {"terran", MakeSound("basic terran voices work complete", "terran/units/scv/upd00.ogg")},
--  "work-complete", {"orc", MakeSound("basic orc voices work complete", "orc/basic_voices/work_complete.ogg")},

--  "rescue", {"terran", MakeSound("terran rescue", "terran/rescue.ogg")},
--  "rescue", {"orc", MakeSound("orc rescue", "orc/rescue.ogg")}
)

--MakeSound("highclick", "ui/highclick.ogg")
--MakeSound("statsthump", "ui/statsthump.ogg")
