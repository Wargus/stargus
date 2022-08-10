
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

  # needed internal dependencies to build the tests
  '../../src/Storm.cpp',
  '../../src/Breeze.cpp',
  '../../src/Hurricane.cpp',
  '../../src/DataChunk.cpp',
  '../../src/FileUtil.cpp',
  '../../src/Pcx.cpp',
  '../../src/PaletteImage.cpp',
  '../../src/Color.cpp',
  '../../src/Palette.cpp',
  '../../src/Palette2D.cpp',
  '../../src/PngExporter.cpp',
  '../../src/Converter.cpp',
  '../../src/Storage.cpp',
  '../../src/platform.cpp',
  '../../src/tileset/TiledPaletteImage.cpp',
  '../../src/luagen.cpp'
  )

executable('StartoolUnitTest',
			StartoolUnitTest_sources,
			include_directories : [StartoolUnitTest_incdir, config_incdir],
			dependencies : [cppunit_dep, log4cxx_dep, storm_dep, zlib_dep, png_dep, bzip2_dep],
			install : false)


