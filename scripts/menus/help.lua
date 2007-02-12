function RunHelpMenu()
  local menu = WarGameMenu(panel("264x288"))

  menu:addLabel("Help Menu", 264/2, 8)
  menu:addFullButton("Keystroke ~!Help", "h", 20, 36,
    function() RunKeystrokeHelpMenu() end)
  menu:addFullButton("Stargus ~!Tips", "t", 20, 70,
    function() RunTipsMenu() end)
  menu:addFullButton("Previous (~<Esc~>)", "escape", 20, 252,
    function() menu:stop() end)

  menu:run(false)
end

local keystrokes = {
  {"Alt-F", "- toggle full screen"},
  {"Alt-G", "- toggle grab mouse"},
  {"Ctrl-S", "- mute sound"},
  {"Ctrl-M", "- mute music"},
  {"+", "- increase game speed"},
  {"-", "- decrease game speed"},
  {"Ctrl-P", "- pause game"},
  {"PAUSE", "- pause game"},
  {"PRINT", "- make screen shot"},
  {"Alt-H", "- help menu"},
  {"Alt-R", "- restart scenario"},
  {"Alt-Q", "- quit to main menu"},
  {"Alt-X", "- quit game"},
  {"Alt-B", "- toggle expand map"},
  {"Alt-M", "- game menu"},
  {"ENTER", "- write a message"},
  {"SPACE", "- goto last event"},
  {"TAB", "- hide/unhide terrain"},
  {"Ctrl-T", "- track unit"},
  {"Alt-I", "- find idle peon"},
  {"Alt-C", "- center on selected unit"},
  {"Alt-V", "- next view port"},
  {"Ctrl-V", "- previous view port"},
  {"^", "- select nothing"},
  {"#", "- select group"},
  {"##", "- center on group"},
  {"Ctrl-#", "- define group"},
  {"Shift-#", "- add to group"},
  {"Alt-#", "- add to alternate group"},
  {"F2-F4", "- recall map position"},
  {"Shift F2-F4", "- save map postition"},
  {"F5", "- game options"},
  {"F7", "- sound options"},
  {"F8", "- speed options"},
  {"F9", "- preferences"},
  {"F10", "- game menu"},
  {"F11", "- save game"},
  {"F12", "- load game"},
}

function RunKeystrokeHelpMenu()
  local menu = WarGameMenu(panel(5))
  menu:resize(352, 352)

  local c = Container()
  c:setOpaque(false)

  for i=1,table.getn(keystrokes) do
    local l = Label(keystrokes[i][1])
    l:setFont(Fonts["game"])
    l:adjustSize()
    c:add(l, 0, 20 * (i - 1))
    local l = Label(keystrokes[i][2])
    l:setFont(Fonts["game"])
    l:adjustSize()
    c:add(l, 80, 20 * (i - 1))
  end

  local s = ScrollArea()
  c:setSize(320 - s:getScrollbarWidth(), 20 * table.getn(keystrokes))
  s:setBaseColor(dark)
  s:setBackgroundColor(dark)
  s:setForegroundColor(clear)
  s:setSize(320, 216)
  s:setContent(c)
  menu:add(s, 16, 60)

  menu:addLabel("Keystroke Help Menu", 352 / 2, 11)
  menu:addFullButton("Previous (~<Esc~>)", "escape",
    (352 / 2) - (224 / 2), 352 - 40, function() menu:stop() end)

  menu:run(false)
end

local tips = {
  "Click on NEXT TIP to cycle through all available tips. You can activate this help menu at any time by clicking on the MENU button and choosing HELP. ",
  "Units can be ordered to move, attack, gather resources, or repair other units and buildings automatically. With a unit selected, right-click on the area or target where the action will be performed.",
  "To toggle subtitles on or off, go to MENU. Under OPTIONS, select SOUND and click on the box marked TOGGLE SUBTITLES.",
  "The Terran Refinery, Zerg Extractor and Protoss Assimilator must be constructed on top of a Vespene Geyser before any gas can be collected.",
  "Most commands in the game have hot keys.  These keys are denoted by the highlighted letter in the text of the command button.",
  "To restart a mission, choose END MISSION from the menu.",
  "Mission objectives may be viewed at any time by choosing MISSION OBJECTIVES from the menu.",
  "Any Terran Infantry units may be placed inside a Bunker. While inside a Bunker, units are shielded from attacks, but are free to return fire. To load a unit into a Bunker, select the unit and right-click on the Bunker.",
  "Terran Vultures can lay Spider Mines: select a Vulture unit, then select the MINE button and designate an area of ground as the target. ",
  "Queue up to five units at the same time by selecting a building, then clicking on the button of the unit you wish to queue.",
  "Terran Marines and Firebats have \"Stimpack\" upgrades. Stimpacks increase a unit's attack rate and movement rate, at a cost of 10 hit points per \"stim.\"",
  "In some missions, you must return specific units to a particular location, designated by a glowing Command Point Marker, called a \"Beacon.\"",
  "When building a Terran Command Center, Protoss Nexus, or Zerg Hatchery, try to place it as close to resources as possible.",
  "Both the Terran Wraith and Ghost have the ability to \"Cloak.\" While cloaked, they are safe from attack, unless spotted by enemy detection units.",
  "Cancel any unit in a queue by clicking on its icon in the construction \"pipeline\" display.",
  "Toggle the terrain information on and off in the Mini Map by pressing ~<TAB~>.",
  "Terran Dropships ferry units quickly between areas. Load Dropships by selecting one or more units, then right-clicking on the Dropship. Dropships are built at the Starport.",
  "Toggle the Mini Map between Team Color Identification and Friend-or-Foe recognition modes by pressing ~<SHIFT+TAB~>.",
  "When using the MOVE command, your units will ignore enemy units as they travel to their destination.  In this way, you can also use the MOVE command to retreat.",
  "Most Terran buildings can fly. Select the building and click the LIFTOFF button to fly; press the button again to select a location to land.",
  "Move your units with the ATTACK command when you wish them to engage enemy forces along the way.",
  "You can adjust the sound, music, and speech in the SOUND menu.",
  "Take over abandoned Terran add-ons (Machine Shops, Control Towers, etc.) by landing your own buildings next to them. ",
  "You can adjust the game speed, mouse speed, and other speed settings in the SPEED menu.",
  "In single player games, you can speed up or slow down the game by pressing the ~<+~> or ~<-~> keys.",
  "The Terran Nuclear Silo is an add-on to the Command Center. To launch a nuclear attack, build a nuclear missile at the silo, then use a Ghost unit to designate a target.",
  "Deselect an individual unit from a group by holding down the ~<SHIFT~> key while selecting that unit.",
  "To single out a unit from within a group, either select the individual unit, or select that unit's wireframe from the status display. ",
  "Missile Turrets and Science vessels reveal hidden units within their range. The Comsat station briefly reveals hidden units anywhere on the map with its Sensor Sweep.",
  "Load units into a transport using the MOVE command. The transport will automatically move to meet the units.",
  "Unload units from a transport by clicking the UNLOAD ALL button and selecting an unloading area. Unload an individual unit by clicking on its wireframe.",
  "All Zerg buildings, except the Hatchery and Extractor, must be constructed on creep. Creep can be created by building a Hatchery or a creep colony.",
  "You can designate targets for your commands (MOVE, ATTACK, GATHER, etc.) using the Mini Map.  In this way, you can send units to distant locations without having to scroll the Main Screen.",
  "Click and drag in the Mini Map to rapidly scroll your view in the main screen.",
  "The Zerg Hatchery can be upgraded to a Lair and eventually a Hive.  Each upgrade allows you to build additional Zerg structures.",
  "To select a unit's previous group, hold down the ~<ALT~> key while selecting that unit.",
  "SAVE your game frequently. If you find yourself in a desperate situation, you can go back and LOAD your game before you got into this whole mess. ",
  "Zerg Overlords can be upgraded to carry units at the Lair or Hive. Once upgraded, you can use them as transports by selecting a group of units and right-clicking on an Overlord.",
  "Use the Campaign Editor, found on the Main Menu, to build your own maps and edit unit variables.",
  "You can turn off unit responses in the SOUND menu.",
  "Zerg Queens have the ability to \"Infest\" a severely damaged Terran Command Center. Once infested, the Command Center is now a Zerg structure capable of building Infested Terrans that explode when attacking.",
  "The ~<SHIFT~> key allows you to chain together multiple commands. Hold down the SHIFT key while issuing commands; the unit will finish each task before proceeding to the next.",
  "You can use the PATROL command to setup a patrol route for your units.  While in patrol mode your units will attack any enemy units that they see.",
  "Most Zerg ground units have the ability to Burrow. When Burrowed, they cannot attack or be attacked unless detected. ",
  "Stationary combat units are assumed to be on guard: if they see an enemy unit they will automatically engage it.",
  "Using the HOLD POSITION command, units will remain stationary, even if attacked, and attack enemy units within their range.",
  "Zerg Mutalisks can be transformed into a unit called the Guardian. Once a Spire is upgraded into a Greater Spire, all Mutalisks automatically gain the ability to transform into Guardians.",
  "You can setup convoys by selecting your escorts and telling them to MOVE onto the unit you want escorted.  They will then follow the designated unit.",
  "To send messages to your opponent during multiplayer games, press ~<Enter~>, type in your message and press ~<Enter~> again.",
  "Zerg Defilers have the ability to CONSUME their own units. Every unit consumed restores 50 energy points to the Defiler.",
  "You can form alliances during a multiplayer game using the DIPLOMACY button on the Command Console.",
  "During multiplayer games, allies achieve a shared victory only if all surviving allies have selected ALLIED VICTORY from the DIPLOMACY MENU.",
  "Use the PLAGUE spell to severely damage any unit or building. It will cause up to 300 points of damage to its target, but will not kill a target.",
  "In a multiplayer game, allies can share their fog of war information once all members of the alliance select SHARE VISION from the DIPLOMACY MENU.",
  "Pressing ~<CTRL-S~> will toggle the sound on or off.  ~<CTRL-M~> will toggle the music on or off.",
  "Zerg Scourge can be set on Patrol to automatically attack all air units that come near. ",
  "To surrender during a campaign or multiplayer game, use the SURRENDER button in the OPTIONS menu.",
  "The Zerg Queen's ENSNARE spell and The Defiler's PLAGUE spell can be cast on cloaked units to allow other units to target them.",
  "Keep the path between the Command Center and available resources clear.  Obstacles slow the rate at which resources can be returned.",
  "All Protoss buildings, except the Nexus, must be built within the energy field of a Pylon. ",
  "To save your current position on the map, press ~<Shift-F2~>. To recall that position at any time, press ~<F2~>. You can save up to three views using keys F2-F4 in this manner.",
  "Protoss Reavers attack by firing explosive \"Scarabs\" at their targets. To build Scarabs, select the Reaver and press the BUILD SCARABS button.",
  "Different units are designed to work together and support each other. Combinations are more effective than a force composed of a single unit type.",
  "Protoss Probes can build multiple buildings at one time. Once a building warp has been started, the Probe can move onto a new task.",
  "Hold down ~<CTRL~> while selecting a unit to select all units of the same type within your view.",
  "Use PSIONIC STORM to damage all units in the spell's area of effect. It is devastating against a tight formation of enemy units.",
  "Double-click a unit to select all units of the same type within your view.",
  "Protoss Templars have the ability to transform into a powerful fighting unit called an Archon. Select two Templars and press the ARCHON WARP button to create an Archon.",
  "Pressing the space bar will center the screen on the location of your last transmission.",
  "Use HALLUCINATION to make multiple holograms of a single unit. Use them to scout and draw enemy fire as decoys. ",
  "To save your currently selected group of units, press ~<CTRL-1~>. To recall that group at any time, press ~<1~>. You can save up to ten groups using keys 1 through 0 in this manner. This also works for buildings.",
  "Protoss Observers are great for scouting: they remain permanently cloaked, and can detect hidden units.",
  "In a multiplayer game, pressing ~<SHIFT-ENTER~> sends your message to all players.",
  "Protoss Carriers attack by launching small interceptors that swarm their target. To build Interceptors, select the Carrier and press the BUILD INTERCEPTORS button.",
  "In a multiplayer game, pressing ~<CTRL-ENTER~> sends a message that is exclusive to your allies.",
  "The Protoss Arbiter cloaks all nearby units, although the Arbiter itself remains visible. Arbiters cannot cloak each other.",
  "Units caught in an Arbiter's Stasis Field can neither attack nor be attacked for the duration of the spell.",
  "Protoss Arbiters can use Recall to instantly teleport units to their location. ",
  "In Greed and Slaughter Mutiplayer games, a leaderboard displays the current leader. Press ~<CTRL-R~> to toggle between displaying the leader, and displaying all players.",
  "Tell everyone you know to buy Starcraft.",}

function RunTipsMenu()
  local menu = WarGameMenu(panel("384x256"))
  menu:resize(384, 256)

  menu:addLabel("Stargus Tips", 384/2, 8)

  local l = MultiLineLabel()
  l:setFont(Fonts["game"])
  l:setSize(372, 148)
  l:setLineWidth(372)
  menu:add(l, 6, 32)

  function l:prevTip()
    preferences.TipNumber = preferences.TipNumber - 1
    if (preferences.TipNumber < 1) then
      preferences.TipNumber = table.getn(tips)
    end
    SavePreferences()
  end
  function l:nextTip()
    preferences.TipNumber = preferences.TipNumber + 1
    if (preferences.TipNumber > table.getn(tips)) then
      preferences.TipNumber = 1
    end
    SavePreferences()
  end
  function l:updateCaption()
    self:setCaption(tips[preferences.TipNumber])
  end

  if (preferences.TipNumber == 0) then
    l:nextTip()
  end
  l:updateCaption()

  local showtips = {}
  showtips = menu:addCheckBox("~!Show Tips at Startup", 20, 188,
    function()
      preferences.ShowTips = showtips:isMarked()
      SavePreferences()
    end)
  showtips:setMarked(preferences.ShowTips)

  menu:addHalfLeftButton("~!OK", "o", 20, 216,
    function() l:nextTip(); menu:stop() end)
  menu:addHalfButton("~!Previous Tip", "p", 140, 216,
    function() l:prevTip(); l:updateCaption() end)
  menu:addHalfRightButton("~!Next Tip", "n", 260, 216,
    function() l:nextTip(); l:updateCaption() end)

  menu:run(false)
end


