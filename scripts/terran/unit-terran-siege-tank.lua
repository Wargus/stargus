--
-- unit-terran-siege-tank
--

DefineAnimations("animations-terran-siege-tank", {
  Still = {
    "frame 0", "wait 125",
  },
  Move = {
    "unbreakable begin", "move 4", "wait 1", "frame 0", "move 4", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 17", "move 4", "wait 1", "frame 34", "move 4", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 0", "move 4", "wait 1", "frame 17", "move 4", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 34", "move 4", "wait 1", "frame 0", "move 4", "unbreakable end", "wait 1", "frame 17",
  },
  Attack = {
    "unbreakable begin", "sound terran-siege-tank-attack", "attack",
    "unbreakable end", "wait 1",
  },
  Death = {
    "unbreakable begin",
    --[[sound 317]] --[[active overlay 333,0]] "wait 3",
    "unbreakable end", "wait 1",
  },
})

DefineUnitType("unit-terran-siege-tank-tank-mode", {
  Animations = "animations-terran-siege-tank", Icon = "icon-terran-siege-tank",
  Costs = {"time", 60, "minerals", 150, "gas", 100},
  Speed = 10,
  DrawLevel = 40,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-none",
  AnnoyComputerFactor = 55,
  MaxAttackRange = 1,
  Priority = 60,
  Points = 50,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-medium",
  Type = "land",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  LandUnit = true,
  organic = true,
  SelectableByRectangle = true,
  OnReady = function(self)
    local turret = CreateUnit("unit-terran-siege-tank-turret", GetUnitVariable(self, "Player"), {GetUnitVariable(self, "PosX") + 4, GetUnitVariable(self, "PosY") + 4})
    SetUnitVariable(turret, "Summoned", self)
    SetUnitVariable(self, "Summoned", turret)
  end,
  OnDeath = function(self)
    local turret = GetUnitVariable(self, "Summoned", turret)
    RemoveUnit(turret)
  end,
  Sounds = {
    "selected", "terran-siege-tank-selected",
    "acknowledge", "terran-siege-tank-acknowledge",
    "ready", "terran-siege-tank-ready",
    "help", "terran-units-attacked",
    "dead", "terran-siege-tank-death"} } )

DefineAnimations("animations-terran-siege-tank-turret", {
  Still = {
    "frame 0", "random-rotate 1", "wait 8",
  },
})

DefineUnitType("unit-terran-siege-tank-turret", {
  Image = {"file", "graphics/unit/terran/stankt.png", "size", {128, 128}},
  TileSize = {1, 1},
  Animations = "animations-terran-siege-tank-turret",
  DrawLevel = 50,
  SightRange = 0,
  Indestructible = 1,
  Flip = false,
  NumDirections = 32,
  IsNotSelectable = true,
  NonSolid = true,
  ComputerReactionRange = 0,
  PersonReactionRange = 0,
  AnnoyComputerFactor = -100,
  AiAdjacentRange = 0,
  Revealer = false,
  Decoration = true,
  OnEachCycle = function(self)
    local owner = GetUnitVariable(self, "Summoned")
    -- local pixelPos = GetUnitVariable(owner, "PixelPos")
    MoveUnit(self, {GetUnitVariable(owner, "PosX") + 1, GetUnitVariable(owner, "PosY")})
  end,
})
