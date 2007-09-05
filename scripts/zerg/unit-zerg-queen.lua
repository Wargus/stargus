

DefineAnimations("animations-zerg-queen", {
  Still = {"frame 0", "wait 125",--[[FIXME: shift down 79A2]]},
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "attack", "sound terran-wraith-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound zerg-mutalisk-death",
    --[[active overlay 332,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-zerg-queen", { Name = "Queen",
  Image = {"file", "zerg/units/queen.png", "size", {128, 128}},
  Shadow = {"file", "zerg/units/queen.png", "size", {128, 128}},
  Animations = "animations-zerg-queen", Icon = "icon-zerg-queen",
  Costs = {"time", 100, "minerals", 100, "gas", 100,},
  RepairHp = 1,
  Speed = 4, NumDirections = 32,
  HitPoints = 120,
  DrawLevel = 45,
  TileSize = {1, 1}, BoxSize = {50, 50},
  SightRange = 3,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 200,
  ExplodeWhenKilled = "missile-terran-explosion-large",
  RegenerationRate = 1,
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  Sounds = {
    "selected", "zerg-queen-selected",
    "acknowledge", "zerg-queen-acknowledgement",
    "ready", "zerg-queen-ready",
    "help", "basic human voices help 1",
	"dead", "zerg-queen-death"} } )
