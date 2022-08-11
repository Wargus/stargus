project('stargus', 'cpp', 'c',
default_options : ['cpp_std=c++17'])

cpp = meson.get_compiler('cpp')

# https://mesonbuild.com/Configuration.html
pkgdatadir = join_paths(get_option('datadir'), 'stargus')
conf = configuration_data()
conf.set_quoted('PACKAGE_DATA_DIR', join_paths(get_option('prefix'), pkgdatadir))
conf.set_quoted('PACKAGE_SOURCE_DIR', meson.current_build_dir())
configure_file(
  output: 'config.h',
  configuration: conf
)
config_incdir = include_directories('.')
add_project_arguments('-DHAVE_CONFIG_H', language: 'cpp')

# Install our json files
# https://mesonbuild.com/Installing.html
install_data(
	['dataset/palettes.json', 'dataset/units.json'],
	install_dir: get_option('datadir') / 'dataset'
)

casc_dep = cpp.find_library('casc', required : false)
storm_dep = cpp.find_library('storm', required : false)
png_dep = cpp.find_library('png', required : true)
bzip2_dep = cpp.find_library('bz2', required : true)
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
subdir('test/lua')

if cppunit_dep.found()
	subdir('test/module')
endif

subdir('test/datafiles/dat')
