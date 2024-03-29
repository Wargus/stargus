--
-- unit-terran-wraith
--

DefineAnimations("animations-terran-wraith", {
  Still = {"frame 0", "wait 125",--[[FIXME: shift down 79A2]]},
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "attack", "sound terran-wraith-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound terran-wraith-death",
    --[[active overlay 332,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-terran-wraith", {
DrawLevel = 45,
  Animations = "animations-terran-wraith", Icon = "icon-terran-wraith",
  Speed = 14,
  DrawLevel = 60,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-terran-wraith-laser",
  AnnoyComputerFactor = 55,
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-small",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true, CanTargetAir = true,
  DetectCloak = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-wraith-selected",
    "acknowledge", "terran-wraith-acknowledge",
    "ready", "terran-wraith-ready",
    "help", "terran-units-attacked",
    "dead", "terran-wraith-death"} } )

