--
-- unit-zerg-defiler
--


--[[
DefineAnimations("animations-zerg-hydralisk-death", {
  Death = {"unbreakable begin", "frame 0", "wait 40", "frame 1", "wait 40",
    "frame 2", "wait 40", "frame 3", "wait 40", "frame 4", "unbreakable end", "wait 1", },
})

DefineUnitType("unit-zerg-hydralisk-death", { Name = "DEAD HYDRLAISK",
  Image = {"file", "zerg/units/hydralisk death.png", "size", {128, 128}},
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
  },
  Move = {},
--FIXME:do this
  Death = {
  },
})

DefineUnitType("unit-zerg-defiler", { Name = "Hydralisk",
  Image = {"file", "zerg/units/defiler.png", "size", {80, 80}},
  Shadow = {"file", "zerg/units/defiler.png", "size", {80, 80}, "offset", {0, 7}},
  Animations = "animations-zerg-defiler", Icon = "icon-zerg-defiler",
  Costs = {"time", 50, "minerals", 50, "gas", 150,},
  Speed = 10, NumDirections = 32,
  HitPoints = 80,
  Mana = 200,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},--FIXME:wrong boxsize
  SightRange = 10, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 1, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
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
    "help", "zerg-units-attacked",
	"dead", "zerg-hydralisk-death"} } )
--[[
DefineButton( { Pos = 9, Level = 0, Icon = "icon-cancel",
  Action = "cast-spell", Value = "d-s",
  Key = "d", Hint = "Dark Swarm",
  ForUnit = {"unit-zerg-defiler"} } )
--]]
