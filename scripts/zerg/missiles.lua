--
--  Missiles
--

DefineMissileType("missile-zerg-spit", {
  File = image_504_bullet_zspark_file, Size = image_504_bullet_zspark_size,
  Frames = 8, DrawLevel = 50,
  Class = "missile-class-stay", Sleep = 1, Speed = 4, Range = 0,
})

-- FIXME: Graphic not drawing in proper directions
DefineMissileType("missile-zerg-mutalisk-glaive-wurm", {
  File = image_511_bullet_spores_file, Size = image_511_bullet_spores_size,
  Frames = 10, DrawLevel = 50,
  Class = "missile-class-point-to-point", Sleep = 1, Speed = 12, Range = 0,
})

