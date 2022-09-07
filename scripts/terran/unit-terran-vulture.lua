--
-- unit-terran-vulture
--

DefineAnimations("animations-terran-vulture", {
  Still = {
    "frame 0", "wait 125",
  },
  Move = {
    "label accel1", "unbreakable begin",
      "frame 0", "move 1", "wait 1", "frame 0", "move 1", "wait 1",
      "frame 0", "move 1", "wait 1", "frame 0", "move 1", "wait 1",
      "frame 0", "move 2", "wait 1", "frame 0", "move 2", "wait 1",
    "unbreakable end", "wait 1",
      "if-var R >= 80 accel1", -- 180 turn, accellerate from slow
      "if-var R <= -80 accel1", -- 180 turn, accellerate from slow
      "if-var W < 2 accel1", -- less than 4 tiles remaining on path, slow down
    
    "label accel2", "unbreakable begin",
      "frame 0", "move 2", "wait 1", "frame 0", "move 3", "wait 1", "frame 0", "move 3",
    "unbreakable end", "wait 1",
      "if-var R >= 80 accel1", -- 180 turn, accellerate from slow
      "if-var R <= -80 accel1", -- 180 turn, accellerate from slow
      "if-var R >= 20 accel2", -- 90 turn, accellerate from med
      "if-var R <= -20 accel2", -- 90 turn, accellerate from med
      "lua-callback print W",
      "if-var W < 4 accel2", -- less than 8 tiles remaining on path, slow down
      "if-var W < 2 accel1", -- less than 4 tiles remaining on path, slow down

    "label fullspeed",
      "unbreakable begin", "frame 0", "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",
      "if-var R >= 80 accel1", -- 180 turn, accellerate from slow
      "if-var R <= -80 accel1", -- 180 turn, accellerate from slow
      "if-var R >= 20 accel2", -- 90 turn, accellerate from med
      "if-var R <= -20 accel2", -- 90 turn, accellerate from med
      "lua-callback print W",
      "if-var W < 4 accel2", -- less than 8 tiles remaining on path, slow down
      "if-var W < 2 accel1", -- less than 4 tiles remaining on path, slow down
      "unbreakable begin", "frame 0", "move 2", "wait 1", "move 2", "wait 1", "move 4", "unbreakable end", "wait 1",
      "if-var R >= 80 accel1", -- 180 turn, accellerate from slow
      "if-var R <= -80 accel1", -- 180 turn, accellerate from slow
      "if-var R >= 20 accel2", -- 90 turn, accellerate from med
      "if-var R <= -20 accel2", -- 90 turn, accellerate from med
      "lua-callback print W",
      "if-var W < 4 accel2", -- less than 8 tiles remaining on path, slow down
      "if-var W < 2 accel1", -- less than 4 tiles remaining on path, slow down
      "unbreakable begin", "frame 0", "move 4", "wait 1", "move 4", "unbreakable end", "wait 1",
      "if-var R >= 80 accel1", -- 180 turn, accellerate from slow
      "if-var R <= -80 accel1", -- 180 turn, accellerate from slow
      "if-var R >= 20 accel2", -- 90 turn, accellerate from med
      "if-var R <= -20 accel2", -- 90 turn, accellerate from med
      "lua-callback print W",
      "if-var W < 4 accel2", -- less than 8 tiles remaining on path, slow down
      "if-var W < 2 accel1", -- less than 4 tiles remaining on path, slow down
      "unbreakable begin", "frame 0", "move 2", "wait 1", "move 2", "wait 1", "move 4", "unbreakable end", "wait 1",
      "if-var R >= 80 accel1", -- 180 turn, accellerate from slow
      "if-var R <= -80 accel1", -- 180 turn, accellerate from slow
      "if-var R >= 20 accel2", -- 90 turn, accellerate from med
      "if-var R <= -20 accel2", -- 90 turn, accellerate from med
      "lua-callback print W",
      "if-var W < 4 accel2", -- less than 8 tiles remaining on path, slow down
      "if-var W < 2 accel1", -- less than 4 tiles remaining on path, slow down
      "goto fullspeed",
  },
  Attack = {
    "unbreakable begin", "attack",
    "unbreakable end", "wait 1",
  },
--
  Death = {
    "unbreakable begin",
    "sound terran-vulture-death", --[[active overlay 332,0]] "wait 3",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-terran-vulture", {
  Animations = "animations-terran-vulture", Icon = "icon-terran-vulture",
  Costs = {"time", 60, "minerals", 75},
  Speed = 10,
  DrawLevel = 40,
  RotationSpeed = 10,
  -- TileSize = {5, 5}, BoxSize = {47, 47}, Offset = {1, -2}, BoxOffset = {1, -2},
  BoardSize = 2,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-terran-vulture-grenade",
  AnnoyComputerFactor = 55,
  Priority = 60,
  Points = 50,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-small",
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-vulture-selected",
    "acknowledge", "terran-vulture-acknowledge",
    "ready", "terran-vulture-ready",
    "help", "terran-units-attacked",} } )

-- TODO: temporarily Jim is the same as any other vulture
CopyUnitType("unit-terran-vulture", "Jim-Raynor-(Vulture)")
DefineUnitType("Jim-Raynor-(Vulture)", { Name = "Jim Raynor" })
