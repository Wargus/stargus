DefineAnimations("animations-ragnasaur-ashworld-critter", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineUnitType("unit-critter-ragnasaur", {
  Animations = "animations-ragnasaur-ashworld-critter", Icon = "icon-ragnasaur-ashworld-critter",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  DrawLevel = 5,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
})
