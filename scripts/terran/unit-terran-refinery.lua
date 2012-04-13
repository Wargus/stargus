--
-- unit-terran-refinery
--

DefineAnimations("animations-terran-refinery", {
  Still = {
    "frame 0", "wait 5", "label 691B", --[[0x38 0x00]]
    "wait 20", "random-wait 5 100", "goto 691B",
  }
})

DefineConstruction("construction-terran-refinery", {
  Constructions = {
   {Percent = 0,
    File = "main",
    Frame = 1},
   {Percent = 20,
    File = "main",
    Frame = 2},
   {Percent = 40,
    File = "main",
    Frame = 3},
   {Percent = 60,
    File = "main",
    Frame = 4}}
})

DefineUnitType("unit-terran-refinery", { Name = "Refinery",
  Image = {"file", "terran/units/refinery.png", "size", {192, 192}},
  Shadow = {"file", "terran/units/refinery shadow.png", "size", {192, 192}},
  Animations = "animations-terran-refinery", Icon = "icon-terran-refinery",
  Costs = {"time", 200, "minerals", 100},
  Construction = "construction-terran-refinery",
  Speed = 0,
  BurnPercent = 30,
  BurnDamageRate = 1,
  HitPoints = 500,
  DrawLevel = 50,
  TileSize = {4, 2}, BoxSize = {127, 63},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 20,
  Points = 160,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-explosion",
  Type = "land",
  Building = true, VisibleUnderFog = true,
  BuildingRules = { { "ontop", { Type = "unit-vespene-geyser", ReplaceOnDie = true, ReplaceOnBuild = true} } },
  GivesResource = "gas", CanHarvest = true,
  Sounds = {
    "selected", "terran-refinery-selected",
    "ready", "terran-scv-done",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

