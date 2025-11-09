cmake_minimum_required(VERSION 3.25)

# FetchContent module allows us to download dependencies during the configuration
include(FetchContent)

# Project name is not the same as binary name
set(PROJECT_NAME "ImGuiProj")
set(BINARY_NAME "ImGuiApp")

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
set(IGG_COMPONENTS  "IMGUI" CACHE STRING "" FORCE)
set(IGG_GLAD_DOWNLOAD ON CACHE BOOL "" FORCE)
set(IGG_GLAD_GL_CORE ON CACHE BOOL "" FORCE)
set(IGG_GLAD_GL_VERSION "4.6" CACHE STRING "" FORCE)
set(IGG_IMGUI_TAG "v1.91.9b" CACHE STRING "" FORCE)
set(IGG_GLFW_TAG "3.3.10" CACHE STRING "" FORCE)
FetchContent_Declare(
    imgui-glfw-glad-glm
    GIT_REPOSITORY https://github.com/cmmw/imgui-glfw-glad-glm.git
    GIT_TAG e838972ee51d08c35ee8fbeaa98b1edc36722d58 # v4.2.0
)
FetchContent_MakeAvailable(imgui-glfw-glad-glm)

# Executable setup
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/App/*.cpp"    
)

add_executable("${BINARY_NAME}"
    "Run.cpp"
	${SOURCES}
)

if(MSVC)
	target_compile_definitions("${BINARY_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_link_libraries("${BINARY_NAME}"
    imgui
)

# Copy resources folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/App/Resources 
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/
)
