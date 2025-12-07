cmake_minimum_required(VERSION 3.24)

project(QtProj)

# ===================== Include Qt ===================== #

# What is QTDIR ?
# Windows:
# - QTDIR is a system environment variable pointing to `<path_to_qt_installation>\Qt\6.10.0\msvc2022_64`
# - Two values must be added to system environment variable PATH: `%QTDIR%\bin` & `%QTDIR%\lib`
# Linux:
# - export QTDIR=<path_to_qt_installation>/6.10.0/gcc_64/

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# =============== Include Project Files ================ #

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
        "${INCLUDE_DIR}/*.h"
        "${INCLUDE_DIR}/*.hpp"
        "${SOURCE_DIR}/*.cpp"
)

add_executable(QtProj ${SOURCES})

target_include_directories(QtProj PRIVATE ${INCLUDE_DIR})
target_include_directories(QtProj PRIVATE ${SOURCE_DIR})

# =================== Link libraries =================== #

target_link_libraries(QtProj Qt6::Widgets)

# =======
if (MSVC)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
    #set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") # No console
endif ()
