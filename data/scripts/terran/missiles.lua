--
--  Missiles
--

DefineMissileType("missile-terran-explosion-small", {
  File = "terran/explosion small.png", Size = {128, 128},
  Frames = 9, NumDirections = 1, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-explosion-medium", {
  File = "terran/explosion medium.png", Size = {200, 200},
  Frames = 10, NumDirections = 1, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-explosion-large", {
  File = "terran/explosion large.png", Size = {252, 200},
  Frames = 14, NumDirections = 1, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-firebat-flame", {
  File = "terran/flamer.png", Size = {224, 224},
  Frames = 221, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 0,
})

