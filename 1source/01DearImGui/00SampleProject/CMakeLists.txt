cmake_minimum_required(VERSION 3.12)

project(ImguiApp)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_PARALLEL ON CACHE BOOL "" FORCE)

find_package(imgui CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Freetype REQUIRED)

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
    glfw
	Freetype::Freetype
)

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/App/Resources 
#	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/
#)
