DefineAnimations("animations-bengalaas-jungle-critter", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineUnitType("unit-critter-bengalaas", {
  Animations = "animations-bengalaas-jungle-critter", Icon = "icon-bengalaas-jungle-critter",
  NeutralMinimapColor = {0, 228, 252},
  DrawLevel = 5,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  LandUnit = true,
  organic = true,
})
