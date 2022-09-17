TestDatafilesDat_sources = files(
  'DatTest.cpp',
  )

executable('DatTest',
			TestDatafilesDat_sources,
			include_directories : [config_incdir],
			dependencies : [cppunit_dep, log4cxx_dep, libstarformat_dep],
			install : false)
