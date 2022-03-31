
StartoolUnitTest_sources = files(
  'TestMain.cpp',
  'StormTest.cpp'
  )

cppunit_dep = [dependency('cppunit', required : false)]

executable('StartoolUnitTest', 
	StartoolUnitTest_sources,
	dependencies : [cppunit_dep, log4cxx_dep],
	install : false)
