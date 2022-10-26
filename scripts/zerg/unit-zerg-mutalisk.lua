--
-- unit-zerg-mutalisk
--


DefineAnimations("animations-zerg-mutalisk", {
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
  Attack = {"unbreakable begin", "attack", "sound zerg-mutalisk-attack",
    "unbreakable end", "wait 40",},
  Death = {"unbreakable begin", "sound zerg-mutalisk-death",
    --[[active overlay 41,0]] "wait 1", "unbreakable end", "wait 1",},
})


DefineUnitType("unit-zerg-mutalisk", {
  DrawLevel = 45,
  Animations = "animations-zerg-mutalisk", Icon = "icon-zerg-mutalisk",
  Speed = 14,
  DrawLevel = 60,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-zerg-mutalisk-glaive-wurm",
  AnnoyComputerFactor = 55,
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-small",--FIXME:wrong explosion
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true, CanTargetAir = true,
  DetectCloak = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-mutalisk-selected",
    "acknowledge", "zerg-mutalisk-acknowledgement",
    "ready", "zerg-mutalisk-ready",
    "help", "zerg-units-attacked",
    "dead", "zerg-mutalisk-death"} } )

DefineUnitType("unit-zerg-guardian", {})


DefineButton( { Pos = 7, Level = 0, Icon = "icon-zerg-guardian",
  Action = "upgrade-to", Value = "unit-zerg-guardian",
  Key = "h", Hint = "Morph into Guardian",
  ForUnit = {"unit-zerg-guardian"} } )

