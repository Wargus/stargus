--
-- unit-zerg-queen
--


DefineAnimations("animations-zerg-queen", {
  Still = {
    "frame 0", "wait 2", "frame 17", "wait 2", "frame 34", "wait 2",
    "frame 51", "wait 2", "frame 68", "wait 2",
  },
  Move = {
    "unbreakable begin",
    "frame 0", "move 4", "wait 1", "frame 17", "move 3", "wait 1",
    "frame 34", "move 3", "wait 1", "frame 51", "move 3", "wait 1",
    "frame 68", "move 3", "wait 1", "frame 0", "move 4", "wait 1",
    "frame 17", "move 3", "wait 1", "frame 34", "move 3", "wait 1",
    "frame 51", "move 3", "wait 1", "frame 68", "move 3",
    "unbreakable end", "wait 1",
  },
  Attack = {
    "unbreakable begin",
    "frame 85", "wait 1", "frame 102", "wait 1", "frame 119", "wait 1",
    "frame 136", "sound zerg-queen-attack", "attack", "wait 1",
    "frame 153", "wait 1", "frame 170",
    "unbreakable end", "wait 1",
  },
  Death = {
    "frame 0", "wait 1",
  },
})


DefineUnitType("unit-zerg-queen", {
  Animations = "animations-zerg-queen", Icon = "icon-zerg-queen",
  RepairHp = 1,
  Speed = 4,
  DrawLevel = 45,
  Demand = 2,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 200,
  ExplodeWhenKilled = "missile-terran-explosion-large",
  RegenerationRate = 1,
  Sounds = {
    "selected", "zerg-queen-selected",
    "acknowledge", "zerg-queen-acknowledgement",
    "ready", "zerg-queen-ready",
    "help", "zerg-units-attacked",
    "dead", "zerg-queen-death"} } )
