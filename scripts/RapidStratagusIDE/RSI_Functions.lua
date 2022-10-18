function RSI_MapStarter()
    mapname = "scripts/RapidStratagusIDE/\(2\)Space Madness.smp"    
    Load(mapname)
    RunMap(mapname)
end

function RSI_MapConfiguration()
    CreateUnitTest("unit-terran-marine")
    CreateUnit("unit-terran-scv", 0, {0, 0})
    CreateUnit("unit-terran-command-center", 0, {0, 0})

    -- on screen
    SetFogOfWar(false)
    RevealMap("explored")
end

