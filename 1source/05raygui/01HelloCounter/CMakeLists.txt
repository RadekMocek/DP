cmake_minimum_required(VERSION 3.10)

project(RayguiProject)

find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(RayguiProject "RayguiProject.c")

target_include_directories(RayguiProject PRIVATE
	${RAYGUI_INCLUDE_DIRS}	
)

target_link_libraries(RayguiProject PRIVATE
	raylib
    glfw
)
