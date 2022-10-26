--
-- unit-zerg-zergling
--


DefineAnimations("animations-zerg-zergling-death", {
  Death = {
    "unbreakable begin",
    "frame 0", "wait 50", "frame 1", "wait 50", "frame 2", "wait 50",
    "frame 3", "wait 50", "frame 4", "wait 50",
    "unbreakable end", "wait 1",
  },
})


DefineUnitType("unit-zerg-zergling-death", { Name = "Dead Zergling",
  Image = image_57_zerg_zzedeath,
  Animations = "animations-zerg-zergling-death", Icon = "icon-zerg-zergling",
  NumDirections = image_57_zerg_zzedeath_NumDirections,
  HitPoints = 255,
  DrawLevel = 30,
  TileSize = {1, 1}, BoxSize = {31, 31},
  SightRange = 1,
  BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 0,
  Type = "land",
  Vanishes = true,
  Sounds = {} } )


DefineAnimations("animations-zerg-zergling", {
  Still = {
    "frame 85", "wait 125",
  },
  Move = {
    "label jumpoff", "unbreakable begin",
    "frame 102", "move 1", "wait 2", "frame 119", "move 7",
    "unbreakable end", "wait 1", "goto fly",

    "label runningstart", "unbreakable begin",
    "if-var R >= 40 jumpoff", -- 180 turn, accellerate from slow
    "if-var R <= -40 jumpoff", -- 180 turn, accellerate from slow
    "frame 102", "move 1", "wait 1", "frame 119", "move 7",
    "unbreakable end", "wait 1",

    "label fly", "unbreakable begin",
    "if-var R >= 40 jumpoff", -- 180 turn, accellerate from slow
    "if-var R <= -40 jumpoff", -- 180 turn, accellerate from slow
    "frame 136", "move 8",
    "unbreakable end", "wait 1",

    "label land", "unbreakable begin",
    "if-var R >= 40 jumpoff", -- 180 turn, accellerate from slow
    "if-var R <= -40 jumpoff", -- 180 turn, accellerate from slow
    "frame 153", "move 4", "wait 1", "frame 170", "move 4",
    "unbreakable end", "wait 1",

    "wait crash", "unbreakable begin",
    "if-var R >= 40 jumpoff", -- 180 turn, accellerate from slow
    "if-var R <= -40 jumpoff", -- 180 turn, accellerate from slow
    "frame 187", "move 6", "wait 1", "frame 187", "move 2",
    "unbreakable end", "wait 1",

    "goto runningstart",
  },
  Attack = {
    "frame 0", "wait 1",
    "unbreakable begin", "frame 17", "wait 1", "frame 34",
    "sound zerg-zergling-attack", "attack", "wait 1",
    "frame 51", "wait 1", "frame 68", "wait 1",
    "unbreakable end",
  },
  Death = {
    "unbreakable begin",
    "sound zerg-zergling-death", "exact-frame 289", "wait 2",
    "exact-frame 290", "wait 2", "exact-frame 291", "wait 2",
    "exact-frame 292", "wait 2", "exact-frame 293", "wait 2",
    "exact-frame 294", "wait 2", "exact-frame 295", "wait 2",
    "unbreakable end", "wait 1",
  },
--[[ Burrow = frame 204,221,238,255,272 ]]
})


DefineUnitType("unit-zerg-zergling", {
  Animations = "animations-zerg-zergling", Icon = "icon-zerg-zergling",
  Speed = 10,
  RotationSpeed = 40,
  DrawLevel = 40,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-none",
  AnnoyComputerFactor = 50,
  MaxAttackRange = 1,
  Priority = 60,
  Points = 50,
  Demand = 1,
  Corpse = "unit-zerg-zergling-death",
  RegenerationRate = 1,
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  SelectableByRectangle = true,
  Sounds = {
    "selected", "zerg-zergling-selected",
    "acknowledge", "zerg-zergling-acknowledgement",
    "ready", "zerg-zergling-ready",
    "help", "zerg-units-attacked",
	"dead", "zerg-zergling-death",} } )

