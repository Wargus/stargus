project('stargus', 'cpp', 'c',
default_options : ['cpp_std=c++17'])

cpp = meson.get_compiler('cpp')

casc_dep = cpp.find_library('casc', required : false)
storm_dep = cpp.find_library('storm', required : false)
png_dep = cpp.find_library('png', required : true)
zlib_dep = dependency('zlib', required : false)
imagemagickpp_dep = dependency('ImageMagick++', required : false)

log4cxx_dep = dependency('liblog4cxx', required : false)
if log4cxx_dep.found()
  add_project_arguments('-DHAVE_LOG4CXX', language: 'cpp')
endif

if casc_dep.found()
	add_project_arguments('-DHAVE_CASC', language: 'cpp')
endif

if imagemagickpp_dep.found()
	add_project_arguments('-DHAVE_IMAGEMAGICKPP', language: 'cpp')
endif

cppunit_dep = dependency('cppunit', required : false)

subdir('src')
subdir('tools')

if cppunit_dep.found()
	subdir('test/module')
endif

