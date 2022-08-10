
LuaTest_incdir = include_directories('../../src')

LuaTest_sources = files(
  'CreateUnitLuaTest.cpp',
  'LuaTest.cpp',

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

executable('LuaTest',
			LuaTest_sources,
			include_directories : [LuaTest_incdir, config_incdir],
			dependencies : [log4cxx_dep, storm_dep, zlib_dep, png_dep, bzip2_dep],
			install : false)


