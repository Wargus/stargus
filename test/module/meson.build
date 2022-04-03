
StartoolUnitTest_incdir = include_directories('../../src')

StartoolUnitTest_sources = files(
  'TestMain.cpp',
  'StormTest.cpp',
  'DataChunkTest.cpp',
  'BreezeTest.cpp',
  
  # needed internal dependencies to build the tests
  '../../src/Storm.cpp',
  '../../src/Breeze.cpp',
  '../../src/Hurricane.cpp',
  '../../src/DataChunk.cpp',
  '../../src/FileUtil.cpp'  
  )

executable('StartoolUnitTest', 
			StartoolUnitTest_sources,
			include_directories : StartoolUnitTest_incdir,
			dependencies : [cppunit_dep, log4cxx_dep, storm_dep, zlib_dep],
			install : false)

	