
TestDatafilesDat_incdir = include_directories('../../../src')

TestDatafilesDat_sources = files(
  'DatTest.cpp',
  )

executable('DatTest',
			TestDatafilesDat_sources,
			include_directories : [StartoolUnitTest_incdir, config_incdir],
			dependencies : [cppunit_dep, log4cxx_dep],
			link_with : libstartool,
			install : false)
