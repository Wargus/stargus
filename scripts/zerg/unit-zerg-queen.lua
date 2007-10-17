--
-- unit-zerg-queen
--


DefineAnimations("animations-zerg-queen", {
  Still = {},
  Move = {},--FIXME: Do this
  Attack = {},
  Death = {},
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
  TileSize = {1, 1}, BoxSize = {50, 50},--FIXME: wrong box size
  SightRange = 7,
  Demand = 2,
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
    "help", "zerg-units-attacked",
	"dead", "zerg-queen-death"} } )
