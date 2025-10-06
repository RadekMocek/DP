cmake_minimum_required(VERSION 3.8)

project(SampleProject)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/App/*.cpp"
)

add_executable(SampleProject
	"SampleProject.cpp"
	${SOURCES}
)

target_link_libraries(SampleProject PRIVATE
	raylib
	glfw
)
