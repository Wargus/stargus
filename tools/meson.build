
iscript_sources = files('iscript.c')

json_transition_sources = files('json_transition.cpp')

executable('iscript', 
	iscript_sources,
	install : false)
	
executable('json_transition', 
	json_transition_sources,
	dependencies : [nlohmann_json_dep, png_dep],
	install : false)
