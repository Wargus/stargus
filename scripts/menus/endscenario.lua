function RunEndScenarioMenu()
  local menu = WarGameMenu(panel("264x288"))
  menu:resize(264, 288)

  menu:addLabel("End Mission", 264/2, 8)

  local b = menu:addFullButton("~!Restart Mission", "r", 20, 70,
    function() RunRestartConfirmMenu() end)
  if (IsNetworkGame()) then
    b:setEnabled(false)
  end
  menu:addFullButton("~!Quit Mission", "q", 20, 104,
    function() RunQuitToMenuConfirmMenu() end)
  menu:addFullButton("E~!xit Program", "x", 20, 138,
    function() RunExitConfirmMenu() end)
  menu:addFullButton("Previous (~<Esc~>)", "escape", 20, 252,
    function() menu:stop() end)

--  menu:addFullButton("~!Surrender", "s", 20, 172,
--    function() RunSurrenderConfirmMenu() end)

  menu:run(false)
end

function RunRestartConfirmMenu()
  local menu = WarGameMenu(panel("264x288"))
  menu:resize(264, 288)

  menu:addLabel("Are you sure you", 264/2, 8)
  menu:addLabel("want to restart", 264/2, 32)
  menu:addLabel("the scenario?", 264/2, 56)
  menu:addFullButton("~!Restart Mission", "r", 20, 104,
    function() StopGame(GameRestart); menu:stopAll() end)
  menu:addFullButton("Cancel (~<Esc~>)", "escape", 20, 252,
    function() menu:stop() end)

  menu:run(false)
end

function RunSurrenderConfirmMenu()
  local menu = WarGameMenu(panel(1))

  menu:addLabel("Are you sure you", 128, 11)
  menu:addLabel("want to surrender", 128, 11 + (24 * 1))
  menu:addLabel("to your enemies?", 128, 11 + (24 * 2))
  menu:addFullButton("~!Surrender", "s", 16, 11 + (24 * 3) + 29,
    function() StopGame(GameDefeat); menu:stopAll() end)
  menu:addFullButton("Cancel (~<Esc~>)", "escape", 16, 248,
    function() menu:stop() end)

  menu:run(false)
end

function RunQuitToMenuConfirmMenu()
  local menu = WarGameMenu(panel("264x288"))
  menu:resize(264, 288)

  menu:addLabel("Are you sure you", 264/2, 8)
  menu:addLabel("want to quit", 264/2, 32)
  menu:addLabel("the mission?", 264/2, 56)
  menu:addFullButton("~!Quit Mission", "q", 20, 104,
    function() StopGame(GameQuitToMenu); menu:stopAll() end)
--  menu:addFullButton("Become O~!bserver", "b", 20, 138,
--    function() end)
  menu:addFullButton("Cancel (~<Esc~>)", "escape", 20, 252,
    function() menu:stop() end)

  menu:run(false)
end

function RunExitConfirmMenu()
  local menu = WarGameMenu(panel("264x288"))
  menu:resize(264, 288)

  menu:addLabel("Are you sure you", 264/2, 8)
  menu:addLabel("want to exit", 264/2, 32)
  menu:addLabel("Stratagus?", 264/2, 56)
  menu:addFullButton("E~!xit Program", "x", 20, 104,
    function() Exit(0) end)
  menu:addFullButton("Cancel (~<Esc~>)", "escape", 20, 252,
    function() menu:stop() end)

  menu:run(false)
end

