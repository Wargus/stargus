--
-- unit-terran-supply-depot
--

DefineAnimations("animations-zerg-overlord-depot", {
  Still = {
    "frame 0", "wait 4",
  },
  Move = {
    "frame 0", "wait 4", "frame 10", "wait 4", "frame 20", "wait 4", "frame 30"
}
})

DefineUnitType("unit-zerg-overlord", { Name = "Overlord",
  Image = {"file", "graphics/zerg/units/overlord.png", "size", {84, 84}},
  Shadow = {"file", "graphics/terran/units/overlord shadow.png", "size", {84, 84}},
  Animations = "animations-zerg-overlord", Icon = "icon-zerg-overlord",
  Costs = {"time", 100, "minerals", 100},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 1},
  Speed = 0,
  HitPoints = 500,
  DrawLevel = 50,
  TileSize = {3, 2}, BoxSize = {95, 63},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 20, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 8,
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  Sounds = {
    "selected", "zerg-overlord-selected",
--    "acknowledge", "farm-acknowledge",
--    "ready", "farm-ready",
    "help", "zerg-base-attacked",
    "dead", "explosion-large"} } )

