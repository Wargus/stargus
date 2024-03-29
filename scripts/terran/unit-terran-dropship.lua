--
-- unit-terran-dropship
--

DefineAnimations("animations-terran-dropship", {
  Still = {"frame 0", "wait 125",--[[FIXME: shift down 79A2]]},
  Move = {
    "unbreakable begin", -- accellerate
      "frame 0", "move 1", "wait 1", "frame 0", "move 2", "wait 1",
      "frame 0", "move 3", "wait 1", "frame 0", "move 2",
    "unbreakable end", "wait 1",
    "label fullspeed", "unbreakable begin", "frame 0", "move 3", "wait 1", "frame 0", "move 2", "wait 1", "frame 0", "move 3", "unbreakable end", "wait 1",
    "goto fullspeed",},
  Death = {"unbreakable begin", "sound terran-dropship-death",
    --[[active overlay 332,0]] "wait 3", "unbreakable end", "wait 1",},
})

DefineUnitType("unit-terran-dropship", {
  DrawLevel = 45,
  Animations = "animations-terran-dropship", Icon = "icon-terran-dropship",
  Speed = 14,
  DrawLevel = 60,
  MaxOnBoard = 8,
  -- PersonalSpace = {7, 7}, TileSize = {2, 2}
  Armor = 5, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  MaxAttackRange = 4,
  Priority = 65,
  Points = 150,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-small",
  RightMouseAction = "move",
  CanAttack = false,
  CanTransport = {},
  DetectCloak = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "terran-dropship-selected",
    "acknowledge", "terran-dropship-acknowledge",
    "ready", "terran-dropship-ready",
    "help", "terran-units-attacked",
    "dead", "terran-dropship-death"} } )

