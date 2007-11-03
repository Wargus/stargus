 
InitFuncs:add(function()
  ai_zerg_func = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
end)

local player

local zerg_funcs = {
  function() AiDebug(false) return false end,
  function() return AiSleep(AiGetSleepCycles()) end,
  
--get started
  function() return AiNeed("unit-zerg-hatchery") end,
  function() return AiWait("unit-zerg-hatchery") end,

  function() return AiSet("unit-zerg-overlord", 1) end,
  function() return AiWait("unit-zerg-overlord") end,

  function() return AiSet("unit-zerg-drone", 7) end,
  function() return AiWait("unit-zerg-drone") end,
 
  function() return AiNeed("unit-zerg-spawning-pool") end,
  function() return AiWait("unit-zerg-spawning-pool") end,
  
-- Rush with 4 zerglings
  function() return AiForce(4, {"unit-zerg-zergling", 4}) end,
  function() return AiWaitForce(4) end,
  function() return AiAttackWithForce(4) end,
  
--Get the basics of a common zerg base
  function() return AiNeed("unit-zerg-extractor") end,
  function() return AiWait("unit-zerg-extractor") end,

  function() return AiNeed("unit-zerg-hydralisk-den") end,
  function() return AiWait("unit-zerg-hydralisk-den") end,
  
  function() return AiSet("unit-zerg-overlord", 2) end,
  function() return AiWait("unit-zerg-overlord") end,
  
  function() return AiSet("unit-zerg-drone", 15) end,
  function() return AiWait("unit-zerg-drone") end,
  
  function() return AiSet("unit-zerg-overlord", 4) end,
  function() return AiWait("unit-zerg-overlord") end,
  
--Mid game rush (hydralisk + zerglings)
  function() return AiForce(5, {"unit-zerg-hydralisk", 4}) end,

  function() return AiForce(5, {"unit-zerg-zergling", 4}) end,
  function() return AiWaitForce(5) end,
  function() return AiAttackWithForce(5) end,
  
--Prepare for massing + setting up a defence
  function() return AiSet("unit-zerg-overlord", 5) end,
  function() return AiWait("unit-zerg-overlord") end,

  function() return AiNeed("unit-zerg-hatchery") end,
  function() return AiNeed("unit-zerg-evolution-chamber") end,
  function() return AiWait("unit-zerg-evolution-chamber") end,
  
--Build a defence (sunkens + spore colonies)
--FIXME: Upgrade from creep colonies to spore colonies/sunken colonies
  function() return AiSet("unit-zerg-creep-colony", 4) end,
  function() return AiWait("unit-zerg-creep-colony") end,

--Build a mobile defence
  function() return AiForce(6, {"unit-zerg-hydralisk", 4}) end,

  function() return AiForce(6, {"unit-zerg-zergling", 4}) end,


--Build an army + ATTACK!



--[[
  function() return AiNeed("unit-terran-barracks") end,

  function() return AiSet("unit-terran-scv", 8) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,

--rush
--rush force is #4

  function() return AiForce(4, {"unit-terran-marine", 4}) end,
  function() return AiWaitForce(4) end,
  function() return AiSleep(50*GameSettings.Difficulty) end, 
  function() return AiAttackWithForce(4) end,

  function() return AiNeed("unit-terran-refinery") end,
  function() return AiWait("unit-terran-refinery") end,

  function() return AiSet("unit-terran-scv", 10) end,

--base defence force is #1
  function() return AiForce(1, {"unit-terran-marine", 2}) end,
--  function() return AiForceRole(1, {"defend"}) end,

  function() return AiSet("unit-terran-scv", 11) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiForce(1, {"unit-terran-marine", 3}) end,

  function() return AiSet("unit-terran-scv", 12) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,

  function() return AiForce(1, {"unit-terran-marine", 4}) end,

  function() return AiSet("unit-terran-scv", 13) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiForce(1, {"unit-terran-marine", 5}) end,

  function() return AiSet("unit-terran-scv", 14) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-bunker") end,
  function() return AiWait("unit-terran-bunker") end,

  function() return AiSet("unit-terran-scv", 15) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-barracks") end,
  function() return AiWait("unit-terran-barracks") end,

  function() return AiForce(1, {"unit-terran-marine", 6}) end,

  function() return AiSet("unit-terran-scv", 16) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,

  function() return AiForce(1, {"unit-terran-marine", 7}) end,

  function() return AiSet("unit-terran-scv", 17) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-refinery") end,
  function() return AiWait("unit-terran-refinery") end,

  function() return AiForce(1, {"unit-terran-marine", 8}) end,

  function() return AiSet("unit-terran-scv", 18) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,

  function() return AiNeed("unit-terran-academy") end,
  function() return AiWait("unit-terran-academy") end,

--  function() return AiResearch(upgrade-terran-u238-shells()) end,

--  function() return AiNeed("upgrade-terran-u238-shells") end,
--  function() return AiNeed("upgrade-terran-infantry-weapons1") end,
--  function() return AiNeed("upgrade-terran-infantry-armor1") end,

  function() return AiForce(1, {"unit-terran-firebat", 2}) end,

  function() return AiNeed("unit-terran-factory") end,
  function() return AiWait("unit-terran-factory") end,

  function() return AiNeed("unit-terran-barracks") end,
  function() return AiWait("unit-terran-barracks") end,

--end of building stage
--war stage

  function() return AiNeed("unit-terran-supply-depot") end,

--  function() return AiNeed("upgrade-terran-infantry-weapons2") end,
--  function() return AiNeed("upgrade-terran-infantry-armor2") end,


--first attack force is #2

  function() return AiForce(2, {"unit-terran-marine", 10}) end,

  function() return AiForce(2, {"unit-terran-vulture", 3}) end,

  function() return AiNeed("unit-terran-supply-depot") end,

  function() return AiForce(2, {"unit-terran-siege-tank", 2}) end,

  function() return AiForce(2, {"unit-terran-firebat", 5}) end,

  function() return AiForce(2, {"unit-terran-goliath", 5}) end,
  function() return AiWait("unit-terran-goliath") end,


--ATTACK!!!!!

  function() return AiWaitForce(2) end,
  function() return AiSleep(50*GameSettings.Difficulty) end, 
  function() return AiAttackWithForce(2) end,

--  function() return AiNeed("upgrade-terran-infantry-weapons3") end,

--  function() return AiNeed("upgrade-terran-infantry-armor3") end,

-- start new base

  function() return AiNeed("unit-terran-command-center") end,
  function() return AiWait("unit-terran-command-center") end,

  function() return AiNeed("unit-terran-refinery") end,
  function() return AiWait("unit-terran-refinery") end,

  function() return AiNeed("unit-terran-supply-depot") end,

  function() return AiNeed("unit-terran-starport") end,

--next attack force #5 (bigger) 
-- :)

--  function() return AiForce(5, {"unit-terran-wraith", 3}) end,

  function() return AiForce(5, {"unit-terran-marine", 12}) end,

  function() return AiForce(5, {"unit-terran-vulture", 5}) end,

  function() return AiNeed("unit-terran-supply-depot") end,

  function() return AiForce(5, {"unit-terran-siege-tank", 4}) end,

  function() return AiForce(5, {"unit-terran-firebat", 7}) end,

  function() return AiForce(5, {"unit-terran-goliath", 7}) end,

--attack with #5

  function() return AiWaitForce(5) end,
  function() return AiSleep(50*GameSettings.Difficulty) end, 
  function() return AiAttackWithForce(5) end,
--]]

  function() return true end,
}

function AiZerg()
  local ret

  player = AiPlayer() + 1

  while (true) do
    ret = zerg_funcs[ai_zerg_func[player]]()
    if (ret) then
      break
    end
    ai_zerg_func[player] = ai_zerg_func[player] + 1
  end
end


DefineAi("zerg-ai", "*", "zerg-ai", AiZerg)

