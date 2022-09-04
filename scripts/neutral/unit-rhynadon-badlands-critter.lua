DefineAnimations("animations-rhynadon-badlands-critter", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineUnitType("unit-critter-rhynadon", {
  Animations = "animations-rhynadon-badlands-critter", Icon = "icon-rhynadon-badlands-critter",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  DrawLevel = 5,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  LandUnit = true,
  organic = true,
})
