#       _________ __                 __
#      /   _____//  |_____________ _/  |______     ____  __ __  ______
#      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
#      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
#     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
#             \/                  \/          \//_____/            \/
#  ______________________                           ______________________
#                        T H E   W A R   B E G I N S
#         Stratagus - A free fantasy real time strategy game engine
#
#    CMakeLists.txt
#    Copyright (C) 2011-2012  Pali Rohár <pali.rohar@gmail.com>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#

project(stargus)
cmake_minimum_required(VERSION 2.6)
set(STARGUS_VERSION 2.2.6)

# Stargus sources

set(scmconvert_SRCS
	mpq.cpp
	scm.cpp
	huff.cpp
)

set(scmconvert_HDRS
	mpq.h
	huff.h
)

set(startool_SRCS
	startool.cpp
	mpq.cpp
	scm.cpp
	huff.cpp
)

set(startool_HDRS
	mpq.h
	huff.h
)

set(stargus_SRCS
	stargus.cpp
)

if(WIN32)
	set(stargus_SRCS
		${stargus_SRCS}
		stargus.rc
	)
endif()

set(starextract_SRCS
	starextract.c
)

# Additional platform checks

find_package(PkgConfig QUIET REQUIRED)

# Check if platform is Maemo
if(UNIX AND CMAKE_SYSTEM_NAME MATCHES Linux)
	pkg_check_modules(MAEMO_VERSION maemo-version)
	if(MAEMO_VERSION_FOUND)
		set(MAEMO true)
	endif()
endif()

# Find all libraries

option(ENABLE_STATIC "Compile Stargus binaries as static executable" OFF)

if(ENABLE_STATIC)
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.a")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

find_package(Stratagus REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

if(WIN32)
	find_package(MakeNSIS)
endif()

if(NOT WIN32)
	find_package(X11 REQUIRED)
	find_package(GTK2 REQUIRED gtk)
endif()

if(MAEMO)
	pkg_check_modules(HILDON REQUIRED hildon-1)
endif()

find_package(SelfPackers)

# Windows RC compiler definitions

if(WIN32)
	enable_language(RC)
	include(CMakeDetermineRCCompiler)

	if(MINGW)
		set(CMAKE_RC_COMPILER_INIT windres)
		set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
	endif()
endif()

# Options for compiling

if(WIN32)
	option(ENABLE_NSIS "Create Stratagus Window NSIS Installer" OFF)
endif()

option(ENABLE_UPX "Compress Stratagus executable binary with UPX packer" OFF)
option(ENABLE_STRIP "Strip all symbols from executables" OFF)

# Stargus definitions

add_definitions(${PNG_DEFINITIONS})
include_directories(${PNG_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS} ${STRATAGUS_INCLUDE_DIR})
set(scmconvert_LIBS ${scmconvert_LIBS} ${ZLIB_LIBRARIES})
set(startool_LIBS ${scmconvert_LIBS} ${PNG_LIBRARIES} ${ZLIB_LIBRARIES})

# Platform definitions

if(NOT WIN32)
	include_directories(${X11_INCLUDE_DIR} ${GTK2_INCLUDE_DIRS})
	set(stargus_LIBS ${stargus_LIBS} ${X11_X11_LIB} ${GTK2_LIBRARIES})
endif()

if (NOT WIN32 AND NOT MAEMO)
	add_definitions(-DDATA_PATH="${CMAKE_INSTALL_PREFIX}/share/games/stratagus/stargus")
	add_definitions(-DSCRIPTS_PATH="${CMAKE_INSTALL_PREFIX}/share/games/stratagus/stargus")
	add_definitions(-DSTRATAGUS_BIN="${STRATAGUS}")
endif()

if(MAEMO)
	add_definitions(-DDATA_PATH="/home/user/MyDocs/stratagus/stargus")
	add_definitions(-DSCRIPTS_PATH="/opt/stratagus/share/stargus")
	add_definitions(-DSTRATAGUS_BIN="/opt/stratagus/bin/stratagus")
	add_definitions(${HILDON_CFLAGS})
	include_directories(${HILDON_INCLUDE_DIRS})
	set(stargus_LIBS ${stargus_LIBS} ${HILDON_LIBRARIES})
	set(starextract_LIBS ${starextract_LIBS} ${GTK2_LIBRARIES} ${HILDON_LIBRARIES})
endif()

if(ENABLE_STRIP)
	set(CMAKE_EXE_LINKER_FLAGS "-s")
else()
	set(CMAKE_EXE_LINKER_FLAGS "")
endif()

# Compile Stargus

add_executable(scmconvert ${scmconvert_SRCS} ${scmconvert_HDRS})
target_link_libraries(scmconvert ${scmconvert_LIBS})
set_target_properties(scmconvert PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")

if(MAEMO)
	add_executable(starextract ${starextract_SRCS} ${starextract_HDRS})
	target_link_libraries(starextract ${starextract_LIBS})
endif()

add_executable(stargus ${stargus_SRCS} ${stargus_HDRS})
target_link_libraries(stargus ${stargus_LIBS})

add_executable(startool ${startool_SRCS} ${startool_HDRS})
target_link_libraries(startool ${startool_LIBS})

if(WIN32 AND MINGW AND ENABLE_STATIC)
	set_target_properties(scmconvert PROPERTIES LINK_FLAGS "${LINK_FLAGS} -static-libgcc")
	set_target_properties(stargus PROPERTIES LINK_FLAGS "${LINK_FLAGS} -static-libgcc")
	set_target_properties(startool PROPERTIES LINK_FLAGS "${LINK_FLAGS} -static-libgcc")
endif()

########### next target ###############

macro(self_packer PACKER_TARGET)
	get_target_property(PACKER_NAME ${PACKER_TARGET} OUTPUT_NAME)
	if(NOT PACKER_NAME)
		set(PACKER_NAME ${PACKER_TARGET})
	endif()
	add_custom_command(TARGET ${PACKER_TARGET} POST_BUILD
		COMMAND ${SELF_PACKER_FOR_EXECUTABLE}
		ARGS ${SELF_PACKER_FOR_EXECUTABLE_FLAGS} ${PACKER_NAME}${CMAKE_EXECUTABLE_SUFFIX}
	)
endmacro()

if(ENABLE_UPX AND SELF_PACKER_FOR_EXECUTABLE)
	self_packer(scmconvert)
	self_packer(stargus)
	self_packer(startool)
endif()

########### next target ###############

if(WIN32 AND ENABLE_NSIS AND MAKENSIS_FOUND)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/COPYING DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stargus.ico DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	add_custom_command(OUTPUT Stargus-${STARGUS_VERSION}${MAKENSIS_SUFFIX}
		COMMAND ${MAKENSIS}
		ARGS ${MAKENSIS_FLAGS} -DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}" -DCMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/stargus.nsi
		DEPENDS stargus.nsi scmconvert stargus startool COPYING stargus.ico
		COMMENT "Generating Stargus Windows NSIS Installer" VERBATIM
	)
	add_custom_target(nsis ALL DEPENDS Stargus-${STARGUS_VERSION}${MAKENSIS_SUFFIX})
endif()

########### install files ###############

install(TARGETS stargus DESTINATION games)
install(TARGETS scmconvert startool DESTINATION bin)
install(FILES stargus.png DESTINATION share/pixmaps)
install(FILES stargus.desktop DESTINATION share/applications)

install(DIRECTORY scripts DESTINATION share/games/stratagus/stargus)
install(FILES mpqlist.txt DESTINATION share/games/stratagus/stargus)
install(FILES fog.png DESTINATION share/games/stratagus/stargus/graphics/tilesets)

if(MAEMO)
	install(TARGETS starextract DESTINATION bin)
endif()
