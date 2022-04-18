-- Basic Terran sounds

MakeSound("terran-base-attacked", "terran/units/advisor/upd00.ogg")
MakeSound("terran-units-attacked", "terran/units/advisor/upd01.ogg")

-- Marine sounds

MakeSound("terran-marine-ready", "terran/units/marine/ready.ogg")
MakeSound("terran-marine-death",
  {"terran/units/marine/death/1.ogg",
  "terran/units/marine/death/2.ogg"})

MakeSound("terran-marine-attack", "terran/units/marine/fire.ogg")

MakeSound("terran-marine-acknowledge",
  {"terran/units/marine/acknowledgement/1.ogg",
  "terran/units/marine/acknowledgement/2.ogg",
  "terran/units/marine/acknowledgement/3.ogg",
  "terran/units/marine/acknowledgement/4.ogg"})

MakeSound("terran-marine-select",
  {"terran/units/marine/selected/1.ogg",
  "terran/units/marine/selected/2.ogg",
  "terran/units/marine/selected/3.ogg",
  "terran/units/marine/selected/4.ogg"})

MakeSound("terran-marine-annoyed",
  {"terran/units/marine/pissed/1.ogg",
  "terran/units/marine/pissed/2.ogg",
  "terran/units/marine/pissed/3.ogg",
  "terran/units/marine/pissed/4.ogg",
  "terran/units/marine/pissed/5.ogg",
  "terran/units/marine/pissed/6.ogg",
  "terran/units/marine/pissed/7.ogg"})

MakeSoundGroup("terran-marine-selected",
  "terran-marine-select", "terran-marine-annoyed")

-- Firebat sounds

MakeSound("terran-firebat-ready", "terran/units/firebat/ready.ogg")
MakeSound("terran-firebat-death",
  {"terran/units/firebat/death/1.ogg",
  "terran/units/firebat/death/2.ogg",
  "terran/units/firebat/death/3.ogg"})

MakeSound("terran-firebat-attack",
  {"terran/units/firebat/fire1.ogg",
  "terran/units/firebat/fire2.ogg"})

MakeSound("terran-firebat-acknowledge",
  {"terran/units/firebat/acknowledgement/1.ogg",
  "terran/units/firebat/acknowledgement/2.ogg",
  "terran/units/firebat/acknowledgement/3.ogg",
  "terran/units/firebat/acknowledgement/4.ogg"})

MakeSound("terran-firebat-select",
  {"terran/units/firebat/selected/1.ogg",
  "terran/units/firebat/selected/2.ogg",
  "terran/units/firebat/selected/3.ogg",
  "terran/units/firebat/selected/4.ogg"})

MakeSound("terran-firebat-annoyed",
  {"terran/units/firebat/pissed/1.ogg",
  "terran/units/firebat/pissed/2.ogg",
  "terran/units/firebat/pissed/3.ogg",
  "terran/units/firebat/pissed/4.ogg",
  "terran/units/firebat/pissed/5.ogg",
  "terran/units/firebat/pissed/6.ogg",
  "terran/units/firebat/pissed/7.ogg"})

MakeSoundGroup("terran-firebat-selected",
  "terran-firebat-select", "terran-firebat-annoyed")

-- Ghost sounds

MakeSound("terran-ghost-ready", "terran/units/ghost/ready.ogg")
MakeSound("terran-ghost-death",
  {"terran/units/ghost/death/1.ogg",
  --[["terran/units/ghost/death/2.ogg"]]})

MakeSound("terran-ghost-attack",
  {"terran/units/ghost/fire.ogg"})

MakeSound("terran-ghost-acknowledge",
  {"terran/units/ghost/acknowledgement/1.ogg",
  "terran/units/ghost/acknowledgement/2.ogg",
  "terran/units/ghost/acknowledgement/3.ogg",
  "terran/units/ghost/acknowledgement/4.ogg"})

MakeSound("terran-ghost-select",
  {"terran/units/ghost/selected/1.ogg",
  "terran/units/ghost/selected/2.ogg",
  "terran/units/ghost/selected/3.ogg",
  "terran/units/ghost/selected/4.ogg"})

MakeSound("terran-ghost-annoyed",
  {"terran/units/ghost/pissed/1.ogg",
  "terran/units/ghost/pissed/2.ogg",
  "terran/units/ghost/pissed/3.ogg",
  "terran/units/ghost/pissed/4.ogg"})

MakeSoundGroup("terran-ghost-selected",
  "terran-ghost-select", "terran-ghost-annoyed")

-- Goliath sounds

MakeSound("terran-goliath-ready", "terran/units/goliath/ready.ogg")
MakeSound("terran-goliath-death", "terran/units/goliath/death/1.ogg")

MakeSound("terran-goliath-attack",
  {"terran/units/goliath/fire.ogg",
  "terran/units/goliath/fire2.ogg"})

MakeSound("terran-goliath-acknowledge",
  {"terran/units/goliath/acknowledgement/1.ogg",
  "terran/units/goliath/acknowledgement/2.ogg",
  "terran/units/goliath/acknowledgement/3.ogg",
  "terran/units/goliath/acknowledgement/4.ogg"})

MakeSound("terran-goliath-select",
  {"terran/units/goliath/selected/1.ogg",
  "terran/units/goliath/selected/2.ogg",
  "terran/units/goliath/selected/3.ogg",
  "terran/units/goliath/selected/4.ogg"})

MakeSound("terran-goliath-annoyed",
  {"terran/units/goliath/pissed/1.ogg",
  "terran/units/goliath/pissed/2.ogg",
  "terran/units/goliath/pissed/3.ogg",
  "terran/units/goliath/pissed/4.ogg",
  "terran/units/goliath/pissed/5.ogg",
  "terran/units/goliath/pissed/6.ogg"})

MakeSoundGroup("terran-goliath-selected",
  "terran-goliath-select", "terran-goliath-annoyed")

-- Siege tank sounds

MakeSound("terran-siege-tank-ready", "terran/units/tank/ready.ogg")
MakeSound("terran-siege-tank-death", "terran/units/tank/death/1.ogg")

MakeSound("terran-siege-tank-attack", "terran/units/tank/fire.ogg")

MakeSound("terran-siege-tank-acknowledge",
  {"terran/units/tank/acknowledgement/1.ogg",
  "terran/units/tank/acknowledgement/2.ogg",
  "terran/units/tank/acknowledgement/3.ogg",
  "terran/units/tank/acknowledgement/4.ogg"})

MakeSound("terran-siege-tank-select",
  {"terran/units/tank/selected/1.ogg",
  "terran/units/tank/selected/2.ogg",
  "terran/units/tank/selected/3.ogg",
  "terran/units/tank/selected/4.ogg"})

MakeSound("terran-siege-tank-annoyed",
  {"terran/units/tank/pissed/1.ogg",
  "terran/units/tank/pissed/2.ogg",
  "terran/units/tank/pissed/3.ogg",
  "terran/units/tank/pissed/4.ogg"})

MakeSoundGroup("terran-siege-tank-selected",
  "terran-siege-tank-select", "terran-siege-tank-annoyed")

-- SCV sounds

MakeSound("terran-scv-ready", "terran/units/scv/ready.ogg")
MakeSound("terran-scv-death", "terran/units/scv/death/1.ogg")
MakeSound("terran-scv-done", "terran/units/scv/upd00.ogg")
MakeSound("terran-scv-attack", "terran/units/scv/edrrep00.ogg")

MakeSound("terran-scv-acknowledge",
  {"terran/units/scv/acknowledgement/1.ogg",
  "terran/units/scv/acknowledgement/2.ogg",
  "terran/units/scv/acknowledgement/3.ogg",
  "terran/units/scv/acknowledgement/4.ogg"})

MakeSound("terran-scv-select",
  {"terran/units/scv/selected/1.ogg",
  "terran/units/scv/selected/2.ogg",
  "terran/units/scv/selected/3.ogg",
  "terran/units/scv/selected/4.ogg"})

MakeSound("terran-scv-annoyed",
  {"terran/units/scv/pissed/1.ogg",
  "terran/units/scv/pissed/2.ogg",
  "terran/units/scv/pissed/3.ogg",
  "terran/units/scv/pissed/4.ogg",
  "terran/units/scv/pissed/5.ogg",
  "terran/units/scv/pissed/6.ogg",
  "terran/units/scv/pissed/7.ogg"})

MakeSoundGroup("terran-scv-selected",
  "terran-scv-select", "terran-scv-annoyed")

-- Vulture sounds

MakeSound("terran-vulture-ready", "terran/units/vulture/ready.ogg")
MakeSound("terran-vulture-death", "terran/units/vulture/death/1.ogg")
MakeSound("terran-vulture-attack", "terran/units/vulture/fire.ogg")

MakeSound("terran-vulture-acknowledge",
  {"terran/units/vulture/acknowledgement/1.ogg",
  "terran/units/vulture/acknowledgement/2.ogg",
  "terran/units/vulture/acknowledgement/3.ogg",
  "terran/units/vulture/acknowledgement/4.ogg"})

MakeSound("terran-vulture-select",
  {"terran/units/vulture/selected/1.ogg",
  "terran/units/vulture/selected/2.ogg",
  "terran/units/vulture/selected/3.ogg",
  "terran/units/vulture/selected/4.ogg"})

MakeSound("terran-vulture-annoyed",
  {"terran/units/vulture/pissed/1.ogg",
  "terran/units/vulture/pissed/2.ogg",
  "terran/units/vulture/pissed/3.ogg",
  "terran/units/vulture/pissed/4.ogg"})

MakeSoundGroup("terran-vulture-selected",
  "terran-vulture-select", "terran-vulture-annoyed")

-- Dropship sounds

MakeSound("terran-dropship-ready", "terran/units/dropship/ready.ogg")
MakeSound("terran-dropship-death", {"terran/units/dropship/death/1.ogg"})

MakeSound("terran-dropship-acknowledge",
  {"terran/units/dropship/acknowledgement/1.ogg",
  "terran/units/dropship/acknowledgement/2.ogg",
  "terran/units/dropship/acknowledgement/3.ogg",
  "terran/units/dropship/acknowledgement/4.ogg",
  "terran/units/dropship/acknowledgement/5.ogg",
  "terran/units/dropship/acknowledgement/6.ogg"})

MakeSound("terran-dropship-select",
  {"terran/units/dropship/selected/1.ogg",
  "terran/units/dropship/selected/2.ogg",
  "terran/units/dropship/selected/3.ogg",
  "terran/units/dropship/selected/4.ogg"})

MakeSound("terran-dropship-annoyed",
  {"terran/units/dropship/pissed/1.ogg",
  "terran/units/dropship/pissed/2.ogg",
  "terran/units/dropship/pissed/3.ogg",
  "terran/units/dropship/pissed/4.ogg"})

MakeSoundGroup("terran-dropship-selected",
  "terran-dropship-select", "terran-dropship-annoyed")

--- Science Vessel sounds

MakeSound("terran-science-vessel-ready", "terran/units/science vessel/ready.ogg")
MakeSound("terran-science-vessel-death", "terran/units/science vessel/death/1.ogg")
MakeSound("terran-science-vessel-attack", "terran/units/science vessel/irr00.ogg")

MakeSound("terran-science-vessel-acknowledge",
  {"terran/units/science vessel/acknowledgement/1.ogg",
  "terran/units/science vessel/acknowledgement/2.ogg",
  "terran/units/science vessel/acknowledgement/3.ogg",
  "terran/units/science vessel/acknowledgement/4.ogg"})

MakeSound("terran-science-vessel-select",
  {"terran/units/science vessel/selected/1.ogg",
  "terran/units/science vessel/selected/2.ogg",
  "terran/units/science vessel/selected/3.ogg",
  "terran/units/science vessel/selected/4.ogg"})

MakeSound("terran-science-vessel-annoyed",
  {"terran/units/science vessel/pissed/1.ogg",
  "terran/units/science vessel/pissed/2.ogg",
  "terran/units/science vessel/pissed/3.ogg",
  "terran/units/science vessel/pissed/4.ogg",
  "terran/units/science vessel/pissed/5.ogg",
  "terran/units/science vessel/pissed/6.ogg",
  "terran/units/science vessel/pissed/7.ogg"})

MakeSoundGroup("terran-science-vessel-selected",
  "terran-science-vessel-select", "terran-science-vessel-annoyed")

--- Wraith sounds

MakeSound("terran-wraith-ready", "terran/units/wraith/ready.ogg")
MakeSound("terran-wraith-death", "terran/units/wraith/death/1.ogg")
MakeSound("terran-wraith-attack", "terran/units/wraith/fire100.ogg")

MakeSound("terran-wraith-acknowledge",
  {"terran/units/wraith/acknowledgement/1.ogg",
  "terran/units/wraith/acknowledgement/2.ogg",
  "terran/units/wraith/acknowledgement/3.ogg",
  "terran/units/wraith/acknowledgement/4.ogg"})

MakeSound("terran-wraith-select",
  {"terran/units/wraith/selected/1.ogg",
  "terran/units/wraith/selected/2.ogg",
  "terran/units/wraith/selected/3.ogg",
  "terran/units/wraith/selected/4.ogg"})

MakeSound("terran-wraith-annoyed",
  {"terran/units/wraith/pissed/1.ogg",
  "terran/units/wraith/pissed/2.ogg",
  "terran/units/wraith/pissed/3.ogg",
  "terran/units/wraith/pissed/4.ogg",
  "terran/units/wraith/pissed/5.ogg",
  "terran/units/wraith/pissed/6.ogg",
  "terran/units/wraith/pissed/7.ogg"})

MakeSoundGroup("terran-wraith-selected",
  "terran-wraith-select", "terran-wraith-annoyed")

--- Battlecruiser sounds

MakeSound("terran-battlecruiser-ready", "terran/units/battlecruiser/ready.ogg")
MakeSound("terran-battlecruiser-death", "terran/units/battlecruiser/death/1.ogg")
MakeSound("terran-battlecruiser-attack", "terran/units/battlecruiser/yamato.ogg")

MakeSound("terran-battlecruiser-acknowledge",
  {"terran/units/battlecruiser/acknowledgement/1.ogg",
  "terran/units/battlecruiser/acknowledgement/2.ogg",
  "terran/units/battlecruiser/acknowledgement/3.ogg",
  "terran/units/battlecruiser/acknowledgement/4.ogg"})

MakeSound("terran-battlecruiser-select",
  {"terran/units/battlecruiser/selected/1.ogg",
  "terran/units/battlecruiser/selected/2.ogg",
  "terran/units/battlecruiser/selected/3.ogg",
  "terran/units/battlecruiser/selected/4.ogg"})

MakeSound("terran-battlecruiser-annoyed",
  {"terran/units/battlecruiser/pissed/1.ogg",
  "terran/units/battlecruiser/pissed/2.ogg",
  "terran/units/battlecruiser/pissed/3.ogg",
  "terran/units/battlecruiser/pissed/4.ogg",
  "terran/units/battlecruiser/pissed/5.ogg"})

MakeSoundGroup("terran-battlecruiser-selected",
  "terran-battlecruiser-select", "terran-battlecruiser-annoyed")

-- Terran buildings

MakeSound("terran-academy-selected", "terran/units/academy.ogg")
MakeSound("terran-armory-selected", "terran/units/armory.ogg")
MakeSound("terran-supply-depot-selected", "terran/units/supply depot.ogg")
MakeSound("terran-missile-turret-selected", "terran/units/missile turret.ogg")
MakeSound("terran-engineering-bay-selected", "terran/units/engineering bay.ogg")
MakeSound("terran-factory-selected", "terran/units/factory.ogg")
MakeSound("terran-refinery-selected", "terran/units/refinery.ogg")
MakeSound("terran-science-facility-selected", "terran/units/science facility.ogg")

