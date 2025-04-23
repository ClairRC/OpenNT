cmake_minimum_required(VERSION 3.14)

# Going with this for now! :)
project(OpenNT)

# Sets C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get GLFW
include (FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.3.10
)

# Builds CMake target I think?? I need to do a deeper dive into this
FetchContent_MakeAvailable(glfw)

# Define source file paths
file(GLOB_RECURSE SRC_FILES 
	${PROJECT_SOURCE_DIR}/src/*.cpp
	${PROJECT_SOURCE_DIR}/lib/src/*
	${PROJECT_SOURCE_DIR}/main.cpp # Including this for now as a demo kinda deal
)

# Define library
add_executable(OpenNT ${SRC_FILES})

# Include directories
target_include_directories(OpenNT PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/include
)

# Links OpenGL and GLFW libraries
find_package(OpenGL REQUIRED)
target_link_libraries(OpenNT PUBLIC
    OpenGL::GL
    glfw
)

# Unit tests
file(GLOB_RECURSE SRC_TESTS
    ${PROJECT_SOURCE_DIR}/tests/*.cpp
)

file(GLOB_RECURSE SRC_TESTEES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
	${PROJECT_SOURCE_DIR}/lib/src/*
)

foreach(test_file ${SRC_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)

    # This adds ALL of the src files to the test executables.
    # I'm SURE there's a better way, but I don't know of any.
    # It should be fine though for how little these will need to be recompiled.
    add_executable(${test_name} ${test_file} ${SRC_TESTEES})

    set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

    # Include directories
    target_include_directories(${test_name} PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/lib/include
    )

    target_link_libraries(${test_name} PRIVATE OpenGL::GL glfw)
endforeach()
