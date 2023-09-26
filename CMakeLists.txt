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

# Project setup

project(stargus)
cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10..3.20.2)
set(STARGUS_VERSION 2.4.1)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# CMake setup

if(WIN32 AND MSVC)
  if(EXISTS ${WIN32_CMAKE_PREFIX_PATH})
    list(APPEND CMAKE_PREFIX_PATH "${WIN32_CMAKE_PREFIX_PATH}")
    message("Using prefix path ${CMAKE_PREFIX_PATH}")
  endif()
  if (NOT CMAKE_PREFIX_PATH)
    # use a default
    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies)
  endif()
endif()

# Stargus sources

set(scmconvert_SRCS
	Storm.cpp
	scm.cpp
	FileUtil.cpp
)

set(scmconvert_HDRS
	Storm.h
	FileUtil.h
)

file(GLOB startool_SRCS
	src/*.cpp
	src/kaitai/*.cpp
	src/dat/*.cpp
	src/tileset/*.cpp
)

file(GLOB startool_HDRS
	src/*.h
	src/kaitai/*.h
	src/dat/*.h
	src/tileset/*.h
)

file(GLOB stargus_SRCS
	src/stargus.cpp
)

list(REMOVE_ITEM startool_SRCS "${stargus_SRCS}")

if(WIN32)
	set(stargus_SRCS
		${stargus_SRCS}
		stargus.rc
	)
endif()

# Find all libraries

find_package(Stratagus REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(StormLib REQUIRED)
find_package(CascLib)

if(WIN32)
	find_package(MakeNSIS)
endif()

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

option(WITH_CASCLIB "Compile startool with CascLib support" ON)

# General definitions and compilation settings

add_definitions(${PNG_DEFINITIONS})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../")
add_definitions(-DKS_STR_ENCODING_NONE)
add_definitions(-DUSE_STORMLIB -D__STORMLIB_SELF__)

include_directories(${PNG_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS} ${STORMLIB_INCLUDE_DIR} src)

set(scmconvert_LIBS ${scmconvert_LIBS} ${ZLIB_LIBRARIES} ${STORMLIB_LIBRARY} ${BZIP2_LIBRARIES})
set(startool_LIBS ${scmconvert_LIBS} ${PNG_LIBRARIES} ${ZLIB_LIBRARIES} ${STORMLIB_LIBRARY} ${BZIP2_LIBRARIES})

# Platform specific definitions and compilation settings

add_subdirectory("third-party/nlohmann-json")
include_directories("third-party/nlohmann-json/include")
set(startool_LIBS ${startool_LIBS} ${NLOHMANN_JSON_TARGET_NAME})

if(WIN32 AND MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE=1 -D_HAS_STD_BYTE=0)
	add_subdirectory("third-party/win-iconv")
	include_directories("third-party/win-iconv")
	set(startool_LIBS ${startool_LIBS} iconv-static)
endif()

include(CheckCXXSourceCompiles)

set(FS_SRC "
#include <filesystem>
namespace fs = std::filesystem;
int main() {
	fs::path p = fs::path(\".\");
	if (fs::absolute(p).is_absolute()) {
		return 0;
	} else {
		return 1;
	}
}
")
check_cxx_source_compiles("${FS_SRC}" HAS_17_FS)

if(NOT HAS_17_FS) # Tr
	set(EXPERIMENTAL_FS_SRC "
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
	int main() {
		fs::path p = fs::path(\".\");
		if (fs::absolute(p).is_absolute()) {
			return 0;
		} else {
			return 1;
		}
	}
	")
	check_cxx_source_compiles("${EXPERIMENTAL_FS_SRC}" HAS_17_EXPERIMENTAL_FS)
	if(NOT HAS_17_EXPERIMENTAL_FS)
		set(CMAKE_REQUIRED_LIBRARIES stdc++fs)
		check_cxx_source_compiles("${EXPERIMENTAL_FS_SRC}" HAS_EXP_17_FS_WITH_STDC)
		if(HAS_EXP_17_FS_WITH_STDC)
			set(stargus_LIBS ${stargus_LIBS} stdc++fs)
			set(startool_LIBS ${startool_LIBS} stdc++fs)
		else()
			set(CMAKE_REQUIRED_LIBRARIES c++fs)
			check_cxx_source_compiles("${EXPERIMENTAL_FS_SRC}" HAS_EXP_17_FS_WITH_CLIB)
			if(HAS_EXP_17_FS_WITH_CLIB)
				set(stargus_LIBS ${stargus_LIBS} c++fs)
				set(startool_LIBS ${startool_LIBS} c++fs)
			else()
				message(FATAL_ERROR "I don't know how to compile with C++17 filesystem support on your system")
			endif()
		endif()
	endif()
endif()

########### startool ###############

set(BINDIR "bin" CACHE PATH "Where to install user binaries")

#add_executable(scmconvert ${scmconvert_SRCS} ${scmconvert_HDRS})
#target_link_libraries(scmconvert ${scmconvert_LIBS})
#set_target_properties(scmconvert PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
#install(TARGETS scmconvert DESTINATION ${BINDIR})

add_executable(startool ${startool_SRCS} ${startool_HDRS})
target_link_libraries(startool ${startool_LIBS})
install(TARGETS startool DESTINATION ${BINDIR})

########### stargus launcher and installer ###############

if(STRATAGUS_FOUND)
  include_directories(${STRATAGUS_INCLUDE_DIR})

  set(GAMEDIR "games" CACHE PATH "Where to install games binaries")
  set(SHAREDIR "share/games/stratagus/stargus" CACHE PATH "Where to install data files")
  set(DATAROOTDIR "${CMAKE_INSTALL_PREFIX}/share" CACHE PATH "Sets the root of data directories to a non-default location")
  set(ICONDIR "${DATAROOTDIR}/pixmaps" CACHE PATH "Sets the icon directory for desktop entry to a non-default location.")
  set(DESKTOPDIR "${DATAROOTDIR}/applications" CACHE PATH "Sets the desktop file directory for desktop entry to a non-default location.")
  if(NOT IS_ABSOLUTE "${GAMEDIR}")
    set(GAMEDIRABS "${CMAKE_INSTALL_PREFIX}/${GAMEDIR}")
  else()
    set(GAMEDIRABS "${GAMEDIR}")
  endif()
  if(NOT IS_ABSOLUTE "${SHAREDIR}")
    set(DATA_PATH "${CMAKE_INSTALL_PREFIX}/${SHAREDIR}")
  else()
    set(DATA_PATH "${SHAREDIR}")
  endif()

  if (NOT WIN32)
    add_definitions(-DDATA_PATH="${DATA_PATH}")
    add_definitions(-DSCRIPTS_PATH="${DATA_PATH}")
    add_definitions(-DSTRATAGUS_BIN="${STRATAGUS}")
    configure_file (
      "${PROJECT_SOURCE_DIR}/stargus.desktop.in"
      "${PROJECT_BINARY_DIR}/stargus.desktop"
    )
    add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/stargus.png"
      COMMAND convert
      ARGS "${PROJECT_SOURCE_DIR}/stargus.ico" "${PROJECT_BINARY_DIR}/stargus.png"
      DEPENDS stargus.ico
      COMMENT "Generating stargus.png" VERBATIM
    )
    add_custom_target(icon ALL DEPENDS stargus.png)
    install(FILES
      "${PROJECT_BINARY_DIR}/stargus.png"
      "${CMAKE_CURRENT_SOURCE_DIR}/dataset/palettes.json"
      "${CMAKE_CURRENT_SOURCE_DIR}/dataset/units.json"
      DESTINATION ${ICONDIR}
    )
    add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/stargus.xpm"
      COMMAND convert
      ARGS "${PROJECT_SOURCE_DIR}/stargus.ico" -resize 32x32 "${PROJECT_BINARY_DIR}/stargus.xpm"
      DEPENDS stargus.ico
      COMMENT "Generating stargus.xmp" VERBATIM
    )
    add_custom_target(xpmicon ALL DEPENDS stargus.xpm)
    install(FILES "${PROJECT_BINARY_DIR}/stargus.xpm" DESTINATION ${ICONDIR})
    install(FILES "${PROJECT_BINARY_DIR}/stargus.desktop" DESTINATION ${DESKTOPDIR})
    install(DIRECTORY campaigns contrib maps scripts shaders DESTINATION ${SHAREDIR})
	install(FILES mpqlist.txt DESTINATION ${SHAREDIR})
  elseif (WIN32)
    if(ENABLE_NSIS AND MAKENSIS_FOUND)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/COPYING DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stargus.ico DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mpqlist.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
      add_custom_target(nsis ALL
        COMMAND ${MAKENSIS} ${MAKENSIS_FLAGS} -DPORTABLE=1 -DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}" -DCMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/stargus.nsi
        COMMAND ${MAKENSIS} ${MAKENSIS_FLAGS} -DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}" -DCMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}" ${CMAKE_CURRENT_SOURCE_DIR}/stargus.nsi
        DEPENDS stargus.nsi stargus startool COPYING mpqlist.txt stargus.ico
        COMMENT "Generating stargus Windows NSIS Installers" VERBATIM
        SOURCES stargus.nsi)
    endif()
  endif()

  add_executable(stargus WIN32 ${stargus_SRCS})
  target_link_libraries(stargus ${stargus_LIBS})
  set(GAMEDIR "games" CACHE PATH "Where to install games binaries")
  install(TARGETS stargus DESTINATION ${GAMEDIR})
endif()

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
