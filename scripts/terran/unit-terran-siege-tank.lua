--
-- unit-terran-siege-tank
--

function moveTurret(self)
  local turret = GetUnitVariable(self, "Summoned")
  local pixelPos = GetUnitVariable(self, "PixelPos")
  local ix = math.fmod(pixelPos.x, 8)
  local iy = math.fmod(pixelPos.y, 8)
  local x = math.floor(pixelPos.x / 8) - 1
  local y = math.floor(pixelPos.y / 8) - 1
  MoveUnit(turret, {x, y}, {ix - 8, iy - 16})
end

function turnTurret(self, goal, off)
  local turret = GetUnitVariable(self, "Summoned")
  if off == 0 then
    TurnTowardsLocation(turret, goal)
  else
    x = GetUnitVariable(goal, "PosX")
    y = GetUnitVariable(goal, "PosY")
    TurnTowardsLocation(turret, {x + off, y + off})
  end
end

DefineAnimations("animations-terran-siege-tank", {
  Still = {
    "frame 0", "wait 125",
  },
  Move = {
    "unbreakable begin", "move 4", "lua-callback moveTurret U", "wait 1", "frame 0", "move 4", "lua-callback moveTurret U", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 17", "move 4", "lua-callback moveTurret U", "wait 1", "frame 34", "move 4", "lua-callback moveTurret U", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 0", "move 4", "lua-callback moveTurret U", "wait 1", "frame 17", "move 4", "lua-callback moveTurret U", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 34", "move 4", "lua-callback moveTurret U", "wait 1", "frame 0", "move 4", "lua-callback moveTurret U", "unbreakable end", "wait 1", "frame 17",
  },
  Attack = {
    "unbreakable begin",
      "lua-callback turnTurret U G 1",
      "wait 3",
      "lua-callback turnTurret U G 0",
      "wait 3",
      "lua-callback turnTurret U G -1",
      "wait 3",
    "unbreakable end",
    "label shoot",
    "unbreakable begin",
      "lua-callback turnTurret U G 0",
      "sound terran-siege-tank-attack", "attack", "wait 60",
    "unbreakable end", "wait 1",
    "goto shoot",
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
  SurroundAttack = true,
  organic = false,
  SelectableByRectangle = true,
  OnReady = function(self)
    local turret = CreateUnit("unit-terran-siege-tank-tank-mode-turret", GetUnitVariable(self, "Player"), {0, 0})
    SetUnitVariable(self, "Summoned", turret)
    moveTurret(self)
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
    "frame 0", "wait 125", -- "random-rotate 1", "wait 8",
  },
})

DefineUnitType("unit-terran-siege-tank-tank-mode-turret", {
  Animations = "animations-terran-siege-tank-turret",
  DrawLevel = 50,
  Indestructible = 1,
  Flip = false,
  IsNotSelectable = true,
  NonSolid = true,
  ComputerReactionRange = 0,
  PersonReactionRange = 0,
  AnnoyComputerFactor = -100,
  AiAdjacentRange = 0,
  Revealer = false,
  Decoration = true
})
