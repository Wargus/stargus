--
-- unit-zerg-overlord
--


DefineAnimations("animations-zerg-overlord-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 2", --[[ active overlay 58 ]]
    "wait 1", "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-overlord-death", {
  Image = {"file", "zerg/units/overlord death.png", "size", {72, 72}},
  Animations = "animations-zerg-overlord-death", Icon = "icon-zerg-overlord",
  NumDirections = 1,
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Vanishes = true,
  Sounds = {} } )


DefineAnimations("animations-zerg-overlord", {
  Still = {
    "frame 0", "wait 125",
  },
  Move = {
    "frame 0", "wait 2", "frame 17", "wait 2",
    "label 42D8", "unbreakable begin",
    "frame 34", "move 2", "wait 2", "frame 51", "move 2", "wait 2",
    "frame 34", "move 2", "wait 2", "frame 51", "move 2", "wait 2",
    "frame 34", "move 2", "wait 2", "frame 51", "move 2", "wait 2",
    "frame 34", "move 2", "wait 2", "frame 51", "move 2", "wait 2",
    "frame 34", "move 2", "wait 2", "frame 51", "move 2", "wait 2",
    "frame 34", "move 2", "wait 2", "frame 51", "move 2", "wait 2",
    "frame 34", "move 2", "wait 2", "frame 51", "move 2", "wait 2",
    "frame 34", "move 2", "wait 2", "frame 51", "move 2", "wait 2",
    "unbreakable end", "wait 1", "goto 42D8",
  },
  Death = {
    "sound zerg-overlord-death", "wait 1",
  },
})


DefineUnitType("unit-zerg-overlord", { Name = "Overlord",
  Shadow = {"file", "zerg/units/overlord.png", "size", {84, 84}, "offset", {0, 42}},
  Animations = "animations-zerg-overlord", Icon = "icon-zerg-overlord",
  Costs = {"time", 45, "minerals", 100},
  RepairHp = 4,
  Speed = 0, NumDirections = 32,
  DrawLevel = 45,
  TileSize = {1, 1}, BoxSize = {63, 63},
  SightRange = 10,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 9,
  DetectCloak = true,
  CanTransport = {},
  MaxOnBoard = 6,
  Corpse = "unit-zerg-overlord-death",
  SelectableByRectangle = true,
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "fly", ShadowFly = {Value = 1, Enable = true},
  Sounds = {
    "selected", "zerg-overlord-selected",
    "acknowledge", "zerg-overlord-acknowledgement",
    "ready", "zerg-overlord-ready",
    "help", "zerg-units-attacked",
    "dead", "zerg-overlord-death"} } )
