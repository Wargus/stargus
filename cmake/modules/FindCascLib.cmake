# - Try to find the CascLib library
# Once done this will define
#
#  CASCLIB_FOUND - system has CascLib
#  CASCLIB_INCLUDE_DIR - the CASCLIB include directory
#  CASCLIB_LIBRARY - The CASCLIB library

# Copyright (c) 2015, cybermind <cybermindid@gmail.com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(CASCLIB_INCLUDE_DIR AND CASCLIB_LIBRARY AND (NOT UNIX OR BZIP2_FOUND))
	set(CASCLIB_FOUND true)
else()
	find_path(CASCLIB_INCLUDE_DIR CascLib.h)
	find_library(CASCLIB_LIBRARY NAMES casc)
	if (UNIX)
		find_package(BZip2)
	endif()

	if(CASCLIB_INCLUDE_DIR AND CASCLIB_LIBRARY AND (NOT UNIX OR BZIP2_FOUND))
		set(CASCLIB_FOUND true)
		message(STATUS "Found CascLib: ${CASCLIB_LIBRARY}")
	elseif(UNIX AND NOT BZIP2_FOUND)
		set(CASCLIB_FOUND false)
		message(STATUS "Could not find BZip2 required for CascLib")
	else()
		set(CASCLIB_FOUND false)
		message(STATUS "Could not find CascLib")
	endif()

	mark_as_advanced(CASCLIB_INCLUDE_DIR CASCLIB_LIBRARY)
endif()
