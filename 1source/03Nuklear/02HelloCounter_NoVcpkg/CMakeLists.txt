cmake_minimum_required(VERSION 3.25)

# FetchContent module allows us to download dependencies during the configuration
include(FetchContent)

# Project name is not the same as binary name
set(PROJECT_NAME "NuklearProj")
set(BINARY_NAME "NuklearApp")

# Project setup
project("${PROJECT_NAME}")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

# Build only the necessary parts of GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Configure, fetch and use 'imgui-glfw-glad-glm' by 'cmmw' <3
set(IGG_COMPONENTS  "GLFW;GLAD" CACHE STRING "" FORCE)
set(IGG_GLAD_DOWNLOAD ON CACHE BOOL "" FORCE)
set(IGG_GLAD_GL_CORE ON CACHE BOOL "" FORCE)
set(IGG_GLAD_GL_VERSION "3.3" CACHE STRING "" FORCE)
set(IGG_GLFW_TAG "3.3.10" CACHE STRING "" FORCE)
FetchContent_Declare(
    imgui-glfw-glad-glm
    GIT_REPOSITORY https://github.com/cmmw/imgui-glfw-glad-glm.git
    GIT_TAG e838972ee51d08c35ee8fbeaa98b1edc36722d58 # v4.2.0
)
FetchContent_MakeAvailable(imgui-glfw-glad-glm)

# Fetch Nuklear
FetchContent_Declare(
    nuklear
    GIT_REPOSITORY https://github.com/Immediate-Mode-UI/Nuklear.git
    GIT_TAG 242f35efa067a46c595645eeda7b1771ea1f83b1 # 4.12.8
)
FetchContent_MakeAvailable(nuklear)

# Fetch stb
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(stb)
add_library(stb INTERFACE ${stb_SOURCE_DIR}/stb_image.h)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})

# Executable setup
add_executable("${BINARY_NAME}"
    "NuklearApp.c"
)

if(MSVC)
	target_compile_definitions("${BINARY_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_link_libraries("${BINARY_NAME}"
    glfw
    glad
    stb
)

target_include_directories("${BINARY_NAME}" SYSTEM PRIVATE
    ${nuklear_SOURCE_DIR}	
)

# Copy font folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/font
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
