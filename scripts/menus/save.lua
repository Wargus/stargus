function RunSaveMenu()
  local menu = WarGameMenu(panel("384x256"))
  menu:resize(384, 256)

  menu:addLabel("Save Game", 384/2, 8)

  local t = menu:addTextInputField("game.sav", 32, 44, 320)

  local browser = menu:addBrowser("~save", ".sav.gz$",
    32, 70, 320, 134)
  local function cb(s)
    t:setText(browser:getSelectedItem())
  end
  browser:setActionCallback(cb)

  menu:addHalfLeftButton("~!Save", "s", 20, 216,
    -- FIXME: use a confirm menu if the file exists already
    function()
      local name = t:getText()
      -- check for an empty string
      if (string.len(name) == 0) then
        return
      end
      -- strip .gz
      if (string.find(name, ".gz$") ~= nil) then
        name = string.sub(name, 1, string.len(name) - 3)
      end
      -- append .sav
      if (string.find(name, ".sav$") == nil) then
        name = name .. ".sav"
      end
      -- replace invalid chars with underscore
      local t = {"\\", "/", ":", "*", "?", "\"", "<", ">", "|"}
      table.foreachi(t, function(k,v) name = string.gsub(name, v, "_") end)

      SaveGame(name)
      UI.StatusLine:Set("Saved game to: " .. name)
      menu:stop()
    end)

  menu:addHalfButton("~!Delete", "d", 140, 216,
    function()
      if (browser:getSelected() >= 0) then
        DeleteSaveGame(browser:getSelectedItem())
        browser:updateList()
      end
    end)

  menu:addHalfRightButton("~!Cancel", "c", 260, 216,
    function() menu:stop() end)

  menu:run(false)
end

