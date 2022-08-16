
TestDatafilesDat_incdir = include_directories('../../../src')

TestDatafilesDat_sources = files(
  'DatTest.cpp',
  )

executable('DatTest',
			TestDatafilesDat_sources,
			startool_lib_sources,
			startool_kaitai_sources,
			startool_dat_sources,
			startool_tileset_sources,
			include_directories : [StartoolUnitTest_incdir, config_incdir],
			dependencies : [cppunit_dep, casc_dep, storm_dep, zlib_dep, png_dep, imagemagickpp_dep, bzip2_dep, log4cxx_dep],
			install : false)
