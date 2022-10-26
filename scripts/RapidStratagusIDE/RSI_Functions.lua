function RSI_MapStarter()
  mapname = "maps/\(2\)Space Madness.smp"
  Load(mapname)
  RunMap(mapname)
end

function RSI_MapConfiguration()
  init_x = 40
  init_y = 40
  initPos = {init_x, init_y}
  
  SetStartView(0, init_x, init_y)
  
  Load("rsi_testscenario/rsi_configuration.lua")
  
  if (_G["rsi_tc_run"] ~= nil) then
    RSI_tc_run(initPos)
  else
    print("RapidStratagusIDE->rsi_tc_run() not available") 
  end

  -- on screen
  SetFogOfWar(false)
  RevealMap("explored")
end

function RSI_CreateUnitNum(unit, num)
  if not num then num = 10 end
  
  for i=1,num do 
    CreateUnit(unit, 0, {10, 10})
  end    
end