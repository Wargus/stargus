--
-- unit-terran-siege-tank
--

function moveTurret(self)
  local turret = GetUnitVariable(self, "Summoned")
  local pixelPos = GetUnitVariable(self, "PixelPos")
  local ix = math.fmod(pixelPos.x, 8)
  local iy = math.fmod(pixelPos.y, 8)
  local x = math.floor(pixelPos.x / 8) - 2
  local y = math.floor(pixelPos.y / 8) - 3
  MoveUnit(turret, {x, y}, {ix, iy})
end

function turnTurret(self, goal, y)
  local turret = GetUnitVariable(self, "Summoned")
  if y then
    TurnTowardsLocation(turret, {goal, y})
  else
    TurnTowardsLocation(turret, goal)
  end
end

DefineAnimations("animations-terran-siege-tank", {
  Still = {
    "label still", "frame 0", "wait 125",
    "random-goto 25 turn",
    "goto still",
    "label turn", "lua-callback turnTurret U r.64 r.64",
  },
  Move = {
    "unbreakable begin", "move 4", "lua-callback moveTurret U", "wait 1", "frame 0", "move 4", "lua-callback moveTurret U", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 17", "move 4", "lua-callback moveTurret U", "wait 1", "frame 34", "move 4", "lua-callback moveTurret U", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 0", "move 4", "lua-callback moveTurret U", "wait 1", "frame 17", "move 4", "lua-callback moveTurret U", "unbreakable end", "wait 1",
    "unbreakable begin", "frame 34", "move 4", "lua-callback moveTurret U", "wait 1", "frame 0", "move 4", "lua-callback moveTurret U", "unbreakable end", "wait 1", "frame 17",
  },
  Attack = {
    "label shoot",
    "unbreakable begin",
      "lua-callback turnTurret U G", "wait 3",
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
  Speed = 10,
  RotationSpeed = 4,
  DrawLevel = 40,
  Armor = 2, BasicDamage = 6, PiercingDamage = 3, Missile = "missile-none",
  AnnoyComputerFactor = 55,
  MaxAttackRange = 1,
  Priority = 60,
  Points = 50,
  MinAttackRange = 8, MaxAttackRange = 48,
  Demand = 2,
  ExplodeWhenKilled = "missile-terran-explosion-medium",
  RightMouseAction = "attack",
  CanAttack = true,
  CanTargetLand = true,
  SurroundAttack = true,
  SelectableByRectangle = true,
  OnInit = function(self)
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
  RotationSpeed = 8,
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
