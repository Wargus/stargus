--
--  Missiles
--

DefineMissileType("missile-zerg-spit", {
  File = "neutral/missiles/zspark.png", Size = {40, 40},
  Frames = 8, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 1, Speed = 4, Range = 0,
})

-- FIXME: Graphic not drawing in proper directions
DefineMissileType("missile-zerg-mutalisk-glaive-wurm", {
  File = "neutral/missiles/spores.png", Size = {36, 36},
  Frames = 10, NumDirections = 5, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 12, Range = 0,
})

