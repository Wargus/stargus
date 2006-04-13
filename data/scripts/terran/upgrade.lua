--
--  Upgrades
--

upgrades = {
{ "upgrade-terran-infantry-weapons1",
  "icon", "icon-terran-upgrade-infantry-weapons",
  "costs", {   200,   100,   100,     0,     0,     0,     0}},
{ "upgrade-terran-infantry-weapons2",
  "icon", "icon-terran-upgrade-infantry-weapons",
  "costs", {   200,   175,   175,     0,     0,     0,     0}},
{ "upgrade-terran-infantry-weapons3",
  "icon", "icon-terran-upgrade-infantry-weapons",
  "costs", {   200,   250,   250,     0,     0,     0,     0}},
{ "upgrade-terran-infantry-armor1",
  "icon", "icon-terran-upgrade-infantry-armor",
  "costs", {   200,   100,   100,     0,     0,     0,     0}},
{ "upgrade-terran-infantry-armor2",
  "icon", "icon-terran-upgrade-infantry-armor",
  "costs", {   200,   175,   175,     0,     0,     0,     0}},
{ "upgrade-terran-infantry-armor3",
  "icon", "icon-terran-upgrade-infantry-armor",
  "costs", {   200,   250,   250,     0,     0,     0,     0}},

{ "upgrade-terran-u238-shells",
  "icon", "icon-terran-u238-shells",
  "costs", {   200,   150,   150,     0,     0,     0,     0}},

{ "upgrade-terran-stim-pack",
  "icon", "icon-terran-stim-pack",
  "costs", {   200,   100,   100,     0,     0,     0,     0}}
}

--
--  Modifiers
--

DefineModifier("upgrade-terran-infantry-weapons1",
  {"Level", 1}, {"PiercingDamage", 2},
  {"apply-to", "unit-terran-marine"}, {"apply-to", "unit-terran-firebat"},
  {"apply-to", "unit-terran-ghost"})
DefineModifier("upgrade-terran-infantry-weapons2",
  {"Level", 2}, {"PiercingDamage", 2},
  {"apply-to", "unit-terran-marine"}, {"apply-to", "unit-terran-firebat"},
  {"apply-to", "unit-terran-ghost"})
DefineModifier("upgrade-terran-infantry-weapons3",
  {"Level", 3}, {"PiercingDamage", 2},
  {"apply-to", "unit-terran-marine"}, {"apply-to", "unit-terran-firebat"},
  {"apply-to", "unit-terran-ghost"})

DefineModifier("upgrade-terran-infantry-armor1",
  {"Level", 1}, {"Armor", 2},
  {"apply-to", "unit-terran-marine"}, {"apply-to", "unit-terran-firebat"},
  {"apply-to", "unit-terran-ghost"})
DefineModifier("upgrade-terran-infantry-armor2",
  {"Level", 2}, {"Armor", 2},
  {"apply-to", "unit-terran-marine"}, {"apply-to", "unit-terran-firebat"},
  {"apply-to", "unit-terran-ghost"})
DefineModifier("upgrade-terran-infantry-armor3",
  {"Level", 3}, {"Armor", 2},
  {"apply-to", "unit-terran-marine"}, {"apply-to", "unit-terran-firebat"},
  {"apply-to", "unit-terran-ghost"})

DefineModifier("upgrade-terran-u238-shells",
  {"Level", 1}, {"AttackRange", 1},
  {"apply-to", "unit-terran-marine"}, {"apply-to", "unit-terran-firebat"},
  {"apply-to", "unit-terran-ghost"})

DefineModifier("upgrade-terran-stim-pack",
  {"Level", 1}, {"Armor", 2},
  {"apply-to", "unit-terran-marine"}, {"apply-to", "unit-terran-firebat"},
  {"apply-to", "unit-terran-ghost"})


--
--  Allow
--

DefineAllow("upgrade-terran-infantry-weapons1", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-terran-infantry-weapons2", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-terran-infantry-weapons3", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-terran-infantry-armor1", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-terran-infantry-armor2", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-terran-infantry-armor3", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-terran-stim-pack", "AAAAAAAAAAAAAAAA")
DefineAllow("upgrade-terran-u238-shells", "AAAAAAAAAAAAAAAA")


--
--  Dependencies
--

DefineDependency("upgrade-terran-infantry-weapons2",
  {"upgrade-terran-infantry-weapons1"})
DefineDependency("upgrade-terran-infantry-weapons3",
  {"upgrade-terran-infantry-weapons2"})
DefineDependency("upgrade-terran-infantry-armor2",
  {"upgrade-terran-infantry-armor1"})
DefineDependency("upgrade-terran-infantry-armor3",
  {"upgrade-terran-infantry-armor2"})

DefineDependency("unit-terran-ghost",
  {"unit-terran-academy", "unit-terran-science-facility",
   --[["unit-terran-covert-ops"]]})

DefineDependency("unit-terran-supply-depot",
  {"unit-terran-command-center"})
DefineDependency("unit-terran-engineering-bay",
  {"unit-terran-command-center"})
DefineDependency("unit-terran-barracks",
  {"unit-terran-command-center"})
DefineDependency("unit-terran-refinery",
  {"unit-terran-command-center"})

DefineDependency("unit-terran-missile-turret",
  {"unit-terran-engineering-bay"})

DefineDependency("unit-terran-academy",
  {"unit-terran-barracks"})
DefineDependency("unit-terran-bunker",
  {"unit-terran-barracks"})
DefineDependency("unit-terran-factory",
  {"unit-terran-barracks"})

DefineDependency("unit-terran-armory",
  {"unit-terran-factory"})
DefineDependency("unit-terran-starport",
  {"unit-terran-factory"})

DefineDependency("unit-terran-science-facility",
  {"unit-terran-starport"})
