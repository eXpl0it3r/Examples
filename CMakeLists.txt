cmake_minimum_required(VERSION 3.1)

project(Examples)

OPTION(EXAMPLES_BUILD_SFML "Build all the SFML examples" ON)
OPTION(EXAMPLES_LINK_SFML_STATICALLY "Link SFML libraries statically" ON)

OPTION(EXAMPLES_BUILD_ZLIB "Build all the ZLIB examples" OFF)
OPTION(EXAMPLES_LINK_ZLIB_STATICALLY "Link ZLIB library statically" ON)

set (CMAKE_CXX_STANDARD 17)

if(${EXAMPLES_BUILD_SFML})
	set(SFML_DIR "" CACHE PATH "Path to where SFMLConfig.cmake is located")
	set(SFML_STATIC_LIBRARIES ${EXAMPLES_LINK_SFML_STATICALLY})
	find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

	add_executable(BasicMovement SFML/BasicMovement.cpp)
	target_link_libraries(BasicMovement PRIVATE sfml-graphics)

	add_executable(FadingDots SFML/FadingDots.cpp)
	target_link_libraries(FadingDots PRIVATE sfml-graphics)

	add_executable(Flashlight SFML/Flashlight.cpp)
	target_link_libraries(Flashlight PRIVATE sfml-graphics)

	add_executable(HueShift SFML/HueShift.cpp)
	target_link_libraries(HueShift PRIVATE sfml-graphics)

	add_executable(Lightning SFML/Lightning/main.cpp SFML/Lightning/Lightning.cpp SFML/Lightning/Lightning.hpp)
	target_link_libraries(Lightning PRIVATE sfml-graphics)

	add_executable(MixingSoundBuffers SFML/MixingSoundBuffers.cpp)
	target_link_libraries(MixingSoundBuffers PRIVATE sfml-audio)

	add_executable(Road SFML/Road.cpp)
	target_link_libraries(Road PRIVATE sfml-graphics)

	add_executable(RotatingTriangle SFML/RotatingTriangle.cpp)
	target_link_libraries(RotatingTriangle PRIVATE sfml-graphics)

	add_executable(RotatingVertices SFML/RotatingVertices.cpp)
	target_link_libraries(RotatingVertices PRIVATE sfml-graphics)

	add_executable(SimpleAABB SFML/SimpleAABB.cpp)
	target_link_libraries(SimpleAABB PRIVATE sfml-graphics)
endif()

if(${EXAMPLES_BUILD_ZLIB})
	cmake_policy(SET CMP0074 NEW)
	set(ZLIB_ROOT "" CACHE PATH "Path to where lib/zlib and include/zlib.h are located")
	#set(SFML_STATIC_LIBRARIES ${EXAMPLES_LINK_ZLIB_STATICALLY})
	find_package(ZLIB REQUIRED)

	add_executable(GzipDecompression zlib/GzipDecompression.cpp)
	target_link_libraries(GzipDecompression PRIVATE ZLIB::ZLIB)
endif()

if(WIN32)
	OPTION(EXAMPLES_LINK_RUNTIME_STATICALLY "Link the runtime libraries statically" ON)

	if(${EXAMPLES_LINK_RUNTIME_STATICALLY} AND MSVC)
		# Link against the static runtime library
		foreach(flag
				CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
				CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			if(${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
endif()
