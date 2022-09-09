--
-- unit-zerg-extractor
--


DefineAnimations("animations-zerg-extractor", {
  --[[ active overlay 109 ]]
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 2", "frame 3", "wait 2",
    "frame 2", "wait 2", "frame 1", "wait 2", "frame 0", "wait 2",
    "frame 1", "wait 2", "frame 2", "wait 2", "frame 3", "wait 2",
    "frame 2", "wait 2", "frame 1", "wait 2", "frame 0", "wait 2",
  },
})


DefineUnitType("unit-zerg-extractor", {
  Animations = "animations-zerg-extractor", Icon = "icon-zerg-extractor",
  Costs = {"time", 200, "minerals", 50},
  Construction = "construction-zerg",
  Speed = 0,
  DrawLevel = 30,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 20,
  Points = 160,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-explosion",
  BuilderLost = true,
  VisibleUnderFog = true, 
  BuildingRules = { { "ontop", { Type = "unit-resource-vespene-geyser", ReplaceOnDie = true, ReplaceOnBuild = true} } },
  GivesResource = "gas", CanHarvest = true,
  Sounds = {
    "selected", "zerg-extractor-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
