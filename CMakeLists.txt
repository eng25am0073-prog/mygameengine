cmake_minimum_required(VERSION 3.20)

project(Engine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.5.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glfw)

add_library(glad STATIC vendor/glad/src/gl.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)

add_executable(engine
    src/main.cpp
    src/core/Application.cpp
    src/core/Input.cpp
    src/core/Log.cpp
    src/core/Window.cpp
    src/renderer/Shader.cpp
    src/renderer/VertexBuffer.cpp
    src/renderer/VertexArray.cpp
    src/renderer/BufferLayout.cpp
    src/renderer/Renderer.cpp
    src/sandbox/Game.cpp
)

target_include_directories(engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(engine PRIVATE glad glfw)

if(MSVC)
    target_compile_options(engine PRIVATE /W4 /permissive-)
    target_compile_options(glad PRIVATE /W3)
endif()