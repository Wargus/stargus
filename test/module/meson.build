
StartoolUnitTest_incdir = include_directories('../../src')

StartoolUnitTest_sources = files(
  'TestMain.cpp',
  'StormTest.cpp',
  '../../src/Storm.cpp',
  '../../src/Hurricane.cpp',
  '../../src/DataChunk.cpp',
  '../../src/FileUtil.cpp'
  )

cppunit_dep = [dependency('cppunit', required : false)]

executable('StartoolUnitTest', 
			StartoolUnitTest_sources,
			include_directories : StartoolUnitTest_incdir,
			dependencies : [cppunit_dep, log4cxx_dep, storm_dep, zlib_dep],
			install : false)

	