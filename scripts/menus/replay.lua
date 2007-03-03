function RunReplayGameMenu()
  local menu = WarMenu(nil, panel("384x256"), false)
  menu:setSize(384, 256)
  menu:setPosition((Video.Width - 384) / 2, (Video.Height - 256) / 2)

  menu:addLabel("Select Game", 384/2, 8)

  local browser = menu:addBrowser("~logs/", "%.log%.?g?z?$",
    32, 44, 320, 146)

  local reveal = menu:addCheckBox("Reveal Map", 32, 196, function() end)

  menu:addFullLeftButton("~!OK", "o", 20, 216,
    function()
      if (browser:getSelected() < 0) then
        return
      end
      InitGameVariables()
      StartReplay("~logs/" .. browser:getSelectedItem(), reveal:isMarked())
      InitGameSettings()
      SetPlayerData(GetThisPlayer(), "RaceName", "orc")
      menu:stop()
    end)
  menu:addHalfRightButton("~!Cancel", "c", 260, 216,
    function() menu:stop() end)

  menu:run()
end

function RunSaveReplayMenu()
  local menu = WarGameMenu(panel("384x256"))
  menu:setSize(384, 256)
  menu:setPosition((Video.Width - 384) / 2, (Video.Height - 256) / 2)

  menu:addLabel("Save Replay", 384/2, 8)

  local t = menu:addTextInputField("game.log",
    32, 22, 320)

  local browser = menu:addBrowser("~logs", ".log$",
    32, 44, 320, 146)
  local function cb(s)
    t:setText(browser:getSelectedItem())
  end
  browser:setActionCallback(cb)

  menu:addFullLeftButton("~!Save", "s", 20, 216,
    -- FIXME: use a confirm menu if the file exists already
    function()
      local name = t:getText()
      -- check for an empty string
      if (string.len(name) == 0) then
        return
      end
      -- append .log
      if (string.find(name, ".log$") == nil) then
        name = name .. ".log"
      end
      -- replace invalid chars with underscore
      local t = {"\\", "/", ":", "*", "?", "\"", "<", ">", "|"}
      table.foreachi(t, function(k,v) name = string.gsub(name, v, "_") end)

      SaveReplay(name)
      menu:stop()
    end)

  menu:addHalfRightButton("~!Cancel", "c", 260, 216,
    function() menu:stop() end)

  menu:run()
end
