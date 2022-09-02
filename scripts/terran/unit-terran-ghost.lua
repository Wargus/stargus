--
-- unit-terran-ghost
--


DefineAnimations("animations-terran-ghost", {
  Still = {
    "label 6E17", "frame 51",
    "label 6E1A", "random-wait 63 75", "random-goto 10 6E3E",
      "random-goto 50 6E28", "goto 6E1A",
    "label 6E28", "frame 68", "wait 1", "frame 85", "wait 1",
      "random-rotate 3", "wait 1", "frame 68", "wait 1", "goto 6E17",
    "label 6E3E", "frame 0", "wait 1", "frame 17", "wait 1", "frame 34",
      "random-goto 75 6E8A",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "rotate -2", "wait 3",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "wait 6",
      "rotate 2", "wait 3", "rotate 2", "wait 3", "rotate 2", "wait 3",
      "rotate 2", "wait 3", "rotate 2", "wait 3", "wait 6",
      "rotate -2", "wait 3", "rotate -2", "wait 3", "rotate -2", "wait 3",
      "goto 6E8C",
    "label 6E8A", "wait 13",
    "label 6E8C", "frame 17", "wait 1", "frame 0", "wait 1", "goto 6E17",
  },
  Move = {"unbreakable begin",
    "move 4", "wait 1", "frame 68", "move 4", "wait 1", "frame 85",
    "move 4", "wait 1", "frame 102", "move 4", "wait 1", "frame 119",
    "move 4", "wait 1", "frame 136", "move 4", "wait 1", "frame 153",
    "move 4", "wait 1", "frame 170",
    --FIXME: subtile movement not supported
    --[["move 4", "wait 1", "frame 187",]]
    "move 4", "unbreakable end", "wait 1", "frame 51",
  },
--  StartAttack = {"frame 0", "wait 1", "frame 17", "wait 1", "frame 34",},
  Attack = {
    "wait 1", "unbreakable begin", "sound terran-ghost-attack", "attack",
    "frame 204", "wait 1", "frame 34", "unbreakable end",
  },
--  EndAttack = {"frame 17", "wait 1", "frame 0", "wait 1", --[[goto 6E17]]},
  Death = {
    "unbreakable begin",
    "sound terran-ghost-death", "exact-frame 221", "wait 2",
    "exact-frame 222", "wait 2", "exact-frame 223", "wait 2",
    "exact-frame 224", "wait 2", "exact-frame 225", "wait 2",
    "exact-frame 226", "wait 2", "exact-frame 227", "wait 2",
    "exact-frame 228", "wait 2", "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-terran-ghost", {
  Animations = "animations-terran-ghost", Icon = "icon-terran-ghost",
  Costs = {"time", 60, "minerals", 25, "gas", 75},
  Speed = 10,
  DrawLevel = 40,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-none",
  MaxAttackRange = 1,
  Priority = 60,
  Points = 50,
  Demand = 1,
--  Corpse = "unit-dead-body",
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-ghost-selected",
    "acknowledge", "terran-ghost-acknowledge",
    "ready", "terran-ghost-ready",
    "help", "terran-units-attacked",} } )

