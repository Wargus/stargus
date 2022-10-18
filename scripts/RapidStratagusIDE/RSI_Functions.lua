function RSI_MapStarter()
  mapname = "scripts/RapidStratagusIDE/\(2\)Space Madness.smp"    
  Load(mapname)
  RunMap(mapname)
end

function RSI_MapConfiguration()
  
  init_x = 40
  init_y = 40
  initPos = {init_x, init_y}
  
  SetStartView(0, init_x, init_y)
  
  --CreateUnit("unit-terran-marine", 0, initPos)
  --CreateUnit("unit-terran-scv", 0, initPos)
  --CreateUnit("unit-terran-command-center", 0, initPos)
  CreateUnit("unit-zerg-hive", 0, initPos)
  CreateUnit("unit-protoss-gateway", 0, initPos)

  -- on screen
  SetFogOfWar(false)
  RevealMap("explored")
end

