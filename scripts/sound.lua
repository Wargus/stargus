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
--      $Id: sound.lua 1245 2005-07-02 21:22:56Z jsalmon3 $

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
  "music/title.wav"
}

function SetMusic(music)
  if (music == "menu") then
    playlist = {"music/title.wav"}
  elseif (music == "terran") then
    playlist = {
      "music/terran/1.wav",
      "music/terran/2.wav",
      "music/terran/3.wav"
    }
  elseif (music == "zerg") then
    playlist = {
      "music/zerg/1.wav",
      "music/zerg/2.wav",
      "music/zerg/3.wav"
    }
  elseif (music == "protoss") then
    playlist = {
      "music/protoss/1.wav",
      "music/protoss/2.wav",
      "music/protoss/3.wav"
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
MakeSound("building-placed", "terran/building place.wav")
MakeSound("button", "ui/button.wav")
MakeSound("buzz", "ui/buzz.wav")

-- Explosions

MakeSound("explosion-large", "misc/explolrg.wav")
MakeSound("explosion-medium", "misc/explomed.wav")


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
  "placement-error", SoundForName("buzz"),
  "placement-success", SoundForName("building-placed"),
  "click", SoundForName("button")

-- FIXME: Not ready
--  "transport-docking",
--  "building-construction",

--  "work-complete", {"terran", MakeSound("basic terran voices work complete", "terran/units/scv/upd00.wav")},
--  "work-complete", {"orc", MakeSound("basic orc voices work complete", "orc/basic_voices/work_complete.wav")},

--  "rescue", {"terran", MakeSound("terran rescue", "terran/rescue.wav")},
--  "rescue", {"orc", MakeSound("orc rescue", "orc/rescue.wav")}
)

--MakeSound("highclick", "ui/highclick.wav")
--MakeSound("statsthump", "ui/statsthump.wav")
