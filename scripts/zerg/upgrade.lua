--
--  Upgrades
--

local upgrades = {
{ "upgrade-zerg-melee-attacks1", "icon-zerg-upgrade-melee",
  {   200,   100,   100,     0,     0,     0,     0}},
{ "upgrade-zerg-melee-attacks2", "icon-zerg-upgrade-melee",
  {   200,   150,   150,     0,     0,     0,     0}},
{ "upgrade-zerg-melee-attacks3", "icon-zerg-upgrade-melee",
  {   200,   200,   200,     0,     0,     0,     0}},
  
{ "upgrade-zerg-missle-attacks1", "icon-zerg-upgrade-melee",
  {   200,   100,   100,     0,     0,     0,     0}},
{ "upgrade-zerg-missle-attacks2", "icon-zerg-upgrade-melee",
  {   200,   150,   150,     0,     0,     0,     0}},
{ "upgrade-zerg-missle-attacks3", "icon-zerg-upgrade-melee",
  {   200,   200,   200,     0,     0,     0,     0}},
  
{ "upgrade-zerg-carapace1", "icon-zerg-upgrade-melee",
  {   200,   100,   100,     0,     0,     0,     0}},
{ "upgrade-zerg-carapace2", "icon-zerg-upgrade-melee",
  {   200,   150,   150,     0,     0,     0,     0}},
{ "upgrade-zerg-carapace3", "icon-zerg-upgrade-melee",
  {   200,   200,   200,     0,     0,     0,     0}},

{ "upgrade-zerg-burrow", "icon-zerg-burrow-down",
  {   200,   100,   100,     0,     0,     0,     0}},
{ "upgrade-zerg-ventral-sacs", "icon-zerg-ventral-sacs",
  {   200,   100,   100,     0,     0,     0,     0}},
{ "upgrade-zerg-antennae", "icon-zerg-antennae",
  {   200,   100,   100,     0,     0,     0,     0}},
{ "upgrade-zerg-pneumatized-carapace", "icon-zerg-pneumatized-carapace",
  {   200,   100,   100,     0,     0,     0,     0}},
}

for i = 1,table.getn(upgrades) do
  u = CUpgrade:New(upgrades[i][1])
  u.Icon = Icons[upgrades[i][2]]
  for j = 1,table.getn(upgrades[1][3]) do
    u.Costs[j - 1] = upgrades[i][3][j]
  end
end


--
--  Modifiers
--

DefineModifier("upgrade-zerg-melee-attacks1",
  {"Level", 1}, {"PiercingDamage", 2},
  {"apply-to", "unit-zerg-zergling"}, {"apply-to", "unit-zerg-ultralisk"},
  {"apply-to", "unit-zerg-drone"})
DefineModifier("upgrade-zerg-melee-attacks2",
  {"Level", 2}, {"PiercingDamage", 3},
  {"apply-to", "unit-zerg-zergling"}, {"apply-to", "unit-zerg-ultralisk"},
  {"apply-to", "unit-zerg-drone"})
DefineModifier("upgrade-zerg-melee-attacks3",
  {"Level", 3}, {"PiercingDamage", 4},
  {"apply-to", "unit-zerg-zergling"}, {"apply-to", "unit-zerg-ultralisk"},
  {"apply-to", "unit-zerg-drone"})
  
DefineModifier("upgrade-zerg-missle-attacks1",
  {"Level", 1}, {"PiercingDamage", 2},
  {"apply-to", "unit-zerg-hydralisk"})
DefineModifier("upgrade-zerg-missle-attacks2",
  {"Level", 2}, {"PiercingDamage", 3},
  {"apply-to", "unit-zerg-hydralisk"})
DefineModifier("upgrade-zerg-missle-attacks3",
  {"Level", 3}, {"PiercingDamage", 4},
  {"apply-to", "unit-zerg-hydralisk"})
  
DefineModifier("upgrade-zerg-carapace1",
  {"Level", 1}, {"Armor", 2},
  {"apply-to", "unit-zerg-zergling"}, {"apply-to", "unit-zerg-ultralisk"},
  {"apply-to", "unit-zerg-drone"}, {"apply-to", "unit-zerg-hydralisk"})
DefineModifier("upgrade-zerg-carapace2",
  {"Level", 2}, {"Armor", 3},
  {"apply-to", "unit-zerg-zergling"}, {"apply-to", "unit-zerg-ultralisk"},
  {"apply-to", "unit-zerg-drone"}, {"apply-to", "unit-zerg-hydralisk"})
DefineModifier("upgrade-zerg-carapace3",
  {"Level", 3}, {"Armor", 4},
  {"apply-to", "unit-zerg-zergling"}, {"apply-to", "unit-zerg-ultralisk"},
  {"apply-to", "unit-zerg-drone"}, {"apply-to", "unit-zerg-hydralisk"})

--
--  Allow
--

DefineAllow("upgrade-zerg-melee-attacks1", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-melee-attacks2", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-melee-attacks3", "AAAAAAAAAAAAAAAA")

DefineAllow("upgrade-zerg-missle-attacks1", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-missle-attacks2", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-missle-attacks3", "AAAAAAAAAAAAAAAA")

DefineAllow("upgrade-zerg-carapace1", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-carapace2", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-carapace3", "AAAAAAAAAAAAAAAA")

DefineAllow("upgrade-zerg-burrow",         "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-ventral-sacs",   "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-antennae",       "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-zerg-pneumatized-carapace", "AAAAAAAAAAAAAAAA")


--
--  Dependencies
--

-- upgrades
DefineDependency("upgrade-zerg-melee-attacks2",
  {"upgrade-zerg-melee-attacks1"})
DefineDependency("upgrade-zerg-melee-attacks3",
  {"upgrade-zerg-melee-attacks2"})
  
DefineDependency("upgrade-zerg-missle-attacks2",
  {"upgrade-zerg-melee-attacks1"})
DefineDependency("upgrade-zerg-missle-attacks3",
  {"upgrade-zerg-melee-attacks2"})
  
DefineDependency("upgrade-zerg-carapace2",
  {"upgrade-zerg-carapace1"})
DefineDependency("upgrade-zerg-carapace3",
  {"upgrade-zerg-carapace2"})


-- units
DefineDependency("unit-zerg-drone",
  {"unit-zerg-hatchery"}, "or", {"unit-zerg-lair"}, "or", {"unit-zerg-hive"})
DefineDependency("unit-zerg-overlord",
  {"unit-zerg-hatchery"}, "or", {"unit-zerg-lair"}, "or", {"unit-zerg-hive"})
DefineDependency("unit-zerg-zergling",
  {"unit-zerg-spawning-pool"})
DefineDependency("unit-zerg-hydralisk",
  {"unit-zerg-hydralisk-den"})
DefineDependency("unit-zerg-mutalisk",
  {"unit-zerg-spire"})
DefineDependency("unit-zerg-scourge",
  {"unit-zerg-spire"})
DefineDependency("unit-zerg-queen",
  {"unit-zerg-queens-nest"})
DefineDependency("unit-zerg-defiler",
  {"unit-zerg-defiler-mound"})
DefineDependency("unit-zerg-ultralisk",
  {"unit-zerg-ultralisk-cavern"})
DefineDependency("unit-zerg-guardian",
  {"unit-zerg-greater-spire"})

-- hatchery buildings
DefineDependency("unit-zerg-evolution-chamber",
  {"unit-zerg-hatchery"}, "or", {"unit-zerg-lair"}, "or", {"unit-zerg-hive"})
DefineDependency("unit-zerg-creep-colony",
  {"unit-zerg-hatchery"}, "or", {"unit-zerg-lair"}, "or", {"unit-zerg-hive"})
DefineDependency("unit-zerg-spawning-pool",
  {"unit-zerg-hatchery"}, "or", {"unit-zerg-lair"}, "or", {"unit-zerg-hive"})

DefineDependency("unit-zerg-spore-colony",
  {"unit-zerg-creep-colony", "unit-zerg-evolution-chamber"})
DefineDependency("unit-zerg-sunken-colony",
  {"unit-zerg-creep-colony", "unit-zerg-spawning-pool"})
DefineDependency("unit-zerg-hydralisk-den",
  {"unit-zerg-spawning-pool"})

-- lair buildings
DefineDependency("unit-zerg-lair",
  {"unit-zerg-hatchery", "unit-zerg-spawning-pool"})

DefineDependency("unit-zerg-spire",
  {"unit-zerg-lair"}, "or", {"unit-zerg-hive"})
DefineDependency("unit-zerg-queens-nest",
  {"unit-zerg-lair"}, "or", {"unit-zerg-hive"})

-- hive buildings
DefineDependency("unit-zerg-hive",
  {"unit-zerg-lair", "unit-zerg-queens-nest"})

DefineDependency("unit-zerg-greater-spire",
  {"unit-zerg-hive", "unit-zerg-spire"})
DefineDependency("unit-zerg-nydus-canal",
  {"unit-zerg-hive"})
DefineDependency("unit-zerg-defiler-mound",
  {"unit-zerg-hive"})
DefineDependency("unit-zerg-ultralisk-cavern",
  {"unit-zerg-hive"})

