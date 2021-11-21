cpp = meson.get_compiler('cpp')

startool_sources = files(
	'Casc.cpp', 'FileUtil.cpp',
	'Gfx.cpp',
	'Palettes.cpp',
	'Png.cpp', 
	'Tileset.cpp',
	'Chk.cpp',
	'Font.cpp',
	'Grp.cpp',
	'Panel.cpp',
	'Preferences.cpp',
	'startool.cpp',
	'Widgets.cpp',
	'DataChunk.cpp',
	'Gfu.cpp',
	'Hurricane.cpp',
	'Pcx.cpp',
	'Scm.cpp',
	'Storm.cpp',
	'WorldMap.cpp',
	'Dds.cpp',
	'Breeze.cpp',
	'Video.cpp',
	'Converter.cpp',
	'kaitai/kaitaistream.cpp',
	'kaitai/units_dat.cpp',
	'Units.cpp',
	'kaitai/weapons_dat.cpp',
	'Weapons.cpp'	
	)
	
stratagus_prefix = get_option('prefix')
stratagus_bin = get_option('STRATAGUS_BIN')

stratagus_includedir = get_option('STRATAGUS_INCLUDE_DIR')
stratagus_incdir = include_directories(stratagus_includedir)

add_project_arguments('-DDATA_PATH="' + stratagus_prefix + '/share/games/stratagus/stargus"', language: 'cpp')
add_project_arguments('-DSCRIPTS_PATH="' + stratagus_prefix + '/share/games/stratagus/stargus"', language: 'cpp')
add_project_arguments('-DSTRATAGUS_BIN=' + stratagus_bin, language: 'cpp')
add_project_arguments('-DSOURCE_DIR="' + meson.current_source_dir() + '/../"', language: 'cpp')
add_project_arguments('-DKS_STR_ENCODING_NONE', language: 'cpp')

# inform about which stratagus binary is used
message('Using stratagus: ' + stratagus_bin)

stargus_sources = files('stargus.cpp')

casc_dep = cpp.find_library('casc', required : false)
storm_dep = cpp.find_library('storm', required : false)
png_dep = cpp.find_library('png', required : true)
zlib_dep = dependency('zlib', required : false)
imagemagickpp_dep = dependency('ImageMagick++', required : false)

log4cxx_dep = dependency('liblog4cxx', required : false)
if log4cxx_dep.found()
  add_project_arguments('-DHAVE_LOG4CXX', language: 'cpp')
endif

cppunit_dep = [dependency('cppunit', required : false)]

executable('startool', 
	startool_sources,
	dependencies : [casc_dep, storm_dep, zlib_dep, png_dep, imagemagickpp_dep, log4cxx_dep, cppunit_dep],
	install : true)

executable('stargus', 
	stargus_sources,
	include_directories : stratagus_incdir,
	install : true)