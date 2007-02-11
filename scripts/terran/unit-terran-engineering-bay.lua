--
-- unit-terran-engineering-bay
--

DefineAnimations("animations-terran-engineering-bay", {
  Still = {
    "frame 0", "wait 125",
  },
  Research = {--[[FIXME: active overlay 276]]
    "frame 0", "wait 125",
  },
})

DefineConstruction("construction-terran-engineering-bay", {
  Files = {
    File = "terran/units/building construction large.png",
    Size = {160, 128}},
  ShadowFiles = {
    File = "terran/units/building construction large shadow.png",
    Size = {128, 128}},
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

DefineUnitType("unit-terran-engineering-bay", { Name = "Engineering Bay",
  Image = {"file", "terran/units/engineering bay.png", "size",  {192, 160}},
  Shadow = {"file", "terran/units/engineering bay shadow.png", "size",  {192, 160}},
  Animations = "animations-terran-engineering-bay", Icon = "icon-terran-engineering-bay",
  Costs = {"time", 200, "gold", 125},
  RepairHp = 4,
  RepairCosts = {"gold", 1, "wood", 1, "oil", 1},
  Construction = "construction-terran-engineering-bay",
  Speed = 0,
  HitPoints = 850,
  DrawLevel = 50,
  TileSize = {4, 3}, BoxSize = {127, 95},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 15, AnnoyComputerFactor = 20,
  Points = 170,
  Corpse = "unit-destroyed-3x3-place",
  ExplodeWhenKilled = "missile-terran-explosion-large",
  Type = "land",
  Building = true, VisibleUnderFog = true, 
  Sounds = {
    "selected", "terran-engineering-bay-selected",
--    "ready", "human-blacksmith-ready",
    "help", "terran-base-attacked",
    "dead", "explosion-large"} } )

CUpgrade:New("upgrade-terran-infantry-weapons1")
CUpgrade:New("upgrade-terran-infantry-weapons2")
CUpgrade:New("upgrade-terran-infantry-weapons3")
CUpgrade:New("upgrade-terran-infantry-armor1")
CUpgrade:New("upgrade-terran-infantry-armor2")
CUpgrade:New("upgrade-terran-infantry-armor3")

DefineButton( { Pos = 1, Level = 0, Icon = "icon-terran-upgrade-infantry-weapons",
  Action = "research", Value = "upgrade-terran-infantry-weapons1",
  Allowed = "check-single-research",
  Key = "w", Hint = "Upgrade Infantry ~!Weapons",
  ForUnit = {"unit-terran-engineering-bay"} } )
DefineButton( { Pos = 1, Level = 0, Icon = "icon-terran-upgrade-infantry-weapons",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-terran-infantry-weapons2",
  Key = "w", Hint = "Upgrade Infantry ~!Weapons",
  ForUnit = {"unit-terran-engineering-bay"} } )
DefineButton( { Pos = 1, Level = 0, Icon = "icon-terran-upgrade-infantry-weapons",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-terran-infantry-weapons3",
  Key = "w", Hint = "Upgrade Infantry ~!Weapons",
  ForUnit = {"unit-terran-engineering-bay"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-terran-upgrade-infantry-armor",
  Action = "research", Value = "upgrade-terran-infantry-armor1",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Infantry ~!Armor",
  ForUnit = {"unit-terran-engineering-bay"} } )
DefineButton( { Pos = 2, Level = 0, Icon = "icon-terran-upgrade-infantry-armor",
  Action = "research", Value = "upgrade-terran-infantry-armor1",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Infantry ~!Armor",
  ForUnit = {"unit-terran-engineering-bay"} } )
DefineButton( { Pos = 2, Level = 0, Icon = "icon-terran-upgrade-infantry-armor",
  Action = "research", Value = "upgrade-terran-infantry-armor2",
  Allowed = "check-single-research",
  Key = "a", Hint = "Upgrade Infantry ~!Armor",
  ForUnit = {"unit-terran-engineering-bay"} } )
