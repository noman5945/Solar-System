# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.11)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include GLFW manually (from external folder)
include_directories(
    external/glad/include
    external/glfw/include
    src
)

# GLFW - manual subdirectory
add_subdirectory(external/glfw)

# GLM - FetchContent
include(FetchContent)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)
FetchContent_MakeAvailable(glm)

# Source files
file(GLOB SOURCES
    src/*.cpp
    external/glad/src/glad.c
)

# Build executable
add_executable(SolarSystem ${SOURCES})

# Link libraries
find_package(OpenGL REQUIRED)
target_link_libraries(SolarSystem
    glfw
    OpenGL::GL
    glm::glm
)

