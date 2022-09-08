--
--  Missiles
--

DefineMissileType("missile-terran-explosion-small", {
  File = image_213_thingy_tbangs_file, Size = image_213_thingy_tbangs_size,
  Frames = 9, NumDirections = image_213_thingy_tbangs_NumDirections, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-explosion-medium", {
  File = image_214_thingy_tbangl_file, Size = image_214_thingy_tbangl_size,
  Frames = 10, NumDirections = image_214_thingy_tbangl_NumDirections, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-explosion-large", {
  File = image_215_thingy_tbangx_file, Size = image_215_thingy_tbangx_size,
  Frames = 14, NumDirections = image_215_thingy_tbangx_NumDirections, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 2,
})

DefineMissileType("missile-terran-firebat-flame", {
  File = image_421_thingy_flamer_file, Size = image_421_thingy_flamer_size,
  Frames = 221, NumDirections = image_421_thingy_flamer_NumDirections, DrawLevel = 50,
  SplashFactor = 10;
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 2,
})

DefineMissileType("missile-terran-vulture-grenade", {
  File = image_532_bullet_grenade_file, Size = image_532_bullet_grenade_size,
  Frames = 4, NumDirections = image_532_bullet_grenade_NumDirections, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 2,
})

-- FIXME: wrong graphic
DefineMissileType("missile-terran-battlecruiser-laser", {
  File = image_534_thingy_elbfire_file, Size = image_534_thingy_elbfire_size,
  Frames = 17, NumDirections = image_534_thingy_elbfire_NumDirections, DrawLevel = 50,
  Class = "missile-class-point-to-point-with-hit", Sleep = 1, Speed = 4, Range = 2,
})

-- FIXME: wrong graphic
DefineMissileType("missile-terran-wraith-laser", {
  File = image_535_thingy_elbfirew_file, Size = image_535_thingy_elbfirew_size,
  Frames = 17, NumDirections = image_535_thingy_elbfirew_NumDirections, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 4, Range = 2,
})

