if(${EXAMPLES_LINK_SFML_STATICALLY})
    set(BUILD_SHARED_LIBS OFF)
else()
    set(BUILD_SHARED_LIBS ON)
endif()
set(SFML_USE_STATIC_STD_LIBS ${EXAMPLES_LINK_SFML_STATICALLY})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git)
FetchContent_MakeAvailable(SFML)


add_executable(BasicMovement BasicMovement.cpp)
target_link_libraries(BasicMovement PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET BasicMovement PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(BasicMovement PRIVATE -static)
    endif()
endif()


add_executable(CenterText CenterText.cpp)
target_link_libraries(CenterText PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET CenterText PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(CenterText PRIVATE -static)
    endif()
endif()


add_executable(FadingDots FadingDots.cpp)
target_link_libraries(FadingDots PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET FadingDots PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(FadingDots PRIVATE -static)
    endif()
endif()


add_executable(Flashlight Flashlight.cpp)
target_link_libraries(Flashlight PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET Flashlight PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(Flashlight PRIVATE -static)
    endif()
endif()


add_executable(HueShift HueShift.cpp)
target_link_libraries(HueShift PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET HueShift PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(HueShift PRIVATE -static)
    endif()
endif()


add_executable(Lightning Lightning/main.cpp Lightning/Lightning.cpp Lightning/Lightning.hpp)
target_link_libraries(Lightning PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET Lightning PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(Lightning PRIVATE -static)
    endif()
endif()


add_executable(MixingSoundBuffers MixingSoundBuffers.cpp)
target_link_libraries(MixingSoundBuffers PRIVATE sfml-audio)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET MixingSoundBuffers PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(MixingSoundBuffers PRIVATE -static)
    endif()
endif()


add_executable(Road Road.cpp)
target_link_libraries(Road PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET Road PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(Road PRIVATE -static)
    endif()
endif()


add_executable(RotatingTriangle RotatingTriangle.cpp)
target_link_libraries(RotatingTriangle PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET RotatingTriangle PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(RotatingTriangle PRIVATE -static)
    endif()
endif()


add_executable(RotatingVertices RotatingVertices.cpp)
target_link_libraries(RotatingVertices PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET RotatingVertices PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(RotatingVertices PRIVATE -static)
    endif()
endif()


add_executable(SimpleAABB SimpleAABB.cpp)
target_link_libraries(SimpleAABB PRIVATE sfml-graphics)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET SimpleAABB PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(SimpleAABB PRIVATE -static)
    endif()
endif()


add_executable(SoundRecording SoundRecording.cpp)
target_link_libraries(SoundRecording PRIVATE sfml-audio)

if(WIN32 AND ${EXAMPLES_LINK_SFML_STATICALLY})
    if(MSVC)
        set_property(TARGET SoundRecording PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(SoundRecording PRIVATE -static)
    endif()
endif()


install(TARGETS BasicMovement
                CenterText
                FadingDots
                Flashlight
                HueShift
                Lightning
                MixingSoundBuffers
                Road
                RotatingTriangle
                RotatingVertices
                SimpleAABB
                SoundRecording
                RUNTIME DESTINATION .)

install(DIRECTORY Resources/ DESTINATION .)