cmake_minimum_required(VERSION 3.25)
include(FetchContent)

project(NuklearApp)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_PARALLEL ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    nuklear
    GIT_REPOSITORY https://github.com/Immediate-Mode-UI/Nuklear.git
    GIT_TAG 242f35efa067a46c595645eeda7b1771ea1f83b1 # 4.12.8
)
FetchContent_MakeAvailable(nuklear)

find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(NuklearApp "NuklearApp.c")

if(MSVC)
	target_compile_definitions(NuklearApp PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_link_libraries(NuklearApp PRIVATE
	GLEW::GLEW
	glfw
)

target_include_directories(NuklearApp SYSTEM PRIVATE
    ${nuklear_SOURCE_DIR}	
    ${Stb_INCLUDE_DIR}
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/font
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
