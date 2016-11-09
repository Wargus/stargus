--
-- unit-zerg-creep
--

DefineAnimations("animations-zerg-creep", {
  Still = { "frame 1", "wait 100" }
})

-- Todo: adjust unit image per tileset
DefineUnitType(
   "unit-zerg-creep",
   { Name = "Creep",
     Image = {"file", "tilesets/badlands/creep.png", "size", {32, 32}},
     Costs = {"time", 1},
     Animations = "animations-zerg-creep", 
     NeutralMinimapColor = {100, 100, 100},
     Priority = 0,
     HitPoints = 1,
     TileSize = {1, 1}, BoxSize = {32, 32},
     SightRange = 0,
     Indestructible = 1,
     DrawLevel = 0,
     IsNotSelectable = true,
     NonSolid = true,
     Wall = true,
     NoRandomPlacing = false,
     ComputerReactionRange = 0,
     PersonReactionRange = 0,
     AnnoyComputerFactor = -100,
     AiAdjacentRange = 0,
     Revealer = false,
     Decoration = true,
     Type = "land", Building = false,
     VisibleUnderFog = true,
     NumDirections = 37,
     Flip = false
})
