cmake_minimum_required(VERSION 3.14)

# Going with this for now! :)
project(OpenNT)

# Sets C++ version Stuff
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