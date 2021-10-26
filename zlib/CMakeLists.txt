cmake_policy(SET CMP0074 NEW)
set(ZLIB_ROOT "" CACHE PATH "Path to where lib/zlib and include/zlib.h are located")
find_package(ZLIB REQUIRED)

add_executable(GzipDecompression GzipDecompression.cpp)
target_link_libraries(GzipDecompression PRIVATE ZLIB::ZLIB)

if(WIN32)
	if(MSVC)
		set_property(TARGET GzipDecompression PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		target_compile_options(GzipDecompression PRIVATE -static)
	endif()
endif()

install(TARGETS GzipDecompression RUNTIME DESTINATION .)