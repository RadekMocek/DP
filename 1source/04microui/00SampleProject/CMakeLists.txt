cmake_minimum_required(VERSION 3.8)

project(SampleProject)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(SampleProject main.c microui.c renderer.c)

target_link_libraries(SampleProject PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    ${OPENGL_LIBRARIES}
)
