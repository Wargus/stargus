--
--  unit-zerg-larva
--


DefineAnimations("animations-zerg-larva-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 2", "frame 1", "wait 2", "frame 2", "wait 2",
    "frame 3", "wait 2", "frame 4", "wait 2", "frame 5", "wait 2",
    "frame 6", "wait 25", "frame 7", "wait 25", "frame 8", "wait 25",
    "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-larve-death", { Name = "Dead Larva",
  Image = {"file", "zerg/units/larva death.png", "size", {64, 64}},
  Animations = "animations-zerg-larve-death", Icon = "icon-zerg-larva",
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


DefineAnimations("animations-zerg-larva", {
  Still = {"frame 0", "wait 125",},
})

DefineUnitType("unit-zerg-larva", { Name = "Larva",
  NumDirections = 17,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},
  Animations = "animations-zerg-larva", Icon = "icon-zerg-larva",
  HitPoints = 25,
  Armor = 10, Missile = "missile-none",
  Corpse = "unit-zerg-larva-death",
  Type = "land",
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
} )

-- larva

DefineUnitType("unit-zerg-drone", {})
DefineUnitType("unit-zerg-zergling", {})
DefineUnitType("unit-zerg-hydralisk", {})
DefineUnitType("unit-zerg-ultralisk", {})
DefineUnitType("unit-zerg-overlord", {})
DefineUnitType("unit-zerg-queen", {})
DefineUnitType("unit-zerg-scourge", {})
DefineUnitType("unit-zerg-defiler", {})
DefineUnitType("unit-zerg-mutalisk", {})

DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-drone",
  Action = "upgrade-to", Value = "unit-zerg-drone",
  Key = "d", Hint = "Build Drone",
  ForUnit = {"unit-zerg-larva"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-zerg-zergling",
  Action = "upgrade-to", Value = "unit-zerg-zergling",
  Key = "z", Hint = "Zergling",
  ForUnit = {"unit-zerg-larva"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-zerg-overlord",
  Action = "upgrade-to", Value = "unit-zerg-overlord",
  Key = "o", Hint = "Overlord",
  ForUnit = {"unit-zerg-larva"} } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-zerg-hydralisk",
  Action = "upgrade-to", Value = "unit-zerg-hydralisk",
  Key = "h", Hint = "Hydralisk",
  ForUnit = {"unit-zerg-larva"} } )
  
 DefineButton( { Pos = 5, Level = 0, Icon = "icon-zerg-mutalisk",
  Action = "upgrade-to", Value = "unit-zerg-mutalisk",
  Key = "m", Hint = "Mutalisk",
  ForUnit = {"unit-zerg-larva"} } )
  
DefineButton( { Pos = 6, Level = 0, Icon = "icon-zerg-scourge",
  Action = "upgrade-to", Value = "unit-zerg-scourge",
  Key = "s", Hint = "Scourge",
  ForUnit = {"unit-zerg-larva"} } )
  
DefineButton( { Pos = 7, Level = 0, Icon = "icon-zerg-queen",
  Action = "upgrade-to", Value = "unit-zerg-queen",
  Key = "q", Hint = "Queen",
  ForUnit = {"unit-zerg-larva"} } )
  
DefineButton( { Pos = 8, Level = 0, Icon = "icon-zerg-ultralisk",
  Action = "upgrade-to", Value = "unit-zerg-ultralisk",
  Key = "u", Hint = "Ultralisk",
  ForUnit = {"unit-zerg-larva"} } )
  
DefineButton( { Pos = 9, Level = 0, Icon = "icon-zerg-defiler",
  Action = "upgrade-to", Value = "unit-zerg-defiler",
  Key = "d", Hint = "Defiler",
  ForUnit = {"unit-zerg-larva"} } )


