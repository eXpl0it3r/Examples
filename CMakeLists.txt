cmake_minimum_required(VERSION 3.15)

project(Examples)

OPTION(EXAMPLES_BUILD_SFML "Build all the SFML examples" ON)
OPTION(EXAMPLES_LINK_SFML_STATICALLY "Link SFML libraries statically" ON)

OPTION(EXAMPLES_BUILD_ZLIB "Build all the ZLIB examples" OFF)
OPTION(EXAMPLES_LINK_ZLIB_STATICALLY "Link ZLIB library statically" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
	OPTION(EXAMPLES_LINK_RUNTIME_STATICALLY "Link the runtime libraries statically" ON)
endif()

if(${EXAMPLES_BUILD_SFML})
	add_subdirectory(SFML)
endif()

if(${EXAMPLES_BUILD_ZLIB})
	add_subdirectory(zlib)
endif()
