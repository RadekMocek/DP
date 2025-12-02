cmake_minimum_required(VERSION 3.12)

project(MicrouiApp)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_PARALLEL ON CACHE BOOL "" FORCE)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(MicrouiApp main.c microui.c renderer.c)

if(MSVC)
	target_compile_definitions(MicrouiApp PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_link_libraries(MicrouiApp PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    ${OPENGL_LIBRARIES}
)
