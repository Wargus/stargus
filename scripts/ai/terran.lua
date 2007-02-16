InitFuncs:add(function()
  ai_terran_func = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
end)

local player

local terran_funcs = {
  function() AiDebug(false) return false end,
  function() return AiSleep(AiGetSleepCycles()) end,

  function() return AiNeed("unit-terran-command-center") end,
  function() return AiWait("unit-terran-command-center") end,

  function() return AiSet("unit-terran-scv", 7) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-barracks") end,

  function() return AiSet("unit-terran-scv", 8) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,

  function() return AiSet("unit-terran-scv", 10) end,

  function() return AiForce(0, {"unit-terran-marine", 1}) end,

  function() return AiSet("unit-terran-scv", 11) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiForce(1, {"unit-terran-marine", 2}) end,

  function() return AiSet("unit-terran-scv", 12) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,

  function() return AiForce(1, {"unit-terran-marine", 3}) end,

  function() return AiSet("unit-terran-scv", 13) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiForce(1, {"unit-terran-marine", 4}) end,

  function() return AiSet("unit-terran-scv", 14) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-bunker") end,
  function() return AiWait("unit-terran-bunker") end,

  function() return AiForce(1, {"unit-terran-marine", 5}) end,

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

  function() return AiNeed("unit-terran-bunker") end,
  function() return AiWait("unit-terran-bunker") end,

  function() return AiForce(1, {"unit-terran-marine", 10}) end,

  function() return AiSet("unit-terran-scv", 19) end,
  function() return AiWait("unit-terran-scv") end,

  function() return AiNeed("unit-terran-supply-depot") end,
  function() return AiWait("unit-terran-supply-depot") end,

  function() return AiForce(1, {"unit-terran-marine", 12}) end,

  function() return AiNeed("unit-terran-academy") end,
  function() return AiWait("unit-terran-academy") end,

  function() return AiForce(1, {"unit-terran-marine", 14}) end,

  function() return AiNeed("unit-terran-barracks") end,
  function() return AiWait("unit-terran-barracks") end,

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

