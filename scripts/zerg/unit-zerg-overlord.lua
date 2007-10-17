--
-- unit-zerg-overlord
--


DefineAnimations("animations-zerg-overlord", {
  Still = {"frame 0", "wait 125",  --[[FIXME: shift down 79A2]]},
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 5", "move 3", "wait 1",
    "frame 10", "move 3", "wait 2", "frame 15", "move 2", "wait 1",
    "frame 20", "move 3", "wait 1", "frame 25", "move 2", "wait 1",--FIXME: not original sc animations
    "frame 30", "move 3", "wait 2", "frame 35", "move 3", "wait 1",
    "frame 40", "move 3", "wait 2", "frame 45", "move 2", "wait 1",
    "frame 50", "move 3", "wait 1", "frame 55", "move 2", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "attack", "sound terran-wraith-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound zerg-mutalisk-death",
    --[[active overlay 332,0]] "wait 3", "unbreakable end", "wait 1",},
})


DefineUnitType("unit-zerg-overlord", { Name = "Overlord",
  Image = {"file", "zerg/units/overlord.png", "size", {84, 84}},
  Shadow = {"file", "zerg/units/overlord.png", "size", {84, 84}},
  Animations = "animations-zerg-overlord", Icon = "icon-zerg-overlord",
  Costs = {"time", 45, "minerals", 100},
  RepairHp = 4,
  Speed = 0, NumDirections = 32,
  HitPoints = 500,
  DrawLevel = 45,
  TileSize = {1, 1}, BoxSize = {63, 63},--FIXME:wrong size
  SightRange = 10,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 9,
  DetectCloak = true,
  CanTransport = {},
  MaxOnBoard = 6,
  SelectableByRectangle = true,
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  Sounds = {
    "selected", "zerg-overlord-selected",
    "acknowledge", "zerg-overlord-acknowledgement",
    "ready", "zerg-overlord-ready",
    "help", "zerg-units-attacked",
	"dead", "zerg-overlord-death"} } )
