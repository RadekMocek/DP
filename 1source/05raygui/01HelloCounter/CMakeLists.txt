cmake_minimum_required(VERSION 3.12)

project(RayguiApp)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_PARALLEL ON CACHE BOOL "" FORCE)

find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(RayguiApp "RayguiApp.c")

if(MSVC)
	target_compile_definitions(RayguiApp PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_include_directories(RayguiApp PRIVATE
	${RAYGUI_INCLUDE_DIRS}	
)

target_link_libraries(RayguiApp PRIVATE
	raylib
    glfw
)
