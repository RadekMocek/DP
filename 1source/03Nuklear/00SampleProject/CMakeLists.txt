cmake_minimum_required(VERSION 3.8)

project(SampleProject)

find_package(unofficial-nuklear CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(SampleProject "SampleProject.c")

target_link_libraries(SampleProject PRIVATE
	nuklear
	GLEW::GLEW
	glfw
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/font DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
