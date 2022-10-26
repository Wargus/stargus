
scdat2json_sources = files(
	'scdat2json.cpp',
	'SCJsonExporter.cpp',
	'UnitsJsonExporter.cpp',
	'to_json.cpp'
	)

executable('scdat2json', 
	scdat2json_sources,
	dependencies : [log4cxx_dep,libstarformat_dep],
	install : true)
	
