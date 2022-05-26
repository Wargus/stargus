--
-- unit-minerals*
--

DefineAnimations("animations-minerals", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineUnitType("unit-resource-mineral-field", {
  Shadow = {"file", "neutral/units/mineral1 shadow.png", "size", {128, 96}},
  Animations = "animations-minerals", Icon = "icon-minerals1",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  DrawLevel = 5,
  TileSize = {2, 1}, BoxSize = {63, 31},
  SightRange = 0,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Building = true, VisibleUnderFog = true,
  GivesResource = "minerals", CanHarvest = true,
})

DefineUnitType("unit-resource-mineral-field-type-2", {
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

DefineUnitType("unit-resource-mineral-field-type-3", {
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

