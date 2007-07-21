--
-- unit-terran-refinery
--

DefineAnimations("animations-terran-refinery", {
  Still = {
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-refinery", {
--FIXME:animations
})

DefineUnitType("unit-zerg-extractor", { Name = "Extractor",
  Image = {"file", "zerg/units/extractor.png", "size", {128, 192}},
  Shadow = {"file", "zerg/units/extractor shadow.png", "size", {128, 192}},
  Animations = "animations-zerg-extractor", Icon = "icon-zerg-extractor",
  Costs = {"time", 200, "minerals", 500},
  Construction = "construction-zerg-extractor",
  Speed = 0,
  HitPoints = 500,
  DrawLevel = 50,
  TileSize = {4, 2}, BoxSize = {127, 63},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 20,
  Points = 160,
  Corpse = "unit-destroyed-3x3-place",--FIXME
  ExplodeWhenKilled = "missile-explosion",--FIXME
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "ontop", { Type = "unit-vespene-geyser", ReplaceOnDie = true, ReplaceOnBuild = true} } },
  GivesResource = "gas", CanHarvest = true,
  Sounds = {
    "selected", "zerg-extractor-selected",
--    "ready", "terran-refinery-ready",
    "help", "zerg-base-attacked",
    "dead", "explosion-large"} } )--FIXME
