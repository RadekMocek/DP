cmake_minimum_required(VERSION 3.8)

project(SampleProject)

find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(SampleProject "SampleProject.c")

target_include_directories(SampleProject PRIVATE
	${RAYGUI_INCLUDE_DIRS}	
)

target_link_libraries(SampleProject PRIVATE
	raylib
    glfw
)
