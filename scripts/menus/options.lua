function AddSoundOptions(menu, offx, offy, centerx, bottom)
  local b

  b = menu:addLabel("Sound Options", 264/2, 8)

  b = Label("Effects Volume")
  b:setFont(CFont:Get("game"))
  b:adjustSize();
  menu:add(b, offx + 16, offy + 36 * 1)

  -- FIXME: disable if effects turned off
  local soundslider = Slider(0, 255)
  soundslider:setValue(GetEffectsVolume())
  soundslider:setActionCallback(function() SetEffectsVolume(soundslider:getValue()) end)
  soundslider:setWidth(198)
  soundslider:setHeight(18)
  soundslider:setBaseColor(dark)
  soundslider:setForegroundColor(clear)
  soundslider:setBackgroundColor(clear)
  menu:add(soundslider, offx + 32, offy + 36 * 1.5)

  b = Label("min")
  b:setFont(CFont:Get("game"))
  b:adjustSize();
  menu:addCentered(b, offx + 44, offy + 36 * 2 + 6)

  b = Label("max")
  b:setFont(CFont:Get("game"))
  b:adjustSize();
  menu:addCentered(b, offx + 218, offy + 36 * 2 + 6)

  local effectscheckbox = {}
  effectscheckbox = menu:addCheckBox("Enabled", offx + 240, offy + 36 * 1.5,
    function() SetEffectsEnabled(effectscheckbox:isMarked()) end)
  effectscheckbox:setMarked(IsEffectsEnabled())
  effectscheckbox:adjustSize()

  b = Label("Music Volume")
  b:setFont(CFont:Get("game"))
  b:adjustSize();
  menu:add(b, offx + 16, offy + 36 * 3)

  -- FIXME: disable if music turned off
  local musicslider = Slider(0, 255)
  musicslider:setValue(GetMusicVolume())
  musicslider:setActionCallback(function() SetMusicVolume(musicslider:getValue()) end)
  musicslider:setWidth(198)
  musicslider:setHeight(18)
  musicslider:setBaseColor(dark)
  musicslider:setForegroundColor(clear)
  musicslider:setBackgroundColor(clear)
  menu:add(musicslider, offx + 32, offy + 36 * 3.5)

  b = Label("min")
  b:setFont(CFont:Get("game"))
  b:adjustSize();
  menu:addCentered(b, offx + 44, offy + 36 * 4 + 6)

  b = Label("max")
  b:setFont(CFont:Get("game"))
  b:adjustSize();
  menu:addCentered(b, offx + 218, offy + 36 * 4 + 6)

  local musiccheckbox = {}
  musiccheckbox = menu:addCheckBox("Enabled", offx + 240, offy + 36 * 3.5,
    function() SetMusicEnabled(musiccheckbox:isMarked()); MusicStopped() end)
  musiccheckbox:setMarked(IsMusicEnabled())
  musiccheckbox:adjustSize();

  b = menu:addHalfLeftButton("~!OK", "o", offx + 20, 252,
    function()
      preferences.EffectsVolume = GetEffectsVolume()
      preferences.EffectsEnabled = IsEffectsEnabled()
      preferences.MusicVolume = GetMusicVolume()
      preferences.MusicEnabled = IsMusicEnabled()
      SavePreferences()
      menu:stop()
    end)
  b = menu:addHalfRightButton("~!Cancel", "c", offx + 140, 252,
    function() menu:stop() end)
end

function RunGameSoundOptionsMenu()
  local menu = WarGameMenu(panel("264x288"))
  menu:resize(264, 288)

  AddSoundOptions(menu, 0, 0, 264/2 - 224/2, 288)

  menu:run(false)
end

function RunPreferencesMenu()
  local menu = WarGameMenu(panel("264x288"))

  menu:addLabel("Preferences", 264/2, 8)

  local fog = {}
  fog = menu:addCheckBox("Fog of War", 16, 40 + 36 * 0,
    function() SetFogOfWar(fog:isMarked()) end)
  fog:setMarked(GetFogOfWar())
  if (IsReplayGame() or IsNetworkGame()) then
    fog:setEnabled(false)
  end

  local ckey = {}
  ckey = menu:addCheckBox("Show command key", 16, 40 + 36 * 1,
    function() UI.ButtonPanel.ShowCommandKey = ckey:isMarked() end)
  ckey:setMarked(UI.ButtonPanel.ShowCommandKey)

  menu:addLabel("Game Speed", 16, 40 + 36 * 2, Fonts["game"], false)

  local gamespeed = {}
  gamespeed = menu:addSlider(15, 75, 198, 18, 32, 40 + 36 * 2.5,
    function() SetGameSpeed(gamespeed:getValue()) end)
  gamespeed:setValue(GetGameSpeed())

  menu:addLabel("slow", 34, 40 + (36 * 3) + 6, Fonts["small"], false)
  local l = Label("fast")
  l:setFont(Fonts["small"])
  l:adjustSize()
  menu:add(l, 230 - l:getWidth(), 40 + (36 * 3) + 6)

  menu:addHalfLeftButton("~!OK", "o", 20, 252,
    function()
      preferences.FogOfWar = GetFogOfWar()
      preferences.ShowCommandKey = UI.ButtonPanel.ShowCommandKey
      preferences.GameSpeed = GetGameSpeed()
      SavePreferences()
      menu:stop()
    end)
  menu:addHalfRightButton("~!Cancel", "c", 140, 252,
    function() menu:stop() end)

  menu:run(false)
end

function SetVideoSize(width, height)
  if (Video:ResizeScreen(width, height) == false) then
    return
  end
  bckground:Resize(Video.Width, Video.Height)
  backgroundWidget = ImageWidget(bckground)
  Load("scripts/ui.lua")
  preferences.VideoWidth = Video.Width
  preferences.VideoHeight = Video.Height
  SavePreferences()
end

function BuildOptionsMenu()
  local menu = WarMenu()
  local offx = (Video.Width - 352) / 2
  local offy = (Video.Height - 352) / 2
  local checkTexture
  local b

  menu:addLabel("Global Options", offx + 176, offy + 11)
  menu:addLabel("Video Resolution", offx + 16, offy + 44, Fonts["game"], false)

  b = menu:addCheckBox("640 x 480", offx + 16, offy + 65 + 26*0,
    function() SetVideoSize(640, 480) menu:stop(1) end)
  if (Video.Width == 640) then b:setMarked(true) end
  b = menu:addCheckBox("800 x 480", offx + 16, offy + 65 + 26*1,
    function() SetVideoSize(800, 480) menu:stop(1) end)
  if (Video.Width == 800 and Video.Height == 480) then b:setMarked(true) end
  b = menu:addCheckBox("800 x 600", offx + 16, offy + 65 + 26*2,
    function() SetVideoSize(800, 600) menu:stop(1) end)
  if (Video.Width == 800 and Video.Height == 600) then b:setMarked(true) end
  b = menu:addCheckBox("1024 x 768", offx + 16, offy + 65 + 26*3,
    function() SetVideoSize(1024, 768) menu:stop(1) end)
  if (Video.Width == 1024) then b:setMarked(true) end
  b = menu:addCheckBox("1280 x 800", offx + 16, offy + 65 + 26*4,
    function() SetVideoSize(1280, 800) menu:stop(1) end)
  if (Video.Height == 800) then b:setMarked(true) end 
  b = menu:addCheckBox("1280 x 960", offx + 16, offy + 65 + 26*5,
    function() SetVideoSize(1280, 960) menu:stop(1) end)
  if (Video.Height == 960) then b:setMarked(true) end 
  b = menu:addCheckBox("1280 x 1024", offx + 16, offy + 65 + 26*6,
    function() SetVideoSize(1280, 1024) menu:stop(1) end)
  if (Video.Height == 1024) then b:setMarked(true) end 
  b = menu:addCheckBox("1400 x 1050", offx + 16, offy + 65 + 26*7,
    function() SetVideoSize(1400, 1050) menu:stop(1) end)
  if (Video.Width == 1400) then b:setMarked(true) end 
  b = menu:addCheckBox("1600 x 1200", offx + 16, offy + 65 + 26*8,
    function() SetVideoSize(1600, 1200) menu:stop(1) end)
  if (Video.Width == 1600) then b:setMarked(true) end 
  b = menu:addCheckBox("1680 x 1050", offx + 16, offy + 65 + 26*9,
    function() SetVideoSize(1680, 1050) menu:stop(1) end)
  if (Video.Width == 1680) then b:setMarked(true) end

  b = menu:addCheckBox("Full Screen", offx + 17, offy + 65 + 26*10 + 14,
    function()
      ToggleFullScreen()
      preferences.VideoFullScreen = Video.FullScreen
      SavePreferences()
      menu:stop(1)
    end)
  b:setMarked(Video.FullScreen)

  checkTexture = menu:addCheckBox("Set Maximum OpenGL Texture to 256", offx + 127, offy + 65 + 26*10 + 14, 
    function()
      if (checkTexture:isMarked()) then
        preferences.MaxOpenGLTexture = 256
      else
        preferences.MaxOpenGLTexture = 0
      end
      SetMaxOpenGLTexture(preferences.MaxOpenGLTexture)
      SavePreferences()
    end)
  if (preferences.MaxOpenGLTexture == 128) then checkTexture:setMarked(true) end

  checkOpenGL = menu:addCheckBox("Use OpenGL / OpenGL ES 1.1 (restart required)", offx + 17, offy + 65 + 26*11 + 14,
    function()
--TODO: Add function for immediately change state of OpenGL
      preferences.UseOpenGL = checkOpenGL:isMarked()
      SavePreferences()
--      menu:stop(1) --TODO: Enable if we have an OpenGL function
    end)
  checkOpenGL:setMarked(preferences.UseOpenGL)
--  checkOpenGL:setMarked(UseOpenGL) --TODO: Enable if we have an OpenGL function

  menu:addHalfButton("~!OK", "o", offx + 123, offy + 309, function() menu:stop() end)

  return menu:run()
end

function RunOptionsMenu()
  local continue = 1
  while (continue == 1) do
    continue = BuildOptionsMenu()
  end
end

function RunGameOptionsMenu()
  local menu = WarGameMenu(panel("264x288"))
  menu:resize(264, 288)

  menu:addLabel("Game Options", 264/2, 8)
  menu:addFullButton("~!Sound", "s", 20, 36,
    function() RunGameSoundOptionsMenu() end)
  menu:addFullButton("~!Preferences", "p", 20, 70,
    function() RunPreferencesMenu() end)
  menu:addFullButton("~!Diplomacy", "d", 20, 104,
    function() RunDiplomacyMenu() end)
  menu:addFullButton("Previous (~<Esc~>", "escape", 20, 252,
    function() menu:stop() end)

  menu:run(false)
end

