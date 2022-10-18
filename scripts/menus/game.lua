function WarGameMenu(background)
  local menu = MenuScreen()

  if (background == nil) then
    menu:setOpaque(true)
    menu:setBaseColor(dark)
  else
    local bgg = CGraphic:New(background)
    bgg:Load()
    local bg = ImageWidget(bgg)
    menu:add(bg, 0, 0)
  end

  function menu:resize(w, h)
    menu:setSize(w, h)
    menu:setPosition((Video.Width - menu:getWidth()) / 2,
      (Video.Height - 128 - menu:getHeight()) / 2)
  end

  menu:resize(256, 288)
  menu:setBorderSize(0)

  AddMenuHelpers(menu)

  return menu
end



function RunGameMenu()
  local menu = WarGameMenu(panel("264x288"))
  menu:resize(264, 288)

  menu:addLabel("Game Menu", 264/2, 8)

  menu:addFullButton("~!Save Game", "s", 20, 36,
    function() RunSaveMenu() end)
  menu:addFullButton("~!Load Game", "l", 20, 70,
    function() RunGameLoadGameMenu() end)
--[[
  menu:addFullButton("~!Pause Game", "p", 20, 70,
    function() end)
  menu:addFullButton("~!Resume Game", "r", 20, 70,
    function() end)
]]
  menu:addFullButton("~!Options", "o", 20, 104,
    function() RunGameOptionsMenu() end)  
  menu:addFullButton("~!Help", "h", 20, 138,
    function() RunHelpMenu() end)
  menu:addFullButton("Mission Ob~!jectives", "j", 20, 172,
    function() RunObjectivesMenu() end)
  menu:addFullButton("~!End Mission", "e", 20, 206,
    function() RunEndScenarioMenu() end)
  menu:addFullButton("Return to Game (~<Esc~>)", "escape", 20, 252,
    function() menu:stop() end)

  menu:run(false)
end

