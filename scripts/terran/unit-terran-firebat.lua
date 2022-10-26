--
-- unit-terran-firebat
--


DefineAnimations("animations-terran-firebat", {
  Still = {
    "label 6D07", "frame 34",
    "label 6D0A", "random-wait 63 75", "random-goto 10 6D2E",
      "random-goto 50 6D18", "goto 6D0A",
    "label 6D18", "frame 51", "wait 1", "frame 68", "wait 1",
      "random-rotate 3", "wait 1", "frame 51", "wait 1", "goto 6D07",
    "label 6D2E", "frame 0", "wait 1", "random-goto 75 6D72",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "rotate -2", "wait 3",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "wait 6",
      "rotate 2", "wait 3", "rotate 2", "wait 3", "rotate 2", "wait 3",
      "rotate 2", "wait 3", "rotate 2", "wait 3", "wait 6",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "rotate -2", "wait 3",
      "goto 6D07",
    "label 6D72", "wait 13", "goto 6D07",
  },
  Move = {"unbreakable begin",
    "move 4", "wait 1", "frame 51", "move 4", "wait 1", "frame 68",
    "move 4", "wait 1", "frame 85", "move 4", "wait 1", "frame 102",
    "move 4", "wait 1", "frame 119", "move 4", "wait 1", "frame 136",
    "move 4", "wait 1", "frame 153", "move 4", "unbreakable end",
    "wait 1", "frame 34",},
--  StartAttack = {"frame 0",},
  Attack = {
    "frame 0", "wait 1", "unbreakable begin", --[[active overlay 421,0]] "attack", "sound terran-firebat-attack",
    "wait 2", --[["attack",]] "wait 1", --[["attack",]] "wait 8", "frame 0", "wait 2",
    "unbreakable end", "wait 22",
  },
  Death = {
    "unbreakable begin",
    "sound terran-firebat-death", --[[active overlay 332,0]] "wait 3",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-terran-firebat", {
  Animations = "animations-terran-firebat", Icon = "icon-terran-firebat",
  Speed = 10,
  DrawLevel = 40,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-terran-firebat-flame",
  AnnoyComputerFactor = 50,
  MaxAttackRange = 1,
  Priority = 60,
  Points = 50,
  Demand = 1,
  ExplodeWhenKilled = "missile-terran-explosion-small",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-firebat-selected",
    "acknowledge", "terran-firebat-acknowledge",
    "ready", "terran-firebat-ready",
    "help", "terran-units-attacked",} } )

