
subdir('kaitai')
subdir('dat')
subdir('tileset')

startool_sources = files(
	'startool.cpp'
)

startool_lib_sources = files(
	'Casc.cpp',
	'FileUtil.cpp',
	'Palette.cpp',
	'PngExporter.cpp',
	'Chk.cpp',
	'Font.cpp',
	'Grp.cpp',
	'Panel.cpp',
	'Preferences.cpp',
	'Widgets.cpp',
	'DataChunk.cpp',
	'Hurricane.cpp',
	'Pcx.cpp',
	'Scm.cpp',
	'Storm.cpp',
	'WorldMap.cpp',
	'Dds.cpp',
	'Breeze.cpp',
	'Smacker.cpp',
	'Converter.cpp',
	'KaitaiConverter.cpp',
	'Storage.cpp',
	'PaletteImage.cpp',
	'Color.cpp',
	'Wav.cpp',
	'Palette2D.cpp',
	'StringUtil.cpp',
	'luagen.cpp',
	'platform.cpp',
	'UIConsole.cpp',
	'pacman.cpp',
	'FileNotFoundException.cpp'
	)

stratagus_prefix = get_option('prefix')
stratagus_bin = get_option('STRATAGUS_BIN')

stratagus_includedir = get_option('STRATAGUS_INCLUDE_DIR')
stratagus_incdir = include_directories(stratagus_includedir)

add_project_arguments('-DDATA_PATH="' + stratagus_prefix + '/share/games/stratagus/stargus"', language: 'cpp')
add_project_arguments('-DSCRIPTS_PATH="' + stratagus_prefix + '/share/games/stratagus/stargus"', language: 'cpp')
add_project_arguments('-DSTRATAGUS_BIN="' + stratagus_bin + '"', language: 'cpp')
add_project_arguments('-DSOURCE_DIR="' + meson.current_source_dir() + '/../"', language: 'cpp')
add_project_arguments('-DKS_STR_ENCODING_NONE', language: 'cpp')

# inform about which stratagus binary is used
message('Using stratagus: ' + stratagus_bin)

stargus_sources = files('stargus.cpp')

executable('startool',
	startool_lib_sources,
	startool_sources,
	startool_kaitai_sources,
	startool_dat_sources,
	startool_tileset_sources,
	include_directories : config_incdir,
	dependencies : [casc_dep, storm_dep, zlib_dep, png_dep, imagemagickpp_dep, log4cxx_dep, bzip2_dep],
	install : true)

executable('stargus',
	stargus_sources,
	include_directories : [stratagus_incdir, config_incdir],
	install : true)
