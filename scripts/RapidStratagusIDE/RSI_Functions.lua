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
  
  if (_G["RSI_tc_run"] ~= nil) then
    RSI_tc_run(initPos)
  else
    print("RapidStratagusIDE->RSI_tc_run() not available") 
  end

  -- on screen
  SetFogOfWar(false)
  RevealMap("explored")
end

