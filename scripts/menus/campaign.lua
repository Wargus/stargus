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

function RunCampaign(campaign)
  Load(campaign)

  if (campaign ~= currentCampaign or position == nil) then
    position = 1
  end

  currentCampaign = campaign

  while (position <= table.getn(campaign_steps)) do
    campaign_steps[position]()
    if (GameResult == GameVictory) then
      position = position + 1
    elseif (GameResult == GameDefeat) then
    elseif (GameResult == GameDraw) then
    else
      break -- quit to menu
    end
  end

  currentCampaign = nil
end

function RunCampaignGameMenu()
  local menu = WarMenu()
  local offx = (Video.Width - 640) / 2
  local offy = (Video.Height - 480) / 2
  
  menu:addAnimation("videos/campaign/disk.mng", 80 + 100, 250 + 150)
  menu:addAnimatedButton(
    "videos/campaign/terr.mng",
    "videos/campaign/terron.mng",
    80, 250,
    "~light-green~T~!erran",
    "t",
    function() RunCampaign("scripts/terran/campaign1.lua"); menu:stop() end
  )
  
  menu:addAnimation("videos/campaign/disk.mng", 350, 150 + 150)
  menu:addAnimatedButton(
    "videos/campaign/prot.mng",
    "videos/campaign/proton.mng",
    350, 150,
    "~light-green~P~!rotoss",
    "p",
    function() RunCampaign("scripts/protoss/campaign1.lua"); menu:stop() end
  )
  
  menu:addAnimation("videos/campaign/disk.mng", 550, 250 + 150)
  menu:addAnimatedButton(
    "videos/campaign/zerg.mng",
    "videos/campaign/zergon.mng",
    550, 250,
    "~light-green~Z~!erg",
    "z",
    function() RunCampaign("scripts/zerg/campaign1.lua"); menu:stop() end
  )
  
  

  --menu:addFullButton("~!Terran Campaign", "t", offx + 208, offy + 212 + (36 * 0),
    --function() RunCampaign("scripts/terran/campaign1.lua"); menu:stop() end)
  --menu:addFullButton("~!Zerg Campaign", "z", offx + 208, offy + 212 + (36 * 1),
    --function() RunCampaign("scripts/zerg/campaign1.lua"); menu:stop() end):setEnabled(false)
  --menu:addFullButton("~!Protoss Campaign", "p", offx + 208, offy + 212 + (36 * 2),
    --function() RunCampaign("scripts/protoss/campaign1.lua"); menu:stop() end):setEnabled(false)

  menu:addFullButton("~!Cancel", "c", offx + 208, offy + 232 + (36 * 5),
    function() menu:stop() end)

  menu:run()
end

