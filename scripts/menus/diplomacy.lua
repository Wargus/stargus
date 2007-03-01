function RunDiplomacyMenu()
  local menu = WarGameMenu(panel("296x336"))
  menu:resize(296, 336)

  menu:addLabel("Alliances", 11, 13, Fonts["font16"], false)
  menu:addLabel("Allies", 179, 21, Fonts["game"])
  menu:addLabel("Shared", 246, 5, Fonts["game"])
  menu:addLabel("Vision", 246, 21, Fonts["game"])

--  menu:addCheckBox("Allied Victory", 11, 274)

  local allied = {}
  local enemy = {}
  local sharedvision = {}
  local j = 0

  for i=0,11 do
    if (Players[i].Type ~= PlayerNobody and ThisPlayer.Index ~= i) then
      local l = Label(Players[i].Name)
      l:setFont(Fonts["font16"])
      l:adjustSize()
      menu:add(l, 31, (17 * j) + 41)
      -- player color is at x=11, name is at x=31

      -- FIXME: disable checkboxes in replays or if on the same team

      local alliedcb = {}
      local sharedvisioncb = {}

      alliedcb = menu:addCheckBox("", 227, (17 * j) + 41,
        function() end)
      alliedcb:setMarked(ThisPlayer:IsAllied(Players[i]))
      allied[j] = alliedcb
      allied[j].index = i

      sharedvisioncb = menu:addCheckBox("", 269, (17 * j) + 41,
        function() end)
      sharedvisioncb:setMarked(ThisPlayer:IsSharedVision(Players[i]))
      sharedvision[j] = sharedvisioncb

      j = j + 1
    end
  end

  menu:addHalfLeftButton("Accept", nil, 11, 299,
    function()
      for j=1,table.getn(allied) do
        local i = allied[j].index

        -- allies
        if (allied[j]:isMarked()) then
          if (ThisPlayer:IsAllied(Players[i]) == false or
             ThisPlayer:IsEnemy(Players[i])) then
            SetDiplomacy(ThisPlayer.Index, "allied", i)
          end
        end

        -- enemies
        if (allied[j]:isMarked() == false) then
          if (ThisPlayer:IsAllied(Players[i]) or
             ThisPlayer:IsEnemy(Players[i]) == false) then
            SetDiplomacy(ThisPlayer.Index, "enemy", i)
          end
        end

        -- shared vision
        if (sharedvision[j]:isMarked()) then
          if (ThisPlayer:IsSharedVision(Players[i]) == false) then
            SetSharedVision(ThisPlayer.Index, true, i)
          end
        else
          if (ThisPlayer:IsSharedVision(Players[i])) then
            SetSharedVision(ThisPlayer.Index, false, i)
          end
        end
      end
      menu:stop()
    end)
  menu:addHalfRightButton("Cancel", nil, 165, 299, function() menu:stop() end)

  menu:run(false)
end

