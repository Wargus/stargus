--
--  unit-zerg-egg
--


DefineAnimations("animations-zerg-egg-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 2", "frame 1", "wait 2", "frame 2", "wait 2",
    "frame 3", "wait 2", "frame 4", "wait 2", "frame 5", "wait 2",
    "frame 6", "wait 2", "frame 7", "wait 2", "frame 8", "wait 2",
    "frame 9", "wait 25", "frame 10", "wait 25", "frame 11", "wait 25",
    "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-egg-death", { Name = "Dead Egg",
  Image = {"file", "zerg/units/egg death.png", "size", {96, 96}},
  Animations = "animations-zerg-egg-death", Icon = "icon-zerg-egg",
  NumDirections = 1,
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  SelectableByRectangle = false,
  Vanishes = true,
  Sounds = {} } )


DefineAnimations("animations-zerg-egg", {
  Still = {
    "frame 20", "wait 2", "frame 21", "wait 2", "frame 22", "wait 2",
    "frame 23", "wait 2",
    "label 3E03", "frame 0", "wait 2", "frame 1", "wait 2",
    "frame 3", "wait 2", "frame 4", "wait 2", "frame 4", "wait 2",
    "frame 6", "wait 2", "frame 7", "wait 2", "frame 8", "wait 2",
    "frame 9", "wait 2", "frame 10", "wait 2", "frame 11", "wait 2",
    "goto 3E03"
  },
})

DefineUnitType("unit-zerg-egg", { Name = "Egg",
  Image = {"file", "zerg/units/egg.png", "size", {96, 96}},
  Shadow = {"file", "zerg/units/egg shadow.png", "size", {96, 96}},
  NumDirections = 1,
  DrawLevel = 30,
  Animations = "animations-zerg-egg", Icon = "icon-zerg-egg",
  HitPoints = 200,
  Armor = 10, Missile = "missile-none",
  Corpse = "unit-zerg-egg-death",
  Type = "land",
} )