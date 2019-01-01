cmake_minimum_required(VERSION 3.9)
project(GPR5204)


if(UNIX)
    if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
        message(" * C++ compiler: Emscripten")
        set(CMAKE_CXX_COMPILER_ID "Emscripten")
    else()
        message(" * C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
endif()

SET(BENCHMARK_ENABLE_TESTING OFF CACHE STRING "Description")

#Adding google Benchmark
add_subdirectory(benchmark)
include_directories(benchmark/include)

#Adding ctpl
include_directories(CTPL/)

if(NOT EMSCRIPTEN)
#adding sdl
set(SDL_DIR "SDL2-2.0.9")
add_subdirectory(${SDL_DIR})
include_directories(${SDL_DIR}/include)

#adding SFML
SET(BUILD_SHARED_LIBS OFF CACHE STRING "Description")
set(SFML_DIR "SFML-2.5.1")
set(SFML_BUILD_EXAMPLES FALSE)
add_subdirectory(${SFML_DIR})
include_directories(${SFML_DIR}/include ${SFML_DIR}/src ${SFML_DIR}/extlibs/headers)
endif()
#source files
include_directories(include/)
file(GLOB_RECURSE SRC_FILES src/*.cpp)


SET(COURSE_DIR ${CMAKE_SOURCE_DIR}/tests)
file(GLOB COURSE_FILES ${COURSE_DIR}/*.cpp )

foreach(course_file ${COURSE_FILES} )
    # I used a simple string replace, to cut off .cpp.
    file(RELATIVE_PATH course_relative_path ${COURSE_DIR} ${course_file})
    string( REPLACE ".cpp" "" course_name ${course_relative_path} )
    add_executable(${course_name} ${course_file} ${SRC_FILES} src/job_system.cpp include/job_system.h include/misc.h)
    # Make sure YourLib is linked to each app
    target_link_libraries(${course_name} PUBLIC benchmark)
    set_property(TARGET ${course_name} PROPERTY CXX_STANDARD 17)

    IF(UNIX)
        set_target_properties(${course_name} PROPERTIES COMPILE_FLAGS "-save-temps -march=native")
    ENDIF(UNIX)
    set_target_properties (${course_name} PROPERTIES
        FOLDER Courses)
    IF(APPLE)
        set_target_properties(${course_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
                RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
    ENDIF()
endforeach()
if(NOT EMSCRIPTEN)
SET(COURSE_GRAPHICS_DIR ${CMAKE_SOURCE_DIR}/tests_graphics)
file(GLOB COURSE_GRAPHICS_FILES ${COURSE_GRAPHICS_DIR}/*.cpp )
foreach(course_file ${COURSE_GRAPHICS_FILES} )
    # I used a simple string replace, to cut off .cpp.
    file(RELATIVE_PATH course_relative_path ${COURSE_GRAPHICS_DIR} ${course_file})
    string( REPLACE ".cpp" "" course_name ${course_relative_path} )
    add_executable(${course_name} ${course_file} ${SRC_FILES} src/job_system.cpp include/job_system.h include/misc.h)
    # Make sure YourLib is linked to each app
    target_link_libraries(${course_name} PUBLIC benchmark SDL2-static SDL2main sfml-system
            sfml-window
            sfml-graphics
            sfml-audio
            sfml-network)
    set_property(TARGET ${course_name} PROPERTY CXX_STANDARD 17)
    IF(UNIX)
        set_target_properties(${course_name} PROPERTIES COMPILE_FLAGS "-save-temps -march=native -ffast-math")
    ENDIF(UNIX)
    set_target_properties (${course_name} PROPERTIES
            FOLDER Courses)
    IF(APPLE)
        set_target_properties(${course_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
                RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
    ENDIF()
endforeach()

file(COPY data/ DESTINATION ${CMAKE_BINARY_DIR}/data/)
endif()
