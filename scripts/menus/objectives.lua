function RunObjectivesMenu()
  local menu = WarGameMenu(panel("384x256"))
  menu:resize(384, 256)

  menu:addLabel("Mission Objectives", 384/2, 8, Fonts["large"], true)

  local objectives = ""
  table.foreachi(Objectives, function(k,v) objectives = objectives .. v .. "\n" end)

  local l = MultiLineLabel(objectives)
  l:setFont(Fonts["large"])
  l:setAlignment(MultiLineLabel.LEFT)
  l:setLineWidth(228)
  l:adjustSize()
  menu:add(l, 6, 32)

  menu:addFullButton("Previous (~<Esc~>)", "escape", 80, 216, function() menu:stop() end)

  menu:run()
end

