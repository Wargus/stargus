 
InitFuncs:add(function()
  ai_zerg_func = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
end)

local player

local zerg_funcs = {
  function() AiDebug(false) return false end,
  function() return AiSleep(AiGetSleepCycles()) end,
  
--cheat a little
  function() return SetPlayerData(GetThisPlayer(), "Resources", "minerals", + 500) end,
  function() return SetPlayerData(GetThisPlayer(), "Resources", "gas", + 500) end,
  
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
  function() return AiSet("unit-zerg-creep-colony", 4) end,
  function() return AiWait("unit-zerg-creep-colony") end,
  function() return AiUpgradeTo("unit-zerg-sunken-colony") end,
  function() return AiUpgradeTo("unit-zerg-spore-colony") end,
  
--Upgrade Hatchery to lair
  function() return AiUpgradeTo("unit-zerg-lair") end,

--Build a mobile defence
  function() return AiForce(6, {"unit-zerg-hydralisk", 4}) end,
  function() return AiForceRole(6, {"defend"}) end,

--Build an army
  function() return AiForce(7, {"unit-zerg-hydralisk", 4}) end,
  function() return AiForce(7, {"unit-zerg-zergling", 4}) end,
  function() return AiForce(7, {"unit-zerg-ultralisk", 4}) end,
  function() return AiForce(7, {"unit-zerg-mutalisk", 4}) end,
  function() return AiForce(7, {"unit-zerg-overlord", 2}) end, --Need to detect cloaked enemy units + for transporting
  function() return AiWaitForce(7) end,
  
--Attack with force
  function() return AiAttackWithForce(7) end,

--Morph Lair to hive
  function() return AiUpgradeTo("unit-zerg-hive") end,
  
  function() return AiNeed("unit-zerg-ultralisk-cavern") end,
  function() return AiWait("unit-zerg-ultralisk-cavern") end,
  
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

