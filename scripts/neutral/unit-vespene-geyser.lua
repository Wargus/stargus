--
-- unit-vespene-geyser
--

DefineAnimations("animations-vespene-geyser", {
  Still = {--[[FIXME: frame depends on tileset]]
    "frame 0", "wait 125",
  },
})



DefineUnitType("unit-resource-vespene-geyser", {
  Animations = "animations-vespene-geyser", Icon = "icon-vespene-geyser",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  DrawLevel = 5,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Building = true, VisibleUnderFog = true,
  GivesResource = "gas",
})

