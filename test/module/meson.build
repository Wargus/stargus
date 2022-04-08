
StartoolUnitTest_incdir = include_directories('../../src')

StartoolUnitTest_sources = files(
  'TestHelpers.cpp',
  'TestMain.cpp',
  'StormTest.cpp',
  'DataChunkTest.cpp',
  'BreezeTest.cpp',
  'PcxTest.cpp',
  
  # needed internal dependencies to build the tests
  '../../src/Storm.cpp',
  '../../src/Breeze.cpp',
  '../../src/Hurricane.cpp',
  '../../src/DataChunk.cpp',
  '../../src/FileUtil.cpp',
  '../../src/Pcx.cpp',
  '../../src/PaletteImage.cpp',
  '../../src/RGBColor.cpp',
  '../../src/Palette.cpp',
  '../../src/Png.cpp',
  '../../src/Converter.cpp',
  '../../src/Storage.cpp'
  )

executable('StartoolUnitTest', 
			StartoolUnitTest_sources,
			include_directories : StartoolUnitTest_incdir,
			dependencies : [cppunit_dep, log4cxx_dep, storm_dep, zlib_dep, png_dep],
			install : false)

	