cmake_minimum_required(VERSION 3.10)

project(NuklearApp)

find_package(unofficial-nuklear CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(NuklearApp "NuklearApp.c")

target_link_libraries(NuklearApp PRIVATE
	nuklear
	GLEW::GLEW
	glfw
)

target_include_directories(NuklearApp PRIVATE
	${Stb_INCLUDE_DIR}
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/font DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
