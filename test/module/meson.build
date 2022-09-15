
StartoolUnitTest_incdir = include_directories('../../src')

StartoolUnitTest_sources = files(
  'TestHelpers.cpp',
  'TestMain.cpp',
  'StormTest.cpp',
  'DataChunkTest.cpp',
  'BreezeTest.cpp',
  'PcxTest.cpp',
  'TiledPaletteImageTest.cpp',
  'luagenTest.cpp',
  )

executable('StartoolUnitTest',
			StartoolUnitTest_sources,
			include_directories : [StartoolUnitTest_incdir, config_incdir],
			dependencies : [cppunit_dep, zlib_dep, log4cxx_dep],
			link_with : libstartool,
			install : false)
