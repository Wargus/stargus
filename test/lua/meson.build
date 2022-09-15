
LuaTest_incdir = include_directories('../../src')

LuaTest_sources = files(
  'CreateUnitLuaTest.cpp',
  'LuaTest.cpp'
  )

executable('LuaTest',
			LuaTest_sources,
			include_directories : [LuaTest_incdir, config_incdir],
			dependencies : [log4cxx_dep],
			link_with : libstartool,
			install : false)


