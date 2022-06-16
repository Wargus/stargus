function Briefing(title, objs, bg, text, voices)
  local menu = WarMenu(nil, bg)

  Objectives = objs

  menu:addLabel(title, (70 + 340) / 2 * Video.Width / 640, 28 * Video.Height / 480,
    Fonts["large"], true)

  local t = LoadBuffer(text)
  t = "\n\n\n\n\n\n\n\n\n\n\n\n\n" .. t .. "\n\n\n\n\n\n\n\n\n\n\n\n\n"
  local sw = ScrollingWidget(320, 170 * Video.Height / 480)
  sw:setBackgroundColor(Color(0,0,0,0))
  sw:setSpeed(0.38)
  local l = MultiLineLabel(t)
  l:setFont(Fonts["large"])
  l:setAlignment(MultiLineLabel.LEFT)
  l:setLineWidth(320)
  l:adjustSize()
  sw:add(l, 0, 0)
  menu:add(sw, 70 * Video.Width / 640, 80 * Video.Height / 480)

  menu:addLabel("Objectives:", 372 * Video.Width / 640, 306 * Video.Height / 480, Fonts["large"], false)

  local objectives = ""
  table.foreachi(objs, function(k,v) objectives = objectives .. v .. "\n" end)

  local l = MultiLineLabel(objectives)
  l:setFont(Fonts["large"])
  l:setAlignment(MultiLineLabel.LEFT)
  l:setLineWidth(250 * Video.Width / 640)
  l:adjustSize()
  menu:add(l, 372 * Video.Width / 640, (306 * Video.Height / 480) + 30)

  local voice = 0
  local channel = -1

  menu:addHalfButton("~!Continue", "c", 455 * Video.Width / 640, 440 * Video.Height / 480,
    function()
      if (channel ~= -1) then
        voice = table.getn(voices)
        StopChannel(channel)
      end
      menu:stop()
    end)


  function PlayNextVoice()
    voice = voice + 1
    if (voice <= table.getn(voices)) then
      channel = PlaySoundFile(voices[voice], PlayNextVoice);
    else
      channel = -1
    end
  end
  PlayNextVoice()

  local speed = GetGameSpeed()
  SetGameSpeed(30)

  menu:run()

  SetGameSpeed(speed)
end

function CreatePictureStep(bg, title, text)
  return function()
    local menu = WarMenu(nil, bg)
    local offx = (Video.Width - 640) / 2
    local offy  = (Video.Height - 480) / 2
    menu:addLabel(title, offx + 320, offy + 240 - 67, Fonts["large-title"], true)
    menu:addLabel(text, offx + 320, offy + 240 - 25, Fonts["small-title"], true)
    menu:addHalfButton("~!Continue", "c", 455 * Video.Width / 640, 440 * Video.Height / 480,
      function() menu:stop() end)
    menu:run()
    GameResult = GameVictory
  end
end

function CreateMapStep(map)
  return function()
    Load(map)
    RunMap(map)
  end
end

function RunImageStep(filename, pagenum)
  local txt = LoadBuffer(filename)

  local fadespeed = 100
  local displaytime = 5000
  local bg = false
  local verticalAlignment = MultiLineLabel.TOP
  local menu
  local label
  if pagenum == nil then
    pagenum = 1
  end
  local current_page = 1
  local text = ""

  for s in txt:gmatch("[^\r\n]*") do
    if s:find("</FADESPEED ", 1, true) then
      s = s:gsub("[^0-9]+", "")
      fadespeed = tonumber(s)
    elseif s:find("</DISPLAYTIME ", 1, true) then
      s = s:gsub("[^0-9]+", "")
      displaytime = tonumber(s)
    elseif s:find("</BACKGROUND ", 1, true) then
      bg = s:sub(string.len("</BACKGROUND ") + 1):gsub("[\\]", "/"):gsub("%.pcx>", ".png")
      if CanAccessFile(bg) then
        menu = WarMenu(nil, bg)
      else
        print("Missing background: " .. bg)
        menu = WarMenu(nil, false)
      end
    elseif s:find("</SCREENLOWERLEFT>", 1, true) then
      text = ""
      verticalAlignment = MultiLineLabel.BOTTOM
      label = MultiLineLabel("...")
      label:setForegroundColor(Color(128, 128, 128, 255))
      label:setAlignment(MultiLineLabel.LEFT)
      label:setVerticalAlignment(verticalAlignment)
      label:setFont(Fonts["font16x"])
    elseif s:find("</SCREENLEFT>", 1, true) then
      text = ""
      verticalAlignment = MultiLineLabel.TOP
      label = MultiLineLabel("...")
      label:setForegroundColor(Color(128, 128, 128, 255))
      label:setAlignment(MultiLineLabel.LEFT)
      label:setVerticalAlignment(verticalAlignment)
      label:setFont(Fonts["font16x"])
    elseif s:find("</PAGE>", 1, true) then
      if pagenum == current_page then
        label:setCaption(text)
        label:setSize(Video.Width - 30, Video.Height - 30)
        label:setLineWidth(Video.Width - 40)
        menu:add(label, 15, 15)

        local blackScreen = Container()
        blackScreen:setSize(Video.Width, Video.Height)
        blackScreen:setBaseColor(Color(0, 0, 0, 255))
        blackScreen:setOpaque(true)
        menu:add(blackScreen, 0, 0)

        local time = 0
        local alpha = 255
        local function listen()
          menu:setDirty(true)
          if time <= fadespeed then
            alpha = math.max(0, alpha - 255 / fadespeed)
            blackScreen:setBaseColor(Color(0, 0, 0, math.floor(alpha)))
          else
            blackScreen:setVisible(false)
          end
          if time >= displaytime then
            menu:stop()
            RunImageStep(filename, current_page + 1)
            GameResult = GameVictory
          end
          time = time + (1000 / (GetGameSpeed() + 1))
        end
        local listener = LuaActionListener(listen)
        menu:addLogicCallback(listener)

        label:setMouseCallback(function (evt, btn, cnt)
          if evt == "mouseClick" then
            time = displaytime
          end
        end)

        menu:run()
      end
      current_page = current_page + 1
    elseif not s:find("</", 1, true) then
      if label then
        text = text .. "\n" .. s
      end
    else
      print("Unsupported tag: " .. s)
    end
  end
end

function RunCampaignSubmenu(campaign)
  Load(campaign)

  if not preferences.Progress then
    preferences.Progress = {}
    SavePreferences()
  end
  local campaign_key = string.gsub(campaign, "[/.]", "_")
  if not preferences.Progress[campaign_key] then
    preferences.Progress[campaign_key] = #campaign_steps
    SavePreferences()
  end
  campaign_position = preferences.Progress[campaign_key]

  local menu = WarMenu(nil, false)

  local function RunMission(number)
    campaign_position = number
    while (campaign_position <= #campaign_steps) do
      campaign_steps[campaign_position]()
      if (GameResult == GameVictory) then
        campaign_position = campaign_position + 1
        preferences.Progress[campaign_key] = math.max(preferences.Progress[campaign_key], campaign_position)
        SavePreferences()
      else
        menu:stop() -- quit to menu
        break
      end
    end
  end

  for i=1,#campaign_menu do
    menu:addTextButton("Mission " .. i, nil, Video.Width / 2 - (Fonts["large"]:Width("Mission 10") / 2), 20 + i * Fonts["large"]:Height() * 2,
      function() RunMission(campaign_menu[i]) end)
  end

  menu:addBottomButton("Cancel", "c", Video.Width / 2, 0, function()
    menu:stop()
  end)

  menu:run()
end

function RunCampaignGameMenu()
  local menu = WarMenu(nil, false)
  local offx = (Video.Width - 640) / 2
  local offy = (Video.Height - 480) / 2
  local center = Video.Width / 2
  
  local t_x = Video.Width / 6 * 3
  local t_y = 50 + offy
  local p_x = Video.Width / 6 * 5
  local p_y = 100 + offy
  local z_x = Video.Width / 6 * 1
  local z_y = 100 + offy

  menu:addAnimation("videos/campaign/disk.mng", t_x, t_y + 160, true)
  menu:addAnimation("videos/campaign/disk.mng", p_x, p_y + 160, true)
  menu:addAnimation("videos/campaign/disk.mng", z_x, z_y + 160, true)

  menu:addAnimatedButton(
    "videos/campaign/terr.mng",
    "videos/campaign/terron.mng",
    t_x - 35, t_y,
    t_x - 140, t_y - 50,
    "~light-green~T~!erran",
    "t",
    function() RunCampaignSubmenu("scripts/terran/campaign1.lua"); menu:stop() end,
    false,
    true
  )

  menu:addAnimatedButton(
    "videos/campaign/prot.mng",
    "videos/campaign/proton.mng",
    p_x, p_y,
    p_x - 140, p_y - 90,
    "~light-green~P~!rotoss",
    "p",
    function() RunCampaignSubmenu("scripts/protoss/campaign1.lua"); menu:stop() end,
    false,
    true
  )
  
  menu:addAnimatedButton(
    "videos/campaign/zerg.mng",
    "videos/campaign/zergon.mng",
    z_x + 5, z_y - 15,
    z_x - 105, z_y - 50,
    "~light-green~Z~!erg",
    "z",
    function() RunCampaignSubmenu("scripts/zerg/campaign1.lua"); menu:stop() end,
    false,
    true
  )
  
  --menu:addFullButton("~!Terran Campaign", "t", offx + 208, offy + 212 + (36 * 0),
    --function() RunCampaign("scripts/terran/campaign1.lua"); menu:stop() end)
  --menu:addFullButton("~!Zerg Campaign", "z", offx + 208, offy + 212 + (36 * 1),
    --function() RunCampaign("scripts/zerg/campaign1.lua"); menu:stop() end):setEnabled(false)
  --menu:addFullButton("~!Protoss Campaign", "p", offx + 208, offy + 212 + (36 * 2),
    --function() RunCampaign("scripts/protoss/campaign1.lua"); menu:stop() end):setEnabled(false)

  menu:addBottomButton("~!Skirmish", "s", center, 1.9, RunSinglePlayerGameMenu)
  menu:addBottomButton("~!Load", "l", center, 0.7, RunReplayGameMenu)
  menu:addBottomButton("~!Replay", "r", center, -0.5, RunReplayGameMenu)
  menu:addBottomButton("~!Cancel", "c", center + Video.Width / 3, 0, function() menu:stop() end)

  menu:run()
end

