--
-- unit-zerg-defiler
--


DefineAnimations("animations-zerg-defiler-death", {
  Death = {
    "unbreakable begin", "frame 0", "wait 50", "frame 1", "wait 50",
    "frame 2", "wait 50", "frame 3", "wait 50", "frame 4", "wait 50",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-zerg-defiler-death", {
  Animations = "animations-zerg-defiler-death", Icon = "icon-zerg-defiler",
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


DefineAnimations("animations-zerg-defiler", {
  Still = {
    "frame 0", "wait 3", "frame 17", "wait 3", "frame 34", "wait 3",
    "frame 17", "wait 3",
  },
  Move = {"unbreakable begin",
    "frame 0", "move 5", "wait 1", "frame 17", "move 4", "wait 1",
    "frame 51", "move 5", "wait 1", "frame 68", "move 4", "wait 1",
    "frame 85", "move 5", "wait 1", "frame 102", "move 4", "wait 1",
    "frame 119", "move 5", "wait 1",
    "unbreakable end", "wait 1",
  },
  Death = {"unbreakable begin",
    "frame 136", "wait 2", "frame 153", "wait 2", "frame 170", "wait 2",
    "frame 187", "wait 2",
    "unbreakable end", "wait 1",
  },
--[[ Burrow =
  "frame 204", "wait 1", "frame 221", "wait 1", "frame 238", "wait 1",
  "frame 255", "wait 1", "frame 272", "wait 1",
]]
})

DefineUnitType("unit-zerg-defiler", { Name = "Hydralisk",
  Animations = "animations-zerg-defiler", Icon = "icon-zerg-defiler",
  Costs = {"time", 50, "minerals", 50, "gas", 150,},
  Speed = 10, NumDirections = 32,
  Mana = 200,
  DrawLevel = 30,
  SightRange = 10, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 1, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  MaxAttackRange = 0,
  Priority = 60,
  Points = 50,
  Demand = 2,
  Corpse = "unit-zerg-defiler-death",
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
    "selected", "zerg-defiler-selected",
    "acknowledge", "zerg-defiler-acknowledgement",
    "ready", "zerg-defiler-ready",
    "help", "zerg-units-attacked",
	"dead", "zerg-defiler-death"} } )
--[[
DefineButton( { Pos = 9, Level = 0, Icon = "icon-cancel",
  Action = "cast-spell", Value = "d-s",
  Key = "d", Hint = "Dark Swarm",
  ForUnit = {"unit-zerg-defiler"} } )
--]]
