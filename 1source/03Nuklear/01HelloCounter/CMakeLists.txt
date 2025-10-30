cmake_minimum_required(VERSION 3.24)
project(NuklearApp)

include(FetchContent)

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
