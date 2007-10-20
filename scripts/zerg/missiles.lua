--
--  Missiles
--

DefineMissileType("missile-zerg-spit", {
  File = "neutral/missiles/zspark.png", Size = {40, 40},
  Frames = 8, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 1, Speed = 4, Range = 0,
})

-- FIXME: wrong graphic
DefineMissileType("missile-zerg-mutalisk-glaive-wurm", {
  File = "neutral/missiles/blastcan.png", Size = {32, 32},
  Frames = 17, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 0,
})

