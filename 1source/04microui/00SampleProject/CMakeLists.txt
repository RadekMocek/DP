cmake_minimum_required(VERSION 3.8)

project(SampleProject)

set(CMAKE_BUILD_TYPE Release)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(SampleProject main.c microui.c renderer.c)

if(MSVC)
	target_compile_definitions(SampleProject PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_link_libraries(SampleProject PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    ${OPENGL_LIBRARIES}
)
