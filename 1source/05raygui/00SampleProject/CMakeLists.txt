cmake_minimum_required(VERSION 3.8)

project(SampleProject)

find_package(raylib CONFIG REQUIRED)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")

add_executable(SampleProject "SampleProject.c")

target_include_directories(SampleProject PRIVATE
	raylib
	${RAYGUI_INCLUDE_DIRS}	
)

target_link_libraries(SampleProject PRIVATE
	raylib	
)
