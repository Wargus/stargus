--
-- unit-protoss-dragoon
--

DefineAnimations("animations-protoss-dragoon-death", {
  Death = {"unbreakable begin", "frame 0", "wait 50", "frame 1", "wait 50",
    "frame 2", "wait 50", "frame 3", "wait 50", "frame 4", "wait 50", "unbreakable end", "wait 1", },
})

DefineUnitType("unit-protoss-dragoon-death", { Name = "Dead dragoon",
  Image = image_124_protoss_pdrdeath,
  Animations = "animations-terran-marine-death", Icon = "icon-terran-marine",
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Vanishes = true,
  Sounds = {} } )

DefineAnimations("animations-protoss-dragoon", {
   Still = {
    "frame 0", "wait 125",
  },
  Move = {
  "unbreakable begin",
    "move 4", "wait 1", "frame 136",
    "move 4", "wait 1", "frame 153",
    "move 4", "wait 1", "frame 170",
    "move 4", "wait 1", "frame 187",
    "move 4", "wait 1", "frame 204",
    "move 4", "wait 1", "frame 221",
    "move 4", "wait 1", "frame 238", 
	"move 4", "wait 1", "frame 255", 
    "unbreakable end", "wait 1",
  },
  Attack = {
    "unbreakable begin", "frame 272", "wait 2", "frame 289", "wait 2", "frame 306", "wait 2", "frame 323",
    "wait 2", "frame 340", "wait 2", "frame 357", "attack",
    "unbreakable end", "wait 2",
  },
  Death = {
    "unbreakable begin",
    "frame 408", "wait 1", "frame 409", "wait 1", "frame 410", "wait 1", "frame 411", "wait 1", "frame 412",
    "wait 1", "frame 413", "wait 1", "frame 414",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-protoss-dragoon", {
  Animations = "animations-protoss-dragoon", Icon = "icon-protoss-dragoon",
  Speed = 10,
  ShieldPoints = 200,
  DrawLevel = 40,
  Armor = 2, BasicDamage = 10, PiercingDamage = 3, Missile = "missile-none",
  MaxAttackRange = 2,
  Priority = 60,
  Points = 50,
  Demand = 2,
  RightMouseAction = "attack",
  Corpse = "unit-protoss-dragoon-death",
  CanAttack = true,
  CanTargetLand = true, CanTargetAir = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "protoss-dragoon-selected",
    "acknowledge", "protoss-dragoon-acknowledge",
    "ready", "protoss-dragoon-ready",
    "help", "protoss-units-attacked",} } )

