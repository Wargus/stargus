SetPlayerData(GetThisPlayer(), "RaceName", "terran")

-- Global useful objects for menus  ----------
dark = Color(38, 38, 78)
clear = Color(200, 200, 120)
black = Color(0, 0, 0)

bckground = CGraphic:New("ui/Menu background without title.png")
bckground:Load()
bckground:Resize(Video.Width, Video.Height)
backgroundWidget = ImageWidget(bckground)

g_tbln = CGraphic:New("ui/terran/button 224x28.png")
g_tbln:Load()
g_tblp = CGraphic:New("ui/terran/button pressed 224x28.png")
g_tblp:Load()
g_tblg = CGraphic:New("ui/terran/button disabled 224x28.png")
g_tblg:Load()

g_zbln = CGraphic:New("ui/zerg/button 224x28.png")
g_zbln:Load()
g_zblp = CGraphic:New("ui/zerg/button pressed 224x28.png")
g_zblp:Load()
g_zblg = CGraphic:New("ui/zerg/button disabled 224x28.png")
g_zblg:Load()

g_pbln = CGraphic:New("ui/protoss/button 224x28.png")
g_pbln:Load()
g_pblp = CGraphic:New("ui/protoss/button pressed 224x28.png")
g_pblp:Load()
g_pblg = CGraphic:New("ui/protoss/button disabled 224x28.png")
g_pblg:Load()


g_tblln = CGraphic:New("ui/terran/button left 224x28.png")
g_tblln:Load()
g_tbllp = CGraphic:New("ui/terran/button left pressed 224x28.png")
g_tbllp:Load()
g_tbllg = CGraphic:New("ui/terran/button left disabled 224x28.png")
g_tbllg:Load()

g_zblln = CGraphic:New("ui/zerg/button left 224x28.png")
g_zblln:Load()
g_zbllp = CGraphic:New("ui/zerg/button left pressed 224x28.png")
g_zbllp:Load()
g_zbllg = CGraphic:New("ui/zerg/button left disabled 224x28.png")
g_zbllg:Load()

g_pblln = CGraphic:New("ui/protoss/button left 224x28.png")
g_pblln:Load()
g_pbllp = CGraphic:New("ui/protoss/button left pressed 224x28.png")
g_pbllp:Load()
g_pbllg = CGraphic:New("ui/protoss/button left disabled 224x28.png")
g_pbllg:Load()


g_tbhn = CGraphic:New("ui/terran/button 104x28.png")
g_tbhn:Load()
g_tbhp = CGraphic:New("ui/terran/button pressed 104x28.png")
g_tbhp:Load()
g_tbhg = CGraphic:New("ui/terran/button disabled 104x28.png")
g_tbhg:Load()

g_zbhn = CGraphic:New("ui/zerg/button 104x28.png")
g_zbhn:Load()
g_zbhp = CGraphic:New("ui/zerg/button pressed 104x28.png")
g_zbhp:Load()
g_zbhg = CGraphic:New("ui/zerg/button disabled 104x28.png")
g_zbhg:Load()

g_pbhn = CGraphic:New("ui/protoss/button 104x28.png")
g_pbhn:Load()
g_pbhp = CGraphic:New("ui/protoss/button pressed 104x28.png")
g_pbhp:Load()
g_pbhg = CGraphic:New("ui/protoss/button disabled 104x28.png")
g_pbhg:Load()


g_tbhln = CGraphic:New("ui/terran/button left 104x28.png")
g_tbhln:Load()
g_tbhlp = CGraphic:New("ui/terran/button left pressed 104x28.png")
g_tbhlp:Load()
g_tbhlg = CGraphic:New("ui/terran/button left disabled 104x28.png")
g_tbhlg:Load()

g_zbhln = CGraphic:New("ui/zerg/button left 104x28.png")
g_zbhln:Load()
g_zbhlp = CGraphic:New("ui/zerg/button left pressed 104x28.png")
g_zbhlp:Load()
g_zbhlg = CGraphic:New("ui/zerg/button left disabled 104x28.png")
g_zbhlg:Load()

g_pbhln = CGraphic:New("ui/protoss/button left 104x28.png")
g_pbhln:Load()
g_pbhlp = CGraphic:New("ui/protoss/button left pressed 104x28.png")
g_pbhlp:Load()
g_pbhlg = CGraphic:New("ui/protoss/button left disabled 104x28.png")
g_pbhlg:Load()


g_tbhrn = CGraphic:New("ui/terran/button right 104x28.png")
g_tbhrn:Load()
g_tbhrp = CGraphic:New("ui/terran/button right pressed 104x28.png")
g_tbhrp:Load()
g_tbhrg = CGraphic:New("ui/terran/button right disabled 104x28.png")
g_tbhrg:Load()

g_zbhrn = CGraphic:New("ui/zerg/button right 104x28.png")
g_zbhrn:Load()
g_zbhrp = CGraphic:New("ui/zerg/button right pressed 104x28.png")
g_zbhrp:Load()
g_zbhrg = CGraphic:New("ui/zerg/button right disabled 104x28.png")
g_zbhrg:Load()

g_pbhrn = CGraphic:New("ui/protoss/button right 104x28.png")
g_pbhrn:Load()
g_pbhrp = CGraphic:New("ui/protoss/button right pressed 104x28.png")
g_pbhrp:Load()
g_pbhrg = CGraphic:New("ui/protoss/button right disabled 104x28.png")
g_pbhrg:Load()




function panel(n)
  return "ui/panels/" .. n .. ".png"
end



function AddMenuHelpers(menu)
  function menu:addCentered(widget, x, y)
    self:add(widget, x - widget:getWidth() / 2, y)
  end

  function menu:addLabel(text, x, y, font, center)
    local label = Label(text)
    if (font == nil) then font = Fonts["large"] end
    label:setFont(font)
    label:adjustSize()
    if (center == nil or center == true) then -- center text by default
      x = x - label:getWidth() / 2
    end
    self:add(label, x, y)

    return label
  end

  function menu:writeText(text, x, y)
    return self:addLabel(text, x, y, Fonts["game"], false)
  end

  function menu:writeLargeText(text, x, y)
    return self:addLabel(text, x, y, Fonts["large"], false)
  end

  function menu:addButton(caption, hotkey, x, y, callback, size)
    local b = ButtonWidget(caption)
    b:setHotKey(hotkey)
    b:setActionCallback(callback)
    if (size == nil) then size = {200, 24} end
    b:setSize(size[1], size[2])
    b:setBackgroundColor(dark)
    b:setBaseColor(dark)
    self:add(b, x, y)
    return b
  end

  function menu:addImageButton(caption, hotkey, x, y, callback)
    local b = ImageButton(caption)
    b:setBorderSize(0)
    b:setHotKey(hotkey)
    b:setActionCallback(callback)
    self:add(b, x, y)
    return b
  end

  function menu:addFullLeftButton(caption, hotkey, x, y, callback)
    local b = self:addImageButton(caption, hotkey, x, y, callback)
    if (GetPlayerData(GetThisPlayer(), "RaceName") == "terran") then
      b:setNormalImage(g_tblln)
      b:setPressedImage(g_tbllp)
      b:setDisabledImage(g_tbllg)
    elseif (GetPlayerData(GetThisPlayer(), "RaceName") == "zerg") then
      b:setNormalImage(g_zblln)
      b:setPressedImage(g_zbllp)
      b:setDisabledImage(g_zbllg)
    else
      b:setNormalImage(g_pblln)
      b:setPressedImage(g_pbllp)
      b:setDisabledImage(g_pbllg)
    end
    b:setSize(224, 28)
    return b
  end

  function menu:addFullButton(caption, hotkey, x, y, callback)
    local b = self:addImageButton(caption, hotkey, x, y, callback)
    if (GetPlayerData(GetThisPlayer(), "RaceName") == "terran") then
      b:setNormalImage(g_tbln)
      b:setPressedImage(g_tblp)
      b:setDisabledImage(g_tblg)
    elseif (GetPlayerData(GetThisPlayer(), "RaceName") == "zerg") then
      b:setNormalImage(g_zbln)
      b:setPressedImage(g_zblp)
      b:setDisabledImage(g_zblg)
    else
      b:setNormalImage(g_pbln)
      b:setPressedImage(g_pblp)
      b:setDisabledImage(g_pblg)
    end
    b:setSize(224, 28)
    return b
  end

  function menu:addHalfLeftButton(caption, hotkey, x, y, callback)
    local b = self:addImageButton(caption, hotkey, x, y, callback)
    if (GetPlayerData(GetThisPlayer(), "RaceName") == "terran") then
      b:setNormalImage(g_tbhln)
      b:setPressedImage(g_tbhlp)
      b:setDisabledImage(g_tbhlg)
    elseif (GetPlayerData(GetThisPlayer(), "RaceName") == "zerg") then
      b:setNormalImage(g_zbhln)
      b:setPressedImage(g_zbhlp)
      b:setDisabledImage(g_zbhlg)
    else
      b:setNormalImage(g_pbhln)
      b:setPressedImage(g_pbhlp)
      b:setDisabledImage(g_pbhlg)
    end
    b:setSize(104, 28)
    return b
  end

  function menu:addHalfButton(caption, hotkey, x, y, callback)
    local b = self:addImageButton(caption, hotkey, x, y, callback)
    if (GetPlayerData(GetThisPlayer(), "RaceName") == "terran") then
      b:setNormalImage(g_tbhn)
      b:setPressedImage(g_tbhp)
      b:setDisabledImage(g_tbhg)
    elseif (GetPlayerData(GetThisPlayer(), "RaceName") == "zerg") then
      b:setNormalImage(g_zbhn)
      b:setPressedImage(g_zbhp)
      b:setDisabledImage(g_zbhg)
    else
      b:setNormalImage(g_pbhn)
      b:setPressedImage(g_pbhp)
      b:setDisabledImage(g_pbhg)
    end
    b:setSize(104, 28)
    return b
  end

  function menu:addHalfRightButton(caption, hotkey, x, y, callback)
    local b = self:addImageButton(caption, hotkey, x, y, callback)
    if (GetPlayerData(GetThisPlayer(), "RaceName") == "terran") then
      b:setNormalImage(g_tbhrn)
      b:setPressedImage(g_tbhrp)
      b:setDisabledImage(g_tbhrg)
    elseif (GetPlayerData(GetThisPlayer(), "RaceName") == "zerg") then
      b:setNormalImage(g_zbhrn)
      b:setPressedImage(g_zbhrp)
      b:setDisabledImage(g_zbhrg)
    else
      b:setNormalImage(g_pbhrn)
      b:setPressedImage(g_pbhrp)
      b:setDisabledImage(g_pbhrg)
    end
    b:setSize(104, 28)
    return b
  end

  function menu:addSlider(min, max, w, h, x, y, callback)
    local b = Slider(min, max)
    b:setBaseColor(dark)
    b:setForegroundColor(clear)
    b:setBackgroundColor(clear)
    b:setSize(w, h)
    b:setActionCallback(function(s) callback(b, s) end)
    self:add(b, x, y)
    return b
  end

  function menu:addListBox(x, y, w, h, list)
    local bq = ListBoxWidget(w, h)
    bq:setList(list)
    bq:setBaseColor(black)
    bq:setForegroundColor(clear)
    bq:setBackgroundColor(dark)
    bq:setFont(Fonts["game"])
    self:add(bq, x, y)   
    bq.itemslist = list
    return bq
  end

  function menu:addBrowser(path, filter, x, y, w, h, default)
    -- Create a list of all dirs and files in a directory
    local function listfiles(path)
      local dirlist = {}
      local i
      local f
      local u = 1

      local dirs = ListDirsInDirectory(path)
      for i,f in ipairs(dirs) do
        dirlist[u] = f .. "/"
        u = u + 1
      end

      local fileslist = ListFilesInDirectory(path)
      for i,f in ipairs(fileslist) do
        if (string.find(f, filter)) then
          dirlist[u] = f
          u = u + 1
        end
      end

      return dirlist
    end

    local bq = self:addListBox(x, y, w, h, {})
    bq.origpath = path
    bq.actioncb = nil

    -- The directory changed, update the list
    function bq:updateList()
      self.itemslist = listfiles(self.path)
      if (self.path ~= self.origpath) then
        table.insert(self.itemslist, 1, "../")
      end
      self:setList(self.itemslist)
    end

    -- Change to the default directory and select the default file
    if (default == nil) then
      bq.path = path
      bq:updateList()
    else
      local i
      for i=string.len(default)-1,1,-1 do
        if (string.sub(default, i, i) == "/") then
          bq.path = string.sub(default, 1, i)
          bq:updateList()

          local f = string.sub(default, i + 1)
          for i=1,table.getn(bq.itemslist) do
            if (bq.itemslist[i] == f) then
              bq:setSelected(i - 1)
            end
          end
          break
        end
      end
    end

    function bq:getSelectedItem()
      if (self:getSelected() < 0) then
        return self.itemslist[1]
      end
      return self.itemslist[self:getSelected() + 1]
    end

    -- If a directory was clicked change dirs
    -- Otherwise call the user's callback
    local function cb(s)
      local f = bq:getSelectedItem()
      if (f == "../") then
        local i
        for i=string.len(bq.path)-1,1,-1 do
          if (string.sub(bq.path, i, i) == "/") then
            bq.path = string.sub(bq.path, 1, i)
            bq:updateList()
            break
          end
        end
      elseif (string.sub(f, string.len(f)) == '/') then
        bq.path = bq.path .. f
        bq:updateList()
      else
        if (bq.actioncb ~= nil) then
          bq:actioncb(s)
        end
      end
    end
    bq:setActionCallback(cb)

    bq.oldSetActionCallback = bq.setActionCallback
    function bq:setActionCallback(cb)
      bq.actioncb = cb
    end

    return bq
  end

  function menu:addCheckBox(caption, x, y, callback)
    local b = CheckBox(caption)
    b:setBaseColor(clear)
    b:setForegroundColor(clear)
    b:setBackgroundColor(dark)
    b:setActionCallback(function(s) callback(b, s) end)
    b:setFont(Fonts["game"])
    self:add(b, x, y)
    return b
  end

  function menu:addRadioButton(caption, group, x, y, callback)
    local b = RadioButton(caption, group)
    b:setBaseColor(dark)
    b:setForegroundColor(clear)
    b:setBackgroundColor(dark)
    b:setActionCallback(callback)
    self:add(b, x, y)
    return b
  end

  function menu:addDropDown(list, x, y, callback)
    local dd = DropDownWidget()
    dd:setFont(Fonts["game"])
    dd:setList(list)
    dd:setActionCallback(function(s) callback(dd, s) end)
    dd:setBaseColor(dark)
    dd:setForegroundColor(clear)
    dd:setBackgroundColor(dark)
    self:add(dd, x, y)
    return dd
  end

  function menu:addTextInputField(text, x, y, w)
    local b = TextField(text)
    b:setActionCallback(function() end) --FIXME: remove this?
    b:setFont(Fonts["game"])
    b:setBaseColor(clear)
    b:setForegroundColor(clear)
    b:setBackgroundColor(dark)
    if (w == nil) then w = 100 end
    b:setSize(w, 18)
    self:add(b, x, y)
    return b
  end
end

function WarMenu(title, background, resize)
  local menu
  local exitButton
  local bg
  local bgg

  menu = MenuScreen()

  if background == nil then
    bg = backgroundWidget
  else
    bgg = CGraphic:New(background)
    bgg:Load()
    if (resize == nil or resize == true) then
      bgg:Resize(Video.Width, Video.Height)
    end
    bg = ImageWidget(bgg)
  end
  menu:add(bg, 0, 0)

  AddMenuHelpers(menu)

  if title then
    menu:addLabel(title, Video.Width / 2, Video.Height / 20, Fonts["large"])
  end

  return menu
end

-- Default configurations -------
Widget:setGlobalFont(Fonts["large"])


DefaultObjectives = {"-Destroy the enemy"}
Objectives = DefaultObjectives


-- Define the different menus ----------

function InitGameSettings()
  GameSettings.NetGameType = 1
  for i=0,PlayerMax-1 do
    GameSettings.Presets[i].Race = -1
    GameSettings.Presets[i].Team = -1
    GameSettings.Presets[i].Type = -1
  end
  GameSettings.Resources = -1
  GameSettings.NumUnits = -1
  GameSettings.Opponents = -1
  GameSettings.Terrain = -1
  GameSettings.GameType = -1
  GameSettings.NoFogOfWar = false
  GameSettings.RevealMap = 0
end
InitGameSettings()

function RunMap(map, objective, fow, revealmap)
  SetMusic(GetPlayerData(GetThisPlayer(), "RaceName"))
  if objective == nil then
    Objectives = DefaultObjectives
  else
    Objectives = objective
  end
  loop = true
  while (loop) do
    InitGameVariables()
    if fow ~= nil then
      SetFogOfWar(fow)
    end
    if revealmap == true then
       RevealMap()
    end
    StartMap(map)
    if GameResult ~= GameRestart then
      loop = false
    end
  end
  RunResultsMenu(s)

  InitGameSettings()
  SetPlayerData(GetThisPlayer(), "RaceName", "terran")
  SetMusic("menu")
end

mapname = "maps/\(2\)Space Madness.smp"
local mapinfo = {
  playertypes = {nil, nil, nil, nil, nil, nil, nil, nil},
  description = "",
  nplayers = 1,
  w = 32,
  h = 32,
  id = 0
}

function GetMapInfo(mapname)
  local OldDefinePlayerTypes = DefinePlayerTypes
  local OldPresentMap = PresentMap

  function DefinePlayerTypes(p1, p2, p3, p4, p5, p6, p7, p8)
    mapinfo.playertypes[1] = p1
    mapinfo.playertypes[2] = p2
    mapinfo.playertypes[3] = p3
    mapinfo.playertypes[4] = p4
    mapinfo.playertypes[5] = p5
    mapinfo.playertypes[6] = p6
    mapinfo.playertypes[7] = p7
    mapinfo.playertypes[8] = p8

    mapinfo.nplayers = 0
    for i=0,8 do
      local t = mapinfo.playertypes[i]
      if (t == "person" or t == "computer") then
        mapinfo.nplayers = mapinfo.nplayers + 1
      end
    end
  end

  function PresentMap(description, nplayers, w, h, id)
    mapinfo.description = description
    -- nplayers includes rescue-passive and rescue-active
    -- calculate the real nplayers in DefinePlayerTypes
    --mapinfo.nplayers = nplayers
    mapinfo.w = w
    mapinfo.h = h
    mapinfo.id = id
  end

  Load(mapname)

  DefinePlayerTypes = OldDefinePlayerTypes
  PresentMap = OldPresentMap
end

function RunSelectScenarioMenu()
  local menu = WarMenu(nil, panel("384x256"), false)
  menu:setSize(384, 256)
  menu:setPosition((Video.Width - 384) / 2, (Video.Height - 256) / 2)

  menu:addLabel("Select scenario", 384/2, 8)

  local browser = menu:addBrowser("maps/", "^.*%.smp%.?g?z?$",
    32, 44, 320, 160, mapname)

  menu:addFullLeftButton("~!OK", "o", 20, 216,
    function()
      if (browser:getSelected() < 0) then
        return
      end

      mapname = browser.path .. browser:getSelectedItem()
      menu:stop()
    end)
  menu:addHalfRightButton("~!Cancel", "c", 260, 216,
    function() menu:stop() end)

  menu:run()
end

function RunSinglePlayerGameMenu()
  local menu = WarMenu()
  local offx = (Video.Width - 640) / 2
  local offy = (Video.Height - 480) / 2
  local d
  local race
  local resources
  local opponents
  local numunits
  local gametype
  local mapl
  local descriptionl

  menu:addLabel("Scenario:", offx + 16, offy + 360, Fonts["game"], false)
  mapl = menu:addLabel(string.sub(mapname, 6), offx + 16, offy + 360 + 24, Fonts["game"], false)
  descriptionl = menu:addLabel("descriptionl", offx + 16 + 70, offy + 360, Fonts["game"], false)

  menu:addLabel("~<Single Player Game Setup~>", offx + 640/2 + 12, offy + 192)
  menu:addFullButton("S~!elect Scenario", "e", offx + 640 - 224 - 16, offy + 360 + 36*0,
    function()
      local oldmapname = mapname
      RunSelectScenarioMenu()
      if (mapname ~= oldmapname) then
        GetMapInfo(mapname)
        MapChanged()
      end
    end)
  menu:addFullButton("~!Start Game", "s", offx + 640 - 224 - 16, offy + 360 + 36*1,
    function()
      GameSettings.Presets[0].Race = race:getSelected()
      GameSettings.Resources = resources:getSelected()
      GameSettings.Opponents = opponents:getSelected()
      GameSettings.NumUnits = numunits:getSelected()
      GameSettings.GameType = gametype:getSelected() - 1
      RunMap(mapname)
      menu:stop()
    end)
  menu:addFullButton("~!Cancel Game", "c", offx + 640 - 224 - 16, offy + 360 + 36*2, function() menu:stop() end)

  menu:addLabel("~<Your Race:~>", offx + 40, offy + (10 + 240) - 20, Fonts["game"], false)
  race = menu:addDropDown({"Map Default", "Terran", "Zerg", "Protoss"}, offx + 40, offy + 10 + 240,
    function(dd) end)
  race:setSize(152, 20)

  menu:addLabel("~<Resources:~>", offx + 220, offy + (10 + 240) - 20, Fonts["game"], false)
  resources = menu:addDropDown({"Map Default", "Low", "Medium", "High"}, offx + 220, offy + 10 + 240,
    function(dd) end)
  resources:setSize(152, 20)

  menu:addLabel("~<Units:~>", offx + 640 - 224 - 16, offy + (10 + 240) - 20, Fonts["game"], false)
  numunits = menu:addDropDown({"Map Default", "One Peasant Only"}, offx + 640 - 224 - 16, offy + 10 + 240,
    function(dd) end)
  numunits:setSize(190, 20)

  local opponents_list = {"Map Default", "1 Opponent", "2 Opponents",
    "3 Opponents", "4 Opponents", "5 Opponents", "6 Opponents", "7 Opponents"}

  menu:addLabel("~<Opponents:~>", offx + 40, offy + (10 + 300) - 20, Fonts["game"], false)
  opponents = menu:addDropDown(opponents_list, offx + 40, offy + 10 + 300,
    function(dd) end)
  opponents:setSize(152, 20)

  menu:addLabel("~<Game Type:~>", offx + 220, offy + (10 + 300) - 20, Fonts["game"], false)
  gametype = menu:addDropDown({"Use map settings", "Melee", "Free for all", "Top vs bottom", "Left vs right", "Man vs Machine"}, offx + 220, offy + 10 + 300,
    function(dd) end)
  gametype:setSize(152, 20)

  function MapChanged()
    mapl:setCaption(string.sub(mapname, 6))
    mapl:adjustSize()

    descriptionl:setCaption(mapinfo.description ..
      " (" .. mapinfo.w .. " x " .. mapinfo.h .. ")")
    descriptionl:adjustSize()
 
    local o = {}
    for i=1,mapinfo.nplayers do
      table.insert(o, opponents_list[i])
    end
    opponents:setList(o)
  end

  GetMapInfo(mapname)
  MapChanged()

  menu:run()
end

function BuildProgramStartMenu()
  local menu = WarMenu()
  local offx = (Video.Width - 640) / 2
  local offy = (Video.Height - 480) / 2

  menu:addLabel(Name .. " V" .. Version .. "  " .. Homepage, offx + 320, offy + 426 + 18*0)
  menu:addLabel("Stratagus V" .. GetStratagusVersion() .. "  " .. GetStratagusHomepage(), offx + 320, offy + 426 + 18*1)
  menu:addLabel(Copyright, offx + 320, offy + 390 + 18*4)

  menu:addFullButton("~!Single Player Game", "s", offx + 208, offy + 104 + 36*0,
    function() RunSinglePlayerGameMenu(); menu:stop(1) end)
  menu:addFullButton("~!Multi Player Game", "m", offx + 208, offy + 104 + 36*1,
    function() RunMultiPlayerGameMenu(); menu:stop(1) end)
  menu:addFullButton("~!Campaign Game", "c", offx + 208, offy + 104 + 36*2,
    function() RunCampaignGameMenu(); menu:stop(1) end):setEnabled(false)
  menu:addFullButton("~!Load Game", "l", offx + 208, offy + 104 + 36*3,
    function() RunLoadGameMenu(); menu:stop(1) end)
  menu:addFullButton("~!Replay Game", "r", offx + 208, offy + 104 + 36*4,
    function() RunReplayGameMenu(); menu:stop(1) end)
  menu:addFullButton("~!Options", "o", offx + 208, offy + 104 + 36*5,
    function() RunOptionsMenu(); menu:stop(1) end)
  menu:addFullButton("S~!how Credits", "h", offx + 208, offy + 104 + 36*6, RunShowCreditsMenu)

  menu:addFullButton("E~!xit Program", "x", offx + 208, offy + 104 + 36*8,
    function() menu:stop() end)

  return menu:run()
end

LoadGameFile = nil

function RunProgramStartMenu()
  local continue = 1

  while continue == 1 do
    if (LoadGameFile ~= nil) then
      LoadGame(LoadGameFile)
    else
      continue = BuildProgramStartMenu(menu)
    end
  end
end


Load("scripts/menus/campaign.lua")
Load("scripts/menus/load.lua")
Load("scripts/menus/save.lua")
Load("scripts/menus/replay.lua")
Load("scripts/menus/options.lua")
Load("scripts/menus/credits.lua")
Load("scripts/menus/game.lua")
Load("scripts/menus/help.lua")
Load("scripts/menus/objectives.lua")
Load("scripts/menus/endscenario.lua")
Load("scripts/menus/diplomacy.lua")
Load("scripts/menus/results.lua")
Load("scripts/menus/network.lua")

if SetShader then
  SetShader("none")
end

RunProgramStartMenu()

