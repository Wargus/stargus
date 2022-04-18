DefineAnimations("animations-ragnasaur-ashworld-critter", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineUnitType("Ragnasaur-(Ashworld-Critter)", { Name = "Ragnasaur (Ashworld Critter)",
  Image = {"file", "neutral/units/ragnasaur ashworld critter.png", "size", {104, 104}},
  Shadow = {"file", "neutral/units/ragnasaur ashworld critter shadow.png", "size", {104, 104}},
  Animations = "animations-ragnasaur-ashworld-critter", Icon = "icon-ragnasaur-ashworld-critter",
  NeutralMinimapColor = {0, 228, 252},
  Speed = 0,
  HitPoints = 20,
  DrawLevel = 5,
  TileSize = {2, 1}, BoxSize = {63, 31},
  SightRange = 0,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  LandUnit = true,
  organic = true,
})
