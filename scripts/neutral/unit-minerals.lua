--
-- unit-minerals*
--

DefineAnimations("animations-minerals", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineUnitType("unit-resource-mineral-field", {
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

