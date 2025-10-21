cmake_minimum_required(VERSION 3.10)

project(ImguiApp)

find_package(imgui CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/App/*.cpp"    
)

add_executable(ImguiApp
	"Run.cpp"
	${SOURCES}
)

target_link_libraries(ImguiApp PRIVATE
	imgui::imgui
	GLEW::GLEW
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/App/Resources 
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/
)
