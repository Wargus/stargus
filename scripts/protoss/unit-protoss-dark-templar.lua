--
-- unit-protoss-dark-templar
--

DefineAnimations("animations-protoss-dark-templar", {
  Still = {
	"frame 85", "wait 125",
  },
  Move = {"unbreakable begin",
    "move 4", "wait 1", "frame 85", "move 4", "wait 1", "frame 102",
    "move 4", "wait 1", "frame 119", "move 4", "wait 1", "frame 136",
    "move 4", "wait 1", "frame 153", "move 4", "wait 1", "frame 170",
    "move 4", "wait 1", "frame 187",
    --FIXME: subtile movement not supported
    --[["move 4", "wait 1", "frame 204",]]
    "move 4", "unbreakable end", "wait 1", "frame 119",
  },
--  StartAttack = {"frame 0", "wait 1", "frame 17", "wait 1", "frame 34",},
  Attack = {
    "wait 1", "unbreakable begin", "attack", "sound protoss-zealot-attack",
    "frame 17", "wait 1", "frame 34", "wait 1", "frame 51", "wait 1",
    "frame 68", "sound protoss-zealot-hit", "wait 1", "frame 51", "wait 1", "frame 34", "sound protoss-zealot-hit",
    "unbreakable end", "wait 10", "frame 17",
  },
--  EndAttack = {"frame 17", "wait 1", "frame 0", "wait 1", --[[goto 70FD]]},
  Death = {
    "unbreakable begin",
    "sound protoss-zealot-death", "exact-frame 221", "wait 2",
    "exact-frame 222", "wait 2", "exact-frame 223", "wait 2",
    "exact-frame 239", "wait 2", "exact-frame 225", "wait 2",
    "exact-frame 226", "wait 2", "exact-frame 227", "wait 2",
    "exact-frame 228", "wait 2", "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-protoss-dark-templar", {
  Animations = "animations-protoss-dark-templar", Icon = "icon-protoss-dark-templar",
  Costs = {"time", 100, "minerals", 100},
  Speed = 10, NumDirections = 32,
  DrawLevel = 40,
  Armor = 4, BasicDamage = 10, PiercingDamage = 3, Missile = "missile-none",
  MaxAttackRange = 1,
  Priority = 60,
  Points = 50,
  Demand = 1,
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "protoss-dark-templar-selected",
    "acknowledge", "protoss-dark-templar-acknowledge",
    --FIXME NO READY SOUND!!
    "ready", "protoss-high-templar-ready",
    "help", "protoss-dark-templar-attacked",} } )
