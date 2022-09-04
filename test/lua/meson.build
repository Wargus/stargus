
LuaTest_incdir = include_directories('../../src')

LuaTest_sources = files(
  'CreateUnitLuaTest.cpp',
  'LuaTest.cpp'
  )

executable('LuaTest',
			LuaTest_sources,
			startool_lib_sources,
			startool_kaitai_sources,
			startool_dat_sources,
			startool_tileset_sources,
			include_directories : [LuaTest_incdir, config_incdir],
			dependencies : [casc_dep, storm_dep, zlib_dep, png_dep, imagemagickpp_dep, bzip2_dep, log4cxx_dep],
			install : false)


