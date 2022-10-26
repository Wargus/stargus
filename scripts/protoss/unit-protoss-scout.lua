--
-- unit-protoss-scout
--

DefineAnimations("animations-protoss-scout", {
  Still = {"frame 0", "wait 125",--[[FIXME: shift down 79A2]]},
  Move = {"unbreakable begin", "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 3", "wait 1",
    "frame 0", "move 3", "wait 2", "frame 0", "move 2", "wait 1",
    "frame 0", "move 3", "wait 1", "frame 0", "move 2", "unbreakable end", "wait 1",},
  Attack = {"unbreakable begin", "attack", "sound protoss-scout-attack",
    "unbreakable end", "wait 1",},
  Death = {"unbreakable begin", "sound protoss-scout-death",
    --[[active overlay 332,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-protoss-scout", {
  DrawLevel = 45,
  Animations = "animations-protoss-scout", Icon = "icon-protoss-scout",
  Speed = 14,
  DrawLevel = 60,
  Armor = 5, BasicDamage = 0, PiercingDamage = 16, Missile = "missile-none",
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
    "selected", "protoss-scout-selected",
    "acknowledge", "protoss-scout-acknowledge",
    "ready", "protoss-scout-ready",
    "help", "protoss-unit-attacked",
    "dead", "protoss-scout-death"} } )


