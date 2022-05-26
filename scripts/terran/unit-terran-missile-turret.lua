--
-- unit-terran-missile-turret
--

DefineAnimations("animations-terran-missile-turret", {
  Still = {
    "frame 2", "wait 125",
  },
  Attack = {--[[FIXME: active overlay 297]]
    "frame 2", "wait 125",
  },
})

DefineConstruction("construction-terran-missile-turret", {
  Files = {
    File = "terran/units/building construction small.png",
    Size = {96, 96}},
  ShadowFiles = {
    File = "terran/units/building construction small shadow.png",
    Size = {96, 96}},
  Constructions = {
   {Percent = 0,
    File = "construction",
    Frame = 0},
   {Percent = 20,
    File = "construction",
    Frame = 1},
   {Percent = 40,
    File = "construction",
    Frame = 2},
   {Percent = 60,
    File = "main",
    Frame = 1}}
})

DefineUnitType("unit-terran-missile-turret", {
  Shadow = {"file", "terran/units/missile turret shadow.png", "size", {128, 128}},
  Animations = "animations-terran-missile-turret", Icon = "icon-terran-missile-turret",
  Costs = {"time", 190, "minerals", 200},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-missile-turret",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  DrawLevel = 50,
  BuilderOutside = true,
  TileSize = {2, 2}, BoxSize = {63, 63},
  SightRange = 9, ComputerReactionRange = 7, PersonReactionRange = 7,
  Armor = 20, BasicDamage = 50, PiercingDamage = 0, Missile = "missile-small-cannon",
  MinAttackRange = 2, MaxAttackRange = 7,
  Priority = 40, AnnoyComputerFactor = 50,
  Points = 250,
  Corpse = "unit-destroyed-2x2-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  CanAttack = true,
  CanTargetLand = true, CanTargetSea = true,
  Building = true, VisibleUnderFog = true, 
  DetectCloak = true,
  Sounds = {
    "selected", "terran-missile-turret-selected",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

