InitFuncs:add(function()
  ai_terran_func = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
end)
--WARNING: HARD TO READ CHILDISH COMMENTING BY n0.obAtroN
local player

local terran_funcs = {
  function() AiDebug(false) return false end,
  function() return AiSleep(AiGetSleepCycles()) end,

--st4rt 0f g4m3/bu1lding st4g3

  function() return AiNeed("unit-terran-command-center") end,
  function() return AiWait("unit-terran-command-center") end,

  function() return AiSet("unit-terran-scv", 7) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-barracks") end,
  function() return AiWait("unit-terran-barracks") end,


  function() return AiSet("unit-terran-scv", 8) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,


--ruSh
--ruSh f0rc3 1s #4

  function() return AiForce(4, {"unit-terran-marine", 4}) end,
  function() return AiWaitForce(4) end,
  function() return AiAttackWithForce(4) end,

  function() return AiNeed("unit-terran-refinery") end,
  function() return AiWait("unit-terran-refinery") end,

  function() return AiSet("unit-terran-scv", 10) end,
  function() return AiWait("unit-terran-scv") end,

--b4s3 d3f3nc3 f0rc3 1s #1
  function() return AiForce(1, {"unit-terran-marine", 2}) end,
  function() return AiWaitForce(1) end,
--  function() return AiForceRole(1, {"defend"}) end,

  function() return AiSet("unit-terran-scv", 11) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiForce(1, {"unit-terran-marine", 3}) end,
  function() return AiWaitForce(1) end,

  function() return AiSet("unit-terran-scv", 12) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,

  function() return AiForce(1, {"unit-terran-marine", 4}) end,
  function() return AiWaitForce(1) end,

  function() return AiSet("unit-terran-scv", 13) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiForce(1, {"unit-terran-marine", 5}) end,
  function() return AiWaitForce(1) end,

  function() return AiSet("unit-terran-scv", 14) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-bunker") end,
  function() return AiWait("unit-terran-bunker") end,

  function() return AiSet("unit-terran-scv", 15) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-barracks") end,
  function() return AiWait("unit-terran-barracks") end,

  function() return AiForce(1, {"unit-terran-marine", 6}) end,
  function() return AiWaitForce(1) end,


  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,

  function() return AiForce(1, {"unit-terran-marine", 7}) end,
  function() return AiWaitForce(1) end,


  function() return AiNeed("unit-terran-refinery") end,
  function() return AiWait("unit-terran-refinery") end,

  function() return AiForce(1, {"unit-terran-marine", 8}) end,
  function() return AiWaitForce(1) end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,

  function() return AiNeed("unit-terran-academy") end,
  function() return AiWait("unit-terran-academy") end,

--  function() return AiResearch(upgrade-terran-u238-shells()) end,

--  function() return AiNeed("upgrade-terran-u238-shells") end,
--  function() return AiNeed("upgrade-terran-infantry-weapons1") end,
--  function() return AiNeed("upgrade-terran-infantry-armor1") end,

  function() return AiForce(1, {"unit-terran-firebat", 2}) end,
  function() return AiForceRole(1, {"defend"}) end,

  function() return AiNeed("unit-terran-factory") end,
  function() return AiWait("unit-terran-factory") end,

  function() return AiNeed("unit-terran-barracks") end,
  function() return AiWait("unit-terran-barracks") end,

--3nd of bu1ld1ng st4g3
--w4r st4g3

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,


--  function() return AiNeed("upgrade-terran-infantry-weapons2") end,
--  function() return AiNeed("upgrade-terran-infantry-armor2") end,


--f1rst 4tt4ck f0rc3 is #2

  function() return AiForce(2, {"unit-terran-marine", 10}) end,

  function() return AiForce(2, {"unit-terran-vulture", 3}) end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,

  function() return AiForce(2, {"unit-terran-siege-tank", 2}) end,

  function() return AiForce(2, {"unit-terran-firebat", 5}) end,

  function() return AiForce(2, {"unit-terran-goliath", 5}) end,
  function() return AiWait("unit-terran-goliath") end,
  function() return AiWaitForce(2) end,

--4TT4CK!!!!!

  function() return AiAttackWithForce(2) end,

--  function() return AiNeed("upgrade-terran-infantry-weapons3") end,

--  function() return AiNeed("upgrade-terran-infantry-armor3") end,

-- st4rt n3w b4s3

  function() return AiNeed("unit-terran-command-center") end,
  function() return AiWait("unit-terran-command-center") end,

  function() return AiNeed("unit-terran-refinery") end,
  function() return AiWait("unit-terran-refinery") end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,
  
  function() return AiNeed("unit-terran-starport") end,
  function() return AiWait("unit-terran-starport") end,

--n3xt 4tt4ck f0rc3 #5 (b1gg3r) 
-- :)

--  function() return AiForce(5, {"unit-terran-wraith", 3}) end,

  function() return AiForce(5, {"unit-terran-marine", 12}) end,

  function() return AiForce(5, {"unit-terran-vulture", 5}) end,

  function() return AiNeed("unit-terran-supply-depot") end,

  function() return AiForce(5, {"unit-terran-siege-tank", 4}) end,

  function() return AiForce(5, {"unit-terran-firebat", 7}) end,

  function() return AiForce(5, {"unit-terran-goliath", 7}) end,

  function() return AiWaitForce(5) end,
--4tt4ck w1th #5

  function() return AiAttackWithForce(5) end,

  function() return true end,
}

function AiTerran()
  local ret

  player = AiPlayer() + 1

  while (true) do
    ret = terran_funcs[ai_terran_func[player]]()
    if (ret) then
      break
    end
    ai_terran_func[player] = ai_terran_func[player] + 1
  end
end


DefineAi("terran-ai", "*", "terran-ai", AiTerran)

