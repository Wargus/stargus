project('stargus', 'cpp', 'c',
        default_options : ['cpp_std=c++17'])

cpp = meson.get_compiler('cpp')

# https://mesonbuild.com/Configuration.html
pkgdatadir = join_paths(get_option('datadir'), 'stargus')
conf = configuration_data()
conf.set_quoted('PACKAGE_DATA_DIR', join_paths(get_option('prefix'), pkgdatadir))
conf.set_quoted('PACKAGE_SOURCE_DIR', meson.current_source_dir())
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

nlohmann_json_dep = dependency('nlohmann_json', fallback : ['nlohmann_json', 'nlohmann_json_dep'])
casc_dep = cpp.find_library('casc', required : false)
storm_dep = dependency('storm', required : false)
if not storm_dep.found()
	cmake = import('cmake')
	storm_proj = cmake.subproject('StormLib')
	storm_dep = storm_proj.dependency('storm')
endif
zlib_dep = dependency('zlib', fallback: ['zlib', 'zlib_dep'])
png_dep = dependency('png', fallback: ['libpng', 'png_dep'])
bzip2_dep = dependency('bz2', required: false)
if not bzip2_dep.found()
	cmake = import('cmake')
	bzip2_proj = cmake.subproject('bzip2')
	bzip2_dep = bzip2_proj.dependency('bz2')
endif
imagemagickpp_dep = dependency('ImageMagick++', required : false)

if build_machine.system() == 'windows'
	cmake = import('cmake')
	win_iconv_proj = cmake.subproject('win-iconv')
	iconv_lib = win_iconv_proj.dependency('iconv-static')
else
	if cpp.has_function('iconv_open')
		iconv_lib = []
	elif cpp.has_header_symbol('iconv.h', 'iconv_open')
		iconv_lib = [cpp.find_library('iconv')]
	endif
endif

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
subdir('tools/sauwetter')
subdir('tools/scdat2json')
subdir('tools/grptool')
#subdir('tools/scpalette')
subdir('test/lua')

if cppunit_dep.found()
	subdir('test/module')
endif

#subdir('test/gamedata/dat')
