cmake_minimum_required(VERSION 3.8)

project(SampleProject)

find_package(unofficial-nuklear CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(SampleProject "SampleProject.c")

target_link_libraries(SampleProject PRIVATE
	nuklear
	GLEW::GLEW
	glfw
)

target_include_directories(SampleProject PRIVATE
	${Stb_INCLUDE_DIR}
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/font DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
