cmake_minimum_required(VERSION 3.9)
project(GPR5204)

SET(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE STRING "Description")

add_subdirectory(benchmark)
include_directories(benchmark/include)


SET(COURSE_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB COURSE_FILES ${COURSE_DIR}/*.cpp )
foreach(course_file ${COURSE_FILES} )
    # I used a simple string replace, to cut off .cpp.
    file(RELATIVE_PATH course_relative_path ${COURSE_DIR} ${course_file})
    string( REPLACE ".cpp" "" course_name ${course_relative_path} )
    add_executable(${course_name} ${COURSE_DIR}/${course_relative_path})
    # Make sure YourLib is linked to each app
    target_link_libraries(${course_name} PUBLIC benchmark)
    set_property(TARGET ${course_name} PROPERTY CXX_STANDARD 17)
    IF(UNIX)
        set_target_properties(${course_name} PROPERTIES COMPILE_FLAGS "-save-temps")
    ENDIF(UNIX)
    set_target_properties (${course_name} PROPERTIES
            FOLDER Courses)
    IF(APPLE)
        set_target_properties(${course_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
                RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
    ENDIF()
endforeach()
