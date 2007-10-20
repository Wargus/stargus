--
-- unit-zerg-sunken-colony
--


DefineAnimations("animations-zerg-sunken-colony", {
  Still = {
    "frame 0", "wait 2", "frame 1", "wait 2", "frame 2", "wait 2",
  },
  Attack = {
    "unbreakable begin", "wait 5", "frame 4", "wait 3", "frame 5", "wait 3", "frame 6", "wait 3", "frame 7", "wait 3", "frame 8", "wait 3", "frame 9", "sound sunken-attack", "attack",
    "unbreakable end", "wait 5",
  },  
})


DefineUnitType("unit-zerg-sunken-colony", { Name = "Sunken Colony",
  Image = {"file", "zerg/units/sunken colony.png", "size",  {128, 128}},
  Shadow = {"file", "zerg/units/sunken colony shadow.png", "size",  {128, 128}},
  Animations = "animations-zerg-sunken-colony", Icon = "icon-zerg-sunken-colony",
  Costs = {"time", 200, "minerals", 75},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  HitPoints = 400,
  DrawLevel = 30,
  TileSize = {3, 2}, BoxSize = {95, 63},--FIXME: wrong box size
  SightRange = 7, ComputerReactionRange = 6, PersonReactionRange = 4,
  Armor = 20, BasicDamage = 20, PiercingDamage = 5, Missile = "missile-none",
  MaxAttackRange = 7,
  Priority = 15, AnnoyComputerFactor = 20,
  Points = 170,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  RightMouseAction = "attack",
  BuilderLost = true,
  RegenerationRate = 1,
  CanAttack = true,
  CanTargetLand = true,
  Building = true, VisibleUnderFog = true,
  Sounds = {
    "selected", "zerg-sunken-colony-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-buildin-blowup"} } )
