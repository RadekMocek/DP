cmake_minimum_required(VERSION 3.8)

project(SampleProject)

find_package(imgui CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)

add_executable(SampleProject SampleProject.cpp)

target_link_libraries(SampleProject PRIVATE
	imgui::imgui
	GLEW::GLEW
)
