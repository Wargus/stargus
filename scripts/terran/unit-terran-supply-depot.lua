--
-- unit-terran-supply-depot
--

DefineAnimations("animations-terran-supply-depot", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-supply-depot", {
  Files = {
    File = "terran/units/building construction medium.png",
    Size = {96, 96}},
  ShadowFiles = {
    File = "terran/units/building construction medium shadow.png",
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

DefineUnitType("unit-terran-supply-depot", { Name = "Supply Depot",
  Image = {"file", "graphics/terran/units/supply depot.png", "size", {96, 128}},
  Shadow = {"file", "graphics/terran/units/supply depot shadow.png", "size", {96, 128}},
  Animations = "animations-terran-supply-depot", Icon = "icon-terran-supply-depot",
  Costs = {"time", 100, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-terran-supply-depot",
  Speed = 0,
  HitPoints = 500,
  DrawLevel = 50,
  TileSize = {3, 2}, BoxSize = {95, 63},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 100,
  Supply = 8,
  Corpse = "unit-destroyed-2x2-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  Sounds = {
    "selected", "terran-supply-depot-selected",
--    "acknowledge", "farm-acknowledge",
   "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

