--
-- unit-zerg-spore-colony
--


DefineAnimations("animations-zerg-spore-colony", {
  Still = {
    "frame 0", "wait 2", "frame 1", "wait 2", "frame 2", "wait 2",
    "frame 3", "wait 2",
  },
  Attack = {
    "unbreakable begin", "sound zerg-spore-colony-attack", 
    "frame 0", "wait 1", "attack",
    "unbreakable end", "wait 1",
  },  
})


DefineUnitType("unit-zerg-spore-colony", {
  Animations = "animations-zerg-spore-colony", Icon = "icon-zerg-spore-colony",
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Construction = "construction-zerg",
  Speed = 0,
  DrawLevel = 30,
  Armor = 20, BasicDamage = 15, PiercingDamage = 5, Missile = "missile-none",
  MaxAttackRange = 7,
  Priority = 15, AnnoyComputerFactor = 20,
  Points = 170,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  RightMouseAction = "attack",
  BuilderLost = true,
  RegenerationRate = 1,
  CanAttack = true,
  CanTargetAir = true,
  VisibleUnderFog = true,
  Sounds = {
    "selected", "zerg-spore-colony-selected",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )
