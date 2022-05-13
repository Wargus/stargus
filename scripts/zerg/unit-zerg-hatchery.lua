--
-- unit-zerg-hatchery
--


DefineAnimations("animations-zerg-hatchery", {
  Still = {
    "frame 1", "wait 2", "frame 2", "wait 2", "frame 3", "wait 4",
    "frame 2", "wait 2", "frame 1", "wait 2", "frame 0", "wait 4",
  },
  Train = {
    "frame 0", "wait 125",
  },
})

DefineUnitType("unit-zerg-hatchery", { Name = "Zerg Hatchery",
  Shadow = {"file", "zerg/units/hatchery shadow.png", "size", {192, 160}},
  Animations = "animations-zerg-hatchery", Icon = "icon-zerg-hatchery",
  OnEachSecond = (function (self)
	local timeout = GetUnitVariable(self, "LarvaTimeout")
	if (timeout <= 0) then
	   local larvacount = 0
	   local units = GetUnitsAroundUnit(self, 1)
	   local i
	   for i,unit in ipairs(units) do
	      if (GetUnitVariable(unit, "Ident") == "unit-zerg-larva") then
		 larvacount = larvacount + 1
	      end
	   end
	   if larvacount < 3 then
	      local posx = GetUnitVariable(self, "PosX")
	      local posy = GetUnitVariable(self, "PosY")
	      CreateUnit("unit-zerg-larva", GetUnitVariable(self, "Player"), {posx - 1, posy})
	   end
	   SetUnitVariable(self, "LarvaTimeout", 20)
	else
	   SetUnitVariable(self, "LarvaTimeout", timeout - 1)
	end
  end),
  Costs = {"time", 255, "minerals", 300},
  RepairHp = 4,
  RepairCosts = {"minerals", 1, "gas", 0},
  Construction = "construction-zerg",
  Speed = 0,
  DrawLevel = 30,
  TileSize = {4, 3}, BoxSize = {126, 95},
  SightRange = 1,
  Armor = 20, BasicDamage = 0, PiercingDamage = 0, Missile = "missile-none",
  Priority = 35, AnnoyComputerFactor = 45,
  Points = 200,
  Supply = 8,
  RegenerationRate = 1,
--  ExplodeWhenKilled = "missle-zerg-rubble-large",
  Type = "land",
--  Corpse = "unit-zerg-rubble-large",
  BuilderLost = true,
  Building = true, VisibleUnderFog = true, 
  BuildingRules = { { "distance", { Distance = 3, DistanceType = ">", Type = "unit-minerals1"} } },
  CanStore = {"gas", "minerals"},
  Sounds = {
    "selected", "zerg-hatchery-selected",
--    "ready", "town-hall-ready",
    "ready", "zerg-building-ready",
    "help", "zerg-base-attacked",
    "dead", "zerg-building-blowup"} } )


DefineUnitType("unit-zerg-lair", {})
DefineUnitType("unit-zerg-hive", {})
CUpgrade:New("upgrade-zerg-burrow")
CUpgrade:New("upgrade-zerg-ventral-sacs")
CUpgrade:New("upgrade-zerg-antennae")
CUpgrade:New("upgrade-zerg-pneumatized-carapace")

--DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-larva",
--  Action = "button", Value = 1,
--  Key = "s", Hint = "~!Select Larva",
--  ForUnit = {"unit-zerg-hatchery", "unit-zerg-lair", "unit-zerg-hive"} } )

DefineButton( { Pos = 1, Level = 0, Icon = "icon-zerg-larva",
  Action = "callback", Value = (function(self)
    local units = GetUnitsAroundUnit(self, 1)
	for i,unit in ipairs(units) do
	  if (GetUnitVariable(unit, "Ident") == "unit-zerg-larva") then
        SelectSingleUnit(unit)
      end
    end  
  end),
  Key = "s", Hint = "~!Select Larva",
  ForUnit = {"unit-zerg-hatchery", "unit-zerg-lair", "unit-zerg-hive"} } )

DefineButton( { Pos = 2, Level = 0, Icon = "icon-rally-point",
  Action = "move",
  Key = "r", Hint = "Set ~!Rally Point",
  ForUnit = {"unit-zerg-hatchery", "unit-zerg-lair", "unit-zerg-hive"} } )

DefineButton( { Pos = 3, Level = 0, Icon = "icon-zerg-burrow-down",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-zerg-burrow",
  Key = "b", Hint = "Evolve ~!Burrow",
  ForUnit = {"unit-zerg-hatchery", "unit-zerg-lair", "unit-zerg-hive"} } )

DefineButton( { Pos = 7, Level = 0, Icon = "icon-zerg-lair",
  Action = "upgrade-to", Value = "unit-zerg-lair",
  Key = "l", Hint = "Mutate into ~!Lair",
  ForUnit = {"unit-zerg-hatchery"} } )

DefineButton( { Pos = 7, Level = 0, Icon = "icon-zerg-hive",
  Action = "upgrade-to", Value = "unit-zerg-hive",
  Key = "h", Hint = "Mutate into ~!Hive",
  ForUnit = {"unit-zerg-lair"} } )

DefineButton( { Pos = 4, Level = 0, Icon = "icon-zerg-ventral-sacs",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-zerg-ventral-sacs",
  Key = "v", Hint = "Evolve ~!Ventral Sacs",
  ForUnit = {"unit-zerg-lair", "unit-zerg-hive"} } )

DefineButton( { Pos = 5, Level = 0, Icon = "icon-zerg-antennae",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-zerg-antennae",
  Key = "a", Hint = "Evolve ~!Antennae",
  ForUnit = {"unit-zerg-lair", "unit-zerg-hive"} } )

DefineButton( { Pos = 6, Level = 0, Icon = "icon-zerg-pneumatized-carapace",
  Allowed = "check-single-research",
  Action = "research", Value = "upgrade-zerg-pneumatized-carapace",
  Key = "p", Hint = "Evolve ~!Pneumatized Carapace",
  ForUnit = {"unit-zerg-lair", "unit-zerg-hive"} } )
