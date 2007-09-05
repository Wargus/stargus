--
--  Missiles
--

DefineMissileType("missle-zerg-dark-swarm", {
  File = "terran/dark swarm.png", Size = {252, 188},
  Frames = 10, NumDirections = 1, DrawLevel = 50,
  Class = "missile-class-none", Sleep = 75,
})

DefineSpell( "dark-swarm", 
"range", 1,
"manacost", 6,
"target", "position",
"spawn-missile", "missle-zerg-dark-swarm",
)

DefineMissileType("missle-zerg-rubble-large", {
  File = "zerg/units/rubble large.png", Size = {128, 128},
  Frames = 4, NumDirections = 1, DrawLevel = 1,
  Class = "missile-class-stay", Sleep = 75,
})
--[[
DefineMissileType("missile-zerg-zergling-explode", {
  File = "zerg/units/zzedeath.png", Size = {128, 128},
  Frames = 5, NumDirections = 1, DrawLevel = 1,
  Class = "missile-class-stay", Sleep = 20,
})

DefineMissileType("missile-zerg-hydralisk-explode", {
  File = "zerg/units/zhydeath.png", Size = {128, 128},
  Frames = 4, NumDirections = 1, DrawLevel = 1,
  Class = "missile-class-stay", Sleep = 20,
})

DefineMissileType("missile-terran-firebat-flame", {
  File = "neutral/flamer.png", Size = {224, 224},
  Frames = 221, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 0,
})

--]]