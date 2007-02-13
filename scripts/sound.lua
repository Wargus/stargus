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

MakeSound("button", "ui/button.wav")
MakeSound("buzz", "ui/buzz.wav")

-- Explosions

MakeSound("explosion-large", "misc/explolrg.wav")
MakeSound("explosion-medium", "misc/explomed.wav")

-- Basic Terran sounds

MakeSound("terran-base-attacked", "terran/units/advisor/upd00.wav")
MakeSound("terran-units-attacked", "terran/units/advisor/upd01.wav")

-- Marine sounds

MakeSound("terran-marine-ready", "terran/units/marine/ready.wav")
MakeSound("terran-marine-death",
  {"terran/units/marine/death/1.wav",
  "terran/units/marine/death/2.wav"})

MakeSound("terran-marine-attack", "terran/units/marine/fire.wav")

MakeSound("terran-marine-acknowledge",
  {"terran/units/marine/acknowledgement/1.wav",
  "terran/units/marine/acknowledgement/2.wav",
  "terran/units/marine/acknowledgement/3.wav",
  "terran/units/marine/acknowledgement/4.wav"})

MakeSound("terran-marine-select",
  {"terran/units/marine/selected/1.wav",
  "terran/units/marine/selected/2.wav",
  "terran/units/marine/selected/3.wav",
  "terran/units/marine/selected/4.wav"})

MakeSound("terran-marine-annoyed",
  {"terran/units/marine/pissed/1.wav",
  "terran/units/marine/pissed/2.wav",
  "terran/units/marine/pissed/3.wav",
  "terran/units/marine/pissed/4.wav",
  "terran/units/marine/pissed/5.wav",
  "terran/units/marine/pissed/6.wav",
  "terran/units/marine/pissed/7.wav"})

MakeSoundGroup("terran-marine-selected",
  "terran-marine-select", "terran-marine-annoyed")

-- Firebat sounds

MakeSound("terran-firebat-ready", "terran/units/firebat/ready.wav")
MakeSound("terran-firebat-death",
  {"terran/units/firebat/death/1.wav",
  "terran/units/firebat/death/2.wav",
  "terran/units/firebat/death/3.wav"})

MakeSound("terran-firebat-attack",
  {"terran/units/firebat/fire1.wav",
  "terran/units/firebat/fire2.wav"})

MakeSound("terran-firebat-acknowledge",
  {"terran/units/firebat/acknowledgement/1.wav",
  "terran/units/firebat/acknowledgement/2.wav",
  "terran/units/firebat/acknowledgement/3.wav",
  "terran/units/firebat/acknowledgement/4.wav"})

MakeSound("terran-firebat-select",
  {"terran/units/firebat/selected/1.wav",
  "terran/units/firebat/selected/2.wav",
  "terran/units/firebat/selected/3.wav",
  "terran/units/firebat/selected/4.wav"})

MakeSound("terran-firebat-annoyed",
  {"terran/units/firebat/pissed/1.wav",
  "terran/units/firebat/pissed/2.wav",
  "terran/units/firebat/pissed/3.wav",
  "terran/units/firebat/pissed/4.wav",
  "terran/units/firebat/pissed/5.wav",
  "terran/units/firebat/pissed/6.wav",
  "terran/units/firebat/pissed/7.wav"})

MakeSoundGroup("terran-firebat-selected",
  "terran-firebat-select", "terran-firebat-annoyed")

-- Ghost sounds

MakeSound("terran-ghost-ready", "terran/units/ghost/ready.wav")
MakeSound("terran-ghost-death",
  {"terran/units/ghost/death/1.wav",
  --[["terran/units/ghost/death/2.wav"]]})

MakeSound("terran-ghost-attack",
  {"terran/units/ghost/fire.wav"})

MakeSound("terran-ghost-acknowledge",
  {"terran/units/ghost/acknowledgement/1.wav",
  "terran/units/ghost/acknowledgement/2.wav",
  "terran/units/ghost/acknowledgement/3.wav",
  "terran/units/ghost/acknowledgement/4.wav"})

MakeSound("terran-ghost-select",
  {"terran/units/ghost/selected/1.wav",
  "terran/units/ghost/selected/2.wav",
  "terran/units/ghost/selected/3.wav",
  "terran/units/ghost/selected/4.wav"})

MakeSound("terran-ghost-annoyed",
  {"terran/units/ghost/pissed/1.wav",
  "terran/units/ghost/pissed/2.wav",
  "terran/units/ghost/pissed/3.wav",
  "terran/units/ghost/pissed/4.wav"})

MakeSoundGroup("terran-ghost-selected",
  "terran-ghost-select", "terran-ghost-annoyed")

-- Goliath sounds

MakeSound("terran-goliath-ready", "terran/units/goliath/ready.wav")
MakeSound("terran-goliath-death", "terran/units/goliath/death/1.wav")

MakeSound("terran-goliath-attack",
  {"terran/units/goliath/fire.wav",
  "terran/units/goliath/fire2.wav"})

MakeSound("terran-goliath-acknowledge",
  {"terran/units/goliath/acknowledgement/1.wav",
  "terran/units/goliath/acknowledgement/2.wav",
  "terran/units/goliath/acknowledgement/3.wav",
  "terran/units/goliath/acknowledgement/4.wav"})

MakeSound("terran-goliath-select",
  {"terran/units/goliath/selected/1.wav",
  "terran/units/goliath/selected/2.wav",
  "terran/units/goliath/selected/3.wav",
  "terran/units/goliath/selected/4.wav"})

MakeSound("terran-goliath-annoyed",
  {"terran/units/goliath/pissed/1.wav",
  "terran/units/goliath/pissed/2.wav",
  "terran/units/goliath/pissed/3.wav",
  "terran/units/goliath/pissed/4.wav",
  "terran/units/goliath/pissed/5.wav",
  "terran/units/goliath/pissed/6.wav"})

MakeSoundGroup("terran-goliath-selected",
  "terran-goliath-select", "terran-goliath-annoyed")

-- Siege tank sounds

MakeSound("terran-siege-tank-ready", "terran/units/tank/ready.wav")
MakeSound("terran-siege-tank-death", "terran/units/tank/death/1.wav")

MakeSound("terran-siege-tank-attack", "terran/units/tank/fire.wav")

MakeSound("terran-siege-tank-acknowledge",
  {"terran/units/tank/acknowledgement/1.wav",
  "terran/units/tank/acknowledgement/2.wav",
  "terran/units/tank/acknowledgement/3.wav",
  "terran/units/tank/acknowledgement/4.wav"})

MakeSound("terran-siege-tank-select",
  {"terran/units/tank/selected/1.wav",
  "terran/units/tank/selected/2.wav",
  "terran/units/tank/selected/3.wav",
  "terran/units/tank/selected/4.wav"})

MakeSound("terran-siege-tank-annoyed",
  {"terran/units/tank/pissed/1.wav",
  "terran/units/tank/pissed/2.wav",
  "terran/units/tank/pissed/3.wav",
  "terran/units/tank/pissed/4.wav"})

MakeSoundGroup("terran-siege-tank-selected",
  "terran-siege-tank-select", "terran-siege-tank-annoyed")

-- SCV sounds

MakeSound("terran-scv-ready", "terran/units/scv/ready.wav")
MakeSound("terran-scv-death", "terran/units/scv/death/1.wav")

MakeSound("terran-scv-acknowledge",
  {"terran/units/scv/acknowledgement/1.wav",
  "terran/units/scv/acknowledgement/2.wav",
  "terran/units/scv/acknowledgement/3.wav",
  "terran/units/scv/acknowledgement/4.wav"})

MakeSound("terran-scv-select",
  {"terran/units/scv/selected/1.wav",
  "terran/units/scv/selected/2.wav",
  "terran/units/scv/selected/3.wav",
  "terran/units/scv/selected/4.wav"})

MakeSound("terran-scv-annoyed",
  {"terran/units/scv/pissed/1.wav",
  "terran/units/scv/pissed/2.wav",
  "terran/units/scv/pissed/3.wav",
  "terran/units/scv/pissed/4.wav",
  "terran/units/scv/pissed/5.wav",
  "terran/units/scv/pissed/6.wav",
  "terran/units/scv/pissed/7.wav"})

MakeSoundGroup("terran-scv-selected",
  "terran-scv-select", "terran-scv-annoyed")

-- Vulture sounds

MakeSound("terran-vulture-ready", "terran/units/vulture/ready.wav")
MakeSound("terran-vulture-death", "terran/units/vulture/death/1.wav")
MakeSound("terran-vulture-attack", "terran/units/vulture/fire.wav")

MakeSound("terran-vulture-acknowledge",
  {"terran/units/vulture/acknowledgement/1.wav",
  "terran/units/vulture/acknowledgement/2.wav",
  "terran/units/vulture/acknowledgement/3.wav",
  "terran/units/vulture/acknowledgement/4.wav"})

MakeSound("terran-vulture-select",
  {"terran/units/vulture/selected/1.wav",
  "terran/units/vulture/selected/2.wav",
  "terran/units/vulture/selected/3.wav",
  "terran/units/vulture/selected/4.wav"})

MakeSound("terran-vulture-annoyed",
  {"terran/units/vulture/pissed/1.wav",
  "terran/units/vulture/pissed/2.wav",
  "terran/units/vulture/pissed/3.wav",
  "terran/units/vulture/pissed/4.wav"})

MakeSoundGroup("terran-vulture-selected",
  "terran-vulture-select", "terran-vulture-annoyed")

-- Dropship sounds

MakeSound("terran-dropship-ready", "terran/units/dropship/ready.wav")
MakeSound("terran-dropship-death", {"terran/units/dropship/death/1.wav"})

MakeSound("terran-dropship-acknowledge",
  {"terran/units/dropship/acknowledgement/1.wav",
  "terran/units/dropship/acknowledgement/2.wav",
  "terran/units/dropship/acknowledgement/3.wav",
  "terran/units/dropship/acknowledgement/4.wav",
  "terran/units/dropship/acknowledgement/5.wav",
  "terran/units/dropship/acknowledgement/6.wav"})

MakeSound("terran-dropship-select",
  {"terran/units/dropship/selected/1.wav",
  "terran/units/dropship/selected/2.wav",
  "terran/units/dropship/selected/3.wav",
  "terran/units/dropship/selected/4.wav"})

MakeSound("terran-dropship-annoyed",
  {"terran/units/dropship/pissed/1.wav",
  "terran/units/dropship/pissed/2.wav",
  "terran/units/dropship/pissed/3.wav",
  "terran/units/dropship/pissed/4.wav"})

MakeSoundGroup("terran-dropship-selected",
  "terran-dropship-select", "terran-dropship-annoyed")

--- Science Vessel sounds

MakeSound("terran-science-vessel-ready", "terran/units/science vessel/ready.wav")
MakeSound("terran-science-vessel-death", "terran/units/science vessel/death/1.wav")
MakeSound("terran-science-vessel-attack", "terran/units/science vessel/irr00.wav")

MakeSound("terran-science-vessel-acknowledge",
  {"terran/units/science vessel/acknowledgement/1.wav",
  "terran/units/science vessel/acknowledgement/2.wav",
  "terran/units/science vessel/acknowledgement/3.wav",
  "terran/units/science vessel/acknowledgement/4.wav"})

MakeSound("terran-science-vessel-select",
  {"terran/units/science vessel/selected/1.wav",
  "terran/units/science vessel/selected/2.wav",
  "terran/units/science vessel/selected/3.wav",
  "terran/units/science vessel/selected/4.wav"})

MakeSound("terran-science-vessel-annoyed",
  {"terran/units/science vessel/pissed/1.wav",
  "terran/units/science vessel/pissed/2.wav",
  "terran/units/science vessel/pissed/3.wav",
  "terran/units/science vessel/pissed/4.wav",
  "terran/units/science vessel/pissed/5.wav",
  "terran/units/science vessel/pissed/6.wav",
  "terran/units/science vessel/pissed/7.wav"})

MakeSoundGroup("terran-science-vessel-selected",
  "terran-science-vessel-select", "terran-science-vessel-annoyed")

--- Wraith sounds

MakeSound("terran-wraith-ready", "terran/units/wraith/ready.wav")
MakeSound("terran-wraith-death", "terran/units/wraith/death/1.wav")
MakeSound("terran-wraith-attack", "terran/units/wraith/fire100.wav")

MakeSound("terran-wraith-acknowledge",
  {"terran/units/wraith/acknowledgement/1.wav",
  "terran/units/wraith/acknowledgement/2.wav",
  "terran/units/wraith/acknowledgement/3.wav",
  "terran/units/wraith/acknowledgement/4.wav"})

MakeSound("terran-wraith-select",
  {"terran/units/wraith/selected/1.wav",
  "terran/units/wraith/selected/2.wav",
  "terran/units/wraith/selected/3.wav",
  "terran/units/wraith/selected/4.wav"})

MakeSound("terran-wraith-annoyed",
  {"terran/units/wraith/pissed/1.wav",
  "terran/units/wraith/pissed/2.wav",
  "terran/units/wraith/pissed/3.wav",
  "terran/units/wraith/pissed/4.wav",
  "terran/units/wraith/pissed/5.wav",
  "terran/units/wraith/pissed/6.wav",
  "terran/units/wraith/pissed/7.wav"})

MakeSoundGroup("terran-wraith-selected",
  "terran-wraith-select", "terran-wraith-annoyed")

--- Battlecruiser sounds

MakeSound("terran-battlecruiser-ready", "terran/units/battlecruiser/ready.wav")
MakeSound("terran-battlecruiser-death", "terran/units/battlecruiser/death/1.wav")
MakeSound("terran-battlecruiser-attack", "terran/units/battlecruiser/yamato.wav")

MakeSound("terran-battlecruiser-acknowledge",
  {"terran/units/battlecruiser/acknowledgement/1.wav",
  "terran/units/battlecruiser/acknowledgement/2.wav",
  "terran/units/battlecruiser/acknowledgement/3.wav",
  "terran/units/battlecruiser/acknowledgement/4.wav"})

MakeSound("terran-battlecruiser-select",
  {"terran/units/battlecruiser/selected/1.wav",
  "terran/units/battlecruiser/selected/2.wav",
  "terran/units/battlecruiser/selected/3.wav",
  "terran/units/battlecruiser/selected/4.wav"})

MakeSound("terran-battlecruiser-annoyed",
  {"terran/units/battlecruiser/pissed/1.wav",
  "terran/units/battlecruiser/pissed/2.wav",
  "terran/units/battlecruiser/pissed/3.wav",
  "terran/units/battlecruiser/pissed/4.wav",
  "terran/units/battlecruiser/pissed/5.wav"})

MakeSoundGroup("terran-battlecruiser-selected",
  "terran-battlecruiser-select", "terran-battlecruiser-annoyed")

-- Terran buildings

MakeSound("terran-academy-selected", "terran/units/academy.wav")
MakeSound("terran-armory-selected", "terran/units/armory.wav")
MakeSound("terran-supply-depot-selected", "terran/units/supply depot.wav")
MakeSound("terran-missile-turret-selected", "terran/units/missile turret.wav")
MakeSound("terran-engineering-bay-selected", "terran/units/engineering bay.wav")
MakeSound("terran-factory-selected", "terran/units/factory.wav")
MakeSound("terran-refinery-selected", "terran/units/refinery.wav")
MakeSound("terran-science-facility-selected", "terran/units/science facility.wav")


------------------------------------------------------------------------------
--  Define sound remapping. (FIXME: somebody must clean the order.)
--
--MapSound("peon-acknowledge", "basic orc voices acknowledge")

--  Define sounds used by game
--
DefineGameSounds(
  "placement-error", SoundForName("buzz"),
  "placement-success", SoundForName("button"),
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
