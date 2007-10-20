--
-- unit-zerg-extractor
--


DefineAnimations("animations-zerg-extractor", {
  Still = {
    "frame 0", "wait 5", "frame 1", "wait 5", "frame 2", "wait 5", "frame 3", "wait 5",
  },--FIXME:not original sc animations
})


DefineUnitType("unit-zerg-extractor", { Name = "Extractor",
  Image = {"file", "zerg/units/extractor.png", "size", {128, 192}},
  Shadow = {"file", "zerg/units/extractor shadow.png", "size", {128, 192}},
  Animations = "animations-zerg-extractor", Icon = "icon-zerg-extractor",
  Costs = {"time", 200, "minerals", 500},
  Construction = "construction-zerg",
  Speed = 0,
  HitPoints = 500,
  DrawLevel = 30,
  TileSize = {4, 2}, BoxSize = {127, 63},--FIXME:wrong boxsize
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 20,
  Points = 160,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-explosion",
  Type = "land",
  BuilderLost = true,
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "ontop", { Type = "unit-vespene-geyser", ReplaceOnDie = true, ReplaceOnBuild = true} } },
  GivesResource = "gas", CanHarvest = true,
  Sounds = {
    "selected", "zerg-extractor-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
