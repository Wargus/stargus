


--[[
DefineAnimations("animations-zerg-hydralisk-death", {
  Death = {"unbreakable begin", "frame 0", "wait 40", "frame 1", "wait 40",
    "frame 2", "wait 40", "frame 3", "wait 40", "frame 4", "unbreakable end", "wait 1", },
})

DefineUnitType("unit-zerg-hydralisk-death", { Name = "DEAD HYDRLAISK",
  Image = {"file", "zerg/units/zhydeath.png", "size", {128, 128}},
  Animations = "animations-zerg-hydralisk-death", Icon = "icon-zerg-hydralisk",
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
]]--




DefineAnimations("animations-zerg-defiler", {
   Still = {
    "frame 187", "wait 125",
  },
  Move = {"unbreakable begin",
    "move 6", "wait 1", "frame 136", "move 3", "wait 1", "frame 153",
    "move 3", "wait 1", "frame 0", "move 3", "wait 1", "frame 17",
    "move 5", "wait 1", "frame 34", "move 5", "wait 1", "frame 51",
    "move 4", "wait 1", "frame 68",
    --FIXME: sub-tile movement
    --[["move 8", "wait 1", "frame 85",
    "move 6", "wait 1", "frame 102", "move 4",
    "unbreakable end", "wait 1", "frame 119",]]
    "move 3", "unbreakable end", "wait 1", "frame 119",
	},
  Attack = {
    "unbreakable begin", "wait 5", "frame 68", "sound hydralisk-attack", "attack",
    "unbreakable end", "wait 5",
  },
  Death = {
    "unbreakable begin",
    "frame 203", "wait 200", "frame 208", "wait 30", "frame 209", "wait 30",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-zerg-defiler", { Name = "Hydralisk",
  Image = {"file", "zerg/units/defiler.png", "size", {80, 80}},
  Shadow = {"file", "zerg/units/defiler.png", "size", {80, 80}, "offset", {0, 7}},
  Animations = "animations-zerg-defiler", Icon = "icon-zerg-defiler",
  Costs = {"time", 60, "minerals", 75},
  Speed = 10, NumDirections = 32,
  HitPoints = 80,
  Mana = 200,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 4, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 2, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  MaxAttackRange = 0,
  Priority = 60,
  Points = 50,
  Demand = 2,
  Corpse = "unit-zerg-hydralisk-death",
  RegenerationRate = 1,
  Type = "land",
  RightMouseAction = "attack",
--  CanCastSpell = {"d-s"},
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-hydralisk-selected",
    "acknowledge", "zerg-hydralisk-acknowledgement",
    "ready", "zerg-hydralisk-ready",
    "help", "basic human voices help 1",
	"dead", "zerg-hydralisk-death"} } )
--[[
DefineButton( { Pos = 9, Level = 0, Icon = "icon-cancel",
  Action = "cast-spell", Value = "d-s",
  Key = "d", Hint = "Dark Swarm",
  ForUnit = {"unit-zerg-defiler"} } )
--]]