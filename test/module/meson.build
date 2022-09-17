
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
			include_directories : [config_incdir],
			dependencies : [cppunit_dep, zlib_dep, log4cxx_dep, libstarformat_dep],
			install : false)
