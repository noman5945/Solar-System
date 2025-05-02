# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.11)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(BUILD_ASSETS_DIR "${CMAKE_BINARY_DIR}/bin/assets")

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

# Copy shaders from source to build folder
file(COPY ${ASSETS_DIR}/shaders DESTINATION ${BUILD_ASSETS_DIR})


# Build executable
add_executable(SolarSystem ${SOURCES} "src/Shader.h" "src/Shader.cpp" "universe/Sphere/Sphere.cpp" "universe/CelestalBody/CelestalBody.h" "universe/CelestalBody/CelestalBody.cpp" "universe/Sphere/Sphere.h")
target_include_directories(SolarSystem PRIVATE ${CMAKE_SOURCE_DIR}/universe)


# Link libraries
find_package(OpenGL REQUIRED)
target_link_libraries(SolarSystem
    glfw
    OpenGL::GL
    glm::glm
)

