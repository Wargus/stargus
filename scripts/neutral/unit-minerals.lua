--
-- unit-minerals*
--

DefineAnimations("animations-minerals", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineUnitType("unit-minerals1", { Name = "Minerals 1",
  Image = {"file", "neutral/units/mineral1.png", "size", {64, 96}},
  Shadow = {"file", "neutral/units/mineral1 shadow.png", "size", {128, 96}},
  Animations = "animations-minerals", Icon = "icon-minerals1",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  HitPoints = 100000,
  DrawLevel = 5,
  TileSize = {2, 1}, BoxSize = {63, 31},
  SightRange = 0,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Building = true, VisibleUnderFog = true,
  GivesResource = "minerals", CanHarvest = true,
})

DefineUnitType("unit-minerals2", { Name = "Minerals 2",
  Image = {"file", "neutral/units/mineral2.png", "size", {64, 96}},
  Shadow = {"file", "neutral/units/mineral2 shadow.png", "size", {128, 96}},
  Animations = "animations-minerals", Icon = "icon-minerals1",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  HitPoints = 100000,
  DrawLevel = 5,
  TileSize = {2, 1}, BoxSize = {63, 31},
  SightRange = 0,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Building = true, VisibleUnderFog = true,
  GivesResource = "minerals", CanHarvest = true,
})

DefineUnitType("unit-minerals3", { Name = "Minerals 3",
  Image = {"file", "neutral/units/mineral3.png", "size", {64, 96}},
  Shadow = {"file", "neutral/units/mineral3 shadow.png", "size", {128, 96}},
  Animations = "animations-minerals", Icon = "icon-minerals1",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  HitPoints = 100000,
  DrawLevel = 5,
  TileSize = {2, 1}, BoxSize = {63, 31},
  SightRange = 0,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Building = true, VisibleUnderFog = true,
  GivesResource = "minerals", CanHarvest = true,
})

