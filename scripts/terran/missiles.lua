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
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 2,
})

DefineMissileType("missile-terran-vulture-grenade", {
  File = image_unit_bullet_grenade_file, Size = image_unit_bullet_grenade_size,
  Frames = 4, NumDirections = 32, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 2,
})

-- FIXME: wrong graphic
DefineMissileType("missile-terran-battlecruiser-laser", {
  File = image_unit_thingy_elbfire_file, Size = image_unit_thingy_elbfire_size,
  Frames = 17, NumDirections = 22, DrawLevel = 50,
  Class = "missile-class-point-to-point-with-hit", Sleep = 1, Speed = 4, Range = 2,
})

-- FIXME: wrong graphic
DefineMissileType("missile-terran-wraith-laser", {
  File = image_unit_thingy_elbfirew_file, Size = image_unit_thingy_elbfirew_size,
  Frames = 17, NumDirections = 16, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 2,
})

