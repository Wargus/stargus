function LoadGame(s)
  LoadGameFile = nil
  currentCampaign = nil
  loop = true

  while (loop) do
    InitGameVariables()
    StartSavedGame(s)
    if (GameResult ~= GameRestart) then
      loop = false
    end
  end

  RunResultsMenu()

  InitGameSettings()
  SetPlayerData(GetThisPlayer(), "RaceName", "orc")

  if currentCampaign ~= nil then
    if GameResult == GameVictory then
      position = position + 1
    elseif (GameResult == GameDefeat) then
    elseif (GameResult == GameDraw) then
    else
      currentCampaign = nil -- quit to menu
      return
    end
    RunCampaign(currentCampaign)
  end
end

function AddLoadGameItems(menu)
  menu:addLabel("Load Game", 384/2, 8)
  local browser = menu:addBrowser("~save", "^.*%.sav%.?g?z?$",
    32, 44, 320, 160)

  menu:addFullLeftButton("~!Load", "l", 20, 216,
    function()
      if (browser:getSelected() < 0) then
        return
      end
      LoadGameFile = "~save/" .. browser:getSelectedItem()
      if (menu.ingame) then
        StopGame(GameNoResult)
        menu:stopAll()
      else
        menu:stop()
      end
    end)
  menu:addHalfRightButton("~!Cancel", "c", 260, 216,
    function() menu:stop() end)
end

function RunLoadGameMenu()
  local menu = WarMenu(nil, panel("384x256"), false)
  menu:setSize(384, 256)
  menu:setPosition((Video.Width - 384) / 2, (Video.Height - 256) / 2)

  AddLoadGameItems(menu)

  menu.ingame = false
  menu:run()
end

function RunGameLoadGameMenu()
  local menu = WarGameMenu(panel("384x256"))
  menu:resize(384, 256)

  AddLoadGameItems(menu)

  menu.ingame = true
  menu:run(false)
end

