--
--  Missiles
--

DefineMissileType("missile-terran-explosion-small", {
  File = image_unit_thingy_tbangs_file, Size = image_unit_thingy_tbangs_size,
  Frames = 9, NumDirections = 1, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-explosion-medium", {
  File = image_unit_thingy_tbangl_file, Size = image_unit_thingy_tbangl_size,
  Frames = 10, NumDirections = 1, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-explosion-large", {
  File = image_unit_thingy_tbangx_file, Size = image_unit_thingy_tbangx_size,
  Frames = 14, NumDirections = 1, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-firebat-flame", {
  File = image_unit_thingy_flamer_file, Size = image_unit_thingy_flamer_size,
  Frames = 221, NumDirections = 32, DrawLevel = 50,
  SplashFactor = 10;
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 0,
})

DefineMissileType("missile-terran-vulture-grenade", {
  File = image_unit_bullet_grenade_file, Size = image_unit_bullet_grenade_size,
  Frames = 4, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 2,
})

-- FIXME: wrong graphic
DefineMissileType("missile-terran-battlecruiser-laser", {
  File = "neutral/missiles/blastcan.png", Size = {32, 32},
  Frames = 17, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 0,
})

-- FIXME: wrong graphic
DefineMissileType("missile-terran-wraith-laser", {
  File = "neutral/missiles/blastcan.png", Size = {32, 32},
  Frames = 17, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 0,
})

