
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

--FIXME:do this

--
--  Allow
--


--
--  Dependencies
--

DefineDependency("unit-zerg-zergling",
  {"unit-zerg-spawning-pool"})
DefineDependency("unit-zerg-spawning-pool",
  {"unit-zerg-hatchery"})
DefineDependency("unit-zerg-creep-colony",
  {"unit-zerg-hatchery"})
DefineDependency("unit-zerg-sunken-colony",
  {"unit-zerg-spawning-pool"})

DefineDependency("unit-zerg-hydralisk",
  {"unit-zerg-hydralisk-den"})
DefineDependency("unit-zerg-ultralisk",
  {"unit-zerg-ultralisk-cavern"})
DefineDependency("unit-zerg-hydralisk-den",
  {"unit-zerg-hatchery"})
DefineDependency("unit-zerg-ultralisk-cavern",
  {"unit-zerg-hatchery"})
DefineDependency("unit-zerg-extractor",
  {"unit-zerg-hatchery"})