--
-- unit-vespene-geyser
--

DefineAnimations("animations-vespene-geyser", {
  Still = {--[[FIXME: frame depends on tileset]]
    "frame 0", "wait 125",
  },
})



DefineUnitType("unit-resource-vespene-geyser", { Name = "Vespene Geyser",
  Image = {"file", "neutral/units/geyser.png", "size", {128, 64}},
  Shadow = {"file", "neutral/units/geyser shadow.png", "size", {160, 64}},
  Animations = "animations-vespene-geyser", Icon = "icon-vespene-geyser",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  HitPoints = 0,
  DrawLevel = 5,
  TileSize = {4, 2}, BoxSize = {127, 63},
  SightRange = 0,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Building = true, VisibleUnderFog = true,
  GivesResource = "gas",
})

