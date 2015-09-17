cmake_minimum_required(VERSION 2.8.8)

project(GMusicApi)

set(EXT_PROJECTS_DIR ${CMAKE_SOURCE_DIR}/external)

# Includes Catch in the project:
add_subdirectory(${EXT_PROJECTS_DIR}/catch)

set(Boost_USE_DEBUG_PYTHON ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS python)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_DEBUG_PYTHON -DBOOST_PYTHON_STATIC_LIB)

add_subdirectory(gmusicapi)
add_subdirectory(Tester)